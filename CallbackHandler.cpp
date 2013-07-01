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
	// Create a buffer for the initialization message
	char initMsg[64];
	sprintf( initMsg, "Loaded SqVCMP 0.4 frontend by Stormeus. (v0.9)" );

	// Print the initialization message.
	printf( "\n" );
	OutputMessage( initMsg );

	// Signal outside plugins to register whatever the hell they want
	functions->SendCustomCommand( 0x7D6E22D8, "" );

	// Load the script
	pCore->LoadScript();

	// Prohibit reloading at this time.
	pCore->canReload = false;

	Function callback = RootTable( v ).GetFunction( _SC("onServerStart") );
	if( !callback.IsNull() )
		callback();

	callback.Release();
	
	// Reallow reloading.
	pCore->canReload = true;

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

	// Dereference the core
	pCore->Release();
}

void OnFrame( float fElapsedTime )
{
	// Process any timers we have
	pCore->ProcessTimers(fElapsedTime);
}

void OnPlayerConnect( int nPlayerId )
{
	CPlayer * newPlayer = new CPlayer;

	newPlayer->nPlayerId        = nPlayerId;
	pCore->playerMap[nPlayerId] = newPlayer;

	Function callback = RootTable().GetFunction( _SC("onPlayerJoin") );
	if( !callback.IsNull() )
		callback.Execute<CPlayer *>(newPlayer);

	callback.Release();
}

void OnPlayerDisconnect( int nPlayerId, int nReason )
{
	if( pCore )
	{
		CPlayer * playerInstance = pCore->playerMap[ nPlayerId ];

		Function callback = RootTable().GetFunction( _SC("onPlayerPart") );
		if( !callback.IsNull() )
			callback( playerInstance, nReason );

		// Destroy the player instance we had
		delete playerInstance;

		// Destroy all references
		playerInstance              = NULL;
		pCore->playerMap[nPlayerId] = NULL;
	}
}

int OnPlayerRequestClass( int nPlayerId, int nOffset )
{
	CPlayer * playerInstance = pCore->playerMap[ nPlayerId ];

	Function callback = RootTable().GetFunction( _SC("onPlayerRequestClass") );
	int returnValue   = 1;

	if( !callback.IsNull() )
		returnValue = callback.Evaluate<int, CPlayer *, int>( playerInstance, nOffset );

	callback.Release();
	
	return returnValue;
}

int OnPlayerRequestSpawn( int nPlayerId )
{
	CPlayer * playerInstance = pCore->playerMap[ nPlayerId ];

	Function callback = RootTable().GetFunction( _SC("onPlayerRequestSpawn") );
	int returnValue   = 1;

	if( !callback.IsNull() )
		returnValue = callback.Evaluate<int, CPlayer *>( playerInstance );

	callback.Release();
	
	return returnValue;
}

void OnPlayerSpawn( int nPlayerId )
{
	CPlayer * playerInstance = pCore->playerMap[ nPlayerId ];

	Function callback = RootTable().GetFunction( _SC("onPlayerSpawn") );
	if( !callback.IsNull() )
		callback.Execute<CPlayer *>( playerInstance );

	callback.Release();
}

void OnPlayerDeath( int nPlayerId, int nKillerId, int nReason, int nBodyPart )
{
	CPlayer * playerInstance = pCore->playerMap[ nPlayerId ];

	if( nKillerId == -1 )
	{
		Function callback = RootTable().GetFunction( _SC("onPlayerDeath") );
		if( !callback.IsNull() )
			callback.Execute<CPlayer *, int>( playerInstance, nReason );

		callback.Release();
	}
	else
	{
		CPlayer * killerInstance = pCore->playerMap[ nKillerId ];

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
	CPlayer  * playerInstance  = pCore->playerMap[ nPlayerId ];
	CVehicle * vehicleInstance = pCore->vehicleMap[ nVehicleId ];

	Function callback = RootTable().GetFunction( _SC("onPlayerEnteringVehicle") );
	int returnValue   = 1;

	if( !callback.IsNull() && playerInstance != NULL && vehicleInstance != NULL )
		returnValue = callback.Evaluate<int, CPlayer *, CVehicle *, int>( playerInstance, vehicleInstance, nSlotId );

	callback.Release();
	return returnValue;
}

void OnPlayerEnterVehicle( int nPlayerId, int nVehicleId, int nSlotId )
{
	CPlayer  * playerInstance  = pCore->playerMap[ nPlayerId ];
	CVehicle * vehicleInstance = pCore->vehicleMap[ nVehicleId ];

	Function callback  = RootTable().GetFunction( _SC("onPlayerEnterVehicle") );
	if( !callback.IsNull() && playerInstance != NULL && vehicleInstance != NULL )
		callback.Execute<CPlayer *, CVehicle *, int>( playerInstance, vehicleInstance, nSlotId );

	callback.Release();
}

void OnPlayerExitVehicle( int nPlayerId, int nVehicleId )
{
	CPlayer  * playerInstance  = pCore->playerMap[ nPlayerId ];
	CVehicle * vehicleInstance = pCore->vehicleMap[ nVehicleId ];

	Function callback = RootTable().GetFunction( _SC("onPlayerExitVehicle") );
	if( !callback.IsNull() )
		callback.Execute<CPlayer *, CVehicle *>( playerInstance, vehicleInstance );

	callback.Release();
}

int OnPickupClaimPicked( int nPickupId, int nPlayerId )
{
	CPlayer * playerInstance = pCore->playerMap[ nPlayerId ];
	CPickup * pickupInstance = pCore->pickupMap[ nPickupId ];

	Function callback = RootTable().GetFunction( _SC("onPickupClaimPicked") );
	int returnValue   = 1;

	if( !callback.IsNull() )
		returnValue = callback.Evaluate<int, CPlayer *, CPickup *>( playerInstance, pickupInstance );

	callback.Release();
	return returnValue;
}

void OnPickupPickedUp( int nPickupId, int nPlayerId )
{
	CPlayer * playerInstance = pCore->playerMap[ nPlayerId ];
	CPickup * pickupInstance = pCore->pickupMap[ nPickupId ];

	Function callback = RootTable().GetFunction( _SC("onPickupPickedUp") );
	if( !callback.IsNull() )
		callback.Execute<CPlayer *, CPickup *>( playerInstance, pickupInstance );

	callback.Release();
}

void OnPickupRespawn( int nPickupId )
{
	CPickup * pickupInstance = pCore->pickupMap[ nPickupId ];

	Function callback = RootTable().GetFunction( _SC("onPickupRespawn") );
	if( !callback.IsNull() )
		callback.Execute<CPickup *>( pickupInstance );

	callback.Release();
}

void OnVehicleExplode( int nVehicleId )
{
	CVehicle * vehicleInstance = pCore->vehicleMap[ nVehicleId ];

	Function callback = RootTable().GetFunction( _SC("onVehicleExplode") );
	if( !callback.IsNull() )
		callback.Execute<CVehicle *>( vehicleInstance );

	callback.Release();
}

void OnVehicleRespawn( int nVehicleId )
{
	CVehicle * vehicleInstance = pCore->vehicleMap[ nVehicleId ];

	Function callback = RootTable().GetFunction( _SC("onVehicleRespawn") );
	if( !callback.IsNull() )
		callback.Execute<CVehicle *>( vehicleInstance );

	callback.Release();
}

int OnPublicMessage( int nPlayerId, const char* pszText )
{
	CPlayer * playerInstance = pCore->playerMap[ nPlayerId ];

	Function callback = RootTable().GetFunction( _SC("onPlayerChat") );
	int returnValue   = 1;

	if( !callback.IsNull() )
		returnValue = callback.Evaluate<int, CPlayer *, const char *>( playerInstance, pszText );

	callback.Release();
	return returnValue;
}

int OnCommandMessage( int nPlayerId, const char* pszText )
{
	CPlayer * playerInstance = pCore->playerMap[ nPlayerId ];
	Function callback        = RootTable().GetFunction( _SC("onPlayerCommand") );
	int returnValue          = 1;

	if( !callback.IsNull() )
	{
		char * szText = strdup( pszText );
		char * szSpacePos = strchr( szText, ' ' );

		if(szSpacePos) {
			szSpacePos[0] = '\0';
		}

		const char * szArguments = szSpacePos ? &szSpacePos[1] : "";

		returnValue = callback.Evaluate<int>( playerInstance, szText, szArguments );
		free( szText );
	}
	
	callback.Release();
	return returnValue;
}

int OnPrivateMessage( int nPlayerId, int nTargetId, const char* pszText )
{
	CPlayer * playerInstance = pCore->playerMap[ nPlayerId ];
	CPlayer * targetInstance = pCore->playerMap[ nTargetId ];

	Function callback = RootTable().GetFunction( _SC("onPlayerPM") );
	int returnValue   = 1;

	if( !callback.IsNull() )
		returnValue = callback.Evaluate<int, CPlayer *, CPlayer *, const char *>( playerInstance, targetInstance, pszText );
	
	callback.Release();
	return returnValue;
}

void OnPlayerBeginTyping( int nPlayerId )
{
	CPlayer * playerInstance = pCore->playerMap[ nPlayerId ];
	Function callback        = RootTable().GetFunction( _SC("onPlayerBeginTyping") );

	if( !callback.IsNull() )
		callback.Execute<CPlayer *>( playerInstance );

	callback.Release();
}

void OnPlayerEndTyping( int nPlayerId )
{
	CPlayer * playerInstance = pCore->playerMap[ nPlayerId ];
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
			CVehicle * vehInst = pCore->vehicleMap[nVehicleId];
			callback.Execute<CVehicle *, float, float>( vehInst, lastHP, hp );
		}
		
		callback.Release();
		vehInfo.lastHP = hp;
	}

	// Check for onVehicleMove triggers
	if( lastPos.x != x || lastPos.y != y || lastPos.z != z )
	{
		Function callback = RootTable().GetFunction( _SC("onVehicleMove") );
		if( !callback.IsNull() )
		{
			CVehicle * vehInst = pCore->vehicleMap[nVehicleId];
			callback.Execute<CVehicle *, float, float, float, float, float, float>( vehInst, lastPos.x, lastPos.y, lastPos.z, x, y, z );
		}

		callback.Release();
		vehInfo.lastX = x;
		vehInfo.lastY = y;
		vehInfo.lastZ = z;
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
			callback( pCore->playerMap[nPlayerId], lastPos.x, lastPos.y, lastPos.z, x, y, z );
		
		callback.Release();
		plrInfo.lastX = x;
		plrInfo.lastY = y;
		plrInfo.lastZ = z;
	}

	// Check for onPlayerHealthChange triggers
	if( lastHP != hp )
	{
		Function callback = RootTable().GetFunction( _SC("onPlayerHealthChange") );
		if( !callback.IsNull() )
			callback( pCore->playerMap[nPlayerId], lastHP, hp );
		
		callback.Release();
		plrInfo.lastHP = hp;
	}

	// Check for onPlayerArmourChange triggers
	if( lastArmour != armour )
	{
		Function callback = RootTable().GetFunction( _SC("onPlayerArmourChange") );
		if( !callback.IsNull() )
			callback( pCore->playerMap[nPlayerId], lastArmour, armour );
		
		callback.Release();
		plrInfo.lastArmour = armour;
	}

	// Check for onPlayerWeaponChange triggers
	if( lastWep != wep )
	{
		Function callback = RootTable().GetFunction( _SC("onPlayerWeaponChange") );
		if( !callback.IsNull() )
			callback( pCore->playerMap[nPlayerId], lastWep, wep );
		
		callback.Release();
		plrInfo.lastWep = wep;
	}

	lastPlrInfo[nPlayerId] = plrInfo;
}

void OnObjectShot( int nObjectId, int nPlayerId, int nWeapon )
{
	Function callback = RootTable().GetFunction( _SC("onObjectShot") );
	if( !callback.IsNull() )
		callback.Execute<CObject *, CPlayer *, int>( pCore->objectMap[nObjectId], pCore->playerMap[nPlayerId], nWeapon );
		
	callback.Release();
}

void OnObjectBump( int nObjectId, int nPlayerId )
{
	Function callback = RootTable().GetFunction( _SC("onObjectBump") );
	if( !callback.IsNull() )
		callback.Execute<CObject *, CPlayer *>( pCore->objectMap[nObjectId], pCore->playerMap[nPlayerId] );
		
	callback.Release();
}

// We don't handle this one because we don't take internal commands from other modules.
int OnInternalCommand( unsigned int uCmdType, const char* pszText )
{
	return 1;
}

void OnEntityPoolChange (int nEntityType, int nEntityId, unsigned int bDeleted) {
	if(nEntityType == 1) {
		if(!bDeleted) {
			pCore->vehicleMap[nEntityId] = new CVehicle;
			pCore->vehicleMap[nEntityId]->Init( nEntityId, false );
		}
		else {
			if(pCore->vehicleMap[nEntityId] != NULL) {
				delete pCore->vehicleMap[nEntityId];
			}

			pCore->vehicleMap[nEntityId] = NULL;
		}
	}
	else if(nEntityType == 2) {
		if(!bDeleted) {
			pCore->objectMap[nEntityId] = new CObject;
			pCore->objectMap[nEntityId]->Init( nEntityId, false );
		}
		else {
			if(pCore->objectMap[nEntityId] != NULL) {
				delete pCore->objectMap[nEntityId];
			}

			pCore->objectMap[nEntityId] = NULL;
		}
	}
	else if(nEntityType == 3) {
		if(!bDeleted) {
			pCore->pickupMap[nEntityId] = new CPickup;
			pCore->pickupMap[nEntityId]->Init( nEntityId, false );
		}
		else {
			if(pCore->pickupMap[nEntityId] != NULL) {
				delete pCore->pickupMap[nEntityId];
			}

			pCore->pickupMap[nEntityId] = NULL;
		}
	}
}
