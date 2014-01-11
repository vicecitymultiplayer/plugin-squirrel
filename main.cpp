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
HSQAPI				sq;

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

extern "C" EXPORT unsigned int VcmpPluginInit( PluginFuncs* givenPluginFuncs, PluginCallbacks* givenPluginCalls, PluginInfo* givenPluginInfo )
{
	// Hook into the server
	functions   = givenPluginFuncs;
	callbacks   = givenPluginCalls;
	information = givenPluginInfo;

	// Set our plugin information
	information->uPluginVer = 0x110;
	strcpy( information->szName, "SQHost2" );

	// Define our exports
	sq = nullptr;
	InitSQAPI();

	pExp                 = new SquirrelExports;
	pExp->GetSquirrelAPI = pfGetSquirrelAPI;
	pExp->uStructSize    = sizeof( SquirrelExports );

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
