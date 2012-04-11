#include "main.h"
#include "VCMP.h"
#include "CallbackHandler.h"

#include "CObject.h"
#include "CPickup.h"
#include "CPlayer.h"
#include "CVehicle.h"

// Yet another fugly list.
void ClientMessage( CPlayer player, ARGB colour, const SQChar* message );
void ClientMessageToAll( ARGB colour, const SQChar* message );
void GameMessage( CPlayer player, int type, const SQChar* message );

void SetServerName( const SQChar* message );
void SetMaxPlayers( int newMaxPlayers );
void SetServerPassword( const SQChar* password );
void SetGameModeText( const SQChar* gamemodeName );
void SetTimeRate( unsigned int timeRate );
void SetHour( int hour );
void SetMinute( int minute );
void SetTime( int hour, int minute );
void SetWeather( int weather );
void SetGravity( float gravity );
void SetGamespeed( float speed );
void SetWaterLevel( float waterLevel );
void SetMaxHeight( float maxHeight );

SQChar * GetServerName();
int GetMaxPlayers();
SQChar * GetServerPassword();
SQChar * GetGameModeText();
unsigned int GetTimeRate();
int GetHour();
int GetMinute();
int GetWeather();
float GetGravity();
float GetGamespeed();
float GetWaterLevel();
float GetMaxHeight();

void ToggleSyncFrameLimiter( bool toggle );
void ToggleFrameLimiter( bool toggle );
void ToggleTaxiBoostJump( bool toggle );
void ToggleDriveOnWater( bool toggle );
void ToggleFastSwitch( bool toggle );
void ToggleFriendlyFire( bool toggle );
void ToggleDisableDriveby( bool toggle );
void TogglePerfectHandling( bool toggle );
void ToggleFlyingCars( bool toggle );
void ToggleJumpSwitch( bool toggle );
void ToggleShowOnRadar( bool toggle );
void ToggleStuntBike( bool toggle );
void ToggleShootInAir( bool toggle );
void ToggleShowNametags( bool toggle );
void ToggleJoinMessages( bool toggle );
void ToggleDeathMessages( bool toggle );

bool EnabledSyncFrameLimiter();
bool EnabledFrameLimiter();
bool EnabledTaxiBoostJump();
bool EnabledDriveOnWater();
bool EnabledFastSwitch();
bool EnabledFriendlyFire();
bool EnabledDisableDriveby();
bool EnabledPerfectHandling();
bool EnabledFlyingCars();
bool EnabledJumpSwitch();
bool EnabledShowOnRadar();
bool EnabledStuntBike();
bool EnabledShootInAir();
bool EnabledShowNametags();
bool EnabledJoinMessages();
bool EnabledDeathMessages();

void CreateExplosion( int world, int type, Vector pos, int playerCaused, bool onGround );
void PlayGameSound( int player, int sound, Vector pos );

void SetUseClasses( bool toUse );
bool UsingClasses();
void AddClass( int team, cRGB colour, int skin, Vector spawnPos, float spawnAngle, int wep1, int ammo1, int wep2, int ammo2, int wep3, int ammo3 );

void SetSpawnPlayerPos( Vector pos );
void SetSpawnCameraPos( Vector pos );
void SetSpawnCameraLook( Vector pos );

void BanIP( const SQChar* ip );
void UnbanIP( const SQChar* ip );
bool IsIPBanned( const SQChar* ip );

int GetPlayerIDFromName( const SQChar* name );
bool IsWorldCompatibleWithPlayer( CPlayer player, int world );

CVehicle * CreateVehicle( int model, int world, Vector pos, float angle, int col1, int col2 );
CPickup * CreatePickup( int model, int world, int quantity, Vector pos, int alpha, bool isAuto );
CObject * CreateObject( int model, int world, Vector pos, int alpha );

CPickup * FindPickup( int id );
CPlayer * FindPlayer( int id );
CObject * FindObject( int id );
CVehicle * FindVehicle( int id );

void SetWorldBounds( float maxX, float minX, float maxY, float minY );
Bounds GetWorldBounds();

void SetWastedSettings( int deathTime, int fadeTime, float fadeInSpeed, float fadeOutSpeed, cRGB colour, int corpseFadeDelay, int corpseFadeTime );
WastedSettings GetWastedSettings();

void HideMapObject( int nModelId, float x, float y, float z );
void ShowMapObject( int nModelId, float x, float y, float z );
void ShowAllMapObjects();
void ForceAllSelect();

void ResetAllVehicleHandling();
bool IsHandlingRuleSet( int model, int rule );
void SetHandlingRule( int model, int rule, float value );
float GetHandlingRule( int model, int rule );
void ResetHandlingRule( int model, int rule );
void ResetVehicleHandling( int model );