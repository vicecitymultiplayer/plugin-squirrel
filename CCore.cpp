#include "CCore.h"
#include "CObject.h"
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
	v      = NULL;
	script = NULL;

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
	// See if the VM is open
	if( v != NULL )
	{
		// See if the script is already open
		if( script != NULL )
		{
			// Unload the script
			Function callback = RootTable().GetFunction( _SC( "onScriptUnload" ) );
			if( !callback.IsNull() )
				callback();

			// Destroy the instance
			delete script;
		
			// Remove dangling pointers
			script = NULL;
		}

		// Close the virtual machine
		sq_close( v );
		
		// Get rid of dangling pointers
		v = NULL;
	}

	// Initialize the virtual machine
	v = sq_open( 1024 );

	// Set the default internal error handlers up
	sqstd_seterrorhandlers( v );

	// Set up our print and error functions
	sq_setprintfunc( v, printfunc, errorfunc );

	// Set our default VM in Sqrat
	DefaultVM::Set( v );

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

			Function callback = RootTable( v ).GetFunction( _SC( "onScriptLoad" ) );
			if( !callback.IsNull() )
				callback();

			// Allow script reloading again
			canReload = true;
		}
		catch( Sqrat::Exception e )
		{
			OutputError( "The given gamemode could not be loaded." );
			OutputError( e.Message().c_str() );
		}
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
	if( refCount == 0 && pCoreInstance != NULL )
	{
		// Delete the core instance
		delete pCoreInstance;
	}

	// Done.
}