#include "FunctionHandler.h"
#include "Functions.h"
#include "ConsoleUtils.h"
#include "CCore.h"
#include "main.h"

inline void szlower( char * string )
{
	int i;
	for( i = 0; string[i]; i++ )
		string[i] = tolower( string[i] );
}

// Tha core
extern CCore * pCore;

void ClientMessage( const SQChar * message, CPlayer * player, int r, int g, int b, int a )
{
	if( player != NULL )
	{
		unsigned int dwColour;

		dwColour  = ( r << 24 );
		dwColour += ( ( g & 0xFF ) << 16 );
		dwColour += ( ( b & 0xFF ) << 8 );
		dwColour += ( a & 0xFF );

		functions->SendClientMessage( player->nPlayerId, dwColour, "%s", message );
	}
}

void ClientMessageToAll ( const SQChar* message, int r, int g, int b, int a )
{
	for( int i = 0; i < functions->GetMaxPlayers(); i++ )
	{
		if( functions->IsPlayerConnected( i ) )
			ClientMessage( message, pCore->playerMap[i], r, g, b, a );
	}
}

void GameMessage   ( CPlayer * player, const SQChar* message, int type )
{
	if( player != NULL )
		functions->SendGameMessage( player->nPlayerId, type, const_cast<char *>( message ) );
}

void GameMessageToAll( const SQChar * message, int type )
{
	functions->SendGameMessage( -1, type, const_cast<char *>( message ) );
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
	char * serverName = new char[128];
	functions->GetServerName( serverName, 128 );

	return serverName;
}

int GetMaxPlayers() { return functions->GetMaxPlayers(); }

const SQChar * GetServerPassword()
{
	char * password = new char[128];
	functions->GetServerPassword( password, 128 );

	return password;
}

const SQChar * GetGameModeText()
{
	char * gamemode = new char[96];
	functions->GetGameModeText( gamemode, 96 );

	return gamemode;
}

unsigned int GetTimeRate()   { return ( functions->GetTimeRate() != 0 );   }
int          GetHour()       { return ( functions->GetHour() != 0 );       }
int          GetMinute()     { return ( functions->GetMinute() != 0 );     }
int          GetWeather()    { return ( functions->GetWeather() != 0 );    }
float        GetGravity()    { return ( functions->GetGravity() != 0 );    }
float        GetGamespeed()  { return ( functions->GetGamespeed() != 0 );  }
float        GetWaterLevel() { return ( functions->GetWaterLevel() != 0 ); }
float        GetMaxHeight()  { return ( functions->GetMaxHeight() != 0 );  }

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

bool EnabledSyncFrameLimiter() { return ( functions->EnabledSyncFrameLimiter() != 0 ); }
bool EnabledFrameLimiter()     { return ( functions->EnabledFrameLimiter() != 0 );     }
bool EnabledTaxiBoostJump()    { return ( functions->EnabledTaxiBoostJump() != 0 );    }
bool EnabledDriveOnWater()     { return ( functions->EnabledDriveOnWater() != 0 );     }
bool EnabledFastSwitch()       { return ( functions->EnabledFastSwitch() != 0 );       }
bool EnabledFriendlyFire()     { return ( functions->EnabledFriendlyFire() != 0 );     }
bool EnabledDisableDriveby()   { return ( functions->EnabledDisableDriveby() != 0 );   }
bool EnabledPerfectHandling()  { return ( functions->EnabledPerfectHandling() != 0 );  }
bool EnabledFlyingCars()       { return ( functions->EnabledFlyingCars() != 0 );       }
bool EnabledJumpSwitch()       { return ( functions->EnabledJumpSwitch() != 0 );       }
bool EnabledShowOnRadar()      { return ( functions->EnabledShowMarkers() != 0 );      }
bool EnabledStuntBike()        { return ( functions->EnabledStuntBike() != 0 );        }
bool EnabledShootInAir()       { return ( functions->EnabledShootInAir() != 0 );       }
bool EnabledShowNametags()     { return ( functions->EnabledShowNametags() != 0 );     }
bool EnabledJoinMessages()     { return ( functions->EnabledJoinMessages() != 0 );     }
bool EnabledDeathMessages()    { return ( functions->EnabledDeathMessages() != 0 );    }

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
	unsigned int dwColour = colour->r;
	dwColour = (dwColour << 8) + colour->g;
	dwColour = (dwColour << 8) + colour->b;

	functions->AddPlayerClass( team, dwColour, skin, spawnPos->x, spawnPos->y, spawnPos->z, spawnAngle, wep1, ammo1, wep2, ammo2, wep3, ammo3 );
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
	if( vId < 1 )
		return NULL;
	else
	{
		CVehicle * v = new CVehicle;
		v->Init( vId );

		pCore->vehicleMap[vId] = v;
		return v;
	}
}

CPickup * CreatePickup( int model, int world, int quantity, Vector * pos, int alpha, bool isAuto )
{
	int pId = functions->CreatePickup( model, world, quantity, pos->x, pos->y, pos->z, alpha, isAuto );
	if( pId < 0 )
		return NULL;
	else
	{
		CPickup * p = new CPickup;
		p->Init( pId );

		pCore->pickupMap[pId] = p;
		return p;
	}
}

CObject * CreateObject( int model, int world, Vector * pos, int alpha )
{
	int oId = functions->CreateObject( model, world, pos->x, pos->y, pos->z, alpha );
	if( oId < 0 )
		return NULL;
	else
	{
		CObject * o = new CObject;
		o->Init( oId );

		pCore->objectMap[oId] = o;
		return o;
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

CPickup * FindPickup( int id )
{
	if( id < MAX_PICKUPS )
		return pCore->pickupMap[id];

	return NULL;
}

CObject * FindObject( int id )
{
	if( id < MAX_OBJECTS )
		return pCore->objectMap[id];

	return NULL;
}

CVehicle * FindVehicle( int id )
{
	if( id < MAX_VEHICLES )
		return pCore->vehicleMap[id];

	return NULL;
}

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
	unsigned int rDeathTime, rFadeTime, rCorpseFadeDelay, rCorpseFadeTime, dwColour;

	rDeathTime       = static_cast<unsigned int>(deathTime);
	rFadeTime        = static_cast<unsigned int>(fadeTime);
	rCorpseFadeDelay = static_cast<unsigned int>(corpseFadeDelay);
	rCorpseFadeTime  = static_cast<unsigned int>(corpseFadeTime);
	
	dwColour = colour.r;
	dwColour = (dwColour << 8) + colour.g;
	dwColour = (dwColour << 16) + colour.b;

	functions->SetWastedSettings
	(
		rDeathTime,
		rFadeTime,
		fadeInSpeed,
		fadeOutSpeed,
		dwColour,
		corpseFadeDelay,
		corpseFadeTime
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

void HideMapObject( int nModelId, float x, float y, float z )
{
	int x2 = static_cast<int>(floor( ( x * 10.0f ) + 0.5f ));
	int y2 = static_cast<int>(floor( ( y * 10.0f ) + 0.5f ));
	int z2 = static_cast<int>(floor( ( y * 10.0f ) + 0.5f ));

	functions->HideMapObject( nModelId, x2, y2, z2 );
}

void ShowMapObject( int nModelId, float x, float y, float z )
{
	int x2 = static_cast<int>(floor( ( x * 10.0f ) + 0.5f ));
	int y2 = static_cast<int>(floor( ( y * 10.0f ) + 0.5f ));
	int z2 = static_cast<int>(floor( ( y * 10.0f ) + 0.5f ));

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

void Message            ( const SQChar * message ) { functions->SendClientMessage( -1, 0x0b5fa5ff, message ); }
void MessagePlayer      ( const SQChar * message, CPlayer * player )
{
	if( player != NULL )
		functions->SendClientMessage( player->nPlayerId, 0x0b5fa5ff, message );
}

void MessageAllExcept   ( const SQChar * message, CPlayer * player )
{
	if( player != NULL )
	{
		for( int i = 0; i < MAX_PLAYERS; i++ )
		{
			if( functions->IsPlayerConnected( i ) )
				functions->SendClientMessage( i, 0x0b5fa5ff, message );
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
		functions->SendClientMessage( playerTo->nPlayerId, 0x007f16ff, "** pm from %s >> %s", playerToFake->GetName(), message );
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
		default:  return NULL;
	}
}

void LoadVCMPModule( const SQChar * name )
{
	OutputWarning( "LoadModule() cannot be used by scripts. Specify plugins in server.cfg" );
}

char GetWeaponID( const SQChar * name )
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
			return 0;
	}
}

DWORD SQGetTickCount( void )
{
	#ifdef WIN32
		return GetTickCount();
	#else
		struct timespec ts;
		if( clock_gettime( CLOCK_MONOTONIC, &ts ) != 0 )
			return 0;
		else
			return ts.tv_nsec;
	#endif
}

float DistanceFromPoint( float x1, float y1, float x2, float y2 )
{
	float matrixX = pow( (x2 - x1), 2 );
	float matrixY = pow( (y2 - y1), 2 );
	float matrixF = sqrt( matrixX + matrixY );
	return matrixF;
}

void ReloadScripts( void )
{
	// Are we allowed to reload?
	if( pCore->canReload )
	{
		// Let's not reload the scripts for now
		pCore->canReload = false;

		// Get rid of ALL declared timers
		pCore->DropAllTimers();

		// Clean the world up
		pCore->CleanWorld();
		
		// Release the old root table to free old binds
		Sqrat::RootTable(v).Release();

		// Push a new root table
		sq_pushroottable(v);

		// Set the default internal error handlers up
		sqstd_seterrorhandlers( v );

		// Set up our print and error functions
		sq_setprintfunc( v, printfunc, errorfunc );

		// Reload all global module entities
		pCore->RegisterEntities();

		// Re-run the script
		pCore->script->Run();

		// Trigger the onScriptLoad event
		Function callback = RootTable( v ).GetFunction( _SC( "onScriptLoad" ) );
		if( !callback.IsNull() )
			callback();

		callback.Release();

		// You are now free to move about the cabin
		pCore->canReload = true;

		// And now we dance
		OutputMessage( "Scripts reloaded." );
	}
	else
		OutputError( "The server refused to reload. Is this an infinite loop?" );
}

// <TODO>
int GetVehicleModelFromName( SQChar * name )
{
	char * lowername = strdup( name );
	szlower( lowername );

	if( lowername )
	{
		switch( lowername[0] )
		{
			case 'l':
			{
				if( strlen( lowername ) >= 2 )
				{
					if( lowername[1] == 'a' )
						return 130; // landstalker
					else if( lowername[1] == 'i' )
						return 133; // linerunner
					else if( lowername[1] == 'o' )
						return 201; // love fist
				}

				break;
			}

			case 'i':
				return 131; // idaho

			case 's':
			{
				if( strlen( lowername ) >= 3 )
				{
					if( lowername[1] == 't' )
					{
						if( lowername[2] == 'i' )
							return 132; // stinger
						else if( lowername[2] == 'r' )
							return 139; // stretch
						else if( lowername[2] == 'a' )
							return 169; // stallion
					}
					else if( lowername[1] == 'e' )
					{
						if( lowername[2] == 'c' )
							return 158; // securicar
						else if( lowername[2] == 'a' )
							return 177; // sea sparrow
						else if( strlen( lowername ) > 8 )
							return 174; // sentinel xs
						else
							return 135; // sentinel
					}
					else if( lowername[1] == 'q' )
						return 176; // squalo
					else if( lowername[1] == 'p' )
					{
						if( lowername[2] == 'e' )
							return 182; // speeder
						else if( lowername[2] == 'a' )
						{
							if( strlen( lowername ) >= 4 )
							{
								if( lowername[3] == 'r' )
									return 199; // sparrow
								else if( lowername[3] == 'n' )
									return 213; // spand express
							}
						}
					}
					else if( lowername[1] == 'k' )
						return 190; // skimmer
					else if( lowername[1] == 'a' )
					{
						if( lowername[2] == 'n' )
						{
							if( strlen( lowername ) >= 4 )
							{
								if( lowername[3] == 'c' )
									return 198; // sanchez
								else if( lowername[3] == 'd' )
									return 225; // sandking
							}
						}
						else if( lowername[2] == 'b' && strlen(lowername) > 5 )
							return 206; // sabre turbo
						else if( lowername[2] == 'b' )
							return 205; // sabre
					}
				}

				break;
			}

			case 'p':
			{
				if( lowername[1] == 'e' )
					return 134; // perennial
				else if( lowername[1] == 'o' )
				{
					if( strlen( lowername ) > 6 )
						return 227; // police maverick
					else
						return 156; // police
				}
				else if( lowername[1] == 'r' )
					return 160; // predator
				else if( lowername[1] == 'a' )
				{
					if( strlen( lowername ) >= 3 )
					{
						if( lowername[2] == 'c' )
							return 173; // packer
						else if( lowername[2] == 't' )
							return 200; // patriot
					}
				}
				else if( lowername[1] == 'i' )
					return 178; // pizza boy
				else if( lowername[1] == 'c' )
					return 191; // pcj-600

				break;
			}

			case 'r':
			{
				if( lowername[1] == 'i' )
					return 136; // rio
				else if( lowername[1] == 'h' )
					return 162; // rhino
				else if( lowername[1] == 'u' )
					return 170; // rumpo
				else if( lowername[1] == 'c' )
				{
					if( lowername[2] == 'b' )
					{
						if( strlen( lowername ) >= 5 )
						{
							if( lowername[4] == 'n' )
								return 171; // rcbandit
							else if( lowername[4] == 'r' )
								return 194; // rcbaron
						}
					}
					else if( lowername[2] == 'r' )
						return 195; // rcraider
					else if( lowername[2] == 'g' )
						return 231;
				}
				else if( lowername[1] == 'o' )
					return 172; // romero's hearse
				else if( lowername[1] == 'e' )
				{
					if( strlen( lowername ) >= 3 )
					{
						if( lowername[2] == 'e' )
							return 183; // reefer
						else if( lowername[2] == 'g' )
							return 209; // regina
					}
				}
				else if( lowername[1] == 'a' )
					return 219;

				break;
			}

			case 'f':
			{
				if( lowername[1] == 'i' )
					return 137; // firetruck
				else if( lowername[1] == 'b' )
				{
					if( strlen( lowername ) >= 5 )
					{
						if( lowername[4] == 'w' )
							return 147; // fbi washington
						else if( lowername[4] == 'r' )
							return 220; // fbi rancher
					}
				}
				else if( lowername[1] == 'l' )
					return 185; // flatbed
				else if( lowername[1] == 'a' )
					return 192; // faggio
				else if( lowername[1] == 'r' )
					return 193; // freeway

				break;
			}

			case 't':
			{
				if( lowername[1] == 'r' )
				{
					if( strlen( lowername ) >= 3 )
					{
						if( lowername[2] == 'a' )
							return 138; // trashmaster
						else if( lowername[2] == 'o' )
							return 184; // tropic
					}
				}
				else if( lowername[1] == 'o' )
					return 189; // top fun

				break;
			}

			case 'm':
			{
				if( lowername[1] == 'a' )
				{
					if( strlen( lowername ) >= 3 )
					{
						if( lowername[2] == 'n' )
							return 140; // manana
						else if( lowername[2] == 'r' )
							return 214; // marquis
						else if( lowername[2] == 'v' )
							return 217; // maverick
					}
				}
				else if( lowername[1] == 'u' )
					return 144; // mule
				else if( lowername[1] == 'r' )
					return 153; // mr. whoopee
				else if( lowername[1] == 'e' )
					return 230; // mesa grande

				break;
			}

			case 'c':
			{
				if( lowername[1] == 'h' )
					return 145; // cheetah
				else if( lowername[1] == 'u' )
				{
					if( strlen( lowername ) >= 7 )
					{
						if( lowername[6] == 'h' )
							return 164; // cuban hermes
						else if( lowername[6] == 'j' )
							return 223; // cuban jetmax
					}
				}
				else if( lowername[1] == 'o' )
				{
					if( strlen( lowername ) >= 4 )
					{
						if( lowername[3] == 'c' )
							return 167; // coach
						else if( lowername[3] == 's' )
							return 202; // coast guard
					}
					else if( strlen( lowername ) >= 3 && lowername[2] == 'm' )
						return 210; // comet
				}
				else if( lowername[1] == 'a' )
				{
					if( strlen( lowername ) >= 3 )
					{
						if( lowername[2] == 'b' )
							return 168; // cabbie
						else if( lowername[2] == 'd' )
							return 187; // caddy
					}
				}

				break;
			}

			case 'a':
			{
				if( lowername[1] == 'm' )
					return 146; // ambulance
				else if( lowername[1] == 'n' )
					return 166; // angel
				else if( lowername[1] == 'd' )
					return 175; // admiral
				else if( lowername[1] == 'i' )
					return 180; // airtrain

				break;
			}

			case 'e':
			{
				if( lowername[1] == 's' )
					return 149; // esperanto
				else if( lowername[1] == 'n' )
					return 157; // enforcer

				break;
			}

			case 'w':
			{
				if( strlen( lowername ) >= 3 )
				{
					if( lowername[2] == 's' )
						return 151; // washington
					else if( lowername[2] == 'l' )
						return 208; // walton
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
							return 152; // bobcat
						else if( lowername[2] == 'x' )
							return 228; // boxville
					}
				}
				else if( lowername[1] == 'a' )
				{
					if( strlen( lowername ) >= 3 )
					{
						if( lowername[2] == 'r' )
							return 163; // barracks ol
						else if( lowername[2] == 'g' )
							return 215; // baggage handler
					}
				}
				else if( lowername[1] == 'l' )
					return 226; // blista compact
				else if( lowername[1] == 'e' )
					return 229; // benson

				break;
			}

			case 'h':
			{
				if( lowername[1] == 'u' )
					return 155; // hunter
				else if( lowername[1] == 'e' )
					return 165; // helicopter
				else if( lowername[1] == 'o' )
					return 224; // hotring racer

				break;
			}

			case 'g':
			{
				if( lowername[1] == 'a' )
					return 179; // gang burrito
				else if( lowername[1] == 'l' )
					return 196; // glendale
				else if( lowername[1] == 'r' )
					return 222; // greenwood

				break;
			}

			case 'd':
			{
				if( lowername[1] == 'e' )
					return 211; // deluxo
				else if( lowername[1] == 'i' )
					return 203; // dinghy

				break;
			}

			case 'y':
				return 186; // yankee

			case 'z':
				return 188; // zebra cab

			case 'k':
				return 216; // kaufman cab

			case 'v':
			{
				if( lowername[1] == 'c' )
					return 218; // vcn maverick
				else if( lowername[1] == 'i' )
				{
					if( strlen( lowername ) >= 3 )
					{
						if( lowername[2] == 'r' )
							return 221; // virgo
						else if( lowername[2] == 'c' )
							return 236; // vicechee
					}
				}

				break;
			}
		}

		free( lowername );
	}
	
	return -1;
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

			if( playerID < MAX_PLAYERS )
				pPlayer = pCore->playerMap[playerID];
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

					if( strstr( nameBuf, lowerName ) )
					{
						pID = i;
						break;
					}
				}
			}

			delete [] nameBuf;
			nameBuf = NULL;
			free( lowerName );

			if( pID == 255 )
			{
				sq_pushnull( v );
				return 1;
			}
			else
				pPlayer = pCore->playerMap[pID];
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
			SQInteger stack = sq_gettop( v );
			sq_pushroottable( v );
			sq_pushstring( v, "CPlayer", -1 );
			sq_rawget( v, -2 );

			sq_createinstance( v, -1 );
			sq_remove( v, -3 );
			sq_remove( v, -2 );

			if( SQ_FAILED( sq_setinstanceup( v, -1, pPlayer ) ) )
			{
				// Well, shit.
				sq_settop( v, stack );
				return sq_throwerror( v, "Failed to push instance of CPlayer" );
			}
			
			sq_setreleasehook( v, -1, release_hook );
			return 1;
		}
	}
	else
		return sq_throwerror( v, "Unexpected number of parameters for FindPlayer [integer or string]" );
}

SQInteger InPoly( HSQUIRRELVM v )
{
	if( sq_gettop( v ) >= 9 )
	{
		if( sq_gettop( v ) % 2 == 1 )
		{
			int paramCount = sq_gettop( v );
			int i;
			for( i = 2; i < paramCount; i++ )
			{
				if( sq_gettype( v, i ) != OT_FLOAT )
					return sq_throwerror( v, "Unexpected non-float in InPoly: ALL arguments must be floats" );
			}

			int vertexCount = ( paramCount - 3 ) / 2;
			float * xVertices = new float[vertexCount];
			float * yVertices = new float[vertexCount];
			for( i = 4; i < paramCount; i += 2 )
			{
				sq_getfloat( v, i, &xVertices[i] );
				sq_getfloat( v, i + 1, &yVertices[i] );
			}

			float x, y;
			sq_getfloat( v, 2, &x );
			sq_getfloat( v, 3, &y );

			// http://www.ecse.rpi.edu/Homepages/wrf/Research/Short_Notes/pnpoly.html
			// (adapted)
			bool isInPath = false;
			int j;

			for( i = 0, j = vertexCount - 1; i < vertexCount; j = i++ )
			{
				if( ( ( yVertices[i] > y ) != ( yVertices[j] > y ) )
					&& ( x < xVertices[j] - xVertices[i] ) * ( y - yVertices[i] ) / ( yVertices[j] - yVertices[i] + xVertices[i] ) )
					isInPath = !isInPath;
			}

			sq_pushbool( v, isInPath );
			return 1;
			}
		else
			return sq_throwerror( v, "Unexpected number of parameters for InPoly: all X vertices must be accompanied by a Y vertex" );
	}
	else
		return sq_throwerror( v, "Unexpected number of parameters for InPoly [float, float, float, float, float, float, float, float, [...]]" );
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
							sq_getinteger( v, i, (SQInteger *)&pTempParam.pData );
							break;

						case OT_FLOAT:
							sq_getfloat( v, i, (SQFloat *)&pTempParam.pData );
							break;

						case OT_BOOL:
							sq_getbool( v, i, (SQBool *)&pTempParam.pData );
							break;

						case OT_STRING:
							sq_getstring( v, i, reinterpret_cast<const SQChar **>(const_cast<const void **>(&pTempParam.pData)) );
							break;

						case OT_TABLE:
						case OT_ARRAY:
						case OT_CLASS:
							sq_resetobject( (HSQOBJECT *)pTempParam.pData );
							sq_getstackobj( v, i, (HSQOBJECT *)&pTempParam.pData );
							sq_addref( v, (HSQOBJECT *)&pTempParam.pData );
							break;

						case OT_CLOSURE:
						case OT_NATIVECLOSURE:
							sq_getstackobj( v, i, (HSQOBJECT *)&pTempParam.pData );
							break;

						case OT_INSTANCE:
							sq_getinstanceup( v, i, (SQUserPointer *)&pTempParam.pData, NULL );
							break;

						case OT_USERDATA:
						case OT_USERPOINTER:
							sq_getuserpointer( v, i, (SQUserPointer *)&pTempParam.pData );
							break;

						case OT_NULL:
							break;

						default:
							break;
					}

					pTimer->params.push_back(pTempParam);
				}
			}

			pTimer->pFunc = const_cast<SQChar *>(pFuncName);
			pTimer->intervalInTicks   = fInterval;
			pTimer->maxNumberOfPulses = maxPulses;

			// Go through hell and back to push a CTimer instance
			SQInteger stack = sq_gettop( v );
			sq_pushroottable( v );
			sq_pushstring( v, "CTimer", -1 );
			sq_rawget( v, -2 );

			sq_createinstance( v, -1 );
			sq_remove( v, -3 );
			sq_remove( v, -2 );

			if( SQ_FAILED( sq_setinstanceup( v, -1, pTimer ) ) )
			{
				// Well, shit.
				sq_settop( v, stack );
				return sq_throwerror( v, "Failed to push instance of CTimer" );
			}
			
			sq_setreleasehook( v, -1, release_hook );

			pCore->AddTimer(pTimer);
			return 1;
		}
	}
}

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
	
	char * date = new char[96];
	time_t rawtime;
	time( &rawtime );

	struct tm * timeinfo = localtime( &rawtime );
	strftime( date, 96, "%A, %B %d, %Y, %H:%M:%S %Z", timeinfo );

	return date;
}

// These functions do nothing and exist for the sole purpose of avoiding compiler errors
SQInteger SetAmmuWeapon( HSQUIRRELVM v ) { OutputWarning( "SetAmmuWeapon does not exist in 0.4. Ammunations must be scripted." ); return 0; }
SQInteger IsAmmuWeaponEnabled( HSQUIRRELVM v ) { OutputWarning( "IsAmmuWeaponEnabled does not exist in 0.4. Ammunations must be scripted." ); return 0; }
SQInteger SetAmmuWeaponEnabled( HSQUIRRELVM v ) { OutputWarning( "SetAmmuWeaponEnabled does not exist in 0.4. Ammunations must be scripted." ); return 0; }
SQInteger GetWeaponSync( HSQUIRRELVM v ) { OutputWarning( "GetWeaponSync does not exist in 0.4. Rely on the server's anti-hack system instead." ); return 0; }
SQInteger SetWeaponSync( HSQUIRRELVM v ) { OutputWarning( "SetWeaponSync does not exist in 0.4. Rely on the server's anti-hack system instead." ); return 0; }
SQInteger GetFallEnabled( HSQUIRRELVM v ) { OutputWarning( "GetFallEnabled has no effect." ); return 0; }
SQInteger SetFallEnabled( HSQUIRRELVM v ) { OutputWarning( "SetFallEnabled has no effect." ); return 0; }