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

void OnPlayerUpdate        ( int nPlayerId, int nUpdateType );
void OnPlayerConnect       ( int nPlayerId );
void OnPlayerDisconnect    ( int nPlayerId, int nReason );
int  OnPlayerRequestClass  ( int nPlayerId, int nOffset );
int  OnPlayerRequestSpawn  ( int nPlayerId );
void OnPlayerSpawn         ( int nPlayerId );
void OnPlayerDeath         ( int nPlayerId, int nKillerId, int nReason, int nBodyPart );

int  OnPlayerRequestEnter  ( int nPlayerId, int nVehicleId, int nSlotId );
void OnPlayerEnterVehicle  ( int nPlayerId, int nVehicleId, int nSlotId );
void OnPlayerExitVehicle   ( int nPlayerId, int nVehicleId );

void OnPlayerBeginTyping   ( int nPlayerId );
void OnPlayerEndTyping     ( int nPlayerId );
void OnPlayerAwayChange    ( int nPlayerId, unsigned int bNewAwayStatus );
void OnPlayerSpectate      ( int nPlayerId, int nTargetId );

int  OnLoginAttempt        ( char* playerName, const char* password, const char* pszIpAddress );
void OnNameChangeable      ( char * playerName, char ** namePtr );

int  OnPickupClaimPicked   ( int nPickupId, int nVehicleId );
void OnPickupPickedUp      ( int nPickupId, int nPlayerId );
void OnPickupRespawn       ( int nPickupId );

void OnVehicleUpdate       ( int nVehicleId, int nUpdateType );
void OnVehicleExplode      ( int nVehicleId );
void OnVehicleRespawn      ( int nVehicleId );

int  OnPublicMessage       ( int nPlayerId, const char* pszText );
int  OnCommandMessage      ( int nPlayerId, const char* pszText );
int  OnPrivateMessage      ( int nPlayerId, int nTargetId, const char* pszText );

void OnObjectShot          ( int nObjectId, int nPlayerId, int nWeapon );
void OnObjectBump          ( int nObjectId, int nPlayerId );

void OnEntityPoolChange    ( int nEntityType, int nEntityId, unsigned int bDeleted );
void OnKeyBindDown         ( int nPlayerId, int nBindId );
void OnKeyBindUp           ( int nPlayerId, int nBindId );

void OnPlayerAwayChange    ( int nPlayerId, unsigned int bNewStatus );
void OnPlayerSpectate      ( int nPlayerId, int nTargetId );
void OnPlayerCrashDump     ( int nPlayerId, const char * szCrashReport );

int  OnInternalCommand     ( unsigned int uCmdType, const char* pszText );
void OnPlayerNameChange    ( int nPlayerId, const char * oldName, const char * newName );

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

struct savedServerData
{
	unsigned int lastHour, lastMinute;
};
