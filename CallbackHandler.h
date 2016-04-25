#include "main.h"
#include "Constants.h"
#include "CPlayer.h"
#include "CPickup.h"
#include "CVehicle.h"
#pragma once

// This is one fugly list.
uint8_t  OnInitServer          ( void );
void OnShutdownServer      ( void );
void OnFrame               ( float fElapsedTime );

void OnPlayerUpdate        ( int nPlayerId, vcmpPlayerUpdate nUpdateType );
void OnPlayerConnect       ( int nPlayerId );
void OnPlayerDisconnect    ( int nPlayerId, vcmpDisconnectReason nReason );
uint8_t OnPlayerRequestClass( int nPlayerId, int nOffset );
uint8_t OnPlayerRequestSpawn( int nPlayerId );
void OnPlayerSpawn         ( int nPlayerId );
void OnPlayerDeath         ( int nPlayerId, int nKillerId, int nReason, vcmpBodyPart nBodyPart );

uint8_t  OnPlayerRequestEnter(int nPlayerId, int nVehicleId, int nSlotId);
void OnPlayerEnterVehicle  ( int nPlayerId, int nVehicleId, int nSlotId );
void OnPlayerExitVehicle   ( int nPlayerId, int nVehicleId );

void OnPlayerBeginTyping   ( int nPlayerId );
void OnPlayerEndTyping     ( int nPlayerId );
void OnPlayerAwayChange    ( int nPlayerId, uint8_t bNewAwayStatus );
void OnPlayerSpectate      ( int nPlayerId, int nTargetId );

uint8_t OnLoginAttempt     (char* playerName, size_t size, const char* password, const char* pszIpAddress);
void OnClientScriptData    ( int playerId, const uint8_t* data, size_t size);
void OnNameChangeable      ( char * playerName, char ** namePtr );

uint8_t  OnPickupClaimPicked(int nPickupId, int nVehicleId);
void OnPickupPickedUp      ( int nPickupId, int nPlayerId );
void OnPickupRespawn       ( int nPickupId );

void OnVehicleUpdate       ( int nVehicleId, vcmpVehicleUpdate nUpdateType );
void OnVehicleExplode      ( int nVehicleId );
void OnVehicleRespawn      ( int nVehicleId );

uint8_t  OnPublicMessage(int nPlayerId, const char* pszText);
uint8_t  OnCommandMessage(int nPlayerId, const char* pszText);
uint8_t  OnPrivateMessage(int nPlayerId, int nTargetId, const char* pszText);

void OnObjectShot          ( int nObjectId, int nPlayerId, int nWeapon );
void OnObjectBump          ( int nObjectId, int nPlayerId );

void OnEntityPoolChange    ( vcmpEntityPool nEntityType, int nEntityId, uint8_t bDeleted );
void OnKeyBindDown         ( int nPlayerId, int nBindId );
void OnKeyBindUp           ( int nPlayerId, int nBindId );

void OnPlayerCrashDump     ( int nPlayerId, const char * szCrashReport );

uint8_t  OnInternalCommand     ( uint32_t uCmdType, const char* pszText );
void OnPlayerNameChange    ( int nPlayerId, const char * oldName, const char * newName );
void OnPlayerActionChange  ( int nPlayerId, int nOldAction, int nNewAction );
void OnPlayerStateChange   ( int nPlayerId, vcmpPlayerState nOldState, vcmpPlayerState nNewState );
void OnPlayerOnFireChange  ( int nPlayerId, uint8_t bIsOnFireNow );
void OnPlayerCrouchChange  ( int nPlayerId, uint8_t bIsCrouchingNow );
void OnPlayerGameKeysChange ( int nPlayerId, uint32_t nOldKeys, uint32_t nNewKeys );

void OnCheckpointEntered(int nCheckpointId, int nPlayerId);
void OnCheckpointExited(int nCheckpointId, int nPlayerId);

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
