#include "main.h"
#include "CPlayer.h"
#include "CPickup.h"
#include "CVehicle.h"

// This is one fugly list.
int OnInitServer();
void OnShutdownServer();
void OnFrame( float fElapsedTime );
void OnPlayerConnect( int nPlayerId );
void OnPlayerDisconnect( int nPlayerId, int nReason );
int OnPlayerRequestClass( int nPlayerId, int nOffset );
int OnPlayerRequestSpawn( int nPlayerId );
void OnPlayerSpawn( int nPlayerId );
void OnPlayerDeath( int nPlayerId, int nKillerId, int nReason, int nBodyPart );
void OnPlayerUpdate( int nPlayerId, int nUpdateType );
int OnPlayerRequestEnter( int nPlayerId, int nVehicleId, int nSlotId );
void OnPlayerEnterVehicle( int nPlayerId, int nVehicleId, int nSlotId );
void OnPlayerExitVehicle( int nPlayerId, int nVehicleId );
int OnPickupClaimPicked( int nPickupId, int nVehicleId );
void OnPickupPickedUp( int nPickupId, int nPlayerId );
void OnPickupRespawn( int nPickupId );
void OnVehicleUpdate( int nVehicleId, int nUpdateType );
void OnVehicleExplode( int nVehicleId );
void OnVehicleRespawn( int nVehicleId );
int OnPublicMessage( int nPlayerId, const char* pszText );
int OnCommandMessage( int nPlayerId, const char* pszText );
int OnPrivateMessage( int nPlayerId, int nTargetId, const char* pszText );
int OnInternalCommand( unsigned int uCmdType, const char* pszText );
void OnPlayerBeginTyping( int nPlayerId );
void OnPlayerEndTyping( int nPlayerId );
int OnLoginAttempt( char* playerName, const char* password, const char* pszIpAddress );
void OnNameChangeable( char * playerName, char ** namePtr );

// Player map
extern std::map<int, CPlayer> playerMap;