#include "main.h"
#include "Constants.h"
#include "CPlayer.h"
#include "CPickup.h"
#include "CVehicle.h"
#pragma once

// This is one fugly list.
int  OnInitServer          ( void );
void OnShutdownServer      ( void );
void OnFrame               ( float fElapsedTime );

void OnPlayerConnect       ( int nPlayerId );
void OnPlayerDisconnect    ( int nPlayerId, int nReason );
int  OnPlayerRequestClass  ( int nPlayerId, int nOffset );
int  OnPlayerRequestSpawn  ( int nPlayerId );
void OnPlayerSpawn         ( int nPlayerId );
void OnPlayerDeath         ( int nPlayerId, int nKillerId, int nReason, int nBodyPart );
void OnPlayerUpdate        ( int nPlayerId, int nUpdateType );
int  OnPlayerRequestEnter  ( int nPlayerId, int nVehicleId, int nSlotId );
void OnPlayerEnterVehicle  ( int nPlayerId, int nVehicleId, int nSlotId );
void OnPlayerExitVehicle   ( int nPlayerId, int nVehicleId );

int  OnPickupClaimPicked   ( int nPickupId, int nVehicleId );
void OnPickupPickedUp      ( int nPickupId, int nPlayerId );
void OnPickupRespawn       ( int nPickupId );

void OnVehicleUpdate       ( int nVehicleId, int nUpdateType );
void OnVehicleExplode      ( int nVehicleId );
void OnVehicleRespawn      ( int nVehicleId );

int  OnPublicMessage       ( int nPlayerId, const char* pszText );
int  OnCommandMessage      ( int nPlayerId, const char* pszText );
int  OnPrivateMessage      ( int nPlayerId, int nTargetId, const char* pszText );
void OnPlayerBeginTyping   ( int nPlayerId );
void OnPlayerEndTyping     ( int nPlayerId );
int  OnLoginAttempt        ( char* playerName, const char* password, const char* pszIpAddress );
void OnNameChangeable      ( char * playerName, char ** namePtr );

void OnObjectShot          ( int nObjectId, int nPlayerId, int nWeapon );
void OnObjectBump          ( int nObjectId, int nPlayerId );

int  OnInternalCommand     ( unsigned int uCmdType, const char* pszText );

void OnEntityPoolChange    ( int nEntityType, int nEntityId, unsigned int bDeleted );
void OnKeyBindDown         ( int nPlayerId, int nBindId );

// Define some structures for tracking player data
struct savedPlayerData
{
	unsigned char lastWep;
	float         lastHP, lastArmour;
	float         lastX, lastY, lastZ;
};

struct savedVehicleData
{
	float lastHP;
	float lastX, lastY, lastZ;
};