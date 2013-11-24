#include "CCore.h"
#include "Functions.h"
#include "ConsoleUtils.h"
#include <cassert>

// Static members
unsigned short   CCore::refCount;
CCore          * CCore::pCoreInstance;
extern CCore   * pCore;

// We have to make the VM a global variable, else the server will crash
// due to access violations in Sqrat when the VM pointer becomes NULL for
// no known reason.
HSQUIRRELVM v;

CCore::CCore()
{
	v           = nullptr;
	script      = nullptr;
	pLogFile    = nullptr;

	// Create the entity arrays
	this->playerMap = new CPlayer *[MAX_PLAYERS];
	assert(this->playerMap != nullptr);

	this->pickupMap = new CPickup *[MAX_PICKUPS];
	assert(this->pickupMap != nullptr);

	this->objectMap = new CObject *[MAX_OBJECTS];
	assert(this->objectMap != nullptr);

	this->vehicleMap = new CVehicle *[MAX_VEHICLES];
	assert(this->vehicleMap != nullptr);

	// Construct all timer arrays
	unsigned int i;
	for( i = 0; i < this->maxTimers; i++ )
		this->pTimerArray[i] = nullptr;

	// Clean our entity maps of any garbage and filth
	for ( i = 0; i < MAX_PLAYERS; i++ )
		this->playerMap[i] = nullptr;

	for( i = 0; i < MAX_VEHICLES; i++ )
		this->vehicleMap[i] = nullptr;

	for( i = 0; i < MAX_PICKUPS; i++ )
		this->pickupMap[i] = nullptr;

	for( i = 0; i < MAX_OBJECTS; i++ )
		this->objectMap[i] = nullptr;
	
	canReload = false;
	pLogFile = fopen("server_log.txt", "a");
	this->LoadVM();
}

CCore::~CCore()
{
	if( script != nullptr )
	{
		delete script;
		script = nullptr;
	}

	// Release the VM if we can
	if( v != nullptr )
	{
		sq_close( v );
		v = nullptr;
	}

	// Throughout this entire ordeal, we don't actually kick players
	// or remove vehicles, objects, or pickups. Why not?
	//
	// The server is dying. We'd like to let it manage what to do with
	// entities, rather than manage it ourselves.
	unsigned int i;
	for (i = 0; i < MAX_PLAYERS; i++)
	{
		if (this->playerMap[i] != nullptr)
			delete this->playerMap[i];
	}

	for (i = 0; i < MAX_OBJECTS; i++)
	{
		if (this->objectMap[i] != nullptr)
			delete this->objectMap[i];
	}

	for (i = 0; i < MAX_PICKUPS; i++)
	{
		if (this->pickupMap[i] != nullptr)
			delete this->pickupMap[i];
	}

	for (i = 0; i < MAX_VEHICLES; i++)
	{
		if (this->vehicleMap[i] != nullptr)
			delete this->vehicleMap[i];
	}

	delete[] this->playerMap;
	delete[] this->objectMap;
	delete[] this->pickupMap;
	delete[] this->vehicleMap;
}

void CCore::LoadVM()
{
	// Initialize the virtual machine
	v = sq_open( 1024 );
	sq_setprintfunc( v, printfunc, errorfunc );

	DefaultVM::Set( v );

	// Force Sqrat to enable error handling
	Sqrat::ErrorHandling::Enable(true);
	sq_pushroottable( v );

	// Register our entities so they're accessible by scripts
	this->RegisterEntities();
}

// Look for entities such as vehicles and objects that were created by other plugins
void CCore::ScanForEntities()
{
	// Scan for vehicles
	unsigned int i;
	for( i = 0; i < MAX_VEHICLES; i++ )
	{
		if( functions->GetVehicleModel( i ) > 0 )
		{
			printf("vehicle oops at %d = %d", i, functions->GetVehicleModel(i));
			this->vehicleMap[i] = new CVehicle;
			this->vehicleMap[i]->Init( i, false );
		}
	}

	// Scan for pickups
	for( i = 0; i < MAX_PICKUPS; i++ )
	{
		if( functions->PickupGetModel( i ) > 0 )
		{
			printf("pickup oops at %d = %d", i, functions->PickupGetModel(i));
			this->pickupMap[i] = new CPickup;
			this->pickupMap[i]->Init( i, false );
		}
	}

	// Scan for objects
	for( i = 0; i < MAX_OBJECTS; i++ )
	{
		if( functions->GetObjectModel( i ) > 0 )
		{
			printf("object oops at %d = %d", i, functions->GetObjectModel(i));
			this->objectMap[i] = new CObject;
			this->objectMap[i]->Init( i, false );
		}
	}

	// Scan for players
	for( i = 0; i < MAX_PLAYERS; i++ )
	{
		if( functions->IsPlayerConnected( i ) )
		{
			printf("player oops at %d = %d", i, functions->IsPlayerConnected(i));
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
		if( pTimerArray[i] == nullptr )
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
		if( pTimerArray[i] != nullptr && !pTimerArray[i]->isPaused )
		{
			if( pTimerArray[i]->Pulse( elapsedTime * 1000.0f ) == true )
			{
				delete pTimerArray[i];
				pTimerArray[i] = nullptr;
			}
		}
	}
}

void CCore::DropAllTimers()
{
	for( int i = 0; i < this->maxTimers; i++ )
	{
		if( pTimerArray[i] != nullptr )
			pTimerArray[i]->committingSeppuku = true;
	}
}

void CCore::CleanWorld()
{
	unsigned int i;
	for( i = 0; i < MAX_VEHICLES; i++ )
	{
		if( vehicleMap[i] != nullptr && vehicleMap[i]->isOurs )
		{
			vehicleMap[i]->Delete();
			vehicleMap[i] = nullptr;
		}
	}

	for( i = 0; i < MAX_PICKUPS; i++ )
	{
		if( pickupMap[i] != nullptr && vehicleMap[i]->isOurs )
		{
			pickupMap[i]->Delete();
			vehicleMap[i] = nullptr;
		}
	}

	for( i = 0; i < MAX_OBJECTS; i++ )
	{
		if( objectMap[i] != nullptr && vehicleMap[i]->isOurs )
		{
			objectMap[i]->Delete();
			objectMap[i] = nullptr;
		}
	}
}

// Register *everything*
void CCore::RegisterEntities()
{
	// Register all necessary core libraries
	if (SQ_FAILED(sqstd_register_bloblib(v)))
		OutputWarning("sqstd_bloblib failed to load.");

	if (SQ_FAILED(sqstd_register_iolib(v)))
		OutputWarning("sqstd_iolib failed to load.");

	if (SQ_FAILED(sqstd_register_mathlib(v)))
		OutputWarning("sqstd_mathlib failed to load.");

	if (SQ_FAILED(sqstd_register_stringlib(v)))
		OutputWarning("sqstd_stringlib failed to load.");

	if (SQ_FAILED(sqstd_register_systemlib(v)))
		OutputWarning("sqstd_systemlib failed to load.");

	RegisterStructures();
	RegisterGlobals();
	RegisterConstants();

	// Register the classes
	RegisterObject();
	RegisterPickup();
	RegisterPlayer();
	RegisterTimer();
	RegisterVehicle();

	// Set the default internal error handlers up
	sqstd_seterrorhandlers( v );
}

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
	if( file == nullptr )
		OutputError( "SqVCMP could not read server.cfg" );
	else
	{
		// Is this clean?
		int lineSize = 128;
		int elapsedLineSize = 0;
		char * lineBuffer = (char *)malloc( sizeof(char) * lineSize );

		// Did we do it?
		if( lineBuffer == nullptr )
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
	char * gamemodeSearch = nullptr;
	if( ( gamemodeSearch = strstr( lineBuffer, "sqgamemode " ) ) == nullptr )
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
		catch( Sqrat::Error e )
		{
			char buf[145];
			sprintf( buf, "Could not load script '%s'", gamemodeSearch );

			OutputWarning( buf );
			OutputWarning( e.Message(Sqrat::DefaultVM::Get()).c_str() );

			return false;
		}

		try
		{
			Function callback = RootTable(v).GetFunction(_SC("onScriptLoad"));
			if (!callback.IsNull())
				callback();

			callback.Release();
		}
		catch (Sqrat::Error e)
		{
			OutputWarning("onScriptLoad failed to execute -- check the console for more details.");
		}

		return true;
	}
}

void CCore::printf( char* pszFormat, ... )
{
	char szBuffer[512];

	va_list va;
	va_start(va, pszFormat);
	vsnprintf(szBuffer, 512, pszFormat, va);
	va_end(va);

	fputs(szBuffer, stdout);
	if( this->pLogFile != nullptr )
		fprintf(this->pLogFile, "%s", szBuffer);
	else
		puts("Cannot write to logfile");
}

// Release a core instance
void CCore::Release()
{
	// Decrease the number of references
	if( refCount > 0 )
		refCount--;
	
	// See if we should destroy our instance
	if( refCount <= 0 && pCoreInstance != nullptr )
	{
		// Delete the core instance
		delete pCoreInstance;

		pCoreInstance = nullptr;
		pCore = nullptr;
	}
}

FILE * CCore::GetLogInstance()
{
	if (this->pLogFile == nullptr)
		return nullptr;

	return this->pLogFile;
}