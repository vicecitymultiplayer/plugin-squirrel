#include "CallbackHandler.h"
#include <string>

// Define the player map
std::map<int, CPlayer> playerMap;

int OnInitServer()
{
	Function callback = RootTable( v ).GetFunction( _SC("onServerStart") );
	if( !callback.IsNull() )
		callback();

	callback.Release();
	return 1;
}

void OnShutdownServer()
{
	Function callback = RootTable().GetFunction( _SC("onServerStop") );
	if( !callback.IsNull() )
		callback();
}

void OnFrame( float fElapsedTime )
{
	Function callback = RootTable().GetFunction( _SC("onFrame") );
	if( !callback.IsNull() )
		callback( fElapsedTime );
}

void OnPlayerConnect( int nPlayerId )
{
	CPlayer newPlayer;

	newPlayer.nPlayerId = nPlayerId;
	playerMap.insert( std::pair<int, CPlayer>( nPlayerId, newPlayer ) );

	Function callback = RootTable().GetFunction( _SC("onPlayerJoin") );
	if( !callback.IsNull() )
		callback.Execute<CPlayer>(newPlayer);
}

void OnPlayerDisconnect( int nPlayerId, int nReason )
{
	CPlayer playerInstance              = playerMap[ nPlayerId ];
	std::map<int, CPlayer>::iterator it = playerMap.find( nPlayerId );

	Function callback = RootTable().GetFunction( _SC("onPlayerPart") );
	if( !callback.IsNull() )
		callback( playerInstance, nReason );

	playerMap.erase( it );
	// Haha, "erase it"
}

int OnPlayerRequestClass( int nPlayerId, int nOffset )
{
	CPlayer playerInstance = playerMap[ nPlayerId ];

	Function callback = RootTable().GetFunction( _SC("onPlayerRequestClass") );
	if( !callback.IsNull() )
		return callback.Evaluate<int>( playerInstance, nOffset );
	else
		return 1;
}

int OnPlayerRequestSpawn( int nPlayerId )
{
	CPlayer playerInstance = playerMap[ nPlayerId ];

	Function callback = RootTable().GetFunction( _SC("onPlayerRequestSpawn") );
	if( !callback.IsNull() )
		return callback.Evaluate<int>( playerInstance );
	else
		return 1;
}

void OnPlayerSpawn( int nPlayerId )
{
	CPlayer playerInstance = playerMap[ nPlayerId ];

	Function callback = RootTable().GetFunction( _SC("onPlayerSpawn") );
	if( !callback.IsNull() )
		callback( playerInstance );
}

void OnPlayerDeath( int nPlayerId, int nKillerId, int nReason, int nBodyPart )
{
	CPlayer playerInstance = playerMap[ nPlayerId ];

	if( nKillerId == -1 )
	{
		Function callback = RootTable().GetFunction( _SC("onPlayerDeath") );
		if( !callback.IsNull() )
			callback( playerInstance, nReason );
	}
	else if( functions->GetPlayerTeam( nPlayerId ) == functions->GetPlayerTeam( nKillerId ) )
	{
		CPlayer killerInstance = playerMap[ nKillerId ];

		Function callback = RootTable().GetFunction( _SC("onPlayerTeamKill") );
		if( !callback.IsNull() )
			callback( playerInstance, killerInstance, nReason, nBodyPart );
	}
	else
	{
		CPlayer killerInstance = playerMap[ nKillerId ];

		Function callback = RootTable().GetFunction( _SC("onPlayerKill") );
		if( !callback.IsNull() )
			callback( playerInstance, killerInstance, nReason, nBodyPart );
	}
}

int OnPlayerRequestEnter( int nPlayerId, int nVehicleId, int nSlotId )
{
	CPlayer playerInstance = playerMap[ nPlayerId ];

	CVehicle vehicleInstance;
	vehicleInstance.nVehicleId = nVehicleId;

	Function callback = RootTable().GetFunction( _SC("onPlayerRequestEnter") );
	if( !callback.IsNull() )
		return callback.Evaluate<int>( playerInstance, vehicleInstance, nSlotId );
	else
		return 1;
}

void OnPlayerEnterVehicle( int nPlayerId, int nVehicleId, int nSlotId )
{
	CPlayer playerInstance = playerMap[ nPlayerId ];

	CVehicle vehicleInstance;
	vehicleInstance.nVehicleId = nVehicleId;

	Function callback = RootTable().GetFunction( _SC("onPlayerEnterVehicle") );
	if( !callback.IsNull() )
		callback( playerInstance, vehicleInstance, nSlotId );
}

void OnPlayerExitVehicle( int nPlayerId, int nVehicleId )
{
	CPlayer playerInstance = playerMap[ nPlayerId ];

	CVehicle vehicleInstance;
	vehicleInstance.nVehicleId = nVehicleId;

	Function callback = RootTable().GetFunction( _SC("onPlayerExitVehicle") );
	if( !callback.IsNull() )
		callback( playerInstance, vehicleInstance );
}

int OnPickupClaimPicked( int nPickupId, int nPlayerId )
{
	CPlayer playerInstance = playerMap[ nPlayerId ];

	CPickup pickupInstance;
	pickupInstance.nPickupId = nPickupId;

	Function callback = RootTable().GetFunction( _SC("onPickupClaimPicked") );
	if( !callback.IsNull() )
		return callback.Evaluate<int>( playerInstance, pickupInstance );
	else
		return 1;
}

void OnPickupPickedUp( int nPickupId, int nPlayerId )
{
	CPlayer playerInstance = playerMap[ nPlayerId ];

	CPickup pickupInstance;
	pickupInstance.nPickupId = nPickupId;

	Function callback = RootTable().GetFunction( _SC("onPickupPickedUp") );
	if( !callback.IsNull() )
		callback( playerInstance, pickupInstance );
}

void OnPickupRespawn( int nPickupId )
{
	CPickup pickupInstance;
	pickupInstance.nPickupId = nPickupId;

	Function callback = RootTable().GetFunction( _SC("onPickupRespawn") );
	if( !callback.IsNull() )
		callback( pickupInstance );
}

void OnVehicleExplode( int nVehicleId )
{
	CVehicle vehicleInstance;
	vehicleInstance.nVehicleId = nVehicleId;

	Function callback = RootTable().GetFunction( _SC("onVehicleExplode") );
	if( !callback.IsNull() )
		callback( vehicleInstance );
}

void OnVehicleRespawn( int nVehicleId )
{
	CVehicle vehicleInstance;
	vehicleInstance.nVehicleId = nVehicleId;

	Function callback = RootTable().GetFunction( _SC("onVehicleRespawn") );
	if( !callback.IsNull() )
		callback( vehicleInstance );
}

int OnPublicMessage( int nPlayerId, const char* pszText )
{
	CPlayer playerInstance = playerMap[ nPlayerId ];

	Function callback = RootTable().GetFunction( _SC("onPlayerChat") );
	if( !callback.IsNull() )
	{
		// Convert the message to a wide char
		const size_t newSize  = 1024;
		wchar_t wcText[newSize];
		
		mbstowcs( wcText, pszText, newSize );
		return callback.Evaluate<int>( playerInstance, wcText );
	}
	else
		return 1;
}

int OnCommandMessage( int nPlayerId, const char* pszText )
{
	CPlayer playerInstance = playerMap[ nPlayerId ];
	Function callback      = RootTable().GetFunction( _SC("onPlayerCommand") );

	if( !callback.IsNull() )
	{
		char * szText = const_cast<char *>(pszText);
		char * szCmd  = strtok( szText, " " );
		if( szCmd == NULL )
			return 0;

		char * szArguments = "";
		char * szTok       = strtok( NULL, " " );

		while( szTok != NULL )
			strcat( szArguments, szTok );

		// Convert the command to a wide char
		const size_t newSize  = 1024;
		wchar_t wcCmd[newSize];
		
		mbstowcs( wcCmd, szCmd, newSize );

		// Convert the arguments to a wide char
		wchar_t wcArguments[newSize];
		mbstowcs( wcArguments, szArguments, newSize );

		return callback.Evaluate<int>( playerInstance, wcCmd, wcArguments );
	}
	else
		return 1;
}

int OnPrivateMessage( int nPlayerId, int nTargetId, const char* pszText )
{
	CPlayer playerInstance = playerMap[ nPlayerId ];
	CPlayer targetInstance = playerMap[ nTargetId ];

	Function callback = RootTable().GetFunction( _SC("onPlayerPM") );
	if( !callback.IsNull() )
	{
		// Convert the message to a wide char
		const size_t newSize  = 1024;
		wchar_t wcText[newSize];
		
		mbstowcs( wcText, pszText, newSize );
		return callback.Evaluate<int>( playerInstance, targetInstance, wcText );
	}
	else
		return 1;
}

void OnPlayerBeginTyping( int nPlayerId )
{
	CPlayer playerInstance = playerMap[ nPlayerId ];
	Function callback      = RootTable().GetFunction( _SC("onPlayerBeginTyping") );

	if( !callback.IsNull() )
		callback( playerInstance );
}

void OnPlayerEndTyping( int nPlayerId )
{
	CPlayer playerInstance = playerMap[ nPlayerId ];
	Function callback      = RootTable().GetFunction( _SC("onPlayerEndTyping") );

	if( !callback.IsNull() )
		callback( playerInstance );
}

int OnLoginAttempt( char* playerName, const char* password, const char* pszIpAddress )
{
	Function callback = RootTable().GetFunction( _SC("onLoginAttempt") );
	if( !callback.IsNull() )
	{
		// See if the player's name is going to be changed
		OnNameChangeable( playerName, &playerName );

		// Convert the name to wide char
		wchar_t wcName[ 128 ];
		mbstowcs( wcName, playerName, 128 );

		// Convert the password to wide char
		wchar_t wcPassword[ 128 ];
		mbstowcs( wcPassword, password, 128 );

		// Convert the IP address to wide char
		wchar_t wcIp[ 16 ];
		mbstowcs( wcIp, pszIpAddress, 16 );

		// Pass them on to the callback
		return callback.Evaluate<int>(wcName, wcPassword, wcIp);
	}
	else
		return 1;
}

void OnNameChangeable( char * playerName, char ** namePtr )
{
	Function callback = RootTable().GetFunction( _SC("onNameChangeable") );
	if( !callback.IsNull() )
	{
		char * name = callback.Evaluate<char *>(playerName);
		if( name && strlen(name) > 0 )
			namePtr = &name;
	}
}

// I'm going to hate myself for using this
std::map<int, Vector> lastVehPos;
std::map<int, float> lastVehHP;

void OnVehicleUpdate( int nVehicleId, int nUpdateType )
{
	Vector lastPos = lastVehPos[nVehicleId];
	float lastHP   = lastVehHP[nVehicleId];

	float x, y, z;
	functions->GetVehiclePos( nVehicleId, &x, &y, &z );

	float hp = functions->GetVehicleHealth( nVehicleId );

	// Check for onVehicleHealthChange triggers
	if( lastHP != hp )
	{
	}

	// Check for onVehicleMove triggers
	if( lastPos.x != x || lastPos.y != y || lastPos.z != z )
	{
	}
}

// Yeah
std::map<int, Vector> lastPlrPos;
std::map<int, float> lastPlrArmour;
std::map<int, float> lastPlrHP;
std::map<int, int> lastPlrWep;

void OnPlayerUpdate( int nPlayerId, int nUpdateType )
{
	Vector lastPos   = lastPlrPos[nPlayerId];
	float lastArmour = lastPlrArmour[nPlayerId];
	float lastHP     = lastPlrHP[nPlayerId];
	int lastWep      = lastPlrWep[nPlayerId];

	float x, y, z;
	functions->GetPlayerPos( nPlayerId, &x, &y, &z );

	float hp     = functions->GetPlayerHealth( nPlayerId );
	float armour = functions->GetPlayerArmour( nPlayerId );
	int wep      = functions->GetPlayerWeapon( nPlayerId );

	// Check for onPlayerMove triggers
	if( lastPos.x != x || lastPos.y != y || lastPos.z != z )
	{
	}

	// Check for onPlayerHealthChange triggers
	if( lastHP != hp )
	{
	}

	// Check for onPlayerArmourChange triggers
	if( lastArmour != armour )
	{
	}

	// Check for onPlayerWeaponChange triggers
	if( lastWep != wep )
	{
	}
}

// We don't handle this one because I have no idea what the hell this is.
int OnInternalCommand( unsigned int uCmdType, const char* pszText )
{
	return 1;
}