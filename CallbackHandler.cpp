#include "CallbackHandler.h"
#include <string>

// Create arrays for several structures.
savedVehicleData lastVehInfo[MAX_VEHICLES];
savedPlayerData  lastPlrInfo[MAX_PLAYERS];

// Create array for a map of varying types.
CPlayer  * playerMap[MAX_PLAYERS];
CPickup  * pickupMap[MAX_PICKUPS];
CVehicle * vehicleMap[MAX_VEHICLES];

int OnInitServer()
{
	Function callback = RootTable( v ).GetFunction( _SC("onServerStart") );
	if( !callback.IsNull() )
		callback();

	callback.Release();
	return 1;
}

void OnShutdownServer()
{
	Function callback = RootTable().GetFunction( _SC("onServerStop") );
	if( !callback.IsNull() )
		callback();

	callback.Release();
	callback = RootTable().GetFunction( _SC("onScriptUnload") );

	if( !callback.IsNull() )
		callback();

	callback.Release();
}

void OnFrame( float fElapsedTime )
{
	Function callback = RootTable().GetFunction( _SC("onFrame") );
	if( !callback.IsNull() )
		callback( fElapsedTime );

	callback.Release();
}

void OnPlayerConnect( int nPlayerId )
{
	CPlayer * newPlayer = new CPlayer;

	newPlayer->nPlayerId = nPlayerId;
	playerMap[nPlayerId] = newPlayer;

	Function callback = RootTable().GetFunction( _SC("onPlayerJoin") );
	if( !callback.IsNull() )
		callback.Execute<CPlayer *>(newPlayer);

	callback.Release();
}

void OnPlayerDisconnect( int nPlayerId, int nReason )
{
	CPlayer * playerInstance = playerMap[ nPlayerId ];

	Function callback = RootTable().GetFunction( _SC("onPlayerPart") );
	if( !callback.IsNull() )
		callback( playerInstance, nReason );

	callback.Release();

	// Insert a blank instance that does nothing
	playerMap[nPlayerId] = NULL;

	// Nullify the current instance
	delete playerInstance;
	delete playerMap[nPlayerId];

	playerInstance       = NULL;
	playerMap[nPlayerId] = NULL;
}

int OnPlayerRequestClass( int nPlayerId, int nOffset )
{
	CPlayer * playerInstance = playerMap[ nPlayerId ];

	Function callback = RootTable().GetFunction( _SC("onPlayerRequestClass") );
	int returnValue   = 1;

	if( !callback.IsNull() )
		returnValue = callback.Evaluate<int, CPlayer *, int>( playerInstance, nOffset );
	
	callback.Release();
	return returnValue;
}

int OnPlayerRequestSpawn( int nPlayerId )
{
	CPlayer * playerInstance = playerMap[ nPlayerId ];

	Function callback = RootTable().GetFunction( _SC("onPlayerRequestSpawn") );
	int returnValue   = 1;

	if( !callback.IsNull() )
		returnValue = callback.Evaluate<int, CPlayer *>( playerInstance );
	
	callback.Release();
	return returnValue;
}

void OnPlayerSpawn( int nPlayerId )
{
	CPlayer * playerInstance = playerMap[ nPlayerId ];

	Function callback = RootTable().GetFunction( _SC("onPlayerSpawn") );
	if( !callback.IsNull() )
		callback.Execute<CPlayer *>( playerInstance );

	callback.Release();
}

void OnPlayerDeath( int nPlayerId, int nKillerId, int nReason, int nBodyPart )
{
	CPlayer * playerInstance = playerMap[ nPlayerId ];

	if( nKillerId == -1 )
	{
		Function callback = RootTable().GetFunction( _SC("onPlayerDeath") );
		if( !callback.IsNull() )
			callback.Execute<CPlayer *, int>( playerInstance, nReason );

		callback.Release();
	}
	else
	{
		CPlayer * killerInstance = playerMap[ nKillerId ];

		Function callback;
		if( functions->GetPlayerTeam( nPlayerId ) == functions->GetPlayerTeam( nKillerId ) )
			callback = RootTable().GetFunction( _SC("onPlayerTeamKill") );
		else
			callback = RootTable().GetFunction( _SC("onPlayerKill") );

		if( !callback.IsNull() )
			callback.Execute<CPlayer *, CPlayer *, int, int>( playerInstance, killerInstance, nReason, nBodyPart );

		callback.Release();
	}
}

int OnPlayerRequestEnter( int nPlayerId, int nVehicleId, int nSlotId )
{
	CPlayer  * playerInstance  = playerMap[ nPlayerId ];
	CVehicle * vehicleInstance = vehicleMap[ nVehicleId ];

	Function callback = RootTable().GetFunction( _SC("onPlayerEnteringVehicle") );
	int returnValue   = 1;

	if( !callback.IsNull() && playerInstance != NULL && vehicleInstance != NULL )
		returnValue = callback.Evaluate<int, CPlayer *, CVehicle *, int>( playerInstance, vehicleInstance, nSlotId );
	
	callback.Release();
	return returnValue;
}

void OnPlayerEnterVehicle( int nPlayerId, int nVehicleId, int nSlotId )
{
	CPlayer  * playerInstance  = playerMap[ nPlayerId ];
	CVehicle * vehicleInstance = vehicleMap[ nVehicleId ];

	Function callback  = RootTable().GetFunction( _SC("onPlayerEnterVehicle") );
	if( !callback.IsNull() && playerInstance != NULL && vehicleInstance != NULL )
		callback.Execute<CPlayer *, CVehicle *, int>( playerInstance, vehicleInstance, nSlotId );

	callback.Release();
}

void OnPlayerExitVehicle( int nPlayerId, int nVehicleId )
{
	CPlayer  * playerInstance  = playerMap[ nPlayerId ];
	CVehicle * vehicleInstance = vehicleMap[ nVehicleId ];

	Function callback = RootTable().GetFunction( _SC("onPlayerExitVehicle") );
	if( !callback.IsNull() )
		callback.Execute<CPlayer *, CVehicle *>( playerInstance, vehicleInstance );

	callback.Release();
}

int OnPickupClaimPicked( int nPickupId, int nPlayerId )
{
	CPlayer * playerInstance = playerMap[ nPlayerId ];
	CPickup * pickupInstance = pickupMap[ nPickupId ];

	Function callback = RootTable().GetFunction( _SC("onPickupClaimPicked") );
	int returnValue   = 1;

	if( !callback.IsNull() )
		returnValue = callback.Evaluate<int, CPlayer *, CPickup *>( playerInstance, pickupInstance );
	
	callback.Release();
	return returnValue;
}

void OnPickupPickedUp( int nPickupId, int nPlayerId )
{
	CPlayer * playerInstance = playerMap[ nPlayerId ];
	CPickup * pickupInstance = pickupMap[ nPickupId ];

	Function callback = RootTable().GetFunction( _SC("onPickupPickedUp") );
	if( !callback.IsNull() )
		callback.Execute<CPlayer *, CPickup *>( playerInstance, pickupInstance );

	callback.Release();
}

void OnPickupRespawn( int nPickupId )
{
	CPickup * pickupInstance = pickupMap[ nPickupId ];

	Function callback = RootTable().GetFunction( _SC("onPickupRespawn") );
	if( !callback.IsNull() )
		callback.Execute<CPickup *>( pickupInstance );

	callback.Release();
}

void OnVehicleExplode( int nVehicleId )
{
	CVehicle * vehicleInstance = vehicleMap[ nVehicleId ];

	Function callback = RootTable().GetFunction( _SC("onVehicleExplode") );
	if( !callback.IsNull() )
		callback.Execute<CVehicle *>( vehicleInstance );

	callback.Release();
}

void OnVehicleRespawn( int nVehicleId )
{
	CVehicle * vehicleInstance = vehicleMap[ nVehicleId ];

	Function callback = RootTable().GetFunction( _SC("onVehicleRespawn") );
	if( !callback.IsNull() )
		callback.Execute<CVehicle *>( vehicleInstance );

	callback.Release();
}

int OnPublicMessage( int nPlayerId, const char* pszText )
{
	CPlayer * playerInstance = playerMap[ nPlayerId ];

	Function callback = RootTable().GetFunction( _SC("onPlayerChat") );
	int returnValue   = 1;

	if( !callback.IsNull() )
		returnValue = callback.Evaluate<int, CPlayer *, const char *>( playerInstance, pszText );
	
	callback.Release();
	return returnValue;
}

int OnCommandMessage( int nPlayerId, const char* pszText )
{
	CPlayer * playerInstance = playerMap[ nPlayerId ];
	Function callback        = RootTable().GetFunction( _SC("onPlayerCommand") );
	int returnValue          = 1;

	if( !callback.IsNull() )
	{
		char * szText = const_cast<char *>(pszText);
		char * szCmd  = strtok( szText, " " );
		if( szCmd == NULL )
			return 0;

		char * szArguments = "";
		char * szTok       = strtok( NULL, " " );

		while( szTok != NULL )
			strcat( szArguments, szTok );

		returnValue = callback.Evaluate<int, CPlayer *, char *, char *>( playerInstance, szCmd, szArguments );
	}

	callback.Release();
	return returnValue;
}

int OnPrivateMessage( int nPlayerId, int nTargetId, const char* pszText )
{
	CPlayer * playerInstance = playerMap[ nPlayerId ];
	CPlayer * targetInstance = playerMap[ nTargetId ];

	Function callback = RootTable().GetFunction( _SC("onPlayerPM") );
	int returnValue   = 1;

	if( !callback.IsNull() )
		returnValue = callback.Evaluate<int, CPlayer *, CPlayer *, const char *>( playerInstance, targetInstance, pszText );
	
	callback.Release();
	return returnValue;
}

void OnPlayerBeginTyping( int nPlayerId )
{
	CPlayer * playerInstance = playerMap[ nPlayerId ];
	Function callback        = RootTable().GetFunction( _SC("onPlayerBeginTyping") );

	if( !callback.IsNull() )
		callback.Execute<CPlayer *>( playerInstance );

	callback.Release();
}

void OnPlayerEndTyping( int nPlayerId )
{
	CPlayer * playerInstance = playerMap[ nPlayerId ];
	Function callback        = RootTable().GetFunction( _SC("onPlayerEndTyping") );

	if( !callback.IsNull() )
		callback.Execute<CPlayer *>( playerInstance );

	callback.Release();
}

int OnLoginAttempt( char* playerName, const char* password, const char* pszIpAddress )
{
	Function callback = RootTable().GetFunction( _SC("onLoginAttempt") );
	int returnValue   = 1;

	if( !callback.IsNull() )
		returnValue = callback.Evaluate<int, char *, const char *, const char *>(playerName, password, pszIpAddress);
	
	callback.Release();
	return returnValue;
}

void OnNameChangeable( char * playerName, char ** namePtr )
{
	Function callback = RootTable().GetFunction( _SC("onNameChangeable") );
	if( !callback.IsNull() )
	{
		char * name = callback.Evaluate<char *, char *>(playerName);
		if( name && strlen(name) > 0 )
			namePtr = &name;
	}

	callback.Release();
}

void OnVehicleUpdate( int nVehicleId, int nUpdateType )
{
	savedVehicleData vehInfo = lastVehInfo[nVehicleId];
	Vector lastPos           = Vector( vehInfo.lastX, vehInfo.lastY, vehInfo.lastZ );
	float  lastHP            = vehInfo.lastHP;

	float x, y, z;
	functions->GetVehiclePos( nVehicleId, &x, &y, &z );

	float hp = functions->GetVehicleHealth( nVehicleId );

	// Check for onVehicleHealthChange triggers
	if( lastHP != hp )
	{
		Function callback = RootTable().GetFunction( _SC("onVehicleHealthChange") );
		if( !callback.IsNull() )
		{
			CVehicle * vehInst = vehicleMap[nVehicleId];
			callback.Execute<CVehicle *, float, float>( vehInst, lastHP, hp );
		}

		vehInfo.lastHP = hp;
		callback.Release();
	}

	// Check for onVehicleMove triggers
	if( lastPos.x != x || lastPos.y != y || lastPos.z != z )
	{
		Function callback = RootTable().GetFunction( _SC("onVehicleMove") );
		if( !callback.IsNull() )
		{
			CVehicle * vehInst = vehicleMap[nVehicleId];
			callback.Execute<CVehicle *, float, float, float, float, float, float>( vehInst, lastPos.x, lastPos.y, lastPos.z, x, y, z );
		}

		vehInfo.lastX = x;
		vehInfo.lastY = y;
		vehInfo.lastZ = z;

		callback.Release();
	}

	lastVehInfo[nVehicleId] = vehInfo;
}

void OnPlayerUpdate( int nPlayerId, int nUpdateType )
{
	savedPlayerData plrInfo = lastPlrInfo[nPlayerId];
	Vector lastPos          = Vector( plrInfo.lastX, plrInfo.lastY, plrInfo.lastZ );
	float  lastArmour       = plrInfo.lastArmour;
	float  lastHP           = plrInfo.lastHP;
	int    lastWep          = plrInfo.lastWep;

	float x, y, z;
	functions->GetPlayerPos( nPlayerId, &x, &y, &z );

	float hp     = functions->GetPlayerHealth( nPlayerId );
	float armour = functions->GetPlayerArmour( nPlayerId );
	int wep      = functions->GetPlayerWeapon( nPlayerId );

	// Check for onPlayerMove triggers
	if( lastPos.x != x || lastPos.y != y || lastPos.z != z )
	{
		Function callback = RootTable().GetFunction( _SC("onPlayerMove") );
		if( !callback.IsNull() )
			callback( playerMap[nPlayerId], lastPos.x, lastPos.y, lastPos.z, x, y, z );

		plrInfo.lastX = x;
		plrInfo.lastY = y;
		plrInfo.lastZ = z;

		callback.Release();
	}

	// Check for onPlayerHealthChange triggers
	if( lastHP != hp )
	{
		Function callback = RootTable().GetFunction( _SC("onPlayerHealthChange") );
		if( !callback.IsNull() )
			callback( playerMap[nPlayerId], lastHP, hp );

		plrInfo.lastHP = hp;
		callback.Release();
	}

	// Check for onPlayerArmourChange triggers
	if( lastArmour != armour )
	{
		Function callback = RootTable().GetFunction( _SC("onPlayerArmourChange") );
		if( !callback.IsNull() )
			callback( playerMap[nPlayerId], lastArmour, armour );

		plrInfo.lastArmour = armour;
		callback.Release();
	}

	// Check for onPlayerWeaponChange triggers
	if( lastWep != wep )
	{
		Function callback = RootTable().GetFunction( _SC("onPlayerWeaponChange") );
		if( !callback.IsNull() )
			callback( playerMap[nPlayerId], lastWep, wep );

		plrInfo.lastWep = wep;
		callback.Release();
	}

	lastPlrInfo[nPlayerId] = plrInfo;
}

// We don't handle this one because we don't take internal commands from other modules.
int OnInternalCommand( unsigned int uCmdType, const char* pszText )
{
	return 1;
}