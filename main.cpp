// Main include
#include "main.h"

// Callback handler
#include "CallbackHandler.h"

// Function registration
#include "Functions.h"

// Classes
#include "CCore.h"
#include "CObject.h"
#include "CPickup.h"
#include "CPlayer.h"
#include "CVehicle.h"

// Console stuff
#include "ConsoleUtils.h"

// Module exports
#include "Exports.h"
SquirrelExports * pExp;

// Definitions
PluginFuncs		*	functions;
PluginInfo		* 	information;
PluginCallbacks *	callbacks;
CCore           *   pCore;

// See CCore.cpp for original definition
extern HSQUIRRELVM  v;

// Squirrel's print function
void printfunc(HSQUIRRELVM v, const SQChar *s, ...) 
{ 
	va_list arglist; 
	va_start(arglist, s); 
	char * outbuf = new char[768];
	vsprintf(outbuf, s, arglist);
	va_end(arglist); 

	OutputScriptInfo( outbuf );
	delete outbuf;
} 

// Squirrel's error function
void errorfunc(HSQUIRRELVM v, const SQChar *s, ...) 
{
	va_list arglist; 
	va_start(arglist, s); 
	
	vfprintf(stdout, s, arglist);
	if( pCore->GetLogInstance() != nullptr )
		vfprintf(pCore->GetLogInstance(), s, arglist);

	va_end(arglist);
}

// Convert a Vector to string
const Sqrat::string VectorToString(const Vector* v)
{
	std::basic_stringstream<SQChar> out;
	out << _SC("(") << v->x << _SC(", ") << v->y << _SC(", ") << v->z << _SC(")");

	return out.str();
}

// Convert a Quaternion to string
const Sqrat::string QuaternionToString(const Quaternion* q)
{
	std::basic_stringstream<SQChar> out;
	out << _SC("(") << q->w << _SC(", ") << q->x << _SC(", ") << q->y << _SC(", ") << q->z << _SC(")");

	return out.str();
}

void RegisterStructures()
{
	Class<Vector> a(v);
	Class<Quaternion> b(v);
	Class<RGBa> c(v);
	Class<cRGB> d(v);
	Class<Bounds> e(v);
	Class<WastedSettings> f(v);
	Class<ARGB> g(v);

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
		.Var( _SC("z"), &Vector::z )
		
		.Func(_SC("Distance"), &Vector::Distance)
		.Func(_SC("Dot"), &Vector::Dot)
		.Func(_SC("Length"), &Vector::Length)
		.Func(_SC("Normalize"), &Vector::Normalize)
		
		.Func(_SC("_add"), &Vector::operator +)
		.Func(_SC("_mul"), &Vector::operator *)
		.Func(_SC("_div"), &Vector::operator /)
		.Func<Vector (Vector::*)(void) const>(_SC("unm"), &Vector::operator -)
		.Func<Vector (Vector::*)(const Vector&) const>(_SC("_sub"), &Vector::operator -)
		
		.GlobalFunc(_SC("_tostring"), &VectorToString);

	b
		.Var( _SC("w"), &Quaternion::w )
		.Var( _SC("x"), &Quaternion::x )
		.Var( _SC("y"), &Quaternion::y )
		.Var( _SC("z"), &Quaternion::z )

		.Func(_SC("_add"), &Quaternion::operator +)
		.Func(_SC("_mul"), &Quaternion::operator *)
		.Func(_SC("_div"), &Quaternion::operator /)
		.Func<Quaternion(Quaternion::*)(void) const>(_SC("unm"), &Quaternion::operator -)
		.Func<Quaternion(Quaternion::*)(const Quaternion&) const>(_SC("_sub"), &Quaternion::operator -)

		.GlobalFunc(_SC("_tostring"), &QuaternionToString);

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
	// Hook into the server
	functions   = givenPluginFuncs;
	callbacks   = givenPluginCalls;
	information = givenPluginInfo;

	// Set our plugin information
	information->uPluginVer = 0x100;
	strcpy( information->szName, "SQHost1" );

	// Define our exports
	pExp                = new SquirrelExports;
	pExp->GetSquirrelVM = pfGetSquirrelVM;
	pExp->uStructSize   = sizeof( SquirrelExports );

	// Export them
	functions->ExportFunctions( information->nPluginId, (void **)&pExp, sizeof( SquirrelExports ) );

	// Get a core instance
	pCore = CCore::GetInstance();

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
	callbacks->OnPlayerAwayChange   = OnPlayerAwayChange;
	callbacks->OnPlayerSpectate     = OnPlayerSpectate;
	callbacks->OnPlayerCrashReport  = OnPlayerCrashDump;

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
	
	callbacks->OnObjectShot         = OnObjectShot;
	callbacks->OnObjectBump         = OnObjectBump;

	callbacks->OnEntityPoolChange	= OnEntityPoolChange;
	callbacks->OnKeyBindDown        = OnKeyBindDown;
	callbacks->OnKeyBindUp          = OnKeyBindUp;

	// Done!
	return 1;
}
