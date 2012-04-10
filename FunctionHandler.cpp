#include "FunctionHandler.h"

void ClientMessage( CPlayer player, ARGB colour, const SQChar* message )
{
	unsigned int dwColour;
	dwColour  = ( colour.a << 24 );
	dwColour += ( ( colour.r & 0xFF ) << 16 );
	dwColour += ( ( colour.g & 0xFF ) << 8 );
	dwColour += ( colour.b & 0xFF );

	const size_t newSize  = 4096;
	char nMessage[newSize];

	wcstombs( nMessage, message, newSize );
	functions->SendClientMessage( player.nPlayerId, dwColour, nMessage );
}

void ClientMessageToAll( ARGB colour, const SQChar* message )
{
	for( int i = 0; i < functions->GetMaxPlayers(); i++ )
	{
		if( functions->IsPlayerConnected( i ) )
			ClientMessage( playerMap[i], colour, message );
	}
}

void GameMessage( CPlayer player, int type, const SQChar* message )
{
	const size_t newSize  = 4096;
	char nMessage[newSize];

	wcstombs( nMessage, message, newSize );
	functions->SendGameMessage( player.nPlayerId, type, nMessage );
}

void SetServerName( const SQChar* message )
{
	const size_t newSize  = 512;
	char nMessage[newSize];

	wcstombs( nMessage, message, newSize );
	functions->SetServerName( nMessage );
}

void SetMaxPlayers( int newMaxPlayers ) { functions->SetMaxPlayers( newMaxPlayers ); }
void SetServerPassword( const SQChar* password )
{
	const size_t newSize  = 384;
	char nMessage[newSize];

	wcstombs( nMessage, password, newSize );
	functions->SetServerPassword( nMessage );
}

void SetGameModeText( const SQChar* gamemodeName )
{
	const size_t newSize  = 512;
	char nMessage[newSize];

	wcstombs( nMessage, gamemodeName, newSize );
	functions->SetGameModeText( nMessage );
}

void SetTimeRate( unsigned int timeRate ) { functions->SetTimeRate( timeRate ); }
void SetHour( int hour ) { functions->SetHour( hour ); }
void SetMinute( int minute ) { functions->SetMinute( minute ); }
void SetTime( int hour, int minute ) { SetHour(hour); SetMinute(minute); }
void SetWeather( int weather ) { functions->SetWeather( weather ); }
void SetGravity( float gravity ) { functions->SetGravity( gravity ); }
void SetGamespeed( float speed ) { functions->SetGamespeed( speed ); }
void SetWaterLevel( float waterLevel ) { functions->SetWaterLevel( waterLevel ); }
void SetMaxHeight( float maxHeight ) { functions->SetMaxHeight( maxHeight ); }

SQChar * GetServerName()
{
	char serverName[128];
	functions->GetServerName( serverName, 128 );

	const size_t newSize  = 512;
	static wchar_t wcData[newSize];

	mbstowcs( wcData, serverName, newSize );
	return wcData;
}

int GetMaxPlayers() { return functions->GetMaxPlayers(); }

SQChar * GetServerPassword()
{
	char password[128];
	functions->GetServerPassword( password, 128 );

	const size_t newSize  = 512;
	static wchar_t wcData[newSize];

	mbstowcs( wcData, password, newSize );
	return wcData;
}

SQChar * GetGameModeText()
{
	char gamemode[96];
	functions->GetGameModeText( gamemode, 96 );

	const size_t newSize  = 384;
	static wchar_t wcData[newSize];

	mbstowcs( wcData, gamemode, newSize );
	return wcData;
}

unsigned int GetTimeRate() { return functions->GetTimeRate(); }
int GetHour() { return functions->GetHour(); }
int GetMinute() { return functions->GetMinute(); }
int GetWeather() { return functions->GetWeather(); }
float GetGravity() { return functions->GetGravity(); }
float GetGamespeed() { return functions->GetGamespeed(); }
float GetWaterLevel() { return functions->GetWaterLevel(); }
float GetMaxHeight() { return functions->GetMaxHeight(); }

void ToggleSyncFrameLimiter( bool toggle ) { functions->ToggleSyncFrameLimiter( toggle ); }
void ToggleFrameLimiter( bool toggle ) { functions->ToggleFrameLimiter( toggle ); }
void ToggleTaxiBoostJump( bool toggle ) { functions->ToggleTaxiBoostJump( toggle ); }
void ToggleDriveOnWater( bool toggle ) { functions->ToggleDriveOnWater( toggle ); }
void ToggleFastSwitch( bool toggle ) { functions->ToggleFastSwitch( toggle ); }
void ToggleFriendlyFire( bool toggle ) { functions->ToggleFriendlyFire( toggle ); }
void ToggleDisableDriveby( bool toggle ) { functions->ToggleDisableDriveby( toggle ); }
void TogglePerfectHandling( bool toggle ) { functions->TogglePerfectHandling( toggle ); }
void ToggleFlyingCars( bool toggle ) { functions->ToggleFlyingCars( toggle ); }
void ToggleJumpSwitch( bool toggle ) { functions->ToggleJumpSwitch( toggle ); }
void ToggleShowOnRadar( bool toggle ) { functions->ToggleShowMarkers( toggle ); }
void ToggleStuntBike( bool toggle ) { functions->ToggleStuntBike( toggle ); }
void ToggleShootInAir( bool toggle ) { functions->ToggleShootInAir( toggle ); }
void ToggleShowNametags( bool toggle ) { functions->ToggleShowNametags( toggle ); }
void ToggleJoinMessages( bool toggle ) { functions->ToggleJoinMessages( toggle ); }
void ToggleDeathMessages( bool toggle ) { functions->ToggleDeathMessages( toggle ); }

bool EnabledSyncFrameLimiter() { return functions->EnabledSyncFrameLimiter(); }
bool EnabledFrameLimiter() { return functions->EnabledFrameLimiter(); }
bool EnabledTaxiBoostJump() { return functions->EnabledTaxiBoostJump(); }
bool EnabledDriveOnWater() { return functions->EnabledDriveOnWater(); }
bool EnabledFastSwitch() { return functions->EnabledFastSwitch(); }
bool EnabledFriendlyFire() { return functions->EnabledFriendlyFire(); }
bool EnabledDisableDriveby() { return functions->EnabledDisableDriveby(); }
bool EnabledPerfectHandling() { return functions->EnabledPerfectHandling(); }
bool EnabledFlyingCars() { return functions->EnabledFlyingCars(); }
bool EnabledJumpSwitch() { return functions->EnabledJumpSwitch(); }
bool EnabledShowOnRadar() { return functions->EnabledShowMarkers(); }
bool EnabledStuntBike() { return functions->EnabledStuntBike(); }
bool EnabledShootInAir() { return functions->EnabledShootInAir(); }
bool EnabledShowNametags() { return functions->EnabledShowNametags(); }
bool EnabledJoinMessages() { return functions->EnabledJoinMessages(); }
bool EnabledDeathMessages() { return functions->EnabledDeathMessages(); }

void CreateExplosion( int world, int type, Vector pos, int playerCaused, bool onGround )
{
	functions->CreateExplosion( world, type, pos.x, pos.y, pos.z, playerCaused, onGround );
}

void PlayGameSound( int nPlayer, int sound, Vector pos ) { functions->PlaySound( nPlayer, sound, pos.x, pos.y, pos.z ); }

void SetUseClasses( bool toUse ) { functions->SetUseClasses( toUse ); }
bool UsingClasses() { return functions->GetUseClasses(); }
void AddClass( int team, cRGB colour, int skin, Vector spawnPos, float spawnAngle, int wep1, int ammo1, int wep2, int ammo2, int wep3, int ammo3 )
{
	unsigned int dwColour = colour.r;
	dwColour = (dwColour << 8) + colour.g;
	dwColour = (dwColour << 8) + colour.b;

	functions->AddPlayerClass( team, dwColour, skin, spawnPos.x, spawnPos.y, spawnPos.z, spawnAngle, wep1, ammo1, wep2, ammo2, wep3, ammo3 );
}

void SetSpawnPlayerPos( Vector pos ) { functions->SetSpawnPlayerPos( pos.x, pos.y, pos.z ); }
void SetSpawnCameraPos( Vector pos ) { functions->SetSpawnCameraPos( pos.x, pos.y, pos.z ); }
void SetSpawnCameraLook( Vector pos ) { functions->SetSpawnCameraLookAt( pos.x, pos.y, pos.z ); }

void BanIP( const SQChar* ip )
{
	const size_t newSize  = 64;
	char szIp[newSize];

	wcstombs( szIp, ip, newSize );
	functions->BanIP( szIp );
}

void UnbanIP( const SQChar* ip )
{
	const size_t newSize  = 64;
	char szIp[newSize];

	wcstombs( szIp, ip, newSize );
	functions->UnbanIP( szIp );
}

bool IsIPBanned( const SQChar* ip )
{
	const size_t newSize  = 64;
	char szIp[newSize];

	wcstombs( szIp, ip, newSize );
	return functions->IsIPBanned( szIp );
}

int GetPlayerIDFromName( const SQChar* name )
{
	const size_t newSize  = 256;
	char szName[newSize];

	wcstombs( szName, name, newSize );
	return functions->GetPlayerIDFromName( szName );
}

bool IsWorldCompatibleWithPlayer( CPlayer cPlayer, int world ) { return functions->IsPlayerWorldCompatible( cPlayer.nPlayerId, world ); }

CVehicle * CreateVehicle( int model, int world, Vector pos, float angle, int col1, int col2 )
{
	int vId = functions->CreateVehicle( model, world, pos.x, pos.y, pos.z, angle, col1, col2 );
	if( vId < 1 )
		return NULL;
	else
	{
		static CVehicle vehInst;
		vehInst.nVehicleId = vId;
		
		return &vehInst;
	}
}

CPickup * CreatePickup( int model, int world, int quantity, Vector pos, int alpha, bool isAuto )
{
	int pId = functions->CreatePickup( model, world, quantity, pos.x, pos.y, pos.z, alpha, isAuto );

	if( pId < 0 )
		return NULL;
	else
	{
		static CPickup pickupInst;
		pickupInst.nPickupId = pId;

		return &pickupInst;
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
	if( functions->PickupGetModel( id ) < 1 )
		return NULL;
	else
	{
		static CPickup pickupInst;
		pickupInst.nPickupId = id;

		return &pickupInst;
	}
}

CPlayer * FindPlayer( int id )
{
	if( functions->IsPlayerConnected( id ) == 0 )
		return NULL;
	else
		return &playerMap[id];
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
	if( functions->GetVehicleModel( id ) < 1 )
		return NULL;
	else
	{
		static CVehicle vehInst;
		vehInst.nVehicleId = id;

		return &vehInst;
	}
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

bool HideMapObject( int nModelId, float x, float y, float z )
{
	int x2 = floor( ( x * 10 ) + 0.5 );
	int y2 = floor( ( y * 10 ) + 0.5 );
	int z2 = floor( ( y * 10 ) + 0.5 );

	functions->HideMapObject( nModelId, x2, y2, z2 );
}

bool ShowMapObject( int nModelId, float x, float y, float z )
{
	int x2 = floor( ( x * 10 ) + 0.5 );
	int y2 = floor( ( y * 10 ) + 0.5 );
	int z2 = floor( ( y * 10 ) + 0.5 );

	functions->ShowMapObject( nModelId, x2, y2, z2 );
}

bool ShowAllMapObjects() { return functions->ShowAllMapObjects(); }