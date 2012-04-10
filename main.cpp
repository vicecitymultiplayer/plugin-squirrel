// Main include
#include "main.h"

// Callback handler
#include "CallbackHandler.h"

// Function registration
#include "Functions.h"

// Classes
#include "CObject.h"
#include "CPickup.h"
#include "CPlayer.h"
#include "CVehicle.h"

// Squirrel's print function
void printfunc(HSQUIRRELVM v, const SQChar *s, ...) 
{ 
	va_list arglist; 
	va_start(arglist, s); 
	scvprintf(s, arglist);
	va_end(arglist); 

	printf( "\n" );
} 

// Squirrel's error function
void errorfunc(HSQUIRRELVM v, const SQChar *s, ...) 
{
	va_list arglist; 
	va_start(arglist, s); 
	scvprintf(s, arglist);
	va_end(arglist);
}

// Definitions
PluginFuncs*				functions;
PluginInfo*					information;
PluginCallbacks*			callbacks;
HSQUIRRELVM					v;

void RegisterStructures()
{
	ImprovedClass<Vector> a(v);
	ImprovedClass<Quaternion> b(v);
	ImprovedClass<RGBa> c(v);
	ImprovedClass<cRGB> d(v);
	ImprovedClass<Bounds> e(v);
	ImprovedClass<WastedSettings> f(v);
	ImprovedClass<ARGB> g(v);

	a.Ctor<float, float, float>();
	b.Ctor<float, float, float, float>();
	e.Ctor<float, float, float, float>();

	// Because an unsigned char is crashy
	c.Ctor<int, int, int, int>();
	d.Ctor<int, int, int>();
	f.Ctor<int, int, float, float, cRGB, int, int>();
	g.Ctor<int, int, int, int>();

	a
		.Var( _SC("x"), &Vector::x )
		.Var( _SC("y"), &Vector::y )
		.Var( _SC("z"), &Vector::z );

	b
		.Var( _SC("w"), &Quaternion::w )
		.Var( _SC("x"), &Quaternion::x )
		.Var( _SC("y"), &Quaternion::y )
		.Var( _SC("z"), &Quaternion::z );

	c
		.Var( _SC("r"), &RGBa::r )
		.Var( _SC("g"), &RGBa::g )
		.Var( _SC("b"), &RGBa::b )
		.Var( _SC("a"), &RGBa::a );

	d
		.Var( _SC("r"), &cRGB::r )
		.Var( _SC("g"), &cRGB::g )
		.Var( _SC("b"), &cRGB::b );

	e
		.Var( _SC("MaxX"), &Bounds::maxX )
		.Var( _SC("MinX"), &Bounds::minX )
		.Var( _SC("MaxY"), &Bounds::maxY )
		.Var( _SC("MinY"), &Bounds::minY );

	f
		.Var( _SC("DeathTime"), &WastedSettings::deathTime )
		.Var( _SC("FadeTime"), &WastedSettings::fadeTime )
		.Var( _SC("FadeInSpeed"), &WastedSettings::fadeInSpeed )
		.Var( _SC("FadeOutSpeed"), &WastedSettings::fadeOutSpeed )
		.Var( _SC("FadeColour"), &WastedSettings::fadeColour )
		.Var( _SC("CorpseFadeDelay"), &WastedSettings::corpseFadeDelay )
		.Var( _SC("CorpseFadeTime"), &WastedSettings::corpseFadeTime );
	
	g
		.Var( _SC("a"), &ARGB::a )
		.Var( _SC("r"), &ARGB::r )
		.Var( _SC("g"), &ARGB::g )
		.Var( _SC("b"), &ARGB::b );

	RootTable(v).Bind( _SC("Vector"), a );
	RootTable(v).Bind( _SC("Quaternion"), b );
	RootTable(v).Bind( _SC("RGBA"), c );
	RootTable(v).Bind( _SC("RGB"), d );
	RootTable(v).Bind( _SC("Bounds"), e );
	RootTable(v).Bind( _SC("WastedSettings"), f );
	RootTable(v).Bind( _SC("ARGB"), g );
}

extern "C" EXPORT unsigned int VcmpPluginInit( PluginFuncs* givenPluginFuncs, PluginCallbacks* givenPluginCalls, PluginInfo* givenPluginInfo )
{
	// Open a Squirrel virtual machine
	v = sq_open(1024);
	
	// Set the internal error handlers up
	sqstd_seterrorhandlers(v);

	// Set up our print function
	sq_setprintfunc( v, printfunc, errorfunc );

	// Set our default VM
	DefaultVM::Set(v);

	// Hook into the server
	functions   = givenPluginFuncs;
	callbacks   = givenPluginCalls;
	information = givenPluginInfo;

	// Server events
	callbacks->OnInitServer         = OnInitServer;
	callbacks->OnShutdownServer	    = OnShutdownServer;
	callbacks->OnFrame              = OnFrame;
	callbacks->OnLoginAttempt       = OnLoginAttempt;

	callbacks->OnPlayerConnect      = OnPlayerConnect;
	callbacks->OnPlayerDisconnect   = OnPlayerDisconnect;

	callbacks->OnPlayerRequestClass = OnPlayerRequestClass;
	callbacks->OnPlayerRequestSpawn = OnPlayerRequestSpawn;
	callbacks->OnPlayerSpawn        = OnPlayerSpawn;

	callbacks->OnPlayerDeath        = OnPlayerDeath;
	callbacks->OnPlayerUpdate       = OnPlayerUpdate;

	callbacks->OnPlayerBeginTyping  = OnPlayerBeginTyping;
	callbacks->OnPlayerEndTyping    = OnPlayerEndTyping;

	callbacks->OnPlayerRequestEnter = OnPlayerRequestEnter;
	callbacks->OnPlayerEnterVehicle = OnPlayerEnterVehicle;
	callbacks->OnPlayerExitVehicle  = OnPlayerExitVehicle;

	callbacks->OnPickupClaimPicked  = OnPickupClaimPicked;
	callbacks->OnPickupPickedUp     = OnPickupPickedUp;
	callbacks->OnPickupRespawn      = OnPickupRespawn;

	callbacks->OnVehicleUpdate      = OnVehicleUpdate;
	callbacks->OnVehicleExplode     = OnVehicleExplode;
	callbacks->OnVehicleRespawn     = OnVehicleRespawn;

	callbacks->OnPublicMessage      = OnPublicMessage;
	callbacks->OnCommandMessage     = OnCommandMessage;
	callbacks->OnPrivateMessage     = OnPrivateMessage;
	callbacks->OnInternalCommand    = OnInternalCommand;

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

	// Get the gamemode name
	char gamemode[64] = "SqVCMP_Entry.nut";

	// Load the gamemode if and only if we have a name
	if( strlen(gamemode) > 0 )
	{
		// Print the initialization message.
		functions->printf( ">> Loaded Squirrel frontend by Stormeus." );

		// Convert multi-byte to wide char
		const size_t newSize  = 256;
		wchar_t wcMode[newSize];
		
		mbstowcs( wcMode, gamemode, newSize );
		
		// Hit it!
		try
		{
			Script script;
			script.CompileFile( wcMode );
			script.Run();
		}
		catch( Exception )
		{
			functions->printf( ">> ERROR: The given gamemode does not exist." );
		}
	}
	else
		functions->printf( ">> ERROR: No gamemode was specified. Squirrel frontend dropping." );

	// Done!
	return 1;
}