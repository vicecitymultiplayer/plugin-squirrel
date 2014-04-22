#include "main.h"
#include <time.h>
#include "VCMP.h"
#include "CallbackHandler.h"

#include "CObject.h"
#include "CPickup.h"
#include "CPlayer.h"
#include "CTimer.h"
#include "CVehicle.h"
#include "CSprite.h"
#include "CTextdraw.h"

#pragma once

// Yet another fugly list.
void ClientMessage               ( const SQChar * message, CPlayer * player, int r, int g, int b );
void ClientMessageWithAlpha      ( const SQChar * message, CPlayer * player, int r, int g, int b, int a );
void ClientMessageToAll          ( const SQChar* message, int r, int g, int b );
void ClientMessageToAllWithAlpha ( const SQChar* message, int r, int g, int b, int a );
void GameMessage                 ( CPlayer * player, const SQChar* message, int type = 0 );
void GameMessageToAll            ( const SQChar * message, int type = 0 );

void SetServerName      ( const SQChar* message );
void SetMaxPlayers      ( int newMaxPlayers );
void SetServerPassword  ( const SQChar* password );
void SetGameModeText    ( const SQChar* gamemodeName );
void SetTimeRate        ( unsigned int timeRate );
void SetHour            ( int hour );
void SetMinute          ( int minute );
void SetTime            ( int hour, int minute );
void SetWeather         ( int weather );
void SetGravity         ( float gravity );
void SetGamespeed       ( float speed );
void SetWaterLevel      ( float waterLevel );
void SetMaxHeight       ( float maxHeight );
void SetKillDelay       ( int delay );

const SQChar * GetServerName     ( void );
int      GetMaxPlayers     ( void );
const SQChar * GetServerPassword ( void );
const SQChar * GetGameModeText   ( void );
unsigned int GetTimeRate   ( void );

int   GetHour       ( void );
int   GetMinute     ( void );
int   GetWeather    ( void );
float GetGravity    ( void );
float GetGamespeed  ( void );
float GetWaterLevel ( void );
float GetMaxHeight  ( void );
int   GetKillDelay  ( void );

void ToggleSyncFrameLimiter ( bool toggle );
void ToggleFrameLimiter     ( bool toggle );
void ToggleTaxiBoostJump    ( bool toggle );
void ToggleDriveOnWater     ( bool toggle );
void ToggleFastSwitch       ( bool toggle );
void ToggleFriendlyFire     ( bool toggle );
void ToggleDisableDriveby   ( bool toggle );
void TogglePerfectHandling  ( bool toggle );
void ToggleFlyingCars       ( bool toggle );
void ToggleJumpSwitch       ( bool toggle );
void ToggleShowOnRadar      ( bool toggle );
void ToggleStuntBike        ( bool toggle );
void ToggleShootInAir       ( bool toggle );
void ToggleShowNametags     ( bool toggle );
void ToggleJoinMessages     ( bool toggle );
void ToggleDeathMessages    ( bool toggle );
void ToggleChatTagDefault   ( bool toggle );

bool EnabledSyncFrameLimiter ( void );
bool EnabledFrameLimiter     ( void );
bool EnabledTaxiBoostJump    ( void );
bool EnabledDriveOnWater     ( void );
bool EnabledFastSwitch       ( void );
bool EnabledFriendlyFire     ( void );
bool EnabledDisableDriveby   ( void );
bool EnabledPerfectHandling  ( void );
bool EnabledFlyingCars       ( void );
bool EnabledJumpSwitch       ( void );
bool EnabledShowOnRadar      ( void );
bool EnabledStuntBike        ( void );
bool EnabledShootInAir       ( void );
bool EnabledShowNametags     ( void );
bool EnabledJoinMessages     ( void );
bool EnabledDeathMessages    ( void );
bool EnabledChatTagDefault   ( void );

int CreateBlip( int world, Vector * pos, int scale, RGBa color, int nSpriteId );
void DestroyBlip( int blipID );

int CreateRadioStream(const char * radioName, const char * radioURL, bool bCanSelect);
void CreateRadioStreamWithID(int radioID, const char * radioName, const char * radioURL, bool bCanSelect);
void DestroyRadioStream( int radioID );

void CreateExplosion ( int world, int type, Vector * pos, int playerCaused, bool onGround );
void CreateExplosionExpanded( int world, int type, float x, float y, float z, int playerCaused, bool onGround );

void PlayGameSound   ( int player, int sound, Vector * pos );
void PlayGameSoundExpanded( int player, int sound, float x, float y, float z );

void SetUseClasses ( bool toUse );
bool UsingClasses  ( void );
void AddClass      ( int team,
                     cRGB * colour,
                     int skin,
                     Vector * spawnPos,
                     float spawnAngle,
                     int wep1,
                     int ammo1,
                     int wep2,
                     int ammo2,
                     int wep3,
                     int ammo3 );

/*void AddClassExpanded ( int team,
					 int r,
					 int g,
					 int b,
					 int skin,
					 float x,
					 float y,
					 float z,
					 float spawnAngle,
					 int wep1,
					 int ammo1,
					 int wep2,
					 int ammo2,
					 int wep3,
					 int ammo3 );*/

void SetSpawnPlayerPos  ( Vector * pos );
void SetSpawnCameraPos  ( Vector * pos );
void SetSpawnCameraLook ( Vector * pos );

void SetSpawnPlayerPosExpanded  ( float x, float y, float z );
void SetSpawnCameraPosExpanded  ( float x, float y, float z );
void SetSpawnCameraLookExpanded ( float x, float y, float z );

void BanIP      ( const SQChar* ip );
void UnbanIP    ( const SQChar* ip );
bool IsIPBanned ( const SQChar* ip );

int GetPlayerIDFromName          ( const SQChar* name );
bool IsWorldCompatibleWithPlayer ( CPlayer * player, int world );

CVehicle * CreateVehicle ( int model, int world, Vector * pos, float angle, int col1, int col2 );
CPickup * CreatePickup   ( int model, int world, int quantity, Vector * pos, int alpha, bool isAuto );
CObject * CreateObject   ( int model, int world, Vector * pos, int alpha );
CSprite * CreateSprite   ( const SQChar * filename, uint16_t x, uint16_t y, uint16_t rX, uint16_t rY, float rot, uint16_t alpha );
CTextdraw * CreateTextdraw ( const SQChar * text, int x, int y, unsigned int colour );

CVehicle * CreateVehicleExpanded ( int model, int world, float x, float y, float z, float angle, int col1, int col2 );
CPickup * CreatePickupExpanded   ( int model, int world, int quantity, float x, float y, float z, int alpha, bool isAuto );
CObject * CreateObjectExpanded   ( int model, int world, float x, float y, float z, int alpha );

CPickup * FindPickup   ( int id );
CObject * FindObject   ( int id );
CVehicle * FindVehicle ( int id );

void SetWorldBounds   ( float maxX, float minX, float maxY, float minY );
Bounds GetWorldBounds ( void );

void SetWastedSettings           ( int deathTime, int fadeTime, float fadeInSpeed, float fadeOutSpeed, cRGB colour, int corpseFadeDelay, int corpseFadeTime );
WastedSettings GetWastedSettings ( void );

void RawHideMapObject  ( int nModelId, int x, int y, int z );
void HideMapObject     ( int nModelId, float x, float y, float z );
void ShowMapObject     ( int nModelId, float x, float y, float z );
void ShowAllMapObjects ( void );
void ForceAllSelect    ( void );

void ResetAllVehicleHandling ( void );
bool IsHandlingRuleSet       ( int model, int rule );
void SetHandlingRule         ( int model, int rule, float value );
double GetHandlingRule       ( int model, int rule );
void ResetHandlingRule       ( int model, int rule );
void ResetVehicleHandling    ( int model );

bool SetWeaponDataValue   ( int weaponID, int fieldID, double value );
double GetWeaponDataValue ( int weaponID, int fieldID );
bool ResetWeaponDataValue ( int weaponID, int fieldID );
bool IsWeaponDataModified ( int weaponID, int fieldID );
bool ResetWeaponData      ( int weaponID );
bool ResetAllWeaponData   ( void );

int BindKey( bool onKeyDown, int key1, int key2 = 0, int key3 = 0 );
bool RemoveKeybind( int nKeybindId );
void RemoveAllKeybinds( void );

// All of these functions exist for compatibility
bool GetCinematicBorder ( CPlayer * player );
bool GetGreenScanLines  ( CPlayer * player );
bool GetWhiteScanLines  ( CPlayer * player );
void SetCinematicBorder ( CPlayer * player, bool toEnable );
void SetGreenScanLines  ( CPlayer * player, bool toEnable );
void SetWhiteScanLines  ( CPlayer * player, bool toEnable );
void KickPlayer         ( CPlayer * player );
void BanPlayer          ( CPlayer * player );
void Message            ( const SQChar * message );
void MessagePlayer      ( const SQChar * message, CPlayer * player );
void MessageAllExcept   ( const SQChar * message, CPlayer * player );
void PrivMessage        ( CPlayer * player, const SQChar * message );
void PrivMessageAll     ( const SQChar * message );
void SendPlayerMessage  ( CPlayer * playerToFake, CPlayer * playerTo, const SQChar * message );

const SQChar * GetWeaponName   ( int weaponID );
const SQChar * GetDistrictName ( float x, float y );
const SQChar * GetSkinName     ( int skinID );
int      GetWeaponID     ( const SQChar * name );
DWORD    SQGetTickCount  ( void );

float DistanceFromPoint ( float x1, float y1, float x2, float y2 );
void ReloadScripts      ( void );

int GetVehicleModelFromName ( SQChar * name );
const SQChar * GetVehicleNameFromModel ( int model );
void LoadVCMPModule( const SQChar * name );

SQInteger FindPlayer( HSQUIRRELVM v );
SQInteger InPoly( HSQUIRRELVM v );
SQInteger NewTimer( HSQUIRRELVM v );

// These functions are for compatibility, but will be deprecated
DWORD    GetTime         ( void );
const SQChar * GetFullTime     ( void );