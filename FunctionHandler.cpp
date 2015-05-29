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

const SQChar * GetWeaponName   ( int weaponID )
{
	switch( weaponID )
	{
		case 0:
			return "Unarmed";
		case 1:
			return "Brass Knuckles";
		case 2:
			return "Screwdriver";
		case 3:
			return "Golf Club";
		case 4:
			return "Nightstick";
		case 5:
			return "Knife";
		case 6:
			return "Baseball Bat";
		case 7:
			return "Hammer";
		case 8:
			return "Meat Cleaver";
		case 9:
			return "Machete";
		case 10:
			return "Katana";
		case 11:
			return "Chainsaw";
		case 12:
			return "Grenade";
		case 13:
			return "Remote Detonation Grenade";
		case 14:
			return "Tear Gas";
		case 15:
			return "Molotov Cocktails";
		case 16:
			return "Rocket";
		case 17:
			return "Colt .45";
		case 18:
			return "Python";
		case 19:
			return "Pump-Action Shotgun";
		case 20:
			return "SPAS-12 Shotgun";
		case 21:
			return "Stubby Shotgun";
		case 22:
			return "TEC-9";
		case 23:
			return "Uzi";
		case 24:
			return "Silenced Ingram";
		case 25:
			return "MP5";
		case 26:
			return "M4";
		case 27:
			return "Ruger";
		case 28:
			return "Sniper Rifle";
		case 29:
			return "Laserscope Sniper Rifle";
		case 30:
			return "Rocket Launcher";
		case 31:
			return "Flamethrower";
		case 32:
			return "M60";
		case 33:
			return "Minigun";
		case 34:
			return "Explosion";
		case 35:
			return "Helicannon";
		case 36:
			return "Camera";
		case 39:
			return "Vehicle";
		case 41:
			return "Explosion";
		case 42:
			return "Driveby";
		case 43:
			return "Drowned";
		case 44:
			return "Fall";
		case 51:
			return "Explosion";
		case 70:
			return "Suicide";
		default:
			return "Unknown";
	}
}

const SQChar * GetDistrictName ( float x, float y )
{
	if( x > -1613.03f && y > 413.218f && x < -213.73f && y < 1677.32f )
		return "Downtown Vice City";
	else if( x > 163.656f && y > -351.153f && x < 1246.03f && y < 1398.85f )
		return "Vice Point";
	else if( x > -103.97f && y > -930.526f && x < 1246.03f && y < -351.153f )
		return "Washington Beach";
	else if( x > -253.206f && y > -1805.37f && x < 1254.9f && y < -930.526f )
		return "Ocean Beach";
	else if( x > -1888.21f && y > -1779.61f && x < -1208.21f && y < 230.39f )
		return "Escobar International Airport";
	else if( x > -748.206f && y > -818.266f && x < -104.505f && y < -241.467f )
		return "Starfish Island";
	else if( x > -213.73f && y > 797.605f && x < 163.656f && y < 1243.47f )
		return "Prawn Island";
	else if( x > -213.73f && y > -241.429f && x < 163.656f && y < 797.605f )
		return "Leaf Links";
	else if( x > -1396.76f && y > -42.9113f && x < -1208.21f && y < 230.39f )
		return "Junkyard";
	else if( x > -1208.21f && y > -1779.61f &&  x < -253.206f && y < -898.738f )
		return "Viceport";
	else if( x > -1208.21f && y > -898.738f && x < -748.206f && y < -241.467f )
		return "Little Havana";
	else if( x > -1208.21f && y > -241.467f && x < -578.289f && y < 412.66f )
		return "Little Haiti";
	else
		return "Vice City";
}

const SQChar * GetSkinName     ( int skinID )
{
	switch( skinID )
	{
		case 0:   return "Tommy Vercetti";
		case 1:   return "Cop";
		case 2:   return "SWAT";
		case 3:   return "FBI";
		case 4:   return "Army";
		case 5:   return "Paramedic";
		case 6:   return "Firefighter";
		case 7:   return "Golf Guy #1";
		case 8:   return NULL;
		case 9:   return "Bum Lady #1";
		case 10:  return "Bum Lady #2";
		case 11:  return "Punk #1";
		case 12:  return "Lawyer";
		case 13:  return "Spanish Lady #1";
		case 14:  return "Spanish Lady #2";
		case 15:  return "Cool Guy #1";
		case 16:  return "Arabic Guy";
		case 17:  return "Beach Lady #1";
		case 18:  return "Beach Lady #2";
		case 19:  return "Beach Guy #1";
		case 20:  return "Beach Guy #2";
		case 21:  return "Office Lady #1";
		case 22:  return "Waitress #1";
		case 23:  return "Food Lady";
		case 24:  return "Prostitute #1";
		case 25:  return "Bum Lady #3";
		case 26:  return "Bum Guy #1";
		case 27:  return "Garbageman #1";
		case 28:  return "Taxi Driver #1";
		case 29:  return "Haitian #1";
		case 30:  return "Criminal #1";
		case 31:  return "Hood Lady";
		case 32:  return "Granny #1";
		case 33:  return "Businessman #1";
		case 34:  return "Church Guy";
		case 35:  return "Club Lady";
		case 36:  return "Church Lady";
		case 37:  return "Pimp";
		case 38:  return "Beach Lady #3";
		case 39:  return "Beach Guy #3";
		case 40:  return "Beach Lady #4";
		case 41:  return "Beach Guy #4";
		case 42:  return "Businessman #2";
		case 43:  return "Prostitute #2";
		case 44:  return "Bum Lady #4";
		case 45:  return "Bum Guy #2";
		case 46:  return "Haitian #2";
		case 47:  return "Construction Worker #1";
		case 48:  return "Punk #2";
		case 49:  return "Prostitute #3";
		case 50:  return "Granny #2";
		case 51:  return "Punk #3";
		case 52:  return "Businessman #3";
		case 53:  return "Spanish Lady #3";
		case 54:  return "Spanish Lady #4";
		case 55:  return "Cool Guy #2";
		case 56:  return "Businessman #4";
		case 57:  return "Beach Lady #5";
		case 58:  return "Beach Guy #5";
		case 59:  return "Beach Lady #6";
		case 60:  return "Beach Guy #6";
		case 61:  return "Construction Worker #2";
		case 62:  return "Golf Guy #2";
		case 63:  return "Golf Lady";
		case 64:  return "Golf Guy #3";
		case 65:  return "Beach Lady #7";
		case 66:  return "Beach Guy #7";
		case 67:  return "Office Lady #2";
		case 68:  return "Businessman #5";
		case 69:  return "Businessman #6";
		case 70:  return "Prostitute #2";
		case 71:  return "Bum Lady #4";
		case 72:  return "Bum Guy #3";
		case 73:  return "Spanish Guy";
		case 74:  return "Taxi Driver #2";
		case 75:  return "Gym Lady";
		case 76:  return "Gym Guy";
		case 77:  return "Skate Lady";
		case 78:  return "Skate Guy";
		case 79:  return "Shopper #1";
		case 80:  return "Shopper #2";
		case 81:  return "Tourist #1";
		case 82:  return "Tourist #2";
		case 83:  return "Cuban #1";
		case 84:  return "Cuban #2";
		case 85:  return "Haitian #3";
		case 86:  return "Haitian #4";
		case 87:  return "Shark #1";
		case 88:  return "Shark #2";
		case 89:  return "Diaz Guy #1";
		case 90:  return "Diaz Guy #2";
		case 91:  return "DBP Security #1";
		case 92:  return "DBP Security #2";
		case 93:  return "Biker #1";
		case 94:  return "Biker #2";
		case 95:  return "Vercetti Guy #1";
		case 96:  return "Vercetti Guy #2";
		case 97:  return "Undercover Cop #1";
		case 98:  return "Undercover Cop #2";
		case 99:  return "Undercover Cop #3";
		case 100: return "Undercover Cop #4";
		case 101: return "Undercover Cop #5";
		case 102: return "Undercover Cop #6";
		case 103: return "Rich Guy";
		case 104: return "Cool Guy #3";
		case 105: return "Prostitute #3";
		case 106: return "Prostitute #4";
		case 107: return "Love Fist #1";
		case 108: return "Ken Rosenburg";
		case 109: return "Candy Suxx";
		case 110: return "Hilary";
		case 111: return "Love Fist #2";
		case 112: return "Phil";
		case 113: return "Rockstar Guy";
		case 114: return "Sonny";
		case 115: return "Lance";
		case 116: return "Mercedes";
		case 117: return "Love Fist #3";
		case 118: return "Alex Shrub";
		case 119: return "Lance (Cop)";
		case 120: return "Lance";
		case 121: return "Cortez";
		case 122: return "Love Fist #4";
		case 123: return "Columbian Guy #1";
		case 124: return "Hilary (Robber)";
		case 125: return "Mercedes";
		case 126: return "Cam";
		case 127: return "Cam (Robber)";
		case 128: return "Phil (One Arm)";
		case 129: return "Phil (Robber)";
		case 130: return "Cool Guy #4";
		case 131: return "Pizza Man";
		case 132: return "Taxi Driver #1";
		case 133: return "Taxi Driver #2";
		case 134: return "Sailor #1";
		case 135: return "Sailor #2";
		case 136: return "Sailor #3";
		case 137: return "Chef";
		case 138: return "Criminal #2";
		case 139: return "French Guy";
		case 140: return "Garbageman #2";
		case 141: return "Haitian #5";
		case 142: return "Waitress #2";
		case 143: return "Sonny Guy #1";
		case 144: return "Sonny Guy #2";
		case 145: return "Sonny Guy #3";
		case 146: return "Columbian Guy #2";
		case 147: return "Haitian #6";
		case 148: return "Beach Guy #8";
		case 149: return "Garbageman #3";
		case 150: return "Garbageman #4";
		case 151: return "Garbageman #5";
		case 152: return "Tranny";
		case 153: return "Thug #5";
		case 154: return "SpandEx Guy #1";
		case 155: return "SpandEx Guy #2";
		case 156: return "Stripper #1";
		case 157: return "Stripper #2";
		case 158: return "Stripper #3";
		case 159: return "Store Clerk";
		case 160: return NULL;
		case 161: return "Tommy with Suit";
		case 162: return "Worker Tommy";
		case 163: return "Golfer Tommy";
		case 164: return "Cuban Tommy";
		case 165: return "VCPD Tommy";
		case 166: return "Bank Robber Tommy";
		case 167: return "Street Tommy";
		case 168: return "Mafia Tommy";
		case 169: return "Jogger Tommy #1";
		case 170: return "Jogger Tommy #2";
		case 171: return "Guy With Suit #1";
		case 172: return "Guy With Suit #3";
		case 173: return "Prostitute #5";
		case 174: return "Rico";
		case 175: return "Prostitute #3";
		case 176: return "Club Lady";
		case 177: return "Prostitute #2";
		case 178: return "Skull T-Shirt Guy";
		case 179: return "Easter Egg Tommy";
		case 180: return "Diaz Gangster #1";
		case 181: return "Diaz Gangster #2";
		case 182: return "Hood Lady";
		case 183: return "Punk #1";
		case 184: return "Tray Lady";
		case 185: return "Kent Paul";
		case 186: return "Taxi Driver #1";
		case 187: return "Deformed Ken Rosenberg";
		case 188: return "Deformed Woman";
		case 189: return "Deformed Man";
		case 190: return "Deformed Cortez";
		case 191: return "Deformed Lance Vance";
		case 192: return "Thief #1";
		case 193: return "Thief #2";
		case 194: return "Thief #3";
		default:  return NULL;
	}
}

void LoadVCMPModule( const SQChar * name )
{
	OutputWarning( "LoadModule() cannot be used by scripts. Specify plugins in server.cfg" );
}

int GetWeaponID( const SQChar * name )
{
	if( name == NULL || strlen(name) < 1 )
		return 0;
	
	// Get characters we might need
	char char1, char2, char3;
	char1 = 0;
	char2 = 0;
	char3 = 0;

	char1 = tolower(name[0]);
	if( strlen(name) >= 3 )
	{
		char3 = tolower(name[2]);
		char2 = tolower(name[1]);
	}
	else if( strlen(name) >= 2 )
		char2 = tolower(name[1]);

	switch( char1 )
	{
		// [F]ists, [F]lamethrower
		case 'f':
		{
			// [Fi]sts
			if( char2 && char2 == 'i' )
				return 0;
			
			// Default to flamethrower
			else
				return 31;

			break;
		}

		case 'b':
			// [Br]ass Knuckles
			if( char2 && char2 == 'r' )
				return 1;

			// [Ba]seball Bat
			return 6;

		// [S]crewdriver, [S]hotgun, [S]PAS-12 Shotgun, [S]tubby/[S]awnoff Shotgun, [Si]lenced Ingram [S]niper Rifle
		case 's':
		{
			switch( char2 )
			{
				// [Sc]rewdriver
				case 'c':
					return 2;

				// [Sh]otgun
				case 'h':
					return 19;

				// [SP]AS-12 / [Sp]az Shotgun
				case 'p':
					return 20;

				// [St]ubby / [Sa]wnoff Shotgun
				case 't':
				case 'a':
					return 21;

				// [Si]lenced Ingram
				case 'i':
					return 24;

				// [Sn]iper
				case 'n':
					return 28;

				// Default to screwdriver
				default:
					return 2;
			}
		}

		// [G]olf Club, [G]renade
		case 'g':
		{
			// [Go]lf Club
			if( char2 && char2 == 'o' )
				return 3;

			// Grenades being more popular in servers, default to grenade
			else
				return 12;

			break;
		}

		// [N]ightstick
		case 'n':
			return 4;

		// [K]nife, [K]atana
		case 'k':
		{
			// [Kn]ife
			if( char2 && char2 == 'n' )
				return 5;

			// Default to katana
			else
				return 10;

			break;
		}

		// [H]ammer
		case 'h':
			return 7;

		// [M]eat Cleaver, [M]achete, [M]olotov Cocktail, [M]P5, [M]4, [M]60, [M]inigun
		case 'm':
		{
			switch( char2 )
			{
				// [Me]at Cleaver
				case 'e':
					return 8;

				// [Ma]chete
				case 'a':
					return 9;

				// [Mo]lotov Cocktail
				case 'o':
					return 15;

				// [MP]5
				case 'p':
					return 25;

				// [M4]
				case '4':
					return 26;

				// [M6]0
				case '6':
					return 32;

				// [Mi]nigun
				case 'i':
					return 33;

				// Default to M4
				default:
					return 26;
			}

			break;
		}

		// [C]leaver, [C]hainsaw, [C]olt .45
		case 'c':
		{
			switch( char2 )
			{
				// [Cl]eaver
				case 'l':
					return 8;

				// [Ch]ainsaw
				case 'h':
					return 11;

				// Default to Colt .45
				default:
					return 17;
			}

			break;
		}

		// [R]emote Detonation Grenade, [R]uger, [R]ocket Launcher / [R]PG
		case 'r':
		{
			switch( char2 )
			{
				// [Re]mote Detonation Grenade
				case 'e':
					return 13;

				// [Ro]cket Launcher, [RP]G
				case 'o':
				case 'p':
					return 30;

				// [Ru]ger
				case 'u':
					return 27;

				// Default to ruger
				default:
					return 27;
			}
		}

		// [T]ear Gas, [T]EC-9
		case 't':
		{
			// Both of them have E as a second character anyways.
			if( char2 )
			{
				// [Tea]r Gas
				if( char3 && char3 == 'a' )
					return 14;

				// Default to TEC-9
				else
					return 22;
			}

			// Default to TEC-9 if no second character exists.
			else
				return 22;

			break;
		}

		// [P]ython
		case 'p':
			return 18;

		// [U]zi
		case 'u':
			return 23;

		// [I]ngram
		case 'i':
			return 24;

		// [L]aserscope Sniper
		case 'l':
			return 29;

		// Default to fists
		default:
			return 255;
	}
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

int GetVehicleModelFromName( SQChar * name )
{
	char * lowername = strdup( name );
	szlower( lowername );

	int res = -1;
	if( lowername )
	{
		switch( lowername[0] )
		{
			case 'l':
			{
				if( strlen( lowername ) >= 2 )
				{
					if( lowername[1] == 'a' )
						res = 130; // landstalker
					else if( lowername[1] == 'i' )
						res = 133; // linerunner
					else if( lowername[1] == 'o' )
						res = 201; // love fist
				}

				break;
			}

			case 'i':
			{
				if (strlen(lowername) >= 2)
				{
					if (lowername[1] == 'd')
						res = 131;
					else if (lowername[1] == 'n')
						res = 141;
				}

				break;
			}

			case 's':
			{
				if( strlen( lowername ) >= 3 )
				{
					if( lowername[1] == 't' )
					{
						if( lowername[2] == 'i' )
							res = 132; // stinger
						else if( lowername[2] == 'r' )
							res = 139; // stretch
						else if( lowername[2] == 'a' )
							res = 169; // stallion
					}
					else if( lowername[1] == 'e' )
					{
						if( lowername[2] == 'c' )
							res = 158; // securicar
						else if( lowername[2] == 'a' )
							res = 177; // sea sparrow
						else if( strlen( lowername ) > 8 )
							res = 174; // sentinel xs
						else
							res = 135; // sentinel
					}
					else if( lowername[1] == 'q' )
						res = 176; // squalo
					else if( lowername[1] == 'p' )
					{
						if( lowername[2] == 'e' )
							res = 182; // speeder
						else if( lowername[2] == 'a' )
						{
							if( strlen( lowername ) >= 4 )
							{
								if( lowername[3] == 'r' )
									res = 199; // sparrow
								else if( lowername[3] == 'n' )
									res = 213; // spand express
							}
						}
					}
					else if( lowername[1] == 'k' )
						res = 190; // skimmer
					else if( lowername[1] == 'a' )
					{
						if( lowername[2] == 'n' )
						{
							if( strlen( lowername ) >= 4 )
							{
								if( lowername[3] == 'c' )
									res = 198; // sanchez
								else if( lowername[3] == 'd' )
									res = 225; // sandking
							}
						}
						else if( lowername[2] == 'b' && strlen(lowername) > 5 )
							res = 206; // sabre turbo
						else if( lowername[2] == 'b' )
							res = 205; // sabre
					}
				}

				break;
			}

			case 'p':
			{
				if( lowername[1] == 'e' )
					res = 134; // perennial
				else if( lowername[1] == 'o' )
				{
					if( strlen( lowername ) > 6 )
						res = 227; // police maverick
					else
						res = 156; // police
				}
				else if( lowername[1] == 'r' )
					res = 160; // predator
				else if( lowername[1] == 'a' )
				{
					if( strlen( lowername ) >= 3 )
					{
						if( lowername[2] == 'c' )
							res = 173; // packer
						else if( lowername[2] == 't' )
							res = 200; // patriot
					}
				}
				else if( lowername[1] == 'i' )
					res = 178; // pizza boy
				else if (lowername[1] == 'c')
					res = 191; // pcj-600
				else if (lowername[1] == 'h')
					res = 207; // phoenix
				else if (lowername[1] == 'n')
					res = 143; // pony

				break;
			}

			case 'r':
			{
				if( lowername[1] == 'i' )
					res = 136; // rio
				else if( lowername[1] == 'h' )
					res = 162; // rhino
				else if( lowername[1] == 'u' )
					res = 170; // rumpo
				else if( lowername[1] == 'c' )
				{
					if( lowername[2] == 'b' )
					{
						if( strlen( lowername ) >= 5 )
						{
							if( lowername[4] == 'n' )
								res = 171; // rcbandit
							else if( lowername[4] == 'r' )
								res = 194; // rcbaron
						}
					}
					else if( lowername[2] == 'r' )
						res = 195; // rcraider
					else if( lowername[2] == 'g' )
						res = 231;
				}
				else if( lowername[1] == 'o' )
					res = 172; // romero's hearse
				else if( lowername[1] == 'e' )
				{
					if( strlen( lowername ) >= 3 )
					{
						if( lowername[2] == 'e' )
							res = 183; // reefer
						else if( lowername[2] == 'g' )
							res = 209; // regina
					}
				}
				else if( lowername[1] == 'a' )
					res = 219;

				break;
			}

			case 'f':
			{
				if( lowername[1] == 'i' )
					res = 137; // firetruck
				else if( lowername[1] == 'b' )
				{
					if( strlen( lowername ) >= 5 )
					{
						if( lowername[4] == 'w' )
							res = 147; // fbi washington
						else if( lowername[4] == 'r' )
							res = 220; // fbi rancher
					}
				}
				else if( lowername[1] == 'l' )
					res = 185; // flatbed
				else if( lowername[1] == 'a' )
					res = 192; // faggio
				else if( lowername[1] == 'r' )
					res = 193; // freeway

				break;
			}

			case 't':
			{
				if( lowername[1] == 'r' )
				{
					if( strlen( lowername ) >= 3 )
					{
						if( lowername[2] == 'a' )
							res = 138; // trashmaster
						else if( lowername[2] == 'o' )
							res = 184; // tropic
					}
				}
				else if( lowername[1] == 'o' )
					res = 189; // top fun
				else if( lowername[1] == 'a' )
					res = 150; // taxi

				break;
			}

			case 'm':
			{
				if( lowername[1] == 'a' )
				{
					if( strlen( lowername ) >= 3 )
					{
						if( lowername[2] == 'n' )
							res = 140; // manana
						else if( lowername[2] == 'r' )
							res = 214; // marquis
						else if( lowername[2] == 'v' )
							res = 217; // maverick
					}
				}
				else if( lowername[1] == 'u' )
					res = 144; // mule
				else if( lowername[1] == 'r' )
					res = 153; // mr. whoopee
				else if (lowername[1] == 'e')
					res = 230; // mesa grande
				else if (lowername[1] == 'o')
					res = 148; // moonbeam

				break;
			}

			case 'c':
			{
				if( lowername[1] == 'h' )
					res = 145; // cheetah
				else if( lowername[1] == 'u' )
				{
					if( strlen( lowername ) >= 7 )
					{
						if( lowername[6] == 'h' )
							res = 164; // cuban hermes
						else if( lowername[6] == 'j' )
							res = 223; // cuban jetmax
					}
				}
				else if( lowername[1] == 'o' )
				{
					if( strlen( lowername ) >= 3 && lowername[2] == 'm' )
						res = 210; // comet
					else if( strlen(lowername) >= 4)
					{
						if (lowername[3] == 'c')
							res = 167; // coach
						else if (lowername[3] == 's')
							res = 202; // coast guard
					}
				}
				else if( lowername[1] == 'a' )
				{
					if( strlen( lowername ) >= 3 )
					{
						if( lowername[2] == 'b' )
							res = 168; // cabbie
						else if( lowername[2] == 'd' )
							res = 187; // caddy
					}
				}

				break;
			}

			case 'a':
			{
				if( lowername[1] == 'm' )
					res = 146; // ambulance
				else if( lowername[1] == 'n' )
					res = 166; // angel
				else if( lowername[1] == 'd' )
					res = 175; // admiral
				else if( lowername[1] == 'i' )
					res = 180; // airtrain

				break;
			}

			case 'e':
			{
				if( lowername[1] == 's' )
					res = 149; // esperanto
				else if( lowername[1] == 'n' )
					res = 157; // enforcer

				break;
			}

			case 'w':
			{
				if( strlen( lowername ) >= 3 )
				{
					if( lowername[2] == 's' )
						res = 151; // washington
					else if( lowername[2] == 'l' )
						res = 208; // walton
				}

				break;
			}

			case 'b':
			{
				if( lowername[1] == 'o' )
				{
					if( strlen( lowername ) >= 3 )
					{
						if( lowername[2] == 'b' )
							res = 152; // bobcat
						else if( lowername[2] == 'x' )
							res = 228; // boxville
					}
				}
				else if( lowername[1] == 'a' )
				{
					if( strlen( lowername ) >= 3 )
					{
						if( lowername[2] == 'r' )
							res = 163; // barracks ol
						else if (lowername[2] == 'g')
							res = 215; // baggage handler
						else if (lowername[2] == 'n')
							res = 159; // banshee
					}
				}
				else if (lowername[1] == 'u')
				{
					if (strlen(lowername) >= 3)
					{
						if (lowername[2] == 'r')
							res = 212; // burrito
						else if (lowername[2] == 's')
							res = 161; // bus
					}
				}
				else if (lowername[1] == 'l')
				{
					if (strlen(lowername) >= 3)
					{
						if (lowername[2] == 'i')
							res = 226; // blista compact
						else if (lowername[2] == 'o')
						{
							res = 234; // bloodra
							if (strcmp(lowername, "bloodrb") == 0)
								res = 235; // bloodrb
						}
					}
				}
				else if (lowername[1] == 'e')
					res = 229; // benson
				else if (lowername[1] == 'f')
					res = 154; // bf injection

				break;
			}

			case 'h':
			{
				if( lowername[1] == 'u' )
					res = 155; // hunter
				else if (lowername[1] == 'e')
				{
					if (strlen(lowername) >= 3)
					{
						if (lowername[2] == 'r')
							res = 204; // hermes
						else if (lowername[2] == 'l')
							res = 165; // helicopter
					}
				}
				else if (lowername[1] == 'o')
				{
					res = 224; // hotring racer
					if (strcmp("hotrina", lowername) == 0)
						res = 232; // hotrina
					else if (strcmp("hotrinb", lowername) == 0)
						res = 233; // hotrinb
				}

				break;
			}

			case 'g':
			{
				if( lowername[1] == 'a' )
					res = 179; // gang burrito
				else if( lowername[1] == 'l' )
					res = 196; // glendale
				else if( lowername[1] == 'r' )
					res = 222; // greenwood

				break;
			}

			case 'd':
			{
				if( lowername[1] == 'e' )
					res = 211; // deluxo
				else if( lowername[1] == 'i' )
					res = 203; // dinghy

				break;
			}

			case 'y':
				res = 186; // yankee
				break;

			case 'z':
				res = 188; // zebra cab
				break;

			case 'k':
				res = 216; // kaufman cab
				break;

			case 'o':
				res = 197; // oceanic
				break;

			case 'j':
				res = 223; // cuban [j]etmax
				break;
				
			case 'v':
			{
				if( lowername[1] == 'c' )
					res = 218; // vcn maverick
				else if (lowername[1] == 'i')
				{
					if (strlen(lowername) >= 3)
					{
						if (lowername[2] == 'r')
							res = 221; // virgo
						else if (lowername[2] == 'c')
							res = 236; // vicechee
					}
				}
				else if (lowername[1] == 'o')
					res = 142; // voodoo

				break;
			}
		}

		free(lowername);
	}

	return res;
}

const SQChar * GetVehicleNameFromModel ( int model )
{
	switch( model )
	{
		case 130: return "Landstalker";
		case 131: return "Idaho";
		case 132: return "Stinger";
		case 133: return "Linerunner";
		case 134: return "Perennial";
		case 135: return "Sentinel";
		case 136: return "Rio";
		case 137: return "Firetruck";
		case 138: return "Trashmaster";
		case 139: return "Stretch";
		case 140: return "Manana";
		case 141: return "Infernus";
		case 142: return "Voodoo";
		case 143: return "Pony";
		case 144: return "Mule";
		case 145: return "Cheetah";
		case 146: return "Ambulance";
		case 147: return "FBI Washington";
		case 148: return "Moonbeam";
		case 149: return "Esperanto";
		case 150: return "Taxi";
		case 151: return "Washington";
		case 152: return "Bobcat";
		case 153: return "Mr. Whoopee";
		case 154: return "BF Injection";
		case 155: return "Hunter";
		case 156: return "Police";
		case 157: return "Enforcer";
		case 158: return "Securicar";
		case 159: return "Banshee";
		case 160: return "Predator";
		case 161: return "Bus";
		case 162: return "Rhino";
		case 163: return "Barracks OL";
		case 164: return "Cuban Hermes";
		case 165: return "Helicopter";
		case 166: return "Angel";
		case 167: return "Coach";
		case 168: return "Cabbie";
		case 169: return "Stallion";
		case 170: return "Rumpo";
		case 171: return "RC Bandit";
		case 172: return "Romero's Hearse";
		case 173: return "Packer";
		case 174: return "Sentinel XS";
		case 175: return "Admiral";
		case 176: return "Squalo";
		case 177: return "Sea Sparrow";
		case 178: return "Pizza Boy";
		case 179: return "Gang Burrito";
		case 180: return "Airtrain";
		case 181: return "Deaddodo";
		case 182: return "Speeder";
		case 183: return "Reefer";
		case 184: return "Tropic";
		case 185: return "Flatbed";
		case 186: return "Yankee";
		case 187: return "Caddy";
		case 188: return "Zebra Cab";
		case 189: return "Top Fun";
		case 190: return "Skimmer";
		case 191: return "PCJ-600";
		case 192: return "Faggio";
		case 193: return "Freeay";
		case 194: return "RC Baron";
		case 195: return "RC Raider";
		case 196: return "Glendale";
		case 197: return "Oceanic";
		case 198: return "Sanchez";
		case 199: return "Sparrow";
		case 200: return "Patriot";
		case 201: return "Love Fist";
		case 202: return "Coast Guard";
		case 203: return "Dinghy";
		case 204: return "Hermes";
		case 205: return "Sabre";
		case 206: return "Sabre Turbo";
		case 207: return "Phoenix";
		case 208: return "Walton";
		case 209: return "Regina";
		case 210: return "Comet";
		case 211: return "Deluxo";
		case 212: return "Burrito";
		case 213: return "Spand Express";
		case 214: return "Marquis";
		case 215: return "Baggage Handler";
		case 216: return "Kaufman Cab";
		case 217: return "Maverick";
		case 218: return "VCN Maverick";
		case 219: return "Rancher";
		case 220: return "FBI Rancher";
		case 221: return "Virgo";
		case 222: return "Greenwood";
		case 223: return "Cuban Jetmax";
		case 224: return "Hotring Racer #1";
		case 225: return "Sandking";
		case 226: return "Blista Compact";
		case 227: return "Police Maverick";
		case 228: return "Boxville";
		case 229: return "Benson";
		case 230: return "Mesa Grande";
		case 231: return "RC Goblin";
		case 232: return "Hotring Racer #2";
		case 233: return "Hotring Racer #3";
		case 234: return "Bloodring Banger #1";
		case 235: return "Bloodring Banger #2";
		case 236: return "Vice Squad Cheetah";
		default:  return NULL;
	}
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

// This function is so convoluted, we have to tiptoe around Sqrat.
// This had better work.
SQInteger NewTimer( HSQUIRRELVM v )
{
	// char * pFuncName, float interval, int maxPulses
	if( sq_gettop( v ) < 4 )
		return sq_throwerror( v, "Unexpected number of parameters for NewTimer [string, float, float]" );
	else if( sq_gettype( v, 2 ) != OT_STRING )
		return sq_throwerror( v, "The function name must be given as a string." );
	else if( sq_gettype( v, 3 ) != OT_FLOAT && sq_gettype( v, 3 ) != OT_INTEGER )
		return sq_throwerror( v, "The interval must be a float or integer." );
	else if( sq_gettype( v, 4 ) != OT_FLOAT && sq_gettype( v, 4 ) != OT_INTEGER )
		return sq_throwerror( v, "The maximum number of timer pulses must be a float or integer." );
	else
	{
		const SQChar * pFuncName;
		SQInteger maxPulses;
		SQFloat fInterval;

		sq_getstring( v, 2, &pFuncName );
		{
			if( sq_gettype( v, 3 ) == OT_INTEGER )
			{
				SQInteger interval;
				sq_getinteger( v, 3, &interval );

				fInterval = static_cast<SQFloat>(interval);
			}
			else
				sq_getfloat( v, 3, &fInterval );

			if( sq_gettype( v, 4 ) == OT_FLOAT )
			{
				SQFloat fMaxPulses;
				sq_getfloat( v, 4, &fMaxPulses );

				maxPulses = static_cast<SQInteger>(fMaxPulses);
			}
			else
				sq_getinteger( v, 4, &maxPulses );
		}

		if( RootTable(v).GetFunction( pFuncName ).IsNull() )
			return sq_throwerror( v, "The given timer callback does not exist." );
		else if( fInterval <= 0.0f )
			return sq_throwerror( v, "The timer's interval must be > 0" );
		else if( maxPulses < 0 )
			return sq_throwerror( v, "The timer's maximum number of pulses must be >= 0" );
		else
		{
			CTimer * pTimer  = new CTimer;
			if( sq_gettop( v ) > 4 )
			{
				pTimer->paramCount = sq_gettop(v) - 4;

				for( int i = 5; i <= sq_gettop( v ); i++ )
				{
					TimerParam pTempParam;
					pTempParam.datatype = sq_gettype( v, i );
					switch( pTempParam.datatype )
					{
						case OT_INTEGER:
							pTempParam.pData = new SQInteger();
							sq_getinteger(v, i, (SQInteger *)pTempParam.pData);
							break;

						case OT_FLOAT:
							pTempParam.pData = new SQFloat();
							sq_getfloat(v, i, (SQFloat *)pTempParam.pData);
							break;

						case OT_BOOL:
							pTempParam.pData = new SQBool();
							sq_getbool(v, i, (SQBool *)pTempParam.pData);
							break;

						case OT_STRING:
						{
							const SQChar * pString = NULL;
							sq_getstring(v, i, &pString);

							Sqrat::string * pStringData = new Sqrat::string(pString);
							pTempParam.pData = pStringData;
							break;
						}

						/*case OT_TABLE:
						case OT_ARRAY:
						case OT_CLASS:*/
						case OT_USERDATA:
						case OT_USERPOINTER:
						case OT_INSTANCE:
						case OT_CLOSURE:
						case OT_NATIVECLOSURE:
						{
							HSQOBJECT * o = new HSQOBJECT();
							sq_getstackobj(v, i, o);
							pTempParam.pData = o;
							break;
						}

						case OT_NULL:
						default:
							break;
					}

					pTimer->params.push_back(pTempParam);
				}
			}

			pTimer->pFunc = const_cast<SQChar *>(pFuncName);
			pTimer->intervalInTicks   = fInterval;
			pTimer->maxNumberOfPulses = maxPulses;

			Sqrat::ClassType<CTimer>().PushInstance( v, pTimer );
			pCore->AddTimer(pTimer);

			return 1;
		}
	}
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

#define SKIN_ID_UNKNOWN 				-1
#define SKIN_ID_TOMMY_VERCETTI 			0
#define SKIN_ID_COP 					1
#define SKIN_ID_SWAT 					2
#define SKIN_ID_FBI 					3
#define SKIN_ID_ARMY 					4
#define SKIN_ID_PARAMEDIC 				5
#define SKIN_ID_FIREMAN 				6
#define SKIN_ID_GOLF_GUY_A 				7
#define SKIN_ID_BUM_LADY_A 				9
#define SKIN_ID_BUM_LADY_B 				10
#define SKIN_ID_PUNK_A 					11
#define SKIN_ID_LAWYER 					12
#define SKIN_ID_SPANISH_LADY_A 			13
#define SKIN_ID_SPANISH_LADY_B 			14
#define SKIN_ID_COOL_GUY_A 				15
#define SKIN_ID_ARABIC_GUY 				16
#define SKIN_ID_BEACH_LADY_A 			17
#define SKIN_ID_BEACH_LADY_B 			18
#define SKIN_ID_BEACH_GUY_A 			19
#define SKIN_ID_BEACH_GUY_B 			20
#define SKIN_ID_OFFICE_LADY_A 			21
#define SKIN_ID_WAITRESS_A 				22
#define SKIN_ID_FOOD_LADY 				23
#define SKIN_ID_PROSTITUTE_A 			24
#define SKIN_ID_BUM_LADY_C 				25
#define SKIN_ID_BUM_GUY_A 				26
#define SKIN_ID_GARBAGEMAN_A 			27
#define SKIN_ID_TAXI_DRIVER_A 			28
#define SKIN_ID_HATIAN_A 				29
#define SKIN_ID_CRIMINAL_A 				30
#define SKIN_ID_HOOD_LADY 				31
#define SKIN_ID_GRANNY_A 				32
#define SKIN_ID_BUSINESS_MAN_A 			33
#define SKIN_ID_CHURCH_GUY 				34
#define SKIN_ID_CLUB_LADY 				35
#define SKIN_ID_CHURCH_LADY 			36
#define SKIN_ID_PIMP 					37
#define SKIN_ID_BEACH_LADY_C 			38
#define SKIN_ID_BEACH_GUY_C 			39
#define SKIN_ID_BEACH_LADY_D 			40
#define SKIN_ID_BEACH_GUY_D 			41
#define SKIN_ID_BUSINESS_MAN_B 			42
#define SKIN_ID_PROSTITUTE_B 			43
#define SKIN_ID_BUM_LADY_D 				44
#define SKIN_ID_BUM_GUY_B 				45
#define SKIN_ID_HATIAN_B 				46
#define SKIN_ID_CONSTRUCTION_WORKER_A 	47
#define SKIN_ID_PUNK_B 					48
#define SKIN_ID_PROSTITUTE_C 			49
#define SKIN_ID_GRANNY_B 				50
#define SKIN_ID_PUNK_C 					51
#define SKIN_ID_BUSINESS_MAN_C 			52
#define SKIN_ID_SPANISH_LADY_C 			53
#define SKIN_ID_SPANISH_LADY_D 			54
#define SKIN_ID_COOL_GUY_B 				55
#define SKIN_ID_BUSINESS_MAN_D 			56
#define SKIN_ID_BEACH_LADY_E 			57
#define SKIN_ID_BEACH_GUY_E 			58
#define SKIN_ID_BEACH_LADY_F 			59
#define SKIN_ID_BEACH_GUY_F 			60
#define SKIN_ID_CONSTRUCTION_WORKER_B 	61
#define SKIN_ID_GOLF_GUY_B 				62
#define SKIN_ID_GOLF_LADY 				63
#define SKIN_ID_GOLF_GUY_C 				64
#define SKIN_ID_BEACH_LADY_G 			65
#define SKIN_ID_BEACH_GUY_G 			66
#define SKIN_ID_OFFICE_LADY_B 			67
#define SKIN_ID_BUSINESS_MAN_E 			68
#define SKIN_ID_BUSINESS_MAN_F 			69
#define SKIN_ID_PROSTITUTE_D 			70
#define SKIN_ID_BUM_LADY_E 				71
#define SKIN_ID_BUM_GUY_C 				72
#define SKIN_ID_SPANISH_GUY 			73
#define SKIN_ID_TAXI_DRIVER_B 			74
#define SKIN_ID_GYM_LADY 				75
#define SKIN_ID_GYM_GUY 				76
#define SKIN_ID_SKATE_LADY 				77
#define SKIN_ID_SKATE_GUY 				78
#define SKIN_ID_SHOPPER_A 				79
#define SKIN_ID_SHOPPER_B 				80
#define SKIN_ID_TOURIST_A 				81
#define SKIN_ID_TOURIST_B 				82
#define SKIN_ID_CUBAN_A 				83
#define SKIN_ID_CUBAN_B 				84
#define SKIN_ID_HATIAN_C 				85
#define SKIN_ID_HATIAN_D 				86
#define SKIN_ID_SHARK_A 				87
#define SKIN_ID_SHARK_B 				88
#define SKIN_ID_DIAZ_GUY_A 				89
#define SKIN_ID_DIAZ_GUY_B 				90
#define SKIN_ID_DBP_SECURITY_A 			91
#define SKIN_ID_DBP_SECURITY_B 			92
#define SKIN_ID_BIKER_A 				93
#define SKIN_ID_BIKER_B 				94
#define SKIN_ID_VERCETTI_GUY_A 			95
#define SKIN_ID_VERCETTI_GUY_B 			96
#define SKIN_ID_UNDERCOVER_COP_A 		97
#define SKIN_ID_UNDERCOVER_COP_B 		98
#define SKIN_ID_UNDERCOVER_COP_C 		99
#define SKIN_ID_UNDERCOVER_COP_D 		100
#define SKIN_ID_UNDERCOVER_COP_E 		101
#define SKIN_ID_UNDERCOVER_COP_F 		102
#define SKIN_ID_RICH_GUY 				103
#define SKIN_ID_COOL_GUY_C 				104
#define SKIN_ID_PROSTITUTE_E 			105
#define SKIN_ID_PROSTITUTE_F 			106
#define SKIN_ID_LOVE_FIST_A 			107
#define SKIN_ID_KEN_ROSENBURG 			108
#define SKIN_ID_CANDY_SUXX 				109
#define SKIN_ID_HILARY 					110
#define SKIN_ID_LOVE_FIST_B 			111
#define SKIN_ID_PHIL 					112
#define SKIN_ID_ROCKSTAR_GUY 			113
#define SKIN_ID_SONNY 					114
#define SKIN_ID_LANCE_A 				115
#define SKIN_ID_MERCADES_A 				116
#define SKIN_ID_LOVE_FIST_C 			117
#define SKIN_ID_ALEX_SRUB 				118
#define SKIN_ID_LANCE_COP 				119
#define SKIN_ID_LANCE_B 				120
#define SKIN_ID_CORTEZ 					121
#define SKIN_ID_LOVE_FIST_D 			122
#define SKIN_ID_COLUMBIAN_GUY_A 		123
#define SKIN_ID_HILARY_ROBBER 			124
#define SKIN_ID_MERCADES_B 				125
#define SKIN_ID_CAM 					126
#define SKIN_ID_CAM_ROBBER 				127
#define SKIN_ID_PHIL_ONE_ARM 			128
#define SKIN_ID_PHIL_ROBBER 			129
#define SKIN_ID_COOL_GUY_D 				130
#define SKIN_ID_PIZZAMAN 				131
#define SKIN_ID_TAXI_DRIVER_C 			132
#define SKIN_ID_TAXI_DRIVER_D 			133
#define SKIN_ID_SAILOR_A 				134
#define SKIN_ID_SAILOR_B 				135
#define SKIN_ID_SAILOR_C 				136
#define SKIN_ID_CHEF 					137
#define SKIN_ID_CRIMINAL_B 				138
#define SKIN_ID_FRENCH_GUY 				139
#define SKIN_ID_GARBAGEMAN_B 			140
#define SKIN_ID_HATIAN_E 				141
#define SKIN_ID_WAITRESS_B 				142
#define SKIN_ID_SONNY_GUY_A 			143
#define SKIN_ID_SONNY_GUY_B 			144
#define SKIN_ID_SONNY_GUY_C 			145
#define SKIN_ID_COLUMBIAN_GUY_B 		146
#define SKIN_ID_THUG_A 					147
#define SKIN_ID_BEACH_GUY_H 			148
#define SKIN_ID_GARBAGEMAN_C 			149
#define SKIN_ID_GARBAGEMAN_D 			150
#define SKIN_ID_GARBAGEMAN_E 			151
#define SKIN_ID_TRANNY 					152
#define SKIN_ID_THUG_B 					153
#define SKIN_ID_SPANDEX_GUY_A 			154
#define SKIN_ID_SPANDEX_GUY_B 			155
#define SKIN_ID_STRIPPER_A 				156
#define SKIN_ID_STRIPPER_B 				157
#define SKIN_ID_STRIPPER_C 				158
#define SKIN_ID_STORE_CLERK 			159

int GetSkinID(const SQChar* name)
{
	// Verify that the name is valid and could actually represent a skin name
	if (name == NULL || strlen(name) < 1) return SKIN_ID_UNKNOWN;

	// Create a temporary variable that will hold the actual ID
	int id = SKIN_ID_UNKNOWN;

	// Allocate memory for an editable version of the string
	char *str = (char*)malloc(strlen(name) + 1);

	// Verify that the memory could be allocated and prepare the string
	if (str != NULL)
	{
		int i, j = 0;
		// Convert the string to lowercase and remove non alpha-numeric characters
		for(i = 0; name[i]; i++)
		{
			if (isalnum(name[i]) != 0)
			{
		  		str[j] = tolower(name[i]);
		  		j++;
			}
		}
		// Add the null character to the final string
        str[j] = '\0';
		// Make sure the string had any valid characters
		if (strlen(str) < 1) {
			// Free the previously allocated resources
			free(str);
			// Return the found ID
			return id;
		}
	}
	// No point in going forward
	else return id;

	// Grab the actual length of the string
	int len = strlen(str);

	// Get the most significant characters used to identify a skin
	char a, b, c, d;
	a = tolower(name[0]);
	b = 0;
	c = 0;
	d = tolower(str[len-1]);

	// Look for deeper specifiers
	if (strlen(name) >= 3)
	{
		b = tolower(name[1]);
		c = tolower(name[2]);
	}
	else if ( strlen(name) >= 2 )
	{
		b = tolower(name[1]);
	}

	// Search for a pattern in the name
	switch (a)
	{
		// [A]lex Srub, [A]rabic guy, [A]rmy
		case 'a':
			switch (b)
			{
				// [Al]ex [S]rub
				case 'l':
				case 's':
					id = SKIN_ID_ALEX_SRUB;
				break;
				// [A]rabic [g]uy
				case 'g':
					id = SKIN_ID_ARABIC_GUY;
				break;
				// [Ara]bic guy, [Arm]y
				case 'r':
					if (c && c == 'a') id = SKIN_ID_ARABIC_GUY;
					else if (c && c == 'm') id = SKIN_ID_ARMY;
				break;
			}
		break;
		// [B]each guy (#1|A)/(#2|B)/(#3|C)/(#4|D)/(#5|E)/(#6|F)/(#7|G)/(#8|H)
		// [B]each lady (#1|A)/(#2|B)/(#3|C)/(#4|D)/(#5|E)/(#6|F)/(#7|G)
		// [B]iker (#1|A)/(#2|B)
		// [B]um guy (#1|A)/(#2|B)/(#3|C)
		// [B]um lady (#1|A)/(#2|B)/(#2|C)/(#3|D)/(#4|E)
		// [B]usiness man (#1|A)/(#2|B)/(#3|C)/(#4|D)/(#5|E)/(#6|F)
		case 'b':
			// [Be]ach [g]uy (#1|A)/(#2|B)/(#3|C)/(#4|D)/(#5|E)/(#6|F)/(#7|G)/(#8|H)
			if (b && b == 'e' && ((c && c == 'g') || (len >= 6 && str[5] == 'g')))
			{
				switch (d)
				{
					case '1':
					case 'a':
						id = SKIN_ID_BEACH_GUY_A;
					break;
					case '2':
					case 'b':
						id = SKIN_ID_BEACH_GUY_B;
					break;
					case '3':
					case 'c':
						id = SKIN_ID_BEACH_GUY_C;
					break;
					case '4':
					case 'd':
						id = SKIN_ID_BEACH_GUY_D;
					break;
					case '5':
					case 'e':
						id = SKIN_ID_BEACH_GUY_E;
					break;
					case '6':
					case 'f':
						id = SKIN_ID_BEACH_GUY_F;
					break;
					case '7':
					case 'g':
						id = SKIN_ID_BEACH_GUY_G;
					break;
					case '8':
					case 'h':
						id = SKIN_ID_BEACH_GUY_H;
					break;
				}
			}
			// [Be]ach [l]ady (#1|A)/(#2|B)/(#3|C)/(#4|D)/(#5|E)/(#6|F)/(#7|G)
			else if (b && b == 'e' && ((c && c == 'l') || (len >= 6 && str[5] == 'l')))
			{
				switch (d)
				{
					case '1':
					case 'a':
						id = SKIN_ID_BEACH_LADY_A;
					break;
					case '2':
					case 'b':
						id = SKIN_ID_BEACH_LADY_B;
					break;
					case '3':
					case 'c':
						id = SKIN_ID_BEACH_LADY_C;
					break;
					case '4':
					case 'd':
						id = SKIN_ID_BEACH_LADY_D;
					break;
					case '5':
					case 'e':
						id = SKIN_ID_BEACH_LADY_E;
					break;
					case '6':
					case 'f':
						id = SKIN_ID_BEACH_LADY_F;
					break;
					case '7':
					case 'g':
						id = SKIN_ID_BEACH_LADY_G;
					break;
				}
			}
			// [Bi]ker (#1|A)/(#2|B)
			else if (b && b == 'i' && (d == '1' || d == 'a')) id = SKIN_ID_BIKER_A;
			else if (b && b == 'i' && (d == '2' || d == 'b')) id = SKIN_ID_BIKER_B;
			// [Bum] [g]uy (#1|A)/(#2|B)/(#3|C)
			// [Bum] [l]ady (#1|A)/(#2|B)/(#2|C)/(#3|D)/(#4|E)
			else if (b && b == 'u' && (c && (c == 'm' || c == 'g' || c == 'l')))
			{
				// [Bum] [g]uy (#1|A)/(#2|B)/(#3|C)
				if (c == 'g' || (len >= 4 && str[3] == 'g'))
				{
					if (d == '1' || d == 'a') id = SKIN_ID_BUM_GUY_A;
					else if (d == '2' || d == 'b') id = SKIN_ID_BUM_GUY_B;
					else if (d == '3' || d == 'c') id = SKIN_ID_BUM_GUY_C;
				}
				// [Bum] [l]ady (#1|A)/(#2|B)/(#2|C)/(#3|D)/(#4|E)
				else if (c == 'l' || (len >= 4 && str[3] == 'l'))
				{
					if (d == '1' || d == 'a') id = SKIN_ID_BUM_LADY_A;
					else if (d == '2' || d == 'b') id = SKIN_ID_BUM_LADY_B;
					else if (d == '2' || d == 'c') id = SKIN_ID_BUM_LADY_C;
					else if (d == '3' || d == 'd') id = SKIN_ID_BUM_LADY_D;
					else if (d == '4' || d == 'e') id = SKIN_ID_BUM_LADY_E;
				}
			}
			// [Bus]iness [m]an (#1|A)/(#2|B)/(#3|C)/(#4|D)/(#5|E)/(#6|F)
			else if (b && b == 'u' && ((c && c == 's') || (len >= 10 && str[9] == 'm')))
			{
				switch (d)
				{
					case '1':
					case 'a':
						id = SKIN_ID_BUSINESS_MAN_A;
					break;
					case '2':
					case 'b':
						id = SKIN_ID_BUSINESS_MAN_B;
					break;
					case '3':
					case 'c':
						id = SKIN_ID_BUSINESS_MAN_C;
					break;
					case '4':
					case 'd':
						id = SKIN_ID_BUSINESS_MAN_D;
					break;
					case '5':
					case 'e':
						id = SKIN_ID_BUSINESS_MAN_E;
					break;
					case '6':
					case 'f':
						id = SKIN_ID_BUSINESS_MAN_F;
					break;
				}
			}
		break;
		// [C]am, [C]am (Robber), [C]andy Suxx, [C]hef
		// [C]hurch guy, [C]hurch lady, [C]lub lady
		// [C]olumbian guy (#1|A)/(#2|B),
		// [C]onstruction worker (#1|A)/(#2|B)
		// [C]ool guy (#1|A)/(#2|B)/(#3|C)/(#4|D)
		// [C]op, [C]ortez
		// [C]riminal (#1|A)/(#2|B)
		// [C]uban (#1|A)/(#2|B)
		case 'c':
			// [Ca]m, [Ca]m (Robber), [Ca]ndy Suxx
			if (b && b == 'a')
			{
				// [Cam] ([R]obbe[r])
				if (c && (c == 'm' || c == 'r') && d == 'r') id = SKIN_ID_CAM_ROBBER;
				// [Cam]
				else if (c && c == 'm') id = SKIN_ID_CAM;
				// [Can]dy [S]ux[x]
				else if (c && (c == 'n' || c == 's' || d == 'x')) id = SKIN_ID_CANDY_SUXX;
			}
			// [Ch]ef, [Ch]urch guy, [Ch]urch lady
			else if (b && b == 'h')
			{
				// [Che][f]
				if (c && (c == 'e' || d == 'f')) id = SKIN_ID_CHEF;
				// [Chu]rch [g]uy
				else if (c && ((c == 'u' && len >= 7 && str[6] == 'g') || (c == 'g')))
					id = SKIN_ID_CHURCH_GUY;
				// [Chu]rch [l]ady
				else if (c && ((c == 'u' && len >= 7 && str[6] == 'l') || (c == 'l')))
					id = SKIN_ID_CHURCH_LADY;
			}
			// [Cl]ub [l]ady
			else if (b && b == 'l') id = SKIN_ID_CLUB_LADY;
			// [Co]lumbian guy (#1|A)/(#2|B)
			// [Co]nstruction worker (#1|A)/(#2|B)
			// [Co]ol guy (#1|A)/(#2|B)/(#3|C)/(#4|D)
			// [Co]p, [Co]rtez
			else if (b && b == 'o')
			{
				// [Col]umbian [g]uy (#1|A)/(#2|B)
				if (c && ((c == 'l' && len >= 10 && str[9] == 'g') || (c == 'g')))
				{
					if (d == '1' || d == 'a') id = SKIN_ID_COLUMBIAN_GUY_A;
					else if (d == '2' || d == 'b') id = SKIN_ID_COLUMBIAN_GUY_B;
				}
				// [Con]struction [w]orker (#1|A)/(#2|B)
				else if (c && (c == 'n' || (len >= 13 && str[12] == 'g')))
				{
					if (d == '1' || d == 'a') id = SKIN_ID_CONSTRUCTION_WORKER_A;
					else if (d == '2' || d == 'b') id = SKIN_ID_CONSTRUCTION_WORKER_B;
				}
				// [Coo]l guy (#1|A)/(#2|B)/(#3|C)/(#4|D)
				else if (c && c == 'o')
				{
					switch (d)
					{
						case '1':
						case 'a':
							id = SKIN_ID_COOL_GUY_A;
						break;
						case '2':
						case 'b':
							id = SKIN_ID_COOL_GUY_B;
						break;
						case '3':
						case 'c':
							id = SKIN_ID_COOL_GUY_C;
						break;
						case '4':
						case 'd':
							id = SKIN_ID_COOL_GUY_D;
						break;
					}
				}
				// [Cop]
				else if (c && c == 'p') id = SKIN_ID_COP;
				// [Cor]te[z]
				else if (c && (c == 'r' || c == 'z' || d == 'z')) id = SKIN_ID_CORTEZ;
			}
			// [Cr]iminal (#1|A)/(#2|B)
			else if (b && b == 'r' && (d == '1' || d == 'a')) id = SKIN_ID_CRIMINAL_A;
			else if (b && b == 'r' && (d == '2' || d == 'b')) id = SKIN_ID_CRIMINAL_B;
			// [Cu]ban (#1|A)/(#2|B)
			else if (b && b == 'u' && (d == '1' || d == 'a')) id = SKIN_ID_CUBAN_A;
			else if (b && b == 'u' && (d == '2' || d == 'b')) id = SKIN_ID_CUBAN_B;
		break;
		// [D]BP security (#1|A)/(#2|B)
		// [D]iaz guy (#1|A)/(#2|B)
		case 'd':
			switch (b)
			{
				// [DB]P [s]ecurity (#1|A)/(#2|B)
				case 'b':
				case 's':
					if (d == '1' || d == 'a') id = SKIN_ID_DBP_SECURITY_A;
					else if (d == '2' || d == 'b') id = SKIN_ID_DBP_SECURITY_B;
				break;
				// [Di]a[z] [g]uy (#1|A)/(#2|B)
				case 'i':
				case 'z':
				case 'g':
					if (d == '1' || d == 'a') id = SKIN_ID_DIAZ_GUY_A;
					else if (d == '2' || d == 'b') id = SKIN_ID_DIAZ_GUY_B;
				break;
			}
		break;
		// [F]BI, [F]ireman, [F]ood lady, [F]rench guy
		case 'f':
			switch (b)
			{
				// [FB]I
				case 'b':
					id = SKIN_ID_FBI;
				break;
				// [Fi]re[m]an
				case 'i':
				case 'm':
					id = SKIN_ID_FIREMAN;
				break;
				// [Fo]od [l]ady
				case 'o':
				case 'l':
					id = SKIN_ID_FOOD_LADY;
				break;
				// [Fr]ench [g]uy
				case 'r':
				case 'g':
					id = SKIN_ID_FRENCH_GUY;
				break;
			}
		break;
		// [G]arbageman (#1|A)/(#2|B)/(#3|C)/(#4|D)/(#5|E)
		// [G]olf guy (#1|A)/(#2|B)/(#3|C)
		// [G]olf lady
		// [G]ranny (#1|A)/(#2|B)
		// [G]ym guy, [G]ym lady
		case 'g':
			// [Ga]rbage[m]an (#1|A)/(#2|B)/(#3|C)/(#4|D)/(#5|E)
			if (b && (b == 'a' || b == 'm'))
			{
				switch (d)
				{
					case '1':
					case 'a':
						id = SKIN_ID_GARBAGEMAN_A;
					break;
					case '2':
					case 'b':
						id = SKIN_ID_GARBAGEMAN_B;
					break;
					case '3':
					case 'c':
						id = SKIN_ID_GARBAGEMAN_C;
					break;
					case '4':
					case 'd':
						id = SKIN_ID_GARBAGEMAN_D;
					break;
					case '5':
					case 'e':
						id = SKIN_ID_GARBAGEMAN_E;
					break;
				}
			}
			// [Go]lf [g]uy (#1|A)/(#2|B)/(#3|C)
			else if (b && b == 'o' && ((c && c == 'g') || (len >= 5 && str[4] == 'g')))
			{
				switch (d)
				{
					case '1':
					case 'a':
						id = SKIN_ID_GOLF_GUY_A;
					break;
					case '2':
					case 'b':
						id = SKIN_ID_GOLF_GUY_B;
					break;
					case '3':
					case 'c':
						id = SKIN_ID_GOLF_GUY_C;
					break;
				}
			}
			// [Go]lf [l]ady
			else if (b && b == 'o' && ((c && c == 'l') || (len >= 5 && str[4] == 'l')))
				id = SKIN_ID_GOLF_LADY;
			// [Gr]anny (#1|A)/(#2|B)
			else if (b && b == 'r')
			{
				if (d == '1' || d == 'a') id = SKIN_ID_GRANNY_A;
				else if (d == '2' || d == 'b') id = SKIN_ID_GRANNY_B;
			}
			// [Gy]m [g]uy
			else if (b && (b == 'g' || (b == 'y' && len >= 4 && str[3] == 'g')))
				id = SKIN_ID_GYM_GUY;
			// [Gy]m [l]ady
			else if (b && (b == 'l' || (b == 'y' && len >= 4 && str[3] == 'l')))
				id = SKIN_ID_GYM_LADY;
		break;
		// [H]atian (#1|A)/(#2|B)/(#3|C)/(#4|D)/(#5|E)
		// [H]ilary, [H]ilary (Robber), [H]ood lady
		case 'h':
			// [H]atian (#1|A)/(#2|B)/(#3|C)/(#4|D)/(#5|E)
			if (b && b == 'a')
			{
				switch (d)
				{
					case '1':
					case 'a':
						id = SKIN_ID_HATIAN_A;
					break;
					case '2':
					case 'b':
						id = SKIN_ID_HATIAN_B;
					break;
					case '3':
					case 'c':
						id = SKIN_ID_HATIAN_C;
					break;
					case '4':
					case 'd':
						id = SKIN_ID_HATIAN_D;
					break;
					case '5':
					case 'e':
						id = SKIN_ID_HATIAN_E;
					break;
				}
			}
			// [Hi]lary ([R]obbe[r])
			else if (b && (b == 'i' || b == 'r') && d == 'r') id = SKIN_ID_HILARY_ROBBER;
			// [Hi]lary
			else if (b && b == 'i') id = SKIN_ID_HILARY;
			// [Ho]od [l]ady
			if (b && (b == 'o' || b == 'l')) id = SKIN_ID_HOOD_LADY;
		break;
		// [K]en Rosenburg
		case 'k':
			id = SKIN_ID_KEN_ROSENBURG;
		break;
		// [L]ance (#1|A)/(#1|B)
		// [L]ance (Cop)
		// [L]awyer
		// [L]ove Fist (#1|A)/(#2|B)/(#3|C)/(#3|D)
		case 'l':
			//[Lan]ce ([C]o[p])
			if ((b && b == 'a') && (c && c == 'n') && ((len >= 6 && str[5] == 'c') || d == 'p'))
				id = SKIN_ID_LANCE_COP;
			else if (b && (b == 'c' ||  (b == 'a' && (c && c == 'n'))))
				id = SKIN_ID_LANCE_COP;
			// [La]nce (#1|A)/(#1|B)
			else if (b && b == 'a' && c && c == 'n')
			{
				if (d == '1' || d == 'a') id = SKIN_ID_LANCE_A;
				else if (d == '2' || d == 'b') id = SKIN_ID_LANCE_B;
			}
			// [Law]yer
			else if (b && (b == 'w' || (b == 'a' && c && c == 'w'))) id = SKIN_ID_LAWYER;
			// [Lo]ve [F]ist (#1|A)/(#2|B)/(#3|C)/(#3|D)
			else if (b && (b == 'o' || b == 'f'))
			{
				switch (d)
				{
					case '1':
					case 'a':
						id = SKIN_ID_LOVE_FIST_A;
					break;
					case '2':
					case 'b':
						id = SKIN_ID_LOVE_FIST_B;
					break;
					case '3':
					case 'c':
						id = SKIN_ID_LOVE_FIST_C;
					break;
					case 'd':
						id = SKIN_ID_LOVE_FIST_D;
					break;
				}
			}
		break;
		// [M]ercades
		case 'm':
			if (d == 'b') id = SKIN_ID_MERCADES_B;
			else id = SKIN_ID_MERCADES_A;
		break;
		// [O]ffice lady (#1|A)/(#2|B)
		case 'o':
			if (d == '1' || d == 'a') id = SKIN_ID_OFFICE_LADY_A;
			else if (d == '2' || d == 'b') id = SKIN_ID_OFFICE_LADY_B;
		break;
		// [P]aramedic, [P]hil,  [P]hil (One arm), [P]hil (Robber)
		// [P]imp, [P]izzaman
		// [P]rostitute (#1|A)/(#2|B)/(#2|C)/(#2|D)/(#3|D)/(#4|D)
		// [P]unk (#1|A)/(#2|B)/(#3|C)
		case 'p':
			// [Pa]ramedic
			if (b && b == 'a') id = SKIN_ID_PARAMEDIC;
			// [Ph]il (One arm), [Ph]il (Robber)
			else if (b && b == 'h')
			{
				// [Ph]il ([O]ne ar[m])
				if (b == 'o' || (c && c == 'o') || (len >= 5 && str[4] == 'o') || d == 'm')
					id = SKIN_ID_PHIL_ONE_ARM;
				// [Ph]il ([R]obbe[r])
				else if (c && (c == 'r' || d == 'r' || (len >= 5 && str[4] == 'r')))
					id = SKIN_ID_PHIL_ROBBER;
				// [Phi]l
				else if (c && c == 'i') id = SKIN_ID_PHIL;
			}
			// [Pim][p]
			else if (b && b == 'i' && ((c && c == 'm') || d == 'p')) id = SKIN_ID_PIMP;
			// [Piz]zama[n]
			else if (b && b == 'i' && ((c && c == 'z') || d == 'n')) id = SKIN_ID_PIZZAMAN;
			// [Pr]ostitute (#1|A)/(#2|B)/(#2|C)/(#2|D)/(#3|D)/(#4|D)
			else if (b && b == 'r')
			{
				switch (d)
				{
					case '1':
					case 'a':
						id = SKIN_ID_PROSTITUTE_A;
					break;
					case '2':
					case 'b':
						id = SKIN_ID_PROSTITUTE_B;
					break;
					case 'c':
						id = SKIN_ID_PROSTITUTE_C;
					break;
					case 'd':
						id = SKIN_ID_PROSTITUTE_D;
					break;
					case '3':
					case 'e':
						id = SKIN_ID_PROSTITUTE_E;
					break;
					case '4':
					case 'f':
						id = SKIN_ID_PROSTITUTE_F;
					break;
				}
			}
			// [Pu]nk (#1|A)/(#2|B)/(#3|C)
			else if (b && b == 'u')
			{
				switch (d)
				{
					case '1':
					case 'a':
						id = SKIN_ID_PUNK_A;
					break;
					case '2':
					case 'b':
						id = SKIN_ID_PUNK_B;
					break;
					case '3':
					case 'c':
						id = SKIN_ID_PUNK_C;
					break;
				}
			}
		break;
		// [R]ich guy, [R]ockstar guy
		case 'r':
			// [Ri]ch guy
			if (b && b == 'i') id = SKIN_ID_RICH_GUY;
			// [Ro]ckstar guy
			else if (b && b == 'o') id = SKIN_ID_ROCKSTAR_GUY;
		break;
		// [S]ailor (#1|A)/(#2|B)/(#3|C)
		// [S]hark (#1|A)/(#2|B)
		// [S]hopper (#1|A)/(#2|B)
		// [S]kate guy, [S]kate lady, [S]onny
		// [S]onny guy (#1|A)/(#2|B)/(#3|C)
		// [S]pandEx (#1|A)/(#2|B)
		// [S]panish guy
		// [S]panish lady (#1|A)/(#2|B)/(#3|C)/(#4|D)
		// [S]tore clerk
		// [S]tripper (#1|A)/(#2|B)/(#3|C)
		// [S]wat
		case 's':
			// [Sa]ilor (#1|A)/(#2|B)/(#3|C)
			if (b && b == 'a')
			{
				switch (d)
				{
					case '1':
					case 'a':
						id = SKIN_ID_SAILOR_A;
					break;
					case '2':
					case 'b':
						id = SKIN_ID_SAILOR_B;
					break;
					case '3':
					case 'c':
						id = SKIN_ID_SAILOR_C;
					break;
				}
			}
			// [S]hark (#1|A)/(#2|B)
			else if (b && b == 'h' && (c && c == 'a'))
			{
				switch (d)
				{
					case '1':
					case 'a':
						id = SKIN_ID_SHARK_A;
					break;
					case '2':
					case 'b':
						id = SKIN_ID_SHARK_B;
					break;
				}
			}
			// [S]hopper (#1|A)/(#2|B)
			else if (b && b == 'h' && (c && c == 'o'))
			{
				switch (d)
				{
					case '1':
					case 'a':
						id = SKIN_ID_SHOPPER_A;
					break;
					case '2':
					case 'b':
						id = SKIN_ID_SHOPPER_B;
					break;
				}
			}
			// [Sk]ate [g]uy
			else if (b && b == 'k' && ((c && c == 'g') || (len >= 6 && str[5] == 'g')))
				id = SKIN_ID_SKATE_GUY;
			// [Sk]ate [l]ady
			else if (b && b == 'k' && ((c && c == 'l') || (len >= 6 && str[5] == 'l')))
				id = SKIN_ID_SKATE_LADY;
			// [So]nny
			// [So]nny guy (#1|A)/(#2|B)/(#3|C)
			else if (b && b == 'o')
			{
				switch (d)
				{
					case '1':
					case 'a':
						id = SKIN_ID_SONNY_GUY_A;
					break;
					case '2':
					case 'b':
						id = SKIN_ID_SONNY_GUY_B;
					break;
					case '3':
					case 'c':
						id = SKIN_ID_SONNY_GUY_C;
					break;
				}
			}
			else if (b && b == 'g')
			{
								switch (d)
				{
					case '1':
					case 'a':
						id = SKIN_ID_SONNY_GUY_A;
					break;
					case '2':
					case 'b':
						id = SKIN_ID_SONNY_GUY_B;
					break;
					case '3':
					case 'c':
						id = SKIN_ID_SONNY_GUY_C;
					break;
				}
			}
			// [Sp]andE[x] (#1|A)/(#2|B)
			else if (b && b == 'p' && ((c && c == 'x') || (len >= 7 && str[6] == 'x')))
			{
				switch (d)
				{
					case '1':
					case 'a':
						id = SKIN_ID_SPANDEX_GUY_A;
					break;
					case '2':
					case 'b':
						id = SKIN_ID_SPANDEX_GUY_B;
					break;
				}
			}
			// [Sp]anish [g]uy
			else if (b && b == 'p' && ((c && c == 'g') || (len >= 8 && str[7] == 'g')))
				id = SKIN_ID_SPANISH_GUY;
			// [Sp]anish [l]ady (#1|A)/(#2|B)/(#3|C)/(#4|D)
			else if (b && b == 'p' && ((c && c == 'l') || (len >= 8 && str[7] == 'l')))
			{
				switch (d)
				{
					case '1':
					case 'a':
						id = SKIN_ID_SPANISH_LADY_A;
					break;
					case '2':
					case 'b':
						id = SKIN_ID_SPANISH_LADY_B;
					break;
					case '3':
					case 'c':
						id = SKIN_ID_SPANISH_LADY_C;
					break;
					case '4':
					case 'd':
						id = SKIN_ID_SPANISH_LADY_D;
					break;
				}
			}
			// [Sto]re clerk
			else if ((b && b == 't') && (c && c == 'o')) id = SKIN_ID_STORE_CLERK;
			// [Str]ipper (#1|A)/(#2|B)/(#3|C)
			else if ((b && b == 't') && (c && c == 'r'))
			{
				switch (d)
				{
					case '1':
					case 'a':
						id = SKIN_ID_STRIPPER_A;
					break;
					case '2':
					case 'b':
						id = SKIN_ID_STRIPPER_B;
					break;
					case '3':
					case 'c':
						id = SKIN_ID_STRIPPER_C;
					break;
				}
			}
			// [Sw]at
			else if (b && b == 'w') id = SKIN_ID_SWAT;
		break;
		// [T]axi driver (#1|A)/(#1|B)/(#2|C)/(#2|D)
		// [T]hug (#1|A)/(#2|B)
		// [T]ommy Vercetti
		// [T]ourist (#1|A)/(#2|B)
		// [T]ranny
		case 't':
			switch (b)
			{
				// [Ta]xi driver (#1|A)/(#1|B)/(#2|C)/(#2|D)
				case 'a':
					switch (d)
					{
						case '1':
						case 'a':
							id = SKIN_ID_TAXI_DRIVER_A;
						break;
						case '2':
						case 'b':
							id = SKIN_ID_TAXI_DRIVER_B;
						break;
						case 'c':
							id = SKIN_ID_TAXI_DRIVER_C;
						break;
						case 'd':
							id = SKIN_ID_TAXI_DRIVER_D;
						break;
					}
				break;
				// [Th]ug (#1|A)/(#2|B)
				case 'h':
					switch (d)
					{
						case '1':
						case 'a':
							id = SKIN_ID_THUG_A;
						break;
						case '5':
						case 'b':
							id = SKIN_ID_THUG_B;
						break;
					}
				break;
				// [To]mmy [V]ercetti
				// [To]urist (#1|A)/(#2|B)
				case 'v':
					id = SKIN_ID_TOMMY_VERCETTI;
				break;
				case 'o':
					if (c && c == 'm') id = SKIN_ID_TOMMY_VERCETTI;
					else if (c && c == 'u' && (d == '1' || d == 'a')) id = SKIN_ID_TOURIST_A;
					else if (c && c == 'u' && (d == '2' || d == 'b')) id = SKIN_ID_TOURIST_B;
				break;
				case 'r':
					id = SKIN_ID_TRANNY;
				break;
			}
		break;
		// [U]ndercover cop (#1|A)/(#2|B)/(#3|C)/(#4|D)/(#5|E)/(#6|F)
		case 'u':
			switch (d)
			{
				case '1':
				case 'a':
					id = SKIN_ID_UNDERCOVER_COP_A;
				break;
				case '2':
				case 'b':
					id = SKIN_ID_UNDERCOVER_COP_B;
				break;
				case '3':
				case 'c':
					id = SKIN_ID_UNDERCOVER_COP_C;
				break;
				case '4':
				case 'd':
					id = SKIN_ID_UNDERCOVER_COP_D;
				break;
				case '5':
				case 'e':
					id = SKIN_ID_UNDERCOVER_COP_E;
				break;
				case '6':
				case 'f':
					id = SKIN_ID_UNDERCOVER_COP_F;
				break;
			}
		break;
		// [V]ercetti guy (#1|A)/(#2|B)
		case 'v':
			switch (d)
			{
				case '1':
				case 'a':
					id = SKIN_ID_VERCETTI_GUY_A;
				break;
				case '2':
				case 'b':
					id = SKIN_ID_VERCETTI_GUY_B;
				break;
			}
		break;
		// [W]aitress (#1|A)/(#2|B)
		case 'w':
			switch (d)
			{
				case '1':
				case 'a':
					id = SKIN_ID_WAITRESS_A;
				break;
				case '2':
				case 'b':
					id = SKIN_ID_WAITRESS_B;
				break;
			}
		break;
	}
	// Free the previously allocated resources
	free(str);
	// Return the found ID
	return id;
}
