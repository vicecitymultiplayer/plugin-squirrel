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

	// Clean up all the maps
	this->CleanGarbageMaps();
	
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

	// Set the default internal error handlers up
	sqstd_seterrorhandlers( v );

	// Set up our print and error functions
	sq_setprintfunc( v, printfunc, errorfunc );

	// Set our default VM in Sqrat
	DefaultVM::Set( v );

	// Force Sqrat to enable error handling
	Sqrat::ErrorHandling::Enable(true);

	// Register our entities so they're accessible by scripts
	this->RegisterEntities();
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

void CCore::CleanGarbageMaps()
{
	unsigned int i;
	for( i = 0; i < MAX_VEHICLES; i++ )
		vehicleMap[i] = NULL;

	for( i = 0; i < MAX_PICKUPS; i++ )
		pickupMap[i] = NULL;

	for( i = 0; i < MAX_OBJECTS; i++ )
		objectMap[i] = NULL;
}

void CCore::CleanWorld()
{
	unsigned int i;
	for( i = 0; i < MAX_VEHICLES; i++ )
	{
		if( vehicleMap[i] != NULL )
			vehicleMap[i]->Delete();
	}

	for( i = 0; i < MAX_PICKUPS; i++ )
	{
		if( pickupMap[i] != NULL )
			pickupMap[i]->Delete();
	}

	for( i = 0; i < MAX_OBJECTS; i++ )
	{
		if( objectMap[i] != NULL )
			objectMap[i]->Delete();
	}

	this->CleanGarbageMaps();
}

// Register *everything*
void CCore::RegisterEntities()
{
	// Register all necessary core libraries
	sqstd_register_iolib( v );
	sqstd_register_bloblib( v );
	sqstd_register_mathlib( v );
	sqstd_register_stringlib( v );

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
}

// Load the script
void CCore::LoadScript()
{
	// Create a new script instance
	script = new Script();

	// Get the gamemode name
	char gamemode[64] = "SqVCMP_Entry.nut";

	// Load the gamemode if and only if we have a name
	if( strlen( gamemode ) > 0 )
	{
		// Hit it!
		try
		{
			script->CompileFile( gamemode );
			script->Run();
		}
		catch( Sqrat::Exception e )
		{
			OutputError( "The given gamemode could not be loaded." );
			OutputError( e.Message().c_str() );
		}

		// No reloading at this point.
		this->canReload = false;

		Function callback = RootTable( v ).GetFunction( _SC( "onScriptLoad" ) );
		if( !callback.IsNull() )
			callback();

		// You are now free to move about the cabin.
		this->canReload = true;
	}
	else
		OutputError( "No Squirrel gamemode was specified." );
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