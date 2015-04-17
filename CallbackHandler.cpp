#include "CallbackHandler.h"
#include <string>

// Console stuff
#include "ConsoleUtils.h"

// Script and VM core
#include "CCore.h"
#include "SQModule.h"

// Create arrays for several structures.
savedVehicleData lastVehInfo[MAX_VEHICLES];
savedPlayerData  lastPlrInfo[MAX_PLAYERS];
savedServerData  lastSrvInfo;

// Externalize the core instance and other critical variables
extern CCore * pCore;
extern PluginInfo       *   information;
extern PluginCallbacks  *   callbacks;

int OnInitServer()
{
	// Print the initialization message.
	printf("\n");
	OutputMessage("Loaded SqVCMP 0.4 frontend by Stormeus. (v1.0)");

	// Reload the VM
	pCore->LoadVM();

	// Load the script
	pCore->LoadScript();

	// Prohibit reloading at this time.
	pCore->ChangeReloadPermission(false);

	Function callback = RootTable(v).GetFunction(_SC("onServerStart"));
	try
	{
		if (!callback.IsNull())
			callback();
	}
	catch (Sqrat::Exception e)
	{
		OutputWarning("onServerStart failed to execute -- check the console for more details.");
	}

	callback.Release();

	// Reallow reloading.
	pCore->ChangeReloadPermission(true);

	return 1;
}

void OnShutdownServer()
{
	if (pCore != NULL)
	{
		Function callback;
		try
		{
			callback = RootTable().GetFunction(_SC("onServerStop"));
			if (!callback.IsNull())
				callback();
		}
		catch (Sqrat::Exception e)
		{
			OutputWarning("onServerStop failed to execute -- check the console for more details.");
		}

		callback.Release();
		callback = RootTable().GetFunction(_SC("onScriptUnload"));

		try
		{
			if (!callback.IsNull())
				callback();
		}
		catch (Sqrat::Exception e)
		{
			OutputWarning("onScriptUnload failed to execute -- check the console for more details.");
		}
		callback.Release();

		// Dereference the core
		pCore->Release();
	}
}

void OnFrame( float fElapsedTime )
{
	// Process any timers we have
	pCore->ProcessTimers(fElapsedTime);

	int lastHour            = lastSrvInfo.lastHour;
	int lastMinute          = lastSrvInfo.lastMinute;

	int hour                = functions->GetHour();
	int minute              = functions->GetMinute();

	// Check for onTimeChange triggers
	if( lastHour != hour || lastMinute != minute )
	{
		Function callback = RootTable().GetFunction( _SC("onTimeChange") );
		if( !callback.IsNull() )
			callback( lastHour, lastMinute, hour, minute );

		callback.Release();
		lastSrvInfo.lastHour   = hour;
		lastSrvInfo.lastMinute = minute;
	}
}

void OnPlayerConnect( int nPlayerId )
{
	if (pCore != NULL)
	{
		lastPlrInfo[nPlayerId].lastArmour = 0;
		lastPlrInfo[nPlayerId].lastHP = 100;
		lastPlrInfo[nPlayerId].lastWep = 0;
		lastPlrInfo[nPlayerId].lastX = 0.0f;
		lastPlrInfo[nPlayerId].lastY = 0.0f;
		lastPlrInfo[nPlayerId].lastZ = 0.0f;
		
		CPlayer * newPlayer = pCore->AllocatePlayer(nPlayerId);
		Function callback = RootTable().GetFunction(_SC("onPlayerJoin"));
		try
		{
			if (!callback.IsNull())
				callback.Execute<CPlayer *>(newPlayer);
		}
		catch (Sqrat::Exception e)
		{
			OutputWarning("onPlayerJoin failed to execute -- check the console for more details.");
		}

		callback.Release();
	}
}

void OnPlayerDisconnect( int nPlayerId, int nReason )
{
	if( pCore != NULL )
	{
		CPlayer * playerInstance = pCore->RetrievePlayer(nPlayerId);
		Function callback = RootTable().GetFunction(_SC("onPlayerPart"));

		try
		{
			if (!callback.IsNull())
				callback(playerInstance, nReason);
		}
		catch (Sqrat::Exception e)
		{
			OutputWarning("onPlayerPart failed to execute -- check the console for more details.");
		}

		callback.Release();

		// Destroy the player instance we had
		pCore->DereferencePlayer(nPlayerId);
		playerInstance = NULL;
	}
}

int OnPlayerRequestClass( int nPlayerId, int nOffset )
{
	if (pCore != NULL)
	{
		CPlayer * playerInstance = pCore->RetrievePlayer(nPlayerId);
		Function callback = RootTable().GetFunction(_SC("onPlayerRequestClass"));
		int returnValue = 1;

		try
		{
			if (!callback.IsNull())
				returnValue = callback.Evaluate<int, CPlayer *, int, int, int>(
					playerInstance, nOffset, playerInstance->GetTeam(), playerInstance->GetSkin());
		}
		catch (Sqrat::Exception e)
		{
			OutputWarning("onPlayerRequestClass failed to execute -- check the console for more details.");
		}

		callback.Release();
		return returnValue;
	}
	else
		return 1;
}

int OnPlayerRequestSpawn( int nPlayerId )
{
	if (pCore != NULL)
	{
		CPlayer * playerInstance = pCore->RetrievePlayer(nPlayerId);
		Function callback = RootTable().GetFunction(_SC("onPlayerRequestSpawn"));
		int returnValue = 1;

		try
		{
			if (!callback.IsNull())
				returnValue = callback.Evaluate<int, CPlayer *>(playerInstance);
		}
		catch (Sqrat::Exception e)
		{
			OutputWarning("onPlayerRequestSpawn failed to execute -- check the console for more details.");
		}

		callback.Release();
		return returnValue;
	}
	else
		return 1;
}

void OnPlayerSpawn( int nPlayerId )
{
	if (pCore != NULL)
	{
		CPlayer * playerInstance = pCore->RetrievePlayer(nPlayerId);
		Function callback = RootTable().GetFunction(_SC("onPlayerSpawn"));

		try
		{
			if (!callback.IsNull())
				callback.Execute<CPlayer *>(playerInstance);
		}
		catch (Sqrat::Exception e)
		{
			OutputWarning("onPlayerSpawn failed to execute -- check the console for more details.");
		}

		callback.Release();
	}
}

void OnPlayerDeath( int nPlayerId, int nKillerId, int nReason, int nBodyPart )
{
	if (pCore != NULL)
	{
		CPlayer * playerInstance = pCore->RetrievePlayer(nPlayerId);
		if (!functions->IsPlayerConnected(nKillerId))
		{
			Function callback = RootTable().GetFunction(_SC("onPlayerDeath"));
			try
			{
				if (nReason == 43 || nReason == 50)
					nReason = 43; // drowned

				else if (nReason == 39 && nBodyPart == 7)
					nReason = 39; // car crash

				else if (nReason == 39 || nReason == 40 || nReason == 44)
					nReason = 44; // fell

				if (!callback.IsNull())
					callback.Execute<CPlayer *, int>(playerInstance, nReason);
			}
			catch (Sqrat::Exception e)
			{
				OutputWarning("onPlayerDeath failed to execute -- check the console for more details.");
			}

			callback.Release();
		}
		else
		{
			CPlayer * killerInstance = pCore->RetrievePlayer(nKillerId);
			Function callback;
			if (functions->GetPlayerTeam(nPlayerId) == functions->GetPlayerTeam(nKillerId))
				callback = RootTable().GetFunction(_SC("onPlayerTeamKill"));
			else
				callback = RootTable().GetFunction(_SC("onPlayerKill"));

			try
			{
				if (!callback.IsNull())
					callback.Execute<CPlayer *, CPlayer *, int, int>(killerInstance, playerInstance, nReason, nBodyPart);
			}
			catch (Sqrat::Exception e)
			{
				OutputWarning("onPlayer(Team)Kill failed to execute -- check the console for more details.");
			}

			callback.Release();
		}
	}
}

int OnPlayerRequestEnter( int nPlayerId, int nVehicleId, int nSlotId )
{
	if (pCore != NULL)
	{
		CPlayer  * playerInstance = pCore->RetrievePlayer(nPlayerId);
		CVehicle * vehicleInstance = pCore->RetrieveVehicle(nVehicleId);

		Function callback = RootTable().GetFunction(_SC("onPlayerEnteringVehicle"));
		int returnValue = 1;
		try
		{
			if (!callback.IsNull() && playerInstance != NULL && vehicleInstance != NULL)
				returnValue = callback.Evaluate<int, CPlayer *, CVehicle *, int>(playerInstance, vehicleInstance, nSlotId);
		}
		catch (Sqrat::Exception e)
		{
			OutputWarning("onPlayerEnteringVehicle failed to execute -- check the console for more details.");
		}

		callback.Release();
		return returnValue;
	}
	else
		return 1;
}

void OnPlayerEnterVehicle( int nPlayerId, int nVehicleId, int nSlotId )
{
	if (pCore != NULL)
	{
		CPlayer  * playerInstance = pCore->RetrievePlayer(nPlayerId);
		CVehicle * vehicleInstance = pCore->RetrieveVehicle(nVehicleId);

		Function callback = RootTable().GetFunction(_SC("onPlayerEnterVehicle"));
		try
		{
			if (!callback.IsNull() && playerInstance != NULL && vehicleInstance != NULL)
				callback.Execute<CPlayer *, CVehicle *, int>(playerInstance, vehicleInstance, nSlotId);
		}
		catch (Sqrat::Exception e)
		{
			OutputWarning("onPlayerEnterVehicle failed to execute -- check the console for more details.");
		}

		callback.Release();
	}
}

void OnPlayerExitVehicle( int nPlayerId, int nVehicleId )
{
	if (pCore != NULL)
	{
		CPlayer  * playerInstance = pCore->RetrievePlayer(nPlayerId);
		CVehicle * vehicleInstance = pCore->RetrieveVehicle(nVehicleId);
		Function callback = RootTable().GetFunction(_SC("onPlayerExitVehicle"));

		try
		{
			if (!callback.IsNull() && vehicleInstance)
				callback.Execute<CPlayer *, CVehicle *>(playerInstance, vehicleInstance);
		}
		catch (Sqrat::Exception e)
		{
			OutputWarning("onPlayerExitVehicle failed to execute -- check the console for more details.");
		}

		callback.Release();
	}
}

int OnPickupClaimPicked( int nPickupId, int nPlayerId )
{
	if (pCore != NULL)
	{
		CPlayer * playerInstance = pCore->RetrievePlayer(nPlayerId);
		CPickup * pickupInstance = pCore->RetrievePickup(nPickupId);

		Function callback = RootTable().GetFunction(_SC("onPickupClaimPicked"));
		int returnValue = 1;
		try
		{
			if (!callback.IsNull())
				returnValue = callback.Evaluate<int, CPlayer *, CPickup *>(playerInstance, pickupInstance);
		}
		catch (Sqrat::Exception e)
		{
			OutputWarning("onPickupClaimPicked failed to execute -- check the console for more details.");
		}

		callback.Release();
		return returnValue;
	}
	else
		return 1;
}

void OnPickupPickedUp( int nPickupId, int nPlayerId )
{
	if (pCore != NULL)
	{
		CPlayer * playerInstance = pCore->RetrievePlayer(nPlayerId);
		CPickup * pickupInstance = pCore->RetrievePickup(nPickupId);
		Function callback = RootTable().GetFunction(_SC("onPickupPickedUp"));

		try
		{
			if (!callback.IsNull())
				callback.Execute<CPlayer *, CPickup *>(playerInstance, pickupInstance);
		}
		catch (Sqrat::Exception e)
		{
			OutputWarning("onPickupPickedUp failed to execute -- check the console for more details.");
		}

		callback.Release();
	}
}

void OnPickupRespawn( int nPickupId )
{
	if (pCore != NULL)
	{
		CPickup * pickupInstance = pCore->RetrievePickup(nPickupId);
		Function callback = RootTable().GetFunction(_SC("onPickupRespawn"));

		try
		{
			if (!callback.IsNull())
				callback.Execute<CPickup *>(pickupInstance);
		}
		catch (Sqrat::Exception e)
		{
			OutputWarning("onPickupRespawn failed to execute -- check the console for more details.");
		}

		callback.Release();
	}
}

void OnVehicleExplode( int nVehicleId )
{
	if (pCore != NULL)
	{
		CVehicle * vehicleInstance = pCore->RetrieveVehicle(nVehicleId);
		Function callback = RootTable().GetFunction(_SC("onVehicleExplode"));

		try
		{
			if (!callback.IsNull())
				callback.Execute<CVehicle *>(vehicleInstance);
		}
		catch (Sqrat::Exception e)
		{
			OutputWarning("onVehicleExplode failed to execute -- check the console for more details.");
		}

		callback.Release();
	}
}

void OnVehicleRespawn( int nVehicleId )
{
	if (pCore != NULL)
	{
		CVehicle * vehicleInstance = pCore->RetrieveVehicle(nVehicleId);
		Function callback = RootTable().GetFunction(_SC("onVehicleRespawn"));

		try
		{
			if (!callback.IsNull())
				callback.Execute<CVehicle *>(vehicleInstance);
		}
		catch (Sqrat::Exception e)
		{
			OutputWarning("onVehicleRespawn failed to execute -- check the console for more details.");
		}

		callback.Release();
	}
}

int OnPublicMessage( int nPlayerId, const char* pszText )
{
	if (pCore != NULL)
	{
		CPlayer * playerInstance = pCore->RetrievePlayer(nPlayerId);
		Function callback = RootTable().GetFunction(_SC("onPlayerChat"));
		int returnValue = 1;

		try
		{
			if (!callback.IsNull())
				returnValue = callback.Evaluate<int, CPlayer *, const char *>(playerInstance, pszText);
		}
		catch (Sqrat::Exception e)
		{
			OutputWarning("onPlayerChat failed to execute -- check the console for more details.");
		}

		callback.Release();
		return returnValue;
	}
	else
		return 1;
}

extern HSQAPI sq;
int OnCommandMessage( int nPlayerId, const char* pszText )
{
	if (pCore != NULL)
	{
		// Unlike the other callbacks here, onPlayerCommand is bound by some weird
		// 0.3-era conventions: the arguments of a command can be null when passed
		// to the script. Because Sqrat does not let us push nulls (they just turn
		// into empty strings), we call the Squirrel API directly to use null when
		// the arguments are empty.
		//
		// (this comment formed a rectangle -- isn't that pretty neat?)
		CPlayer * playerInstance = pCore->RetrievePlayer(nPlayerId);

		// Save the current stack position of the VM
		SQInteger top = sq->gettop(v);

		// Push the root table
		sq->pushroottable(v);

		// Get the field "onPlayerCommand" from the root table
		sq->pushstring(v, _SC("onPlayerCommand"), -1);

		// Get the function "onPlayerCommand" itself from the root table if we can
		if (SQ_SUCCEEDED(sq->get(v, -2)))
		{
			SQChar * szText = strdup(pszText);
			SQChar * szSpacePos = strchr(szText, ' ');

			if (szSpacePos) {
				szSpacePos[0] = '\0';
			}

			SQChar * szArguments = szSpacePos ? &szSpacePos[1] : NULL;

			// Push "this" which is the root table since onPlayerCommand is
			// expected to be a global function.
			sq->pushroottable(v);

			// Push a CPlayer instance.
			Var<CPlayer *>::push(v, playerInstance);

			// Push our string arguments
			sq->pushstring(v, _SC(szText), -1);
			if (szArguments == NULL || strlen(szArguments) <= 0)
				sq->pushnull(v);
			else
				sq->pushstring(v, _SC(szArguments), -1);

			// Call the function
			sq->call(v, 4, 0, 1);
		}

		// Restore the stack
		sq->settop(v, top);
	}
	
	return 1;
}

int OnPrivateMessage( int nPlayerId, int nTargetId, const char* pszText )
{
	if (pCore != NULL)
	{
		CPlayer * playerInstance = pCore->RetrievePlayer(nPlayerId);
		CPlayer * targetInstance = pCore->RetrievePlayer(nTargetId);

		Function callback = RootTable().GetFunction(_SC("onPlayerPM"));
		int returnValue = 1;
		try
		{
			if (!callback.IsNull())
				returnValue = callback.Evaluate<int, CPlayer *, CPlayer *, const char *>(playerInstance, targetInstance, pszText);
		}
		catch (Sqrat::Exception e)
		{
			OutputWarning("onPlayerPM failed to execute -- check the console for more details.");
		}

		callback.Release();
		return returnValue;
	}
	else
		return 1;
}

void OnPlayerBeginTyping( int nPlayerId )
{
	if (pCore != NULL)
	{
		CPlayer * playerInstance = pCore->RetrievePlayer(nPlayerId);
		Function callback = RootTable().GetFunction(_SC("onPlayerBeginTyping"));
		try
		{
			if (!callback.IsNull())
				callback.Execute<CPlayer *>(playerInstance);
		}
		catch (Sqrat::Exception e)
		{
			OutputWarning("onPlayerBeginTyping failed to execute -- check the console for more details.");
		}

		callback.Release();
	}
}

void OnPlayerEndTyping( int nPlayerId )
{
	if (pCore != NULL)
	{
		CPlayer * playerInstance = pCore->RetrievePlayer(nPlayerId);
		Function callback = RootTable().GetFunction(_SC("onPlayerEndTyping"));
		try
		{
			if (!callback.IsNull())
				callback.Execute<CPlayer *>(playerInstance);
		}
		catch (Sqrat::Exception e)
		{
			OutputWarning("onPlayerEndTyping failed to execute -- check the console for more details.");
		}

		callback.Release();
	}
}

int OnLoginAttempt( char* playerName, const char* password, const char* pszIpAddress )
{
	if (pCore != NULL)
	{
		Function callback = RootTable().GetFunction(_SC("onLoginAttempt"));
		int returnValue = 1;

		try
		{
			if (!callback.IsNull())
				returnValue = callback.Evaluate<int, char *, const char *, const char *>(playerName, password, pszIpAddress);
		}
		catch (Sqrat::Exception e)
		{
			OutputWarning("onLoginAttempt failed to execute -- check the console for more details.");
		}

		callback.Release();
		return returnValue;
	}
	else
		return 1;
}

void OnNameChangeable( char * playerName, char ** namePtr )
{
	/*if (pCore != NULL)
	{
		Function callback = RootTable().GetFunction(_SC("onNameChangeable"));
		try
		{
			if (!callback.IsNull())
			{
				Sqrat::SharedPtr<char *> name = callback.Evaluate<char *, char *>(playerName);
				char ** realName = name();
				if (name && strlen(*realName) > 0)
					namePtr = realName;
			}
		}
		catch (Sqrat::Exception e)
		{
			OutputWarning("onNameChangeable failed to execute -- check the console for more details.");
		}

		callback.Release();
	}*/
}

void OnVehicleUpdate( int nVehicleId, int nUpdateType )
{
	if (pCore != NULL)
	{
		savedVehicleData * vehInfo = &lastVehInfo[nVehicleId];
		Vector lastPos = Vector(vehInfo->lastX, vehInfo->lastY, vehInfo->lastZ);
		float  lastHP = vehInfo->lastHP;

		float x, y, z;
		functions->GetVehiclePos(nVehicleId, &x, &y, &z);

		float hp = functions->GetVehicleHealth(nVehicleId);

		// Check for onVehicleHealthChange triggers
		if (lastHP != hp)
		{
			Function callback = RootTable().GetFunction(_SC("onVehicleHealthChange"));
			try
			{
				if (!callback.IsNull())
				{
					CVehicle * vehInst = pCore->RetrieveVehicle(nVehicleId);
					callback.Execute<CVehicle *, float, float>(vehInst, lastHP, hp);
				}
			}
			catch (Sqrat::Exception e)
			{
				OutputWarning("onVehicleHealthChange failed to execute -- check the console for more details.");
			}

			callback.Release();
			vehInfo->lastHP = hp;
		}

		// Check for onVehicleMove triggers
		if (lastPos.x != x || lastPos.y != y || lastPos.z != z)
		{
			Function callback = RootTable().GetFunction(_SC("onVehicleMove"));
			try
			{
				if (!callback.IsNull())
				{
					CVehicle * vehInst = pCore->RetrieveVehicle(nVehicleId);
					callback.Execute<CVehicle *, float, float, float, float, float, float>(vehInst, lastPos.x, lastPos.y, lastPos.z, x, y, z);
				}
			}
			catch (Sqrat::Exception e)
			{
				OutputWarning("onVehicleMove failed to execute -- check the console for more details.");
			}

			callback.Release();
			vehInfo->lastX = x;
			vehInfo->lastY = y;
			vehInfo->lastZ = z;
		}
	}
}

void OnPlayerUpdate( int nPlayerId, int nUpdateType )
{
	if (pCore != NULL)
	{
		savedPlayerData * plrInfo = &lastPlrInfo[nPlayerId];
		Vector lastPos = Vector(plrInfo->lastX, plrInfo->lastY, plrInfo->lastZ);
		float  lastArmour = plrInfo->lastArmour;
		float  lastHP = plrInfo->lastHP;
		int    lastWep = plrInfo->lastWep;

		float x, y, z;
		functions->GetPlayerPos(nPlayerId, &x, &y, &z);

		float hp = functions->GetPlayerHealth(nPlayerId);
		float armour = functions->GetPlayerArmour(nPlayerId);
		int wep = functions->GetPlayerWeapon(nPlayerId);

		// Check for onPlayerMove triggers
		if (lastPos.x != x || lastPos.y != y || lastPos.z != z)
		{
			Function callback = RootTable().GetFunction(_SC("onPlayerMove"));
			try
			{
				if (!callback.IsNull())
					callback(pCore->RetrievePlayer(nPlayerId), lastPos.x, lastPos.y, lastPos.z, x, y, z);
			}
			catch (Sqrat::Exception e)
			{
				OutputWarning("onPlayerMove failed to execute -- check the console for more details.");
			}

			callback.Release();
			plrInfo->lastX = x;
			plrInfo->lastY = y;
			plrInfo->lastZ = z;
		}

		// Check for onPlayerHealthChange triggers
		if (lastHP != hp)
		{
			Function callback = RootTable().GetFunction(_SC("onPlayerHealthChange"));
			try
			{
				if (!callback.IsNull())
					callback(pCore->RetrievePlayer(nPlayerId), lastHP, hp);
			}
			catch (Sqrat::Exception e)
			{
				OutputWarning("onPlayerHealthChange failed to execute -- check the console for more details.");
			}

			callback.Release();
			plrInfo->lastHP = hp;
		}

		// Check for onPlayerArmourChange triggers
		if (lastArmour != armour)
		{
			Function callback = RootTable().GetFunction(_SC("onPlayerArmourChange"));
			try
			{
				if (!callback.IsNull())
					callback(pCore->RetrievePlayer(nPlayerId), lastArmour, armour);
			}
			catch (Sqrat::Exception e)
			{
				OutputWarning("onPlayerArmourChange failed to execute -- check the console for more details.");
			}

			callback.Release();
			plrInfo->lastArmour = armour;
		}

		// Check for onPlayerWeaponChange triggers
		if (lastWep != wep)
		{
			Function callback = RootTable().GetFunction(_SC("onPlayerWeaponChange"));
			try
			{
				if (!callback.IsNull())
					callback(pCore->RetrievePlayer(nPlayerId), lastWep, wep);
			}
			catch (Sqrat::Exception e)
			{
				OutputWarning("onPlayerWeaponChange failed to execute -- check the console for more details.");
			}

			callback.Release();
			plrInfo->lastWep = wep;
		}
	}
}

void OnObjectShot( int nObjectId, int nPlayerId, int nWeapon )
{
	if (pCore != NULL)
	{
		Function callback = RootTable().GetFunction(_SC("onObjectShot"));
		try
		{
			if (!callback.IsNull())
				callback.Execute<CObject *, CPlayer *, int>(pCore->RetrieveObject(nObjectId), pCore->RetrievePlayer(nPlayerId), nWeapon);
		}
		catch (Sqrat::Exception e)
		{
			OutputWarning("onObjectShot failed to execute -- check the console for more details.");
		}

		callback.Release();
	}
}

void OnObjectBump( int nObjectId, int nPlayerId )
{
	if (pCore != NULL)
	{
		Function callback = RootTable().GetFunction(_SC("onObjectBump"));
		try
		{
			if (!callback.IsNull())
				callback.Execute<CObject *, CPlayer *>(pCore->RetrieveObject(nObjectId), pCore->RetrievePlayer(nPlayerId));
		}
		catch (Sqrat::Exception e)
		{
			OutputWarning("onObjectBump failed to execute -- check the console for more details.");
		}

		callback.Release();
	}
}

// We don't handle this one because we don't take internal commands from other modules.
int OnInternalCommand( unsigned int uCmdType, const char* pszText )
{
	return 1;
}

void OnEntityPoolChange (int nEntityType, int nEntityId, unsigned int bDeleted)
{
	if (pCore != NULL)
	{
		if (nEntityType == 1)
		{
			if (!bDeleted)
				pCore->AllocateVehicle(nEntityId, false);
			else
				pCore->DereferenceVehicle(nEntityId);
		}
		else if (nEntityType == 2)
		{
			if (!bDeleted)
				pCore->AllocateObject(nEntityId, false);
			else
				pCore->DereferenceObject(nEntityId);
		}
		else if (nEntityType == 3)
		{
			if (!bDeleted)
				pCore->AllocatePickup(nEntityId, false);
			else
				pCore->DereferencePickup(nEntityId);
		}
	}
}

void OnKeyBindDown(int nPlayerId, int nBindId)
{
	if (pCore != NULL)
	{
		Function callback = RootTable().GetFunction(_SC("onKeyDown"));
		try
		{
			if (!callback.IsNull())
				callback.Execute<CPlayer *, int>(pCore->RetrievePlayer(nPlayerId), nBindId);
		}
		catch (Sqrat::Exception e)
		{
			OutputWarning("onKeyDown failed to execute -- check the console for more details.");
		}

		callback.Release();
	}
}

void OnKeyBindUp(int nPlayerId, int nBindId)
{
	if (pCore != NULL)
	{
		Function callback = RootTable().GetFunction(_SC("onKeyUp"));
		try
		{
			if (!callback.IsNull())
				callback.Execute<CPlayer *, int>(pCore->RetrievePlayer(nPlayerId), nBindId);
		}
		catch (Sqrat::Exception e)
		{
			OutputWarning("onKeyUp failed to execute -- check the console for more details.");
		}

		callback.Release();
	}
}

void OnPlayerAwayChange(int nPlayerId, unsigned int bNewStatus)
{
	if (pCore != NULL)
	{
		Function callback = RootTable().GetFunction(_SC("onPlayerAwayChange"));
		try
		{
			if (!callback.IsNull())
				callback.Execute<CPlayer *, bool>(pCore->RetrievePlayer(nPlayerId), bNewStatus == 1);
		}
		catch (Sqrat::Exception e)
		{
			OutputWarning("onPlayerAwayChange failed to execute -- check the console for more details.");
		}

		callback.Release();
	}
}

void OnPlayerSpectate(int nPlayerId, int nTargetId)
{
	if (pCore != NULL)
	{
		Function callback = RootTable().GetFunction(_SC("onPlayerSpectate"));
		try
		{
			if (!callback.IsNull())
				callback.Execute<CPlayer *, CPlayer *>(pCore->RetrievePlayer(nPlayerId), pCore->RetrievePlayer(nTargetId));
		}
		catch (Sqrat::Exception e)
		{
			OutputWarning("onPlayerSpectate failed to execute -- check the console for more details.");
		}

		callback.Release();
	}
}

void OnPlayerCrashDump(int nPlayerId, const char * szCrashReport)
{
	if (pCore != NULL)
	{
		Function callback = RootTable().GetFunction(_SC("onPlayerCrashDump"));
		try
		{
			if (!callback.IsNull())
				callback.Execute<CPlayer *, const SQChar *>(pCore->RetrievePlayer(nPlayerId), szCrashReport);
		}
		catch (Sqrat::Exception e)
		{
			OutputWarning("onPlayerCrashDump failed to execute -- check the console for more details.");
		}

		callback.Release();
	}
}

void OnPlayerNameChange(int nPlayerId, const char * oldName, const char * newName)
{
	if (pCore != NULL)
	{
		Function callback = RootTable().GetFunction(_SC("onPlayerNameChange"));
		try
		{
			if (!callback.IsNull())
				callback.Execute<CPlayer *, const SQChar *, const SQChar *>(pCore->RetrievePlayer(nPlayerId), oldName, newName);
		}
		catch (Sqrat::Exception e)
		{
			OutputWarning("onPlayerNameChange failed to execute -- check the console for more details.");
		}

		callback.Release();
	}
}

void OnPlayerActionChange(int nPlayerId, int nOldAction, int nNewAction)
{
	if (pCore != NULL)
	{
		Function callback = RootTable().GetFunction(_SC("onPlayerActionChange"));
		try
		{
			if (!callback.IsNull())
				callback.Execute<CPlayer *, int, int>(pCore->RetrievePlayer(nPlayerId), nOldAction, nNewAction);
		}
		catch (Sqrat::Exception e)
		{
			OutputWarning("onPlayerActionChange failed to execute -- check the console for more details.");
		}

		callback.Release();
	}
}

void OnPlayerStateChange(int nPlayerId, int nOldState, int nNewState)
{
	if (pCore != NULL)
	{
		Function callback = RootTable().GetFunction(_SC("onPlayerStateChange"));
		try
		{
			if (!callback.IsNull())
				callback.Execute<CPlayer *, int, int>(pCore->RetrievePlayer(nPlayerId), nOldState, nNewState);
		}
		catch (Sqrat::Exception e)
		{
			OutputWarning("onPlayerStateChange failed to execute -- check the console for more details.");
		}

		callback.Release();
	}
}

void OnPlayerOnFireChange(int nPlayerId, unsigned int bIsOnFireNow)
{
	if (pCore != NULL)
	{
		Function callback = RootTable().GetFunction(_SC("onPlayerOnFireChange"));
		try
		{
			if (!callback.IsNull())
				callback.Execute<CPlayer *, bool>(pCore->RetrievePlayer(nPlayerId), bIsOnFireNow == 1);
		}
		catch (Sqrat::Exception e)
		{
			OutputWarning("onPlayerOnFireChange failed to execute -- check the console for more details.");
		}

		callback.Release();
	}
}

void OnPlayerCrouchChange(int nPlayerId, unsigned int bIsCrouchingNow)
{
	if (pCore != NULL)
	{
		Function callback = RootTable().GetFunction(_SC("onPlayerCrouchChange"));
		try
		{
			bool isCrouching = functions->GetPlayerCrouchStatus(nPlayerId);
			if (!callback.IsNull())
				callback.Execute<CPlayer *, bool>(pCore->RetrievePlayer(nPlayerId), isCrouching == 0); // tmp fix
				//callback.Execute<CPlayer *, bool>(pCore->RetrievePlayer(nPlayerId), bIsCrouchingNow == 1);
		}
		catch (Sqrat::Exception e)
		{
			OutputWarning("onPlayerCrouchChange failed to execute -- check the console for more details.");
		}

		callback.Release();
	}
}

void OnPlayerGameKeysChange(int nPlayerId, int nOldKeys, int nNewKeys)
{
	if (pCore != NULL)
	{
		Function callback = RootTable().GetFunction(_SC("onPlayerGameKeysChange"));
		try
		{
			if (!callback.IsNull())
				callback.Execute<CPlayer *, int, int>(pCore->RetrievePlayer(nPlayerId), nOldKeys, nNewKeys);
		}
		catch (Sqrat::Exception e)
		{
			OutputWarning("onPlayerGameKeysChange failed to execute -- check the console for more details.");
		}

		callback.Release();
	}
}
