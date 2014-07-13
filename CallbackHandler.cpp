#include "CallbackHandler.h"
#include <string>

// Console stuff
#include "ConsoleUtils.h"

// Script and VM core
#include "CCore.h"

// Create arrays for several structures.
savedVehicleData lastVehInfo[MAX_VEHICLES];
savedPlayerData  lastPlrInfo[MAX_PLAYERS];

// Externalize the core instance and other critical variables
extern CCore * pCore;
extern PluginInfo       *   information;
extern PluginCallbacks  *   callbacks;

int OnInitServer()
{
	// Print the initialization message.
	printf("\n");
	OutputMessage("Loaded SqVCMP 0.4 frontend by Stormeus. (v1.0b2)");

	// Signal outside plugins to register whatever the hell they want
	functions->SendCustomCommand(0x7D6E22D8, "");

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
	if (pCore != nullptr)
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
}

void OnPlayerConnect( int nPlayerId )
{
	if (pCore != nullptr)
	{
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
	if( pCore != nullptr )
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
		playerInstance = nullptr;
	}
}

int OnPlayerRequestClass( int nPlayerId, int nOffset )
{
	if (pCore != nullptr)
	{
		CPlayer * playerInstance = pCore->RetrievePlayer(nPlayerId);
		Function callback = RootTable().GetFunction(_SC("onPlayerRequestClass"));
		int returnValue = 1;

		try
		{
			if (!callback.IsNull())
				returnValue = callback.Evaluate<int, CPlayer *, int>(playerInstance, nOffset);
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
	if (pCore != nullptr)
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
	if (pCore != nullptr)
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
	if (pCore != nullptr)
	{
		CPlayer * playerInstance = pCore->RetrievePlayer(nPlayerId);
		if (nReason == 70 || !functions->IsPlayerConnected(nKillerId))
		{
			Function callback = RootTable().GetFunction(_SC("onPlayerDeath"));
			try
			{
				if (nReason >= 0 && nReason != 255 && nBodyPart >= 0 && nBodyPart != 255)
					nReason = 39; // vehkill

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
	if (pCore != nullptr)
	{
		CPlayer  * playerInstance = pCore->RetrievePlayer(nPlayerId);
		CVehicle * vehicleInstance = pCore->RetrieveVehicle(nVehicleId);

		Function callback = RootTable().GetFunction(_SC("onPlayerEnteringVehicle"));
		int returnValue = 1;
		try
		{
			if (!callback.IsNull() && playerInstance != nullptr && vehicleInstance != nullptr)
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
	if (pCore != nullptr)
	{
		CPlayer  * playerInstance = pCore->RetrievePlayer(nPlayerId);
		CVehicle * vehicleInstance = pCore->RetrieveVehicle(nVehicleId);

		Function callback = RootTable().GetFunction(_SC("onPlayerEnterVehicle"));
		try
		{
			if (!callback.IsNull() && playerInstance != nullptr && vehicleInstance != nullptr)
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
	if (pCore != nullptr)
	{
		CPlayer  * playerInstance = pCore->RetrievePlayer(nPlayerId);
		CVehicle * vehicleInstance = pCore->RetrieveVehicle(nVehicleId);
		Function callback = RootTable().GetFunction(_SC("onPlayerExitVehicle"));

		try
		{
			if (!callback.IsNull())
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
	if (pCore != nullptr)
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
	if (pCore != nullptr)
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
	if (pCore != nullptr)
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
	if (pCore != nullptr)
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
	if (pCore != nullptr)
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
	if (pCore != nullptr)
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

int OnCommandMessage( int nPlayerId, const char* pszText )
{
	if (pCore != nullptr)
	{
		CPlayer * playerInstance = pCore->RetrievePlayer(nPlayerId);
		Function callback = RootTable().GetFunction(_SC("onPlayerCommand"));

		if (!callback.IsNull())
		{
			char * szText = strdup(pszText);
			char * szSpacePos = strchr(szText, ' ');

			if (szSpacePos) {
				szSpacePos[0] = '\0';
			}

			const char * szArguments = szSpacePos ? &szSpacePos[1] : "";

			try
			{
				if (!callback.IsNull())
					callback.Execute(playerInstance, szText, szArguments);
			}
			catch (Sqrat::Exception e)
			{
				OutputWarning("onPlayerCommand failed to execute -- check the console for more details.");
			}

			free(szText);
		}

		callback.Release();
	}
	
	return 1;
}

int OnPrivateMessage( int nPlayerId, int nTargetId, const char* pszText )
{
	if (pCore != nullptr)
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
	if (pCore != nullptr)
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
	if (pCore != nullptr)
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
	if (pCore != nullptr)
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
	/*if (pCore != nullptr)
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
	if (pCore != nullptr)
	{
		savedVehicleData vehInfo = lastVehInfo[nVehicleId];
		Vector lastPos = Vector(vehInfo.lastX, vehInfo.lastY, vehInfo.lastZ);
		float  lastHP = vehInfo.lastHP;

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
			vehInfo.lastHP = hp;
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
			vehInfo.lastX = x;
			vehInfo.lastY = y;
			vehInfo.lastZ = z;
		}

		lastVehInfo[nVehicleId] = vehInfo;
	}
}

void OnPlayerUpdate( int nPlayerId, int nUpdateType )
{
	if (pCore != nullptr)
	{
		savedPlayerData plrInfo = lastPlrInfo[nPlayerId];
		Vector lastPos = Vector(plrInfo.lastX, plrInfo.lastY, plrInfo.lastZ);
		float  lastArmour = plrInfo.lastArmour;
		float  lastHP = plrInfo.lastHP;
		int    lastWep = plrInfo.lastWep;

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
			plrInfo.lastX = x;
			plrInfo.lastY = y;
			plrInfo.lastZ = z;
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
			plrInfo.lastHP = hp;
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
			plrInfo.lastArmour = armour;
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
			plrInfo.lastWep = wep;
		}

		lastPlrInfo[nPlayerId] = plrInfo;
	}
}

void OnObjectShot( int nObjectId, int nPlayerId, int nWeapon )
{
	if (pCore != nullptr)
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
	if (pCore != nullptr)
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
	if (pCore != nullptr)
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
	if (pCore != nullptr)
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
	if (pCore != nullptr)
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
	if (pCore != nullptr)
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
	if (pCore != nullptr)
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
	if (pCore != nullptr)
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