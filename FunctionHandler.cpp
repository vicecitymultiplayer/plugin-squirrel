#include "FunctionHandler.h"
#include "Functions.h"
#include "ConsoleUtils.h"
#include "CCore.h"
#include "main.h"
#include "SQModule.h"

#include <string.h>
#include <ctype.h>
#include <stdlib.h>

inline void szlower( char * string )
{
	int i;
	for( i = 0; string[i]; i++ )
		string[i] = tolower( string[i] );
}

// Tha core
extern CCore * pCore;

void ShutdownServer(void) { functions->ShutdownServer(); }
void ClientMessage(const SQChar * message, CPlayer * player, int r, int g, int b)
{
	ClientMessageWithAlpha(message, player, r, g, b, 255);
}

void ClientMessageWithAlpha(const SQChar * message, CPlayer * player, int r, int g, int b, int a)
{
	if (player != NULL)
	{
		RGBa colour(r, g, b, a);
		functions->SendClientMessage(player->nPlayerId, colour.toUInt(), "%s", message);
	}
}

void ClientMessageToAll(const SQChar* message, int r, int g, int b)
{
	ClientMessageToAllWithAlpha(message, r, g, b, 255);
}

void ClientMessageToAllWithAlpha(const SQChar* message, int r, int g, int b, int a)
{
	for (int i = 0; i < functions->GetMaxPlayers(); i++)
	{
		if (functions->IsPlayerConnected(i))
			ClientMessageWithAlpha(message, pCore->RetrievePlayer(i), r, g, b, a);
	}
}

void GameMessage   ( const SQChar* message, CPlayer * player, int type )
{
	if( player != NULL )
		functions->SendGameMessage( player->nPlayerId, type, const_cast<char *>( message ) );
}

void GameMessageAlternate(const SQChar * message, CPlayer * player)
{
	if (player != NULL)
		functions->SendGameMessage(player->nPlayerId, 1, const_cast<char *>(message));
}

void GameMessageToAll( const SQChar * message, int type )
{
	functions->SendGameMessage( -1, type, const_cast<char *>( message ) );
}

void GameMessageToAllAlternate(const SQChar * message)
{
	functions->SendGameMessage(-1, 1, const_cast<char *>(message));
}

void SetServerName ( const SQChar* message )       { functions->SetServerName( const_cast<char *>( message ) ); }

void SetMaxPlayers( int newMaxPlayers )            { functions->SetMaxPlayers( newMaxPlayers ); }
void SetServerPassword( const SQChar* password )   { functions->SetServerPassword( const_cast<char *>( password ) ); }
void SetGameModeText( const SQChar* gamemodeName ) { functions->SetGameModeText( const_cast<char *>( gamemodeName ) ); }

void SetTimeRate( unsigned int timeRate ) { functions->SetTimeRate( timeRate ); }
void SetHour( int hour )                  { functions->SetHour( hour ); }
void SetMinute( int minute )              { functions->SetMinute( minute ); }
void SetTime( int hour, int minute )      { SetHour(hour); SetMinute(minute); }
void SetWeather( int weather )            { functions->SetWeather( weather ); }
void SetGravity( float gravity )          { functions->SetGravity( gravity ); }
void SetGamespeed( float speed )          { functions->SetGamespeed( speed ); }
void SetWaterLevel( float waterLevel )    { functions->SetWaterLevel( waterLevel ); }
void SetMaxHeight( float maxHeight )      { functions->SetMaxHeight( maxHeight ); }

const SQChar * GetServerName()
{
	// We cannot guarantee that Squirrel will free serverName once it
	//     is done with it. This could cause a memory leak every time
	//     such a function is called. However, we can't just return a
	//     char array, because it will be undefined once out of scope.
	//
	//     Thus, we try to prevent such an issue by using this static
	//     char array hack.
	static char serverName[128];
	functions->GetServerName( serverName, 128 );

	return serverName;
}

int GetMaxPlayers() { return functions->GetMaxPlayers(); }

const SQChar * GetServerPassword()
{
	static char password[128];
	functions->GetServerPassword( password, 128 );

	return password;
}

const SQChar * GetGameModeText()
{
	static char gamemode[96];
	functions->GetGameModeText( gamemode, 96 );

	return gamemode;
}

unsigned int GetTimeRate()   { return ( functions->GetTimeRate() );   }
int          GetHour()       { return ( functions->GetHour() );       }
int          GetMinute()     { return ( functions->GetMinute() );     }
int          GetWeather()    { return ( functions->GetWeather() );    }
float        GetGravity()    { return ( functions->GetGravity() );    }
float        GetGamespeed()  { return ( functions->GetGamespeed() );  }
float        GetWaterLevel() { return ( functions->GetWaterLevel() ); }
float        GetMaxHeight()  { return ( functions->GetMaxHeight() );  }

void ToggleSyncFrameLimiter ( bool toggle ) { functions->ToggleSyncFrameLimiter( ( toggle ? 1 : 0 ) ); }
void ToggleFrameLimiter     ( bool toggle ) { functions->ToggleFrameLimiter( ( toggle ? 1 : 0 ) );     }
void ToggleTaxiBoostJump    ( bool toggle ) { functions->ToggleTaxiBoostJump( ( toggle ? 1 : 0 ) );    }
void ToggleDriveOnWater     ( bool toggle ) { functions->ToggleDriveOnWater( ( toggle ? 1 : 0 ) );     }
void ToggleFastSwitch       ( bool toggle ) { functions->ToggleFastSwitch( ( toggle ? 1 : 0 ) );       }
void ToggleFriendlyFire     ( bool toggle ) { functions->ToggleFriendlyFire( ( toggle ? 1 : 0 ) );     }
void ToggleDisableDriveby   ( bool toggle ) { functions->ToggleDisableDriveby( ( toggle ? 0 : 1 ) );   }
void TogglePerfectHandling  ( bool toggle ) { functions->TogglePerfectHandling( ( toggle ? 1 : 0 ) );  }
void ToggleFlyingCars       ( bool toggle ) { functions->ToggleFlyingCars( ( toggle ? 1 : 0 ) );       }
void ToggleJumpSwitch       ( bool toggle ) { functions->ToggleJumpSwitch( ( toggle ? 1 : 0 ) );       }
void ToggleShowOnRadar      ( bool toggle ) { functions->ToggleShowMarkers( ( toggle ? 1 : 0 ) );      }
void ToggleStuntBike        ( bool toggle ) { functions->ToggleStuntBike( ( toggle ? 1 : 0 ) );        }
void ToggleShootInAir       ( bool toggle ) { functions->ToggleShootInAir( ( toggle ? 1 : 0 ) );       }
void ToggleShowNametags     ( bool toggle ) { functions->ToggleShowNametags( ( toggle ? 1 : 0 ) );     }
void ToggleJoinMessages     ( bool toggle ) { functions->ToggleJoinMessages( ( toggle ? 1 : 0 ) );     }
void ToggleDeathMessages    ( bool toggle ) { functions->ToggleDeathMessages( ( toggle ? 1 : 0 ) );    }
void ToggleChatTagDefault   ( bool toggle ) { functions->ToggleChatTagsByDefaultEnabled( ( toggle ? 1 : 0 ) ); }
void ToggleShowOnlyTeamMarkers(bool toggle) { functions->ToggleOnlyShowTeamMarkers(toggle); }
void ToggleWallglitch       ( bool toggle ) { functions->ToggleWallglitch(toggle); }

bool EnabledSyncFrameLimiter() { return ( functions->EnabledSyncFrameLimiter() != 0 );  }
bool EnabledFrameLimiter()     { return ( functions->EnabledFrameLimiter() != 0 );      }
bool EnabledTaxiBoostJump()    { return ( functions->EnabledTaxiBoostJump() != 0 );     }
bool EnabledDriveOnWater()     { return ( functions->EnabledDriveOnWater() != 0 );      }
bool EnabledFastSwitch()       { return ( functions->EnabledFastSwitch() != 0 );        }
bool EnabledFriendlyFire()     { return ( functions->EnabledFriendlyFire() != 0 );      }
bool EnabledDisableDriveby()   { return ( functions->EnabledDisableDriveby() != 0 );    }
bool EnabledPerfectHandling()  { return ( functions->EnabledPerfectHandling() != 0 );   }
bool EnabledFlyingCars()       { return ( functions->EnabledFlyingCars() != 0 );        }
bool EnabledJumpSwitch()       { return ( functions->EnabledJumpSwitch() != 0 );        }
bool EnabledShowOnRadar()      { return ( functions->EnabledShowMarkers() != 0 );       }
bool EnabledStuntBike()        { return ( functions->EnabledStuntBike() != 0 );         }
bool EnabledShootInAir()       { return ( functions->EnabledShootInAir() != 0 );        }
bool EnabledShowNametags()     { return ( functions->EnabledShowNametags() != 0 );      }
bool EnabledJoinMessages()     { return ( functions->EnabledJoinMessages() != 0 );      }
bool EnabledDeathMessages()    { return ( functions->EnabledDeathMessages() != 0 );     }
bool EnabledChatTagDefault()   { return ( functions->EnabledChatTagsByDefault() != 0 ); }
bool EnabledShowOnlyTeamMarkers() { return functions->EnabledOnlyShowTeamMarkers() != 0; }
bool EnabledWallglitch()       { return functions->EnabledWallglitch() != 0;            }

void CreateExplosion( int world, int type, Vector * pos, int playerCaused, bool onGround )
{
	functions->CreateExplosion( world, type, pos->x, pos->y, pos->z, playerCaused, onGround );
}

void CreateExplosionExpanded( int world, int type, float x, float y, float z, int playerCaused, bool onGround )
{
	Vector pos = Vector( x, y, z );
	CreateExplosion( world, type, &pos, playerCaused, onGround );
}

void PlayGameSound ( int world, int sound, Vector * pos ) { functions->PlaySound( world, sound, pos->x, pos->y, pos->z ); }
void PlayGameSoundForPlayer(CPlayer* pPlayer, int sound) {
	functions->PlaySound(pPlayer->GetUniqueWorld(), sound, NAN, NAN, NAN);
}

void PlayGameSoundForWorld(int world, int sound) {
	functions->PlaySound(world, sound, NAN, NAN, NAN);
}

void PlayGameSoundExpanded( int world, int sound, float x, float y, float z )
{
	Vector pos = Vector( x, y, z );
	PlayGameSound( world, sound, &pos );
}

void SetUseClasses ( bool toUse )                         { functions->SetUseClasses( toUse ); }
bool UsingClasses  ()                                     { return ( functions->GetUseClasses() != 0 ); }

void AddClass( int team, cRGB * colour, int skin, Vector * spawnPos, float spawnAngle, int wep1, int ammo1, int wep2, int ammo2, int wep3, int ammo3 )
{
	functions->AddPlayerClass( team, colour->toUInt(), skin, spawnPos->x, spawnPos->y, spawnPos->z, spawnAngle, wep1, ammo1, wep2, ammo2, wep3, ammo3 );
}

void AddClassExpanded ( int team, int r, int g, int b, int skin, float x, float y, float z, float spawnAngle, int wep1, int ammo1, int wep2, int ammo2, int wep3, int ammo3 )
{
	cRGB col = cRGB( r, g, b );
	Vector spawn = Vector( x, y, z );

	AddClass( team, &col, skin, &spawn, spawnAngle, wep1, ammo1, wep2, ammo2, wep3, ammo3 );
}

void SetSpawnPlayerPos( Vector * pos )  { functions->SetSpawnPlayerPos( pos->x, pos->y, pos->z ); }
void SetSpawnCameraPos( Vector * pos )  { functions->SetSpawnCameraPos( pos->x, pos->y, pos->z ); }
void SetSpawnCameraLook( Vector * pos ) { functions->SetSpawnCameraLookAt( pos->x, pos->y, pos->z ); }

void SetSpawnPlayerPosExpanded  ( float x, float y, float z ) { Vector p = Vector( x, y, z ); SetSpawnPlayerPos( &p ); }
void SetSpawnCameraPosExpanded  ( float x, float y, float z ) { Vector p = Vector( x, y, z ); SetSpawnCameraPos( &p ); }
void SetSpawnCameraLookExpanded ( float x, float y, float z ) { Vector p = Vector( x, y, z ); SetSpawnCameraLook( &p ); }

void BanIP( const SQChar* ip )      { functions->BanIP( const_cast<char *>( ip ) ); }
void UnbanIP( const SQChar* ip )    { functions->UnbanIP( const_cast<char *>( ip ) ); }
bool IsIPBanned( const SQChar* ip ) { return ( functions->IsIPBanned( const_cast<char *>( ip ) ) != 0 ); }

bool IsWorldCompatibleWithPlayer( CPlayer * cPlayer, int world )
{
	if( cPlayer != NULL )
		return ( functions->IsPlayerWorldCompatible( cPlayer->nPlayerId, world ) != 0 );

	return false;
}

int  GetPlayerIDFromName( const SQChar* name ) { return functions->GetPlayerIDFromName( const_cast<char *>( name ) ); }

CVehicle * CreateVehicle( int model, int world, Vector * pos, float angle, int col1, int col2 )
{
	int vId = functions->CreateVehicle( model, world, pos->x, pos->y, pos->z, angle, col1, col2 );
	if (vId < 1)
		return NULL;
	else
		return pCore->AllocateVehicle(vId);
}

CPickup * CreatePickup( int model, int world, int quantity, Vector * pos, int alpha, bool isAuto )
{
	int pId = functions->CreatePickup(model, world, quantity, pos->x, pos->y, pos->z, alpha, isAuto);
	if (pId < 0)
		return NULL;
	else
		return pCore->AllocatePickup(pId);
}

CPickup * CreatePickupCompat(int model, Vector * pos)
{
	int pId = functions->CreatePickup(model, 1, 0, pos->x, pos->y, pos->z, 255, 0);
	if (pId < 0)
		return NULL;
	else
		return pCore->AllocatePickup(pId);
}

CVehicle * CreateVehicleCompat(int model, Vector * pos, float angle, int col1, int col2)
{
	int vId = functions->CreateVehicle(model, 1, pos->x, pos->y, pos->z, angle, col1, col2);
	if (vId < 1)
		return NULL;
	else
		return pCore->AllocateVehicle(vId);
}

CObject * CreateObject( int model, int world, Vector * pos, int alpha )
{
	int oId = functions->CreateObject( model, world, pos->x, pos->y, pos->z, alpha );
	if (oId < 0)
		return NULL;
	else
		return pCore->AllocateObject(oId);
}

CSprite * CreateSprite(const SQChar * filename, uint16_t x, uint16_t y, uint16_t rX, uint16_t rY, float rot, uint16_t alpha)
{
	int sId = functions->CreateSprite(-1, filename, x, y, rX, rY, rot, alpha, 0);
	if (sId < 0)
		return NULL;
	else
	{
		CSprite * pSprite = new CSprite();
		pSprite->nSpriteId = sId;

		return pSprite;
	}
}

CTextdraw * CreateTextdraw(const SQChar * text, int x, int y, unsigned int colour)
{
	int sId = functions->CreateTextdraw(-1, text, x, y, colour, 0);
	if (sId < 0)
		return NULL;
	else
	{
		CTextdraw * pTextdraw = new CTextdraw();
		pTextdraw->nTextdrawId = sId;

		return pTextdraw;
	}
}

CCheckpoint * CreateCheckpoint(CPlayer* pPlayer, int world, Vector * pos, ARGB * color, float radius)
{
	if (!pos || !color) {
		return NULL;
	}

	int id = (pPlayer ? pPlayer->GetID() : 255);

	int cId = functions->CreateCheckpoint(id, world, pos->x, pos->y, pos->z, color->r, color->g, color->b, color->a, radius);
	if (cId < 0)
		return NULL;
	else {
		CCheckpoint * pCheckpoint = pCore->AllocateCheckpoint(cId);
		pCheckpoint->nOwnerId = id;

		return pCheckpoint;
	}
}

CSphere * CreateSphere(CPlayer* pPlayer, int world, Vector * pos, cRGB * color, float radius)
{
	if (!pos || !color) {
		return NULL;
	}

	int id = (pPlayer ? pPlayer->GetID() : 255);

	int cId = functions->CreateSphere(id, world, pos->x, pos->y, pos->z, color->r, color->g, color->b, radius);
	if (cId < 0)
		return NULL;
	else {
		CSphere * pSphere = pCore->AllocateSphere(cId);
		pSphere->nOwnerId = id;

		return pSphere;
	}
}

CVehicle * CreateVehicleExpanded( int model, int world, float x, float y, float z, float angle, int col1, int col2 )
{
	Vector pos = Vector( x, y, z );
	return CreateVehicle( model, world, &pos, angle, col1, col2 );
}

CPickup * CreatePickupExpanded( int model, int world, int quantity, float x, float y, float z, int alpha, bool isAuto )
{
	Vector pos = Vector( x, y, z );
	return CreatePickup( model, world, quantity, &pos, alpha, isAuto );
}

CObject * CreateObjectExpanded( int model, int world, float x, float y, float z, int alpha )
{
	Vector pos = Vector( x, y, z );
	return CreateObject( model, world, &pos, alpha );
}

CPickup * FindPickup(int id) { return pCore->RetrievePickup(id); }
CObject * FindObject(int id) { return pCore->RetrieveObject(id); }
CVehicle * FindVehicle(int id) { return pCore->RetrieveVehicle(id); }
CCheckpoint * FindCheckpoint(int id) { return pCore->RetrieveCheckpoint(id); }
CSphere * FindSphere(int id) { return pCore->RetrieveSphere(id); }

void SetWorldBounds( float maxX, float minX, float maxY, float minY )
{
	functions->SetWorldBounds( maxX, minX, maxY, minY );
}

Bounds GetWorldBounds()
{
	float maxX, minX, maxY, minY;
	functions->GetWorldBounds( &maxX, &minX, &maxY, &minY );

	return Bounds( maxX, minX, maxY, minY );
}

void SetWastedSettings( int deathTime, int fadeTime, float fadeInSpeed, float fadeOutSpeed, cRGB colour, int corpseFadeDelay, int corpseFadeTime )
{
	unsigned int rDeathTime, rFadeTime, rCorpseFadeDelay, rCorpseFadeTime;

	rDeathTime       = static_cast<unsigned int>(deathTime);
	rFadeTime        = static_cast<unsigned int>(fadeTime);
	rCorpseFadeDelay = static_cast<unsigned int>(corpseFadeDelay);
	rCorpseFadeTime  = static_cast<unsigned int>(corpseFadeTime);

	functions->SetWastedSettings
	(
		rDeathTime,
		rFadeTime,
		fadeInSpeed,
		fadeOutSpeed,
		colour.toUInt(),
		rCorpseFadeDelay,
		rCorpseFadeTime
	);
}

WastedSettings GetWastedSettings()
{
	unsigned int deathTime, fadeTime, corpseFadeDelay, corpseFadeTime, dwColour;
	float fadeInSpeed, fadeOutSpeed;

	functions->GetWastedSettings
	(
		&deathTime,
		&fadeTime,
		&fadeInSpeed,
		&fadeOutSpeed,
		&dwColour,
		&corpseFadeDelay,
		&corpseFadeTime
	);

	int rDeathTime, rFadeTime, rCorpseFadeDelay, rCorpseFadeTime;
	cRGB rColour;

	rDeathTime       = static_cast<int>(deathTime);
	rFadeTime        = static_cast<int>(fadeTime);
	rCorpseFadeDelay = static_cast<int>(corpseFadeDelay);
	rCorpseFadeTime  = static_cast<int>(corpseFadeTime);

	rColour.r = (dwColour >> 16) & 255;
	rColour.g = (dwColour >> 8) & 255;
	rColour.b = dwColour & 255;

	return WastedSettings
	(
		rDeathTime,
		rFadeTime,
		fadeInSpeed,
		fadeOutSpeed,
		rColour,
		rCorpseFadeDelay,
		rCorpseFadeTime
	);
}

void RawHideMapObject( int nModelId, int x, int y, int z )
{
	functions->HideMapObject( nModelId, x, y, z );
}

void HideMapObject( int nModelId, float x, float y, float z )
{
	int x2 = (int)(floor( x * 10.0f ) + 0.5f);
	int y2 = (int)(floor( y * 10.0f ) + 0.5f);
	int z2 = (int)(floor( z * 10.0f ) + 0.5f);

	functions->HideMapObject( nModelId, x2, y2, z2 );
}

void ShowMapObject( int nModelId, float x, float y, float z )
{
	int x2 = (int)(floor( x * 10.0f ) + 0.5f);
	int y2 = (int)(floor( y * 10.0f ) + 0.5f);
	int z2 = (int)(floor( z * 10.0f ) + 0.5f);

	functions->ShowMapObject( nModelId, x2, y2, z2 );
}

void ShowAllMapObjects() { functions->ShowAllMapObjects(); }
void ForceAllSelect() { functions->ForceAllSelect(); }

void ResetAllVehicleHandling() { functions->ResetAllVehicleHandlings(); }
bool IsHandlingRuleSet( int model, int rule ) { return ( functions->ExistsHandlingRule( model, rule ) != 0 ); }
void SetHandlingRule( int model, int rule, float value ) { functions->SetHandlingRule( model, rule, value ); }
double GetHandlingRule( int model, int rule ) { return functions->GetHandlingRule( model, rule ); }
void ResetHandlingRule( int model, int rule ) { functions->ResetHandlingRule( model, rule ); }
void ResetVehicleHandling( int model ) { functions->ResetHandling( model ); }

// All of these functions exist for compatibility
bool GetCinematicBorder ( CPlayer * player )
{
	if( player != NULL )
		return ( functions->EnabledPlayerWidescreen( player->nPlayerId ) != 0 );

	return false;
}

bool GetGreenScanLines  ( CPlayer * player )
{
	if( player != NULL )
		return ( functions->EnabledPlayerGreenScanlines( player->nPlayerId ) != 0 );

	return false;
}

bool GetWhiteScanLines  ( CPlayer * player )
{
	if( player != NULL )
		return ( functions->EnabledPlayerWhiteScanlines( player->nPlayerId ) != 0 );

	return false;
}

void SetCinematicBorder ( CPlayer * player, bool toEnable )
{
	if( player != NULL )
		functions->TogglePlayerWidescreen( player->nPlayerId, toEnable );
}

void SetGreenScanLines  ( CPlayer * player, bool toEnable )
{
	if( player != NULL )
		functions->TogglePlayerGreenScanlines( player->nPlayerId, toEnable );
}

void SetWhiteScanLines  ( CPlayer * player, bool toEnable )
{
	if( player != NULL )
		functions->TogglePlayerWhiteScanlines( player->nPlayerId, toEnable );
}

void KickPlayer         ( CPlayer * player )
{
	if( player != NULL )
		functions->KickPlayer( player->nPlayerId );
}

void BanPlayer          ( CPlayer * player )
{
	if( player != NULL )
		functions->BanPlayer( player->nPlayerId );
}

void Message            ( const SQChar * message ) { functions->SendClientMessage( -1, 0x0b5fa5ff, "%s", message ); }
void MessagePlayer      ( const SQChar * message, CPlayer * player )
{
	if( player != NULL )
		functions->SendClientMessage( player->nPlayerId, 0x0b5fa5ff, "%s", message );
}

void MessageAllExcept   ( const SQChar * message, CPlayer * player )
{
	if( player != NULL )
	{
		for( int i = 0; i < MAX_PLAYERS; i++ )
		{
			if( functions->IsPlayerConnected( i ) && i != player->GetID() )
				functions->SendClientMessage( i, 0x0b5fa5ff, "%s", message );
		}
	}
}

void PrivMessage        ( CPlayer * player, const SQChar * message )
{
	if( player != NULL )
		functions->SendClientMessage( player->nPlayerId, 0x007f16ff, "** pm >> %s", message );
}

void PrivMessageAll     ( const SQChar * message )
{
	for( int i = 0; i < MAX_PLAYERS; i++ )
	{
		if( functions->IsPlayerConnected( i ) )
			functions->SendClientMessage( i, 0x007f16ff, "** pm >> %s", message );
	}
}

void SendPlayerMessage  ( CPlayer * playerToFake, CPlayer * playerTo, const SQChar * message )
{
	if( playerToFake != NULL && playerTo != NULL )
		functions->SendClientMessage( playerTo->nPlayerId, 0x007f16ff, "** pm from %s >> %s", playerToFake->GetName().c_str(), message );
}

void LoadVCMPModule( const SQChar * name )
{
	OutputWarning( "LoadModule() cannot be used by scripts. Specify plugins in server.cfg" );
}

DWORD SQGetTickCount( void )
{
	#ifdef WIN32
		return GetTickCount();
	#else
		struct timespec now;

		if (clock_gettime(CLOCK_MONOTONIC, &now))
			return 0;

		return now.tv_sec * 1000.0 + now.tv_nsec / 1000000.0;
	#endif
}

float DistanceFromPoint( float x1, float y1, float x2, float y2 )
{
	float matrixX = pow( (x2 - x1), 2 );
	float matrixY = pow( (y2 - y1), 2 );
	float matrixF = sqrt( matrixX + matrixY );
	return matrixF;
}

// This is a crude implementation to be replaced later.
int BindKey( bool onKeyDown, int key )
{
    return BindKey( onKeyDown, key, 0 , 0 );
}

int BindKey( bool onKeyDown, int key, int key2 )
{
    return BindKey( onKeyDown, key, key2 , 0 );
}

int BindKey( bool onKeyDown, int key, int key2, int key3 )
{
    int keyslot = functions->GetKeyBindUnusedSlot();
    functions->RegisterKeyBind( keyslot, onKeyDown, key, key2, key3 );

    return keyslot;
}

bool RemoveKeybind( int nKeybindId ) { return (functions->RemoveKeyBind( nKeybindId ) ? true : false); }
void RemoveAllKeybinds( void ) { functions->RemoveAllKeyBinds(); }

void ReloadScripts( void )
{
	// Are we allowed to reload?
	if( pCore->IsReloadingAllowed() )
	{
		// Let's not reload the scripts for now
		pCore->ChangeReloadPermission(false);

		// Get rid of ALL declared timers
		pCore->DropAllTimers();

		// Clean the world up
		pCore->CleanWorld();

		// Release the old root table to free old binds
		Sqrat::RootTable(v).Release();

		// Reload the VM and all entities
		pCore->LoadVM();

		// Re-parse the config and reload the script
		pCore->LoadScript();

		// And now we dance
		OutputMessage( "Scripts reloaded." );
	}
	else
		OutputError( "The server refused to reload. Is this an infinite loop?" );
}

void SetKillDelay( int delay ) { functions->SetKillCmdDelay( delay ); }
int GetKillDelay( void ) { return functions->GetKillCmdDelay(); }

void DestroyBlip( int blipID ) { functions->DestroyCoordBlip( blipID ); }
int CreateBlip( int world, Vector * pos, int scale, RGBa color, int nSpriteId )
{
	return functions->CreateCoordBlip( -1, world, pos->x, pos->y, pos->z, scale, color.toUInt(), nSpriteId );
}

void DestroyRadioStream(int radioID) { functions->RemoveRadioStream(radioID); }
int CreateRadioStream(const char * radioName, const char * radioURL, bool bCanSelect)
{
	return functions->AddRadioStream(-1, radioName, radioURL, bCanSelect);
}
void CreateRadioStreamWithID(int streamID, const char * radioName, const char * radioURL, bool bCanSelect)
{
	functions->AddRadioStream(streamID, radioName, radioURL, bCanSelect);
}

bool SetWeaponDataValue   ( int weaponID, int fieldID, double value ) { return (functions->SetWeaponDataValue( weaponID, fieldID, value ) ? true : false); }
double GetWeaponDataValue ( int weaponID, int fieldID ) { return functions->GetWeaponDataValue( weaponID, fieldID ); }
bool ResetWeaponDataValue ( int weaponID, int fieldID ) { return (functions->ResetWeaponDataValue( weaponID, fieldID ) ? true : false); }
bool IsWeaponDataModified ( int weaponID, int fieldID ) { return (functions->IsWeaponDataValueModified( weaponID, fieldID ) ? true : false); }
bool ResetWeaponData      ( int weaponID ) { return (functions->ResetWeaponData( weaponID ) ? true : false); }
bool ResetAllWeaponData   () { return (functions->ResetAllWeaponData() ? true : false); }

bool IsNum(const SQChar * line)
{
	if (strlen(line) < 1)
		return false;

	char* p;
	strtol(line, &p, 10);
	return *p == 0;
}

int GetVehicleCount()
{
	int count = 0;
	for (int i = 0; i < MAX_VEHICLES; i++)
	if (functions->GetVehicleModel(i) > 0)
		count++;

	return count;
}

int GetPickupCount()
{
	int count = 0;
	for (int i = 0; i < MAX_PICKUPS; i++)
	if (functions->PickupGetModel(i) > 0)
		count++;

	return count;
}

int GetObjectCount()
{
	int count = 0;
	for (int i = 0; i < MAX_OBJECTS; i++)
	if (functions->GetObjectModel(i) > 0)
		count++;

	return count;
}

int GetPlayers()
{
	int count = 0;
	for (int i = 0; i < functions->GetMaxPlayers(); i++)
	if (functions->IsPlayerConnected(i))
		count++;

	return count;
}

SQInteger release_hook( SQUserPointer p, SQInteger size ) { return 1; }
SQInteger FindPlayer( HSQUIRRELVM v )
{
	if( sq_gettop( v ) >= 2 )
	{
		CPlayer * pPlayer = NULL;
		if( sq_gettype( v, 2 ) == OT_INTEGER )
		{
			SQInteger playerID;
			sq_getinteger( v, 2, &playerID );

			if (playerID < MAX_PLAYERS && playerID >= 0)
				pPlayer = pCore->RetrievePlayer(playerID);
			else
			{
				sq_pushnull( v );
				return 1;
			}
		}
		else if( sq_gettype( v, 2 ) == OT_STRING )
		{
			const char * pName;
			sq_getstring( v, 2, &pName );

			int pID = 255;
			int i;

			char * lowerName = strdup( pName );
			szlower( lowerName );

			char * nameBuf = new char[64];
			for( i = 0; i < functions->GetMaxPlayers(); i++ )
			{
				if( functions->IsPlayerConnected( i ) )
				{
					functions->GetPlayerName( i, nameBuf, 64 );
					szlower( nameBuf );

					if( strstr( nameBuf, lowerName ) != NULL )
					{
						pID = i;
						break;
					}
				}
			}

			delete [] nameBuf;
			nameBuf = NULL;
			free( lowerName );

			if (pID == 255)
			{
				sq_pushnull(v);
				return 1;
			}
			else
				pPlayer = pCore->RetrievePlayer(pID);
		}
		else
			return sq_throwerror( v, "Unexpected argument in FindPlayer: must be integer or string" );

		if( pPlayer == NULL )
		{
			sq_pushnull( v );
			return 1;
		}
		else
		{
			// Push a CPlayer instance
			Sqrat::ClassType<CPlayer>().PushInstance( v, pPlayer );
			return 1;
		}
	}
	else
		return sq_throwerror( v, "Unexpected number of parameters for FindPlayer [integer or string]" );
}

struct AreaPoints
{
	float x, y;

	AreaPoints(void) : x(0.0f), y(0.0f) {};
	AreaPoints(float fX, float fY) : x(fX), y(fY) {};
};

inline size_t Internal_NumTok(const char* szText, const char cDelimiter)
{
	if (!*szText) return 0;

	size_t iCounter = 1;
	char* p = (char*)szText;

	if (*p == cDelimiter)
		iCounter = 0;

	while (*p)
	{
		if (*p == cDelimiter)
		{
			if ((*++p) && (*p != cDelimiter)) iCounter++;
		}
		else *p++;
	}

	return iCounter;
}

inline bool Internal_InPoly(float fX, float fY,
	const unsigned int uiPoints, const AreaPoints fPoints[])
{
	// http://sidvind.com/wiki/Point-in-polygon:_Jordan_Curve_Theorem

	// The points creating the polygon
	float x1, x2;

	// How many times the ray crosses a line segment
	int crossings = 0;

	// Iterate through each line
	for (unsigned int i = 0; i < uiPoints; i++)
	{
		// This is done to ensure that we get the same result when
		// the line goes from left to right and right to left.
		if (fPoints[i].x < fPoints[(i + 1) % uiPoints].x)
		{
			x1 = fPoints[i].x;
			x2 = fPoints[(i + 1) % uiPoints].x;
		}
		else
		{
			x1 = fPoints[(i + 1) % uiPoints].x;
			x2 = fPoints[i].x;
		}

		// First check if the ray is able to cross the line
		if (fX > x1 && fX <= x2 && (fY < fPoints[i].y || fY <= fPoints[(i + 1) % uiPoints].y))
		{
			static const float eps = 0.000001f;

			// Calculate the equation of the line
			float dx = fPoints[(i + 1) % uiPoints].x - fPoints[i].x;
			float dy = fPoints[(i + 1) % uiPoints].y - fPoints[i].y;
			float k;

			if (fabs(dx) < eps)
				k = 0xffffffff;
			else
				k = dy / dx;

			float m = fPoints[i].y - k * fPoints[i].x;

			// Find if the ray crosses the line
			float y2 = k * fX + m;
			if (fY <= y2)
				crossings++;
		}
	}

	if (crossings % 2 == 1)
		return true;

	return false;
}

SQInteger InPoly( HSQUIRRELVM v )
{
	SQInteger iArgs = sq_gettop(v);

	if(iArgs >= 9 && (iArgs - 1) % 2 == 0 )
	{
		SQFloat fX = 0.0f, fY = 0.0f;
		sq_getfloat(v, 2, &fX);
		sq_getfloat(v, 3, &fY);

		AreaPoints areaPoints[128];
		SQFloat fPointX = 0.0f, fPointY = 0.0f;
		const unsigned int uiPoints = (iArgs - 3);

		unsigned int uiThing = 4; // todo: better name
		for (unsigned int ui = 0; ui < uiPoints; ui++)
		{
			sq_getfloat(v, uiThing, &fPointX);
			sq_getfloat(v, uiThing + 1, &fPointY);

			areaPoints[ui].x = (float)fPointX;
			areaPoints[ui].y = (float)fPointY;

			uiThing += 2;
		}

		bool bRet = Internal_InPoly((float)fX, (float)fY, uiPoints, areaPoints);

		sq_pushbool(v, bRet);
		return 1;
	}
	else if (iArgs == 4)
	{
		if (sq_gettype(v, 4) == OT_STRING)
		{
			SQFloat fX = 0.0f, fY = 0.0f;
			sq_getfloat(v, 2, &fX);
			sq_getfloat(v, 3, &fY);

			const SQChar* szSqParams = 0;
			sq_getstring(v, 4, &szSqParams);

			char szParams[512] = { 0 };
			memcpy(szParams, &szSqParams, 512);

			AreaPoints areaPoints[128];

			size_t uiPoints = Internal_NumTok(szParams, ',');

			uiPoints /= 2;

			if (uiPoints >= 3)
			{
				areaPoints[0].x = (float)atof(strtok(szParams, ","));
				areaPoints[0].y = (float)atof(strtok(0, ","));

				for (unsigned int ui = 1; ui < uiPoints; ui++)
				{
					areaPoints[ui].x = (float)atof(strtok(0, ","));
					areaPoints[ui].y = (float)atof(strtok(0, ","));
				}

				bool bRet = Internal_InPoly((float)fX, (float)fY, uiPoints, areaPoints);

				sq_pushbool(v, bRet);
				return 1;
			}
		}
		else if (sq_gettype(v, 4) == OT_ARRAY)
		{
			SQFloat fX = 0.0f, fY = 0.0f;
			sq_getfloat(v, 2, &fX);
			sq_getfloat(v, 3, &fY);

			SQObject obj;
			sq_getstackobj(v, 4, &obj);

			Sqrat::Array arr(Sqrat::Object(obj, v));
			AreaPoints areaPoints[128];

			const size_t uiPoints = arr.GetSize() / 2;

			if (uiPoints >= 3)
			{
				for (unsigned int ui = 0; ui < uiPoints; ui++)
				{
					areaPoints[ui].x = arr[2 * ui].Cast<float>();
					areaPoints[ui].y = arr[2 * ui + 1].Cast<float>();
				}

				bool bRet = Internal_InPoly((float)fX, (float)fY, uiPoints, areaPoints);

				sq_pushbool(v, bRet);
				return 1;
			}
		}
	}

	return sq_throwerror( v, "Unexpected number or types of parameters for InPoly" );
}

void SetVehiclesForcedRespawnHeight(SQFloat height) { functions->SetVehiclesForcedRespawnHeight(height); }
SQFloat GetVehiclesForcedRespawnHeight(void) { return functions->GetVehiclesForcedRespawnHeight(); }

// These functions are for compatibility, but will be deprecated
DWORD GetTime( void )
{
	OutputWarning( "GetTime is deprecated and may be removed in the future.\n"
		"          Please use Squirrel's time() function instead." );

	return static_cast<DWORD>( time( NULL ) );
}

const SQChar * GetFullTime( void )
{
	OutputWarning( "GetFullTime is deprecated and may be removed in the future.\n"
		"          Please use Squirrel's date() function instead." );

	static char date[96];
	time_t rawtime;
	time( &rawtime );

	struct tm * timeinfo = localtime( &rawtime );
	strftime( date, 96, "%A, %B %d, %Y, %H:%M:%S %Z", timeinfo );

	return date;
}

// These functions do nothing and exist for the sole purpose of avoiding compiler errors
extern HSQAPI sq;
SQInteger SetAmmuWeapon( HSQUIRRELVM v ) { OutputWarning( "SetAmmuWeapon does not exist in 0.4. Ammunations must be scripted." ); return 0; }
SQInteger IsAmmuWeaponEnabled(HSQUIRRELVM v) { OutputWarning("IsAmmuWeaponEnabled does not exist in 0.4. Ammunations must be scripted."); sq->pushbool(v, false);  return 1; }
SQInteger SetAmmuWeaponEnabled( HSQUIRRELVM v ) { OutputWarning( "SetAmmuWeaponEnabled does not exist in 0.4. Ammunations must be scripted." ); return 0; }

bool GetFallEnabled(void)
{
	OutputWarning("GetFallEnabled has no effect.");
	return false;
}

void SetFallEnabled(bool unused) { OutputWarning("SetFallEnabled has no effect."); }
bool GetDeathmatchScoreboard(void)
{
	OutputWarning("GetDeathmatchScoreboard has no effect. Use scripts to implement it.");
	return false;
}

void SetDeathmatchScoreboard(bool isDmScoreboard) { OutputWarning("GetDeathmatchScoreboard has no effect. Use scripts to implement it."); }
bool GetWeaponSync(int weapon)
{
	OutputWarning("GetWeaponSync does not exist in 0.4. Rely on the server's anti-hack system and callbacks instead.");
	return false;
}

void SetWeaponSync(int weapon, bool isSynced) { OutputWarning("GetWeaponSync does not exist in 0.4. Rely on the server's anti-hack system and callbacks instead."); }
bool GetWeatherLock(void)
{
	OutputWarning("GetWeatherLock has no effect.");
	return true;
}

void SetWeatherLock(bool isLocked) { OutputWarning("SetWeatherLock has no effect."); }
const SQChar * GetMapName(void)
{
	OutputWarning("GetMapName has no effect.");
	return "Vice-City";
}

void SetMapName(const SQChar * mapName) { OutputWarning("SetMapName has no effect."); }	

Sqrat::Array GetPlayersArray()
{
    Sqrat::Array arr( DefaultVM::Get() );
    CPlayer * pPlayer = 0;

    for ( unsigned i = 0; i < MAX_PLAYERS; ++i )
    {
        pPlayer = pCore->RetrievePlayer( i );
        if ( pPlayer != NULL ) arr.Append<CPlayer *>( pPlayer ); 
    }

    return arr;
}

Sqrat::Array GetPickupsArray()
{
    Sqrat::Array arr( DefaultVM::Get() );
    CPickup * pPickup = 0;

    for ( unsigned i = 0; i < MAX_PICKUPS; ++i )
    {
        pPickup = pCore->RetrievePickup( i );
        if ( pPickup != NULL ) arr.Append<CPickup *>( pPickup ); 
    }

    return arr;
}

Sqrat::Array GetObjectsArray()
{
    Sqrat::Array arr( DefaultVM::Get() );
    CObject * pObject = 0;

    for ( unsigned i = 0; i < MAX_OBJECTS; ++i )
    {
        pObject = pCore->RetrieveObject( i );
        if ( pObject != NULL ) arr.Append<CObject *>( pObject ); 
    }

    return arr;
}

Sqrat::Array GetVehiclesArray()
{
    Sqrat::Array arr( DefaultVM::Get() );
    CVehicle * pVehicle = 0;

    for ( unsigned i = 0; i < MAX_VEHICLES; ++i )
    {
        pVehicle = pCore->RetrieveVehicle( i );
        if ( pVehicle != NULL ) arr.Append<CVehicle *>( pVehicle ); 
    }

    return arr;
}

Sqrat::Array GetCheckpointsArray()
{
    Sqrat::Array arr( DefaultVM::Get() );
    CCheckpoint * pCheckpoint = 0;

    for ( unsigned i = 0; i < MAX_CHECKPOINTS; ++i )
    {
        pCheckpoint = pCore->RetrieveCheckpoint( i );
        if ( pCheckpoint != NULL ) arr.Append<CCheckpoint *>( pCheckpoint ); 
    }

    return arr;
}

Sqrat::Array GetSpheresArray()
{
    Sqrat::Array arr( DefaultVM::Get() );
    CSphere * pSphere = 0;

    for ( unsigned i = 0; i < MAX_SPHERES; ++i )
    {
        pSphere = pCore->RetrieveSphere( i );
        if ( pSphere != NULL ) arr.Append<CSphere *>( pSphere ); 
    }

    return arr;
}
