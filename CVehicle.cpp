#include "CPlayer.h"
#include "CVehicle.h"
#include "main.h"

void CVehicle::SetWorld( int world ) { functions->SetVehicleWorld( this->nVehicleId, world ); }
void CVehicle::SetImmunity( int immunity ) { functions->SetVehicleImmunityFlags( this->nVehicleId, immunity ); }
void CVehicle::SetPosition( Vector pos ) { functions->SetVehiclePos( this->nVehicleId, pos.x, pos.y, pos.z, 0.0f ); }

void CVehicle::SetSpawnPos( Vector pos )
{
	float zRot;
	functions->GetVehicleSpawnPos( this->nVehicleId, NULL, NULL, NULL, &zRot );
	functions->SetVehicleSpawnPos( this->nVehicleId, pos.x, pos.y, pos.z, zRot );
}

void CVehicle::SetSpawnAngle( float angle )
{
	float x, y, z;
	functions->GetVehicleSpawnPos( this->nVehicleId, &x, &y, &z, NULL );
	functions->SetVehicleSpawnPos( this->nVehicleId, x, y, z, angle );
}

void CVehicle::SetIdleRespawnTimer( unsigned int time ) { functions->SetVehicleIdleRespawnTimer( this->nVehicleId, time ); }
void CVehicle::SetHealth( float health ) { functions->SetVehicleHealth( this->nVehicleId, health ); }

void CVehicle::SetColour1( int colour1 )
{
	int col2;
	functions->GetVehicleColour( this->nVehicleId, NULL, &col2 );
	functions->SetVehicleColour( this->nVehicleId, colour1, col2 );
}

void CVehicle::SetColour2( int colour2 )
{
	int col1;
	functions->GetVehicleColour( this->nVehicleId, &col1, NULL );
	functions->SetVehicleColour( this->nVehicleId, col1, colour2 );
}

void CVehicle::SetLocked( bool isLocked ) { functions->SetVehicleDoorsLocked( this->nVehicleId, isLocked ); }
void CVehicle::SetDamage( unsigned int damage ) { functions->SetVehicleDamageData( this->nVehicleId, damage ); }
void CVehicle::SetAlarm( bool isAlarmOn ) { functions->SetVehicleAlarm( this->nVehicleId, isAlarmOn ); }
void CVehicle::SetLights( bool lightsOn ) { functions->SetVehicleLights( this->nVehicleId, lightsOn ); }

int CVehicle::GetWorld() { return functions->GetVehicleWorld( this->nVehicleId ); }
int CVehicle::GetModel() { return functions->GetVehicleModel( this->nVehicleId ); }
int CVehicle::GetImmunity() { return functions->GetVehicleImmunityFlags( this->nVehicleId ); }

Vector CVehicle::GetPosition()
{
	float x, y, z;
	functions->GetVehiclePos( this->nVehicleId, &x, &y, &z );

	return Vector( x, y, z );
}

Vector CVehicle::GetSpawnPos()
{
	float x, y, z;
	functions->GetVehicleSpawnPos( this->nVehicleId, &x, &y, &z, NULL );

	return Vector( x, y, z );
}

float CVehicle::GetSpawnAngle()
{
	float angle;
	functions->GetVehicleSpawnPos( this->nVehicleId, NULL, NULL, NULL, &angle );

	return angle;
}

unsigned int CVehicle::GetIdleRespawnTimer() { return functions->GetVehicleIdleRespawnTimer( this->nVehicleId ); }
float CVehicle::GetHealth() { return functions->GetVehicleHealth( this->nVehicleId ); }

int CVehicle::GetColour1()
{
	int col1;
	functions->GetVehicleColour( this->nVehicleId, &col1, NULL );

	return col1;
}

int CVehicle::GetColour2()
{
	int col2;
	functions->GetVehicleColour( this->nVehicleId, NULL, &col2 );

	return col2;
}

bool CVehicle::GetLocked() { return functions->GetVehicleDoorsLocked( this->nVehicleId ); }
unsigned int CVehicle::GetDamage() { return functions->GetVehicleDamageData( this->nVehicleId ); }
bool CVehicle::GetAlarm() { return functions->GetVehicleAlarm( this->nVehicleId ); }
bool CVehicle::GetLights() { return functions->GetVehicleLights( this->nVehicleId ); }

CPlayer * CVehicle::GetDriver()
{
	int driver = -1;
	for( int i = 0; i < functions->GetMaxPlayers(); i++ )
	{
		if( functions->IsPlayerConnected( i ) )
		{
			if( functions->GetPlayerVehicleID( i ) == this->nVehicleId )
			{
				driver = i;
				break;
			}
		}
	}

	if( driver == -1 )
		return NULL;
	else
		return playerMap[driver];
}

void CVehicle::Delete()
{
	functions->DeleteVehicle( this->nVehicleId );
	vehicleMap[this->nVehicleId] = NULL;

	// oh man
	delete this;
}

void CVehicle::Respawn() { functions->RespawnVehicle( this->nVehicleId ); }
void CVehicle::Kill() { functions->KillVehicle( this->nVehicleId ); }
int CVehicle::GetPartStatus( int part ) { return functions->GetVehiclePartStatus( this->nVehicleId, part ); }
void CVehicle::SetPartStatus( int part, int status ) { functions->SetVehiclePartStatus( this->nVehicleId, part, status ); }
int CVehicle::GetTyreStatus( int tyre ) { return functions->GetVehicleTyreStatus( this->nVehicleId, tyre ); }
void CVehicle::SetTyreStatus( int tyre, int status ) { functions->SetVehicleTyreStatus( this->nVehicleId, tyre, status ); }
int CVehicle::GetID() { return this->nVehicleId; }

int CVehicle::GetSyncSource() { return functions->GetVehicleSyncSource( this->nVehicleId ); }
int CVehicle::GetSyncType() { return functions->GetVehicleSyncType( this->nVehicleId ); }
bool CVehicle::GetStreamedForPlayer( CPlayer * player )
{
	if( player != NULL )
		return functions->IsVehicleStreamedForPlayer( this->nVehicleId, player->nPlayerId );

	return false;
}

bool CVehicle::GetWrecked() { return functions->IsVehicleWrecked( this->nVehicleId ); }

CPlayer * CVehicle::GetOccupant( int slot )
{
	int nPlayerId = functions->GetVehicleOccupant( this->nVehicleId, slot );
	
	if( nPlayerId == -1 )
		return NULL;
	else
		return playerMap[nPlayerId];
}

int CVehicle::SetHandlingData( int rule, float value ) { return functions->SetInstHandlingRule( this->nVehicleId, rule, value ); }
float CVehicle::GetHandlingData( int rule ) { return functions->GetInstHandlingRule( this->nVehicleId, rule ); }
void CVehicle::ResetHandlingData( int rule ) { functions->ResetInstHandlingRule( this->nVehicleId, rule ); }
void CVehicle::ResetAllHandling() { functions->ResetInstHandling( this->nVehicleId ); }
bool CVehicle::IsHandlingSet( int rule ) { return functions->ExistsInstHandlingRule( this->nVehicleId, rule ); }

void RegisterVehicle()
{
	Class <CVehicle> c(v);

	// Read-write properties
	c
		.Prop( _SC("World"), &CVehicle::GetWorld, &CVehicle::SetWorld )
		.Prop( _SC("Immunity"), &CVehicle::GetImmunity, &CVehicle::SetImmunity )
		.Prop( _SC("Pos"), &CVehicle::GetPosition, &CVehicle::SetPosition )
		.Prop( _SC("SpawnPos"), &CVehicle::GetSpawnPos, &CVehicle::SetSpawnPos )
		.Prop( _SC("SpawnAngle"), &CVehicle::GetSpawnAngle, &CVehicle::SetSpawnAngle )
		.Prop( _SC("RespawnTimer"), &CVehicle::GetIdleRespawnTimer, &CVehicle::SetIdleRespawnTimer )
		.Prop( _SC("Health"), &CVehicle::GetHealth, &CVehicle::SetHealth )
		.Prop( _SC("Colour1"), &CVehicle::GetColour1, &CVehicle::SetColour1 )
		.Prop( _SC("Colour2"), &CVehicle::GetColour2, &CVehicle::SetColour2 )
		.Prop( _SC("Locked"), &CVehicle::GetLocked, &CVehicle::SetLocked )
		.Prop( _SC("Damage"), &CVehicle::GetDamage, &CVehicle::SetDamage )
		.Prop( _SC("Alarm"), &CVehicle::GetAlarm, &CVehicle::SetAlarm )
		.Prop( _SC("Lights"), &CVehicle::GetLights, &CVehicle::SetLights );

	// Read-only properties
	c
		.Prop( _SC("Model"), &CVehicle::GetModel )
		.Prop( _SC("Driver"), &CVehicle::GetDriver )
		.Prop( _SC("ID"), &CVehicle::GetID )
		.Prop( _SC("SyncSource"), &CVehicle::GetSyncSource )
		.Prop( _SC("SyncType"), &CVehicle::GetSyncType )
		.Prop( _SC("Wrecked"), &CVehicle::GetWrecked );

	// Functions
	c
		.Func( _SC("Delete"), &CVehicle::Delete )
		.Func( _SC("Respawn"), &CVehicle::Respawn )
		.Func( _SC("Kill"), &CVehicle::Kill )
		.Func( _SC("GetPart"), &CVehicle::GetPartStatus )
		.Func( _SC("SetPart"), &CVehicle::SetPartStatus )
		.Func( _SC("GetTyre"), &CVehicle::GetTyreStatus )
		.Func( _SC("SetTyre"), &CVehicle::SetTyreStatus )
		.Func( _SC("GetTire"), &CVehicle::GetTyreStatus )
		.Func( _SC("SetTire"), &CVehicle::SetTyreStatus )
		.Func( _SC("StreamedForPlayer"), &CVehicle::GetStreamedForPlayer )
		.Func( _SC("GetOccupant"), &CVehicle::GetOccupant )
		.Func( _SC("SetHandlingData"), &CVehicle::SetHandlingData )
		.Func( _SC("GetHandlingData"), &CVehicle::GetHandlingData )
		.Func( _SC("ResetHandlingData"), &CVehicle::ResetHandlingData )
		.Func( _SC("ResetAllHandling"), &CVehicle::ResetAllHandling )
		.Func( _SC("IsHandlingSet"), &CVehicle::IsHandlingSet );

	RootTable(v).Bind( _SC("CVehicle"), c );
}