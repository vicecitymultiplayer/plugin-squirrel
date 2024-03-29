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
	char szInitBuffer[512];

	va_start(arglist, s);
	{
		int nChars = vsnprintf(szInitBuffer, sizeof(szInitBuffer), s, arglist);
		if (nChars > sizeof(szInitBuffer) - 1)
		{
			char * szBuffer = (char*)calloc(nChars + 1, sizeof(char));
			if (szBuffer == NULL)
			{
				sprintf(szInitBuffer, "Error could not be printed: failed to malloc the buffer at %d nChars.", nChars + 1);
				pCore->rawprint(szInitBuffer);
			}
			else
			{
				vsnprintf(szBuffer, nChars, s, arglist);
				OutputScriptInfo(szBuffer);

				free(szBuffer);
			}
		}
		else
			OutputScriptInfo(szInitBuffer);
	}
	va_end(arglist);
} 

// Squirrel's error function
void errorfunc(HSQUIRRELVM v, const SQChar *s, ...) 
{
	va_list arglist;
	char szInitBuffer[512];

	va_start(arglist, s);
	{
		int nChars = vsnprintf(szInitBuffer, sizeof(szInitBuffer), s, arglist);
		if (nChars > sizeof(szInitBuffer) - 1)
		{
			char * szBuffer = (char*)calloc(nChars + 1, sizeof(char));
			if (szBuffer == NULL)
			{
				sprintf(szInitBuffer, "Error could not be printed: failed to malloc the buffer at %d nChars.", nChars + 1);
				pCore->rawprint(szInitBuffer);
			}
			else
			{
				vsnprintf(szBuffer, nChars, s, arglist);
				pCore->rawprint(szBuffer);

				free(szBuffer);
			}
		}
		else
			pCore->rawprint(szInitBuffer);
	}
	va_end(arglist);
}

extern "C" EXPORT unsigned int VcmpPluginInit( PluginFuncs* givenPluginFuncs, PluginCallbacks* givenPluginCalls, PluginInfo* givenPluginInfo )
{
	// Hook into the server
	functions   = givenPluginFuncs;
	callbacks   = givenPluginCalls;
	information = givenPluginInfo;

	// Set our plugin information
	information->pluginVersion = 0x110;
	information->apiMajorVersion = PLUGIN_API_MAJOR;
	information->apiMinorVersion = PLUGIN_API_MINOR;
	strcpy( information->name, "SQHost2" );

	// Define our exports
	sq = NULL;
	InitSQAPI();

	pExp                 = new SquirrelExports;
	pExp->GetSquirrelAPI = pfGetSquirrelAPI;
	pExp->GetSquirrelVM  = pfGetSquirrelVM;
	pExp->uStructSize    = sizeof( SquirrelExports );

	// Export them
	functions->ExportFunctions( information->pluginId, (const void **)&pExp, sizeof( SquirrelExports ) );

	// Get a core instance
	pCore = CCore::GetInstance();

	// Server events
	callbacks->OnServerInitialise	= OnInitServer;
	callbacks->OnServerShutdown	    = OnShutdownServer;
	callbacks->OnServerFrame		= OnFrame;
	callbacks->OnIncomingConnection	= OnLoginAttempt;
	callbacks->OnClientScriptData   = OnClientScriptData;

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

	callbacks->OnPlayerRequestEnterVehicle = OnPlayerRequestEnter;
	callbacks->OnPlayerEnterVehicle = OnPlayerEnterVehicle;
	callbacks->OnPlayerExitVehicle  = OnPlayerExitVehicle;

	callbacks->OnPickupPickAttempt  = OnPickupClaimPicked;
	callbacks->OnPickupPicked	    = OnPickupPickedUp;
	callbacks->OnPickupRespawn      = OnPickupRespawn;

	callbacks->OnVehicleUpdate      = OnVehicleUpdate;
	callbacks->OnVehicleExplode     = OnVehicleExplode;
	callbacks->OnVehicleRespawn     = OnVehicleRespawn;

	callbacks->OnPlayerMessage      = OnPublicMessage;
	callbacks->OnPlayerCommand      = OnCommandMessage;
	callbacks->OnPlayerPrivateMessage = OnPrivateMessage;
	callbacks->OnPluginCommand      = OnInternalCommand;

	callbacks->OnObjectShot         = OnObjectShot;
	callbacks->OnObjectTouched         = OnObjectBump;

	callbacks->OnEntityPoolChange	= OnEntityPoolChange;
	callbacks->OnPlayerKeyBindDown  = OnKeyBindDown;
	callbacks->OnPlayerKeyBindUp    = OnKeyBindUp;

	callbacks->OnPlayerNameChange   = OnPlayerNameChange;
	callbacks->OnPlayerStateChange  = OnPlayerStateChange;
	callbacks->OnPlayerActionChange = OnPlayerActionChange;
	callbacks->OnPlayerOnFireChange = OnPlayerOnFireChange;
	callbacks->OnPlayerCrouchChange = OnPlayerCrouchChange;
	callbacks->OnPlayerGameKeysChange = OnPlayerGameKeysChange;

	callbacks->OnCheckpointEntered = OnCheckpointEntered;
	callbacks->OnCheckpointExited = OnCheckpointExited;

	callbacks->OnPlayerModuleList = OnPlayerModuleList;

	// Done!
	return 1;
}
