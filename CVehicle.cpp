#include "CCore.h"
#include "CPlayer.h"
#include "CVehicle.h"
#include "main.h"

// Core instance
extern CCore * pCore;

void CVehicle::SetWorld( int world ) { functions->SetVehicleWorld( this->nVehicleId, world ); }
void CVehicle::SetImmunity( int immunity ) { functions->SetVehicleImmunityFlags( this->nVehicleId, immunity ); }
void CVehicle::SetPosition( Vector pos ) { functions->SetVehiclePos( this->nVehicleId, pos.x, pos.y, pos.z, 0 ); }

void CVehicle::SetSpawnPos( Vector pos )
{
	float zRot;
	functions->GetVehicleSpawnPos( this->nVehicleId, NULL, NULL, NULL, &zRot );
	functions->SetVehicleSpawnPos( this->nVehicleId, pos.x, pos.y, pos.z, zRot );
}

void CVehicle::SetSpawnAngle(Quaternion angle)
{
	functions->SetVehicleSpawnRot(this->nVehicleId, angle.x, angle.y, angle.z, angle.w);
}

void CVehicle::SetSpawnAngleEuler(Vector angle)
{
	functions->SetVehicleSpawnRotEuler(this->nVehicleId, angle.x, angle.y, angle.z);
}

void CVehicle::SetIdleRespawnTimer( unsigned int time ) { functions->SetVehicleIdleRespawnTimer( this->nVehicleId, time ); }
void CVehicle::SetHealth( float health ) { functions->SetVehicleHealth( this->nVehicleId, health ); }

void CVehicle::SetColour1( int colour1 )
{
	int oldCol1, col2;
	functions->GetVehicleColour( this->nVehicleId, &oldCol1, &col2 );
	functions->SetVehicleColour( this->nVehicleId, colour1, col2 );
}

void CVehicle::SetColour2( int colour2 )
{
	int col1, oldCol2;
	functions->GetVehicleColour( this->nVehicleId, &col1, &oldCol2 );
	functions->SetVehicleColour( this->nVehicleId, col1, colour2 );
}

void CVehicle::SetLocked( bool isLocked ) { functions->SetVehicleDoorsLocked( this->nVehicleId, isLocked ); }
void CVehicle::SetDamage( unsigned int damage ) { functions->SetVehicleDamageData( this->nVehicleId, damage ); }
void CVehicle::SetAlarm( bool isAlarmOn ) { functions->SetVehicleAlarm( this->nVehicleId, isAlarmOn ); }
void CVehicle::SetLights( bool lightsOn ) { functions->SetVehicleLights( this->nVehicleId, lightsOn ); }

int CVehicle::GetWorld() { return functions->GetVehicleWorld(this->nVehicleId); }
int CVehicle::GetModel() { return functions->GetVehicleModel(this->nVehicleId); }
int CVehicle::GetImmunity() { return functions->GetVehicleImmunityFlags(this->nVehicleId); }

EntityVector CVehicle::GetPosition()
{
	float x, y, z;
	functions->GetVehiclePos( this->nVehicleId, &x, &y, &z );

	return EntityVector( this->nVehicleId, ENTITY_VEHICLE, VEHVECTOR_POS, x, y, z );
}

EntityVector CVehicle::GetSpawnPos()
{
	float x, y, z;
	functions->GetVehicleSpawnPos( this->nVehicleId, &x, &y, &z, NULL );

	return EntityVector( this->nVehicleId, ENTITY_VEHICLE, VEHVECTOR_SPAWNPOS, x, y, z );
}

EntityQuaternion CVehicle::GetSpawnAngle()
{
	float x, y, z, w;
	functions->GetVehicleSpawnRot(this->nVehicleId, &x, &y, &z, &w);

	return EntityQuaternion(this->nVehicleId, ENTITY_VEHICLE, VEHQUAT_SPAWNANGLE, x, y, z, w);
}

EntityVector CVehicle::GetSpawnAngleEuler()
{
	float x, y, z;
	functions->GetVehicleSpawnRotEuler(this->nVehicleId, &x, &y, &z);

	return EntityVector(this->nVehicleId, ENTITY_VEHICLE, VEHVECTOR_SPAWNANGLE, x, y, z);
}

unsigned int CVehicle::GetIdleRespawnTimer() { return functions->GetVehicleIdleRespawnTimer(this->nVehicleId); }
float CVehicle::GetHealth() { return functions->GetVehicleHealth(this->nVehicleId); }

int CVehicle::GetColour1()
{
	int col1, col2;
	functions->GetVehicleColour( this->nVehicleId, &col1, &col2 );

	return col1;
}

int CVehicle::GetColour2()
{
	int col1, col2;
	functions->GetVehicleColour( this->nVehicleId, &col1, &col2 );

	return col2;
}

bool CVehicle::GetLocked() { return (functions->GetVehicleDoorsLocked(this->nVehicleId) == 1 ? true : false); }
unsigned int CVehicle::GetDamage() { return functions->GetVehicleDamageData(this->nVehicleId); }
bool CVehicle::GetAlarm() { return (functions->GetVehicleAlarm(this->nVehicleId) == 1 ? true : false); }
bool CVehicle::GetLights() { return (functions->GetVehicleLights(this->nVehicleId) == 1 ? true : false); }

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

	return pCore->RetrievePlayer(driver);
}

void CVehicle::Delete()
{
	//PS! this instance will be deleted due to a callback!!!
	functions->DeleteVehicle( this->nVehicleId );
}

void CVehicle::Respawn() { functions->RespawnVehicle( this->nVehicleId ); }
void CVehicle::Kill() { functions->KillVehicle( this->nVehicleId ); }
int CVehicle::GetPartStatus( int part ) { return functions->GetVehiclePartStatus( this->nVehicleId, part ); }
void CVehicle::SetPartStatus( int part, int status ) { functions->SetVehiclePartStatus( this->nVehicleId, part, status ); }
int CVehicle::GetTyreStatus( int tyre ) { return functions->GetVehicleTyreStatus( this->nVehicleId, tyre ); }
void CVehicle::SetTyreStatus( int tyre, int status ) { functions->SetVehicleTyreStatus( this->nVehicleId, tyre, status ); }
int CVehicle::GetID() { return this->nVehicleId; }

int CVehicle::GetSyncSource() { return functions->GetVehicleSyncSource(this->nVehicleId); }
int CVehicle::GetSyncType() { return functions->GetVehicleSyncType( this->nVehicleId ); }
bool CVehicle::GetStreamedForPlayer( CPlayer * player )
{
	if( player != NULL )
		return ( functions->IsVehicleStreamedForPlayer( this->nVehicleId, player->nPlayerId ) == 1 ? true : false );

	return false;
}

bool CVehicle::GetWrecked() { return (functions->IsVehicleWrecked(this->nVehicleId) == 1 ? true : false); }

CPlayer * CVehicle::GetOccupant( int slot )
{
	int nPlayerId = functions->GetVehicleOccupant( this->nVehicleId, slot );
	return pCore->RetrievePlayer(nPlayerId);
}

int CVehicle::SetHandlingData( int rule, float value ) { return functions->SetInstHandlingRule( this->nVehicleId, rule, value ); }
double CVehicle::GetHandlingData( int rule ) { return functions->GetInstHandlingRule( this->nVehicleId, rule ); }
void CVehicle::ResetHandlingData( int rule ) { functions->ResetInstHandlingRule( this->nVehicleId, rule ); }
void CVehicle::ResetAllHandling() { functions->ResetInstHandling(this->nVehicleId); }
bool CVehicle::IsHandlingSet( int rule ) { return ( functions->ExistsInstHandlingRule( this->nVehicleId, rule ) == 1 ? true : false ); }

EntityQuaternion CVehicle::GetRotation()
{
	float w, x, y, z;
	functions->GetVehicleRot( this->nVehicleId, &x, &y, &z, &w );

	return EntityQuaternion(this->nVehicleId, ENTITY_VEHICLE, VEHQUAT_ANGLE, w, x, y, z);
}

EntityVector CVehicle::GetEulerRotation()
{
	float x, y, z;
	functions->GetVehicleRotEuler( this->nVehicleId, &x, &y, &z );

	return EntityVector( this->nVehicleId, ENTITY_VEHICLE, VEHVECTOR_ANGLE, x, y, z );
}

EntityVector CVehicle::GetSpeed()
{
	float x, y, z;
	functions->GetVehicleSpeed( this->nVehicleId, &x, &y, &z );

	return EntityVector( this->nVehicleId, ENTITY_VEHICLE, VEHVECTOR_SPEED, x, y, z );
}

EntityVector CVehicle::GetRelativeSpeed()
{
	float x, y, z;
	functions->GetVehicleRelSpeed( this->nVehicleId, &x, &y, &z );

	return EntityVector( this->nVehicleId, ENTITY_VEHICLE, VEHVECTOR_RELSPEED, x, y, z );
}

EntityVector CVehicle::GetTurnSpeed()
{
	float x, y, z;
	functions->GetVehicleTurnSpeed( this->nVehicleId, &x, &y, &z );

	return EntityVector( this->nVehicleId, ENTITY_VEHICLE, VEHVECTOR_TURNSPEED, x, y, z );
}

EntityVector CVehicle::GetRelativeTurnSpeed()
{
	float x, y, z;
	functions->GetVehicleRelTurnSpeed( this->nVehicleId, &x, &y, &z );

	return EntityVector( this->nVehicleId, ENTITY_VEHICLE, VEHVECTOR_RELTURNSPEED, x, y, z );
}

void CVehicle::SetRotation( Quaternion rotation ) { functions->SetVehicleRot( this->nVehicleId, rotation.x, rotation.y, rotation.z, rotation.w ); }
void CVehicle::SetEulerRotation( Vector rotation ) { functions->SetVehicleRotEuler( this->nVehicleId, rotation.x, rotation.y, rotation.z ); }
void CVehicle::SetSpeed( Vector speed ) { functions->SetVehicleSpeed( this->nVehicleId, speed.x, speed.y, speed.z ); }
void CVehicle::SetRelativeSpeed( Vector speed ) { functions->SetVehicleRelSpeed( this->nVehicleId, speed.x, speed.y, speed.z ); }
void CVehicle::SetTurnSpeed( Vector speed ) { functions->SetVehicleTurnSpeed( this->nVehicleId, speed.x, speed.y, speed.z ); }
void CVehicle::SetRelativeTurnSpeed( Vector speed ) { functions->SetVehicleRelTurnSpeed( this->nVehicleId, speed.x, speed.y, speed.z ); }
void CVehicle::SetFlatTyres( bool isFlat )
{
	if( isFlat )
	{
		functions->SetVehicleTyreStatus( this->nVehicleId, 0, 0 );
		functions->SetVehicleTyreStatus( this->nVehicleId, 1, 0 );
		functions->SetVehicleTyreStatus( this->nVehicleId, 2, 0 );
		functions->SetVehicleTyreStatus( this->nVehicleId, 3, 0 );
	}
	else
	{
		functions->SetVehicleTyreStatus( this->nVehicleId, 0, 1 );
		functions->SetVehicleTyreStatus( this->nVehicleId, 1, 1 );
		functions->SetVehicleTyreStatus( this->nVehicleId, 2, 1 );
		functions->SetVehicleTyreStatus( this->nVehicleId, 3, 1 );
	}
}

void CVehicle::AddVehicleSpeed( Vector speed )
{
	functions->AddVehicleSpeed( this->nVehicleId, speed.x, speed.y, speed.z );
}

void CVehicle::AddVehicleTurnSpeed( Vector speed )
{
	functions->AddVehicleTurnSpeed( this->nVehicleId, speed.x, speed.y, speed.z );
}

void CVehicle::AddVehicleRelTurnSpeed( Vector speed )
{
	functions->AddVehicleRelTurnSpeed( this->nVehicleId, speed.x, speed.y, speed.z );
}

int CVehicle::GetRadio() { return functions->GetVehicleRadio(this->nVehicleId); }
void CVehicle::SetRadio(const int nRadioId) { functions->SetVehicleRadio(this->nVehicleId, nRadioId); }

bool CVehicle::GetRadioLockStatus() { return functions->IsVehicleRadioLocked(this->nVehicleId) == 1; }
void CVehicle::SetRadioLocked(const bool isLocked) { functions->SetVehicleRadioLocked(this->nVehicleId, isLocked); }

void RegisterVehicle()
{
	Class <CVehicle> c(v);

	// Read-write properties
	c
		.Prop( _SC("Immunity"), &CVehicle::GetImmunity, &CVehicle::SetImmunity )
		.Prop( _SC("Pos"), &CVehicle::GetPosition, &CVehicle::SetPosition )
		.Prop( _SC("World"), &CVehicle::GetWorld, &CVehicle::SetWorld )
		.Prop( _SC("SpawnPos"), &CVehicle::GetSpawnPos, &CVehicle::SetSpawnPos )
		.Prop( _SC("EulerSpawnAngle"), &CVehicle::GetSpawnAngleEuler, &CVehicle::SetSpawnAngleEuler )
		.Prop( _SC("SpawnAngle"), &CVehicle::GetSpawnAngle, &CVehicle::SetSpawnAngle )
		.Prop( _SC("RespawnTimer"), &CVehicle::GetIdleRespawnTimer, &CVehicle::SetIdleRespawnTimer )
		.Prop( _SC("Health"), &CVehicle::GetHealth, &CVehicle::SetHealth )
		.Prop( _SC("Colour1"), &CVehicle::GetColour1, &CVehicle::SetColour1 )
		.Prop( _SC("Colour2"), &CVehicle::GetColour2, &CVehicle::SetColour2 )
		.Prop( _SC("Locked"), &CVehicle::GetLocked, &CVehicle::SetLocked )
		.Prop( _SC("Damage"), &CVehicle::GetDamage, &CVehicle::SetDamage )
		.Prop( _SC("Alarm"), &CVehicle::GetAlarm, &CVehicle::SetAlarm )
		.Prop( _SC("Lights"), &CVehicle::GetLights, &CVehicle::SetLights )
		.Prop( _SC("Angle"), &CVehicle::GetRotation, &CVehicle::SetRotation )
		.Prop( _SC("Rotation"), &CVehicle::GetRotation, &CVehicle::SetRotation )
		.Prop( _SC("EulerAngle"), &CVehicle::GetEulerRotation, &CVehicle::SetEulerRotation )
		.Prop( _SC("EulerRotation"), &CVehicle::GetEulerRotation, &CVehicle::SetEulerRotation )
		.Prop( _SC("Speed"), &CVehicle::GetSpeed, &CVehicle::SetSpeed )
		.Prop( _SC("RelativeSpeed"), &CVehicle::GetRelativeSpeed, &CVehicle::SetRelativeSpeed )
		.Prop( _SC("TurnSpeed"), &CVehicle::GetTurnSpeed, &CVehicle::SetTurnSpeed )
		.Prop( _SC("RelativeTurnSpeed"), &CVehicle::GetRelativeTurnSpeed, &CVehicle::SetRelativeTurnSpeed )
		.Prop( _SC("Radio"), &CVehicle::GetRadio, &CVehicle::SetRadio )
		.Prop( _SC("RadioLocked"), &CVehicle::GetRadioLockStatus, &CVehicle::SetRadioLocked );
	
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
		.Func( _SC("Remove"), &CVehicle::Delete )
		.Func( _SC("Respawn"), &CVehicle::Respawn )
		.Func( _SC("Kill"), &CVehicle::Kill )
		.Func( _SC("KillEngine"), &CVehicle::Kill )
		.Func( _SC("GetPart"), &CVehicle::GetPartStatus )
		.Func( _SC("SetPart"), &CVehicle::SetPartStatus )
		.Func( _SC("GetTyre"), &CVehicle::GetTyreStatus )
		.Func( _SC("SetTyre"), &CVehicle::SetTyreStatus )
		.Func( _SC("GetTire"), &CVehicle::GetTyreStatus )
		.Func( _SC("SetTire"), &CVehicle::SetTyreStatus )
		.Func( _SC("SetFlatTyres"), &CVehicle::SetFlatTyres )
		.Func( _SC("StreamedForPlayer"), &CVehicle::GetStreamedForPlayer )
		.Func( _SC("GetOccupant"), &CVehicle::GetOccupant )
		.Func( _SC("SetHandlingData"), &CVehicle::SetHandlingData )
		.Func( _SC("GetHandlingData"), &CVehicle::GetHandlingData )
		.Func( _SC("ResetHandlingData"), &CVehicle::ResetHandlingData )
		.Func( _SC("ResetAllHandling"), &CVehicle::ResetAllHandling )
		.Func( _SC("IsHandlingSet"), &CVehicle::IsHandlingSet )
		.Func( _SC("AddSpeed"), &CVehicle::AddVehicleSpeed )
		.Func( _SC("AddTurnSpeed"), &CVehicle::AddVehicleTurnSpeed )
		.Func( _SC("AddRelTurnSpeed"), &CVehicle::AddVehicleRelTurnSpeed );

	RootTable(v).Bind( _SC("CVehicle"), c );
}