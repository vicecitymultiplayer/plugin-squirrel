#include "main.h"
#include "CallbackHandler.h"
#include "ConsoleUtils.h"
#include "Exports.h"
#include "Functions.h"

#include "CCore.h"
#include "CObject.h"
#include "CPickup.h"
#include "CPlayer.h"
#include "CVehicle.h"

#include <string>

SquirrelExports *	pExp;
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
	char * szBuffer;

	va_start(arglist, s);
	{
		int nReqSize = vsnprintf(NULL, 0, s, arglist) + 1;
		szBuffer = new char[nReqSize];
		vsnprintf(szBuffer, nReqSize, s, arglist);
	}
	va_end(arglist);

	OutputScriptInfo(szBuffer);
	delete[] szBuffer;
} 

// Squirrel's error function
void errorfunc(HSQUIRRELVM v, const SQChar *s, ...) 
{
	va_list arglist; 
	char * szBuffer;

	va_start(arglist, s);
	{
		int nReqSize = vsnprintf(NULL, 0, s, arglist) + 1;
		szBuffer = new char[nReqSize];
		vsnprintf(szBuffer, nReqSize, s, arglist);
	}
	va_end(arglist);

	OutputError(szBuffer);
	delete[] szBuffer;
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
	pExp->GetSquirrelVM  = pfGetSquirrelVM;
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
