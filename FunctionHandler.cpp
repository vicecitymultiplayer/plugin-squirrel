#include "FunctionHandler.h"
#include "Functions.h"
#include "ConsoleUtils.h"
#include "CCore.h"
#include "main.h"

// Tha core
extern CCore * pCore;

void ClientMessage( const SQChar * message, CPlayer * player, int r, int g, int b, int a )
{
	if( player != NULL )
	{
		unsigned int dwColour;
		dwColour  = ( a << 24 );
		dwColour += ( ( r & 0xFF ) << 16 );
		dwColour += ( ( g & 0xFF ) << 8 );
		dwColour += ( b & 0xFF );

		functions->SendClientMessage( player->nPlayerId, dwColour, const_cast<char *>( message ) );
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

SQChar * GetServerName()
{
	char * serverName = new char[128];
	functions->GetServerName( serverName, 128 );

	return serverName;
}

int GetMaxPlayers() { return functions->GetMaxPlayers(); }

SQChar * GetServerPassword()
{
	char * password = new char[128];
	functions->GetServerPassword( password, 128 );

	return password;
}

SQChar * GetGameModeText()
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
void ToggleDisableDriveby   ( bool toggle ) { functions->ToggleDisableDriveby( ( toggle ? 1 : 0 ) );   }
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

void CreateExplosion( int world, int type, Vector pos, int playerCaused, bool onGround )
{
	functions->CreateExplosion( world, type, pos.x, pos.y, pos.z, playerCaused, onGround );
}

void PlayGameSound ( int nPlayer, int sound, Vector pos ) { functions->PlaySound( nPlayer, sound, pos.x, pos.y, pos.z ); }
void SetUseClasses ( bool toUse )                         { functions->SetUseClasses( toUse ); }
bool UsingClasses  ()                                     { return ( functions->GetUseClasses() != 0 ); }

void AddClass( int team, cRGB colour, int skin, Vector spawnPos, float spawnAngle, int wep1, int ammo1, int wep2, int ammo2, int wep3, int ammo3 )
{
	unsigned int dwColour = colour.r;
	dwColour = (dwColour << 8) + colour.g;
	dwColour = (dwColour << 8) + colour.b;

	functions->AddPlayerClass( team, dwColour, skin, spawnPos.x, spawnPos.y, spawnPos.z, spawnAngle, wep1, ammo1, wep2, ammo2, wep3, ammo3 );
}

void SetSpawnPlayerPos( Vector pos )  { functions->SetSpawnPlayerPos( pos.x, pos.y, pos.z ); }
void SetSpawnCameraPos( Vector pos )  { functions->SetSpawnCameraPos( pos.x, pos.y, pos.z ); }
void SetSpawnCameraLook( Vector pos ) { functions->SetSpawnCameraLookAt( pos.x, pos.y, pos.z ); }

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

CVehicle * CreateVehicle( int model, int world, Vector pos, float angle, int col1, int col2 )
{
	int vId = functions->CreateVehicle( model, world, pos.x, pos.y, pos.z, angle, col1, col2 );
	if( vId < 1 )
		return NULL;
	else
	{
		CVehicle * vehInst  = new CVehicle;
		vehInst->nVehicleId = vId;
		pCore->vehicleMap[vId]     = vehInst;
		
		return vehInst;
	}
}

CPickup * CreatePickup( int model, int world, int quantity, Vector pos, int alpha, bool isAuto )
{
	int pId = functions->CreatePickup( model, world, quantity, pos.x, pos.y, pos.z, alpha, isAuto );

	if( pId < 0 )
		return NULL;
	else
	{
		CPickup * pickupInst  = new CPickup;
		pickupInst->nPickupId = pId;

		return pickupInst;
	}
}

CObject * CreateObject( int model, int world, Vector pos, int alpha )
{
	int oId = functions->CreateObject( model, world, pos.x, pos.y, pos.z, alpha );

	if( oId < 0 )
		return NULL;
	else
	{
		static CObject objInst;
		objInst.nObjectId = oId;

		return &objInst;
	}
}

CPickup * FindPickup( int id )
{
	if( id < MAX_PICKUPS )
		return pCore->pickupMap[id];

	return NULL;
}

CPlayer * FindPlayer( int id )
{
	if( id < MAX_PLAYERS )
		return pCore->playerMap[id];

	return NULL;
}

CObject * FindObject( int id )
{
	if( functions->GetObjectModel( id ) < 1 )
		return NULL;
	else
	{
		static CObject objInst;
		objInst.nObjectId = id;

		return &objInst;
	}
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
	int x2 = floor( ( x * 10 ) + 0.5 );
	int y2 = floor( ( y * 10 ) + 0.5 );
	int z2 = floor( ( y * 10 ) + 0.5 );

	functions->HideMapObject( nModelId, x2, y2, z2 );
}

void ShowMapObject( int nModelId, float x, float y, float z )
{
	int x2 = floor( ( x * 10 ) + 0.5 );
	int y2 = floor( ( y * 10 ) + 0.5 );
	int z2 = floor( ( y * 10 ) + 0.5 );

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

SQChar * GetWeaponName   ( int weaponID )
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

SQChar * GetDistrictName ( float x, float y )
{
	if( x > -1613.03f && y > 413.218f && x < -213.73f && y < 1677.32f )
		return "Downtown Vice City";
	else if( x > 163.656f && y > -351.153f && x < 1246.03f && y < 1398.85f )
		return "BEACH3";
	else if( x > -103.97f && y > -930.526f && x < 1246.03f && y < -351.153f )
		return "BEACH2";
	else if( x > -253.206f && y > -1805.37f && x < 1254.9f && y < -930.526f )
		return "BEACH1";
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

SQChar * GetSkinName     ( int skinID )
{
	return "whatever";
}

int      GetWeaponID     ( const SQChar * name )
{
	return -1;
}

DWORD    SQGetTickCount  ( void ) { return GetTickCount(); }

bool InPoly             ( float x, float y, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4 )
{
	return false;
}

float DistanceFromPoint ( float x1, float y1, float x2, float y2 )
{
	float matrixX = pow( (x2 - x1), 2 );
	float matrixY = pow( (y2 - y1), 2 );
	float matrixF = sqrt( matrixX + matrixY );
	return matrixF;
}

void ReloadScripts     ( void )
{
	// Are we allowed to reload?
	if( pCore->canReload )
	{
		// Let's not reload the scripts for now
		pCore->canReload = false;

		// Load the virtual machine
		pCore->LoadVM();

		// Load the script
		pCore->LoadScript();
	}
}

int      GetVehicleModelFromName ( SQChar * name )
{
	return -1;
}

SQChar * GetVehicleNameFromModel ( int model )
{
	return "whatever";
}

// These functions are for compatibility, but will be deprecated
DWORD    GetTime         ( void )
{
	OutputWarning( "GetTime is deprecated and may be removed in the future.\n"
		"          Please use Squirrel's time() function instead." );

	return time( NULL );
}

SQChar * GetFullTime     ( void )
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

// These functions are non-functional at the moment
void GetWeatherRate ( void )      { OutputWarning( "GetWeatherRate is not implemented at the moment." ); }
void SetWeatherRate ( int rate )  { OutputWarning( "SetWeatherRate is not implemented at the moment." ); }
void GetWeatherLock ( void )      { OutputWarning( "GetWeatherLock is not implemented at the moment." ); }
void SetWeatherLock ( bool lock ) { OutputWarning( "SetWeatherLock is not implemented at the moment." ); }

void NewSocket      ( SQChar * function ) { OutputWarning( "NewSocket is not implemented at the moment." ); }
void NewTimer       ( SQChar * function, int interval, int repeat ) { OutputWarning( "NewTimer is not implemented at the moment." ); }