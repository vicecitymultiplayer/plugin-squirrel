#include "CCore.h"
#include "Functions.h"
#include "ConsoleUtils.h"

// Static members
unsigned short   CCore::refCount;
CCore          * CCore::pCoreInstance;

// We have to make the VM a global variable, else the server will crash
// due to access violations in Sqrat when the VM pointer becomes NULL for
// no known reason.
HSQUIRRELVM v;

// Constructor to set everything up in
CCore::CCore()
{
	// Reset this stuff
	v           = NULL;
	script      = NULL;

	// Construct all timer arrays
	for( int i = 0; i < this->maxTimers; i++ )
		pTimerArray[i] = NULL;

	// Clean our entity maps of any garbage and filth
	for( int i = 0; i < MAX_PLAYERS; i++ )
		playerMap[i] = NULL;

	for( int i = 0; i < MAX_VEHICLES; i++ )
		vehicleMap[i] = NULL;

	for( int i = 0; i < MAX_PICKUPS; i++ )
		pickupMap[i] = NULL;

	for( int i = 0; i < MAX_OBJECTS; i++ )
		objectMap[i] = NULL;
	
	// Set up the canReload variable
	canReload = false;

	// Load the VM
	this->LoadVM();
}

// Destructor to clean up
CCore::~CCore()
{
	if( script != NULL )
	{
		// Destroy the script instance
		delete script;

		// Remove dangling pointers
		script = NULL;
	}

	// Release the VM if we can
	if( v != NULL )
	{
		// Close the Squirrel VM
		sq_close( v );

		// Remove dangling pointers
		v = NULL;
	}
}

// Load the VM
void CCore::LoadVM()
{
	// Initialize the virtual machine
	v = sq_open( 1024 );

	// Set up our print and error functions
	sq_setprintfunc( v, printfunc, errorfunc );

	// Set our default VM in Sqrat
	DefaultVM::Set( v );

	// Force Sqrat to enable error handling
	Sqrat::ErrorHandling::Enable(true);

	// Push a root table
	sq_pushroottable( v );

	// Register our entities so they're accessible by scripts
	this->RegisterEntities();
}

// Look for entities such as vehicles and objects that were created by other plugins
void CCore::ScanForEntities()
{
	// Scan for vehicles
	for( int i = 0; i < MAX_VEHICLES; i++ )
	{
		if( functions->GetVehicleModel( i ) > 0 )
		{
			this->vehicleMap[i] = new CVehicle;
			this->vehicleMap[i]->Init( i, false );
		}
	}

	// Scan for pickups
	for( int i = 0; i < MAX_PICKUPS; i++ )
	{
		if( functions->PickupGetModel( i ) > 0 )
		{
			this->pickupMap[i] = new CPickup;
			this->pickupMap[i]->Init( i, false );
		}
	}

	// Scan for objects
	for( int i = 0; i < MAX_OBJECTS; i++ )
	{
		if( functions->GetObjectModel( i ) > 0 )
		{
			this->objectMap[i] = new CObject;
			this->objectMap[i]->Init( i, false );
		}
	}

	// Scan for players
	for( int i = 0; i < MAX_PLAYERS; i++ )
	{
		if( functions->IsPlayerConnected( i ) )
		{
			this->playerMap[i] = new CPlayer;
			this->playerMap[i]->nPlayerId = i;
		}
	}
}

// Process any timers
void CCore::AddTimer(CTimer * pTimer)
{
	for( int i = 0; i < this->maxTimers; i++ )
	{
		if( pTimerArray[i] == NULL )
		{
			pTimerArray[i] = pTimer;
			return;
		}
	}
}

void CCore::ProcessTimers(float elapsedTime)
{
	for( int i = 0; i < this->maxTimers; i++ )
	{
		if( pTimerArray[i] != NULL && !pTimerArray[i]->isPaused )
		{
			if( pTimerArray[i]->Pulse( elapsedTime * 1000.0f ) == true )
			{
				delete pTimerArray[i];
				pTimerArray[i] = NULL;
			}
		}
	}
}

void CCore::DropAllTimers()
{
	for( int i = 0; i < this->maxTimers; i++ )
	{
		if( pTimerArray[i] != NULL )
			pTimerArray[i]->committingSeppuku = true;
	}
}

void CCore::CleanWorld()
{
	unsigned int i;
	for( i = 0; i < MAX_VEHICLES; i++ )
	{
		if( vehicleMap[i] != NULL && vehicleMap[i]->isOurs )
		{
			vehicleMap[i]->Delete();
			vehicleMap[i] = NULL;
		}
	}

	for( i = 0; i < MAX_PICKUPS; i++ )
	{
		if( pickupMap[i] != NULL && vehicleMap[i]->isOurs )
		{
			pickupMap[i]->Delete();
			vehicleMap[i] = NULL;
		}
	}

	for( i = 0; i < MAX_OBJECTS; i++ )
	{
		if( objectMap[i] != NULL && vehicleMap[i]->isOurs )
		{
			objectMap[i]->Delete();
			objectMap[i] = NULL;
		}
	}
}

// Register *everything*
void CCore::RegisterEntities()
{
	// Register our structures
	RegisterStructures();

	// Register our functions
	RegisterGlobals();

	// Register our constants
	RegisterConstants();

	// Register the classes
	RegisterObject();
	RegisterPickup();
	RegisterPlayer();
	RegisterTimer();
	RegisterVehicle();

	// Register all necessary core libraries
	if( SQ_FAILED( sqstd_register_iolib( v ) ) )
		OutputWarning( "sqstd_iolib failed to load." );

	if( SQ_FAILED( sqstd_register_bloblib( v ) ) )
		OutputWarning( "sqstd_bloblib failed to load." );

	if( SQ_FAILED( sqstd_register_mathlib( v ) ) )
		OutputWarning( "sqstd_mathlib failed to load." );
	
	if( SQ_FAILED( sqstd_register_stringlib( v ) ) )
		OutputWarning( "sqstd_stringlib failed to load." );

	// Set the default internal error handlers up
	sqstd_seterrorhandlers( v );
}

// Load the scripts
inline void ZeroBuffer( char * buffer, int size )
{
	for( int i = 0; i < size; i++ )
		buffer[i] = '\0';
}

void CCore::LoadScript()
{
	// Scan for entities that were already created
	this->ScanForEntities();

	// No reloading at this point
	this->canReload = false;
	bool scriptFound = false;
	FILE * file;

	file = fopen( "server.cfg", "r" );
	if( file == NULL )
		OutputError( "SqVCMP could not read server.cfg" );
	else
	{
		// Is this clean?
		int lineSize = 128;
		int elapsedLineSize = 0;
		char * lineBuffer = (char *)malloc( sizeof(char) * lineSize );

		// Did we do it?
		if( lineBuffer == NULL )
			OutputError( "SqVCMP could not allocate memory to read server.cfg" );
		else
		{
			ZeroBuffer(lineBuffer, lineSize);
			char ch = getc( file );

			while( ch != EOF )
			{
				if( ch == '\n' )
				{
					// End of the line. Parse it.
					if( this->ParseConfigLine( lineBuffer ) )
					{
						scriptFound = true;
						break;
					}

					ZeroBuffer(lineBuffer, lineSize);
					elapsedLineSize = 0;
				}
				else
				{
					lineBuffer[elapsedLineSize++] = ch;

					// If we've hit our limit on line size, stop reading the line.
					if( elapsedLineSize + 1 == lineSize )
					{
						// Parse it.
						if( this->ParseConfigLine( lineBuffer ) )
						{
							scriptFound = true;
							break;
						}

						// Go straight to the next one instead.
						while( ch != '\n' )
							ch = getc( file );

						ZeroBuffer(lineBuffer, lineSize);
						elapsedLineSize = 0;
					}
				}

				// Get the next character in the file.
				ch = getc( file );
			}
			
			if( !scriptFound && this->ParseConfigLine( lineBuffer ) )
				scriptFound = true;
		}

		// Clean up our shit
		free( lineBuffer );
	}
	
	// More cleaning
	fclose( file );

	// You are now free to move about the cabin.
	this->canReload = true;

	if( !scriptFound )
		OutputError( "No Squirrel gamemode was specified." );
}

bool CCore::ParseConfigLine( char * lineBuffer )
{
	char * gamemodeSearch = NULL;
	if( ( gamemodeSearch = strstr( lineBuffer, "sqgamemode " ) ) == NULL )
		return false;
	else if( strlen( gamemodeSearch ) < 1 )
		return false;
	else
	{
		// Ew.
		gamemodeSearch += sizeof("sqgamemode");
		this->script = new Script();

		try
		{
			this->script->CompileFile( gamemodeSearch );
			this->script->Run();
		}
		catch( Sqrat::Exception e )
		{
			char buf[145];
			sprintf( buf, "Could not load script '%s'", gamemodeSearch );

			OutputWarning( buf );
			OutputWarning( e.Message().c_str() );

			return false;
		}

		Function callback = RootTable( v ).GetFunction( _SC( "onScriptLoad" ) );
		if( !callback.IsNull() )
			callback();

		callback.Release();
		return true;
	}
}

// Release a core instance
void CCore::Release()
{
	// Decrease the number of references
	if( refCount > 0 )
		refCount--;
			
	// See if we should destroy our instance
	if( refCount <= 0 && pCoreInstance != NULL )
	{
		// Delete the core instance
		delete pCoreInstance;
	}

	// Done.
}
