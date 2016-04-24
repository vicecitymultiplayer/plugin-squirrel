#include "CCore.h"
#include "CPlayer.h"
#include "CVehicle.h"
#include "main.h"

// Core instance
extern CCore * pCore;

void CVehicle::SetWorld( int world ) { functions->SetVehicleWorld( this->nVehicleId, world ); }
void CVehicle::SetImmunity( int immunity ) { functions->SetVehicleImmunityFlags( this->nVehicleId, immunity ); }
void CVehicle::SetPosition( Vector pos ) { functions->SetVehiclePosition( this->nVehicleId, pos.x, pos.y, pos.z, 0 ); }

void CVehicle::SetSpawnPos( Vector pos )
{
	functions->SetVehicleSpawnPosition( this->nVehicleId, pos.x, pos.y, pos.z );
}

void CVehicle::SetSpawnAngle(Quaternion angle)
{
	functions->SetVehicleSpawnRotation(this->nVehicleId, angle.x, angle.y, angle.z, angle.w);
}

void CVehicle::SetSpawnAngleEuler(Vector angle)
{
	functions->SetVehicleSpawnRotationEuler(this->nVehicleId, angle.x, angle.y, angle.z);
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

void CVehicle::SetLocked( bool isLocked ) { functions->SetVehicleOption( this->nVehicleId, vcmpVehicleOptionDoorsLocked, isLocked ); }
void CVehicle::SetDamage( unsigned int damage ) { functions->SetVehicleDamageData( this->nVehicleId, damage ); }
void CVehicle::SetAlarm( bool isAlarmOn ) { functions->SetVehicleOption( this->nVehicleId, vcmpVehicleOptionAlarm, isAlarmOn ); }
void CVehicle::SetSiren(bool isSirenOn) { functions->SetVehicleOption(this->nVehicleId, vcmpVehicleOptionSiren, isSirenOn); }
void CVehicle::SetLights( bool lightsOn ) { functions->SetVehicleOption( this->nVehicleId, vcmpVehicleOptionLights, lightsOn ); }

int CVehicle::GetWorld() { return functions->GetVehicleWorld(this->nVehicleId); }
int CVehicle::GetModel() { return functions->GetVehicleModel(this->nVehicleId); }
int CVehicle::GetImmunity() { return functions->GetVehicleImmunityFlags(this->nVehicleId); }

EntityVector CVehicle::GetPosition()
{
	float x, y, z;
	functions->GetVehiclePosition( this->nVehicleId, &x, &y, &z );

	return EntityVector( this->nVehicleId, ENTITY_VEHICLE, VEHVECTOR_POS, x, y, z );
}

EntityVector CVehicle::GetSpawnPos()
{
	float x, y, z;
	functions->GetVehicleSpawnPosition( this->nVehicleId, &x, &y, &z );

	return EntityVector( this->nVehicleId, ENTITY_VEHICLE, VEHVECTOR_SPAWNPOS, x, y, z );
}

EntityQuaternion CVehicle::GetSpawnAngle()
{
	float x, y, z, w;
	functions->GetVehicleSpawnRotation(this->nVehicleId, &x, &y, &z, &w);

	return EntityQuaternion(this->nVehicleId, ENTITY_VEHICLE, VEHQUAT_SPAWNANGLE, x, y, z, w);
}

EntityVector CVehicle::GetSpawnAngleEuler()
{
	float x, y, z;
	functions->GetVehicleSpawnRotationEuler(this->nVehicleId, &x, &y, &z);

	return EntityVector(this->nVehicleId, ENTITY_VEHICLE, VEHVECTOR_SPAWNANGLE, x, y, z);
}

Vector CVehicle::GetTurretRotation()
{
	float x, y;
	functions->GetVehicleTurretRotation(this->nVehicleId, &x, &y);

	return Vector(x, y, 0.0f);
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

bool CVehicle::GetLocked() { return (functions->GetVehicleOption(this->nVehicleId, vcmpVehicleOptionDoorsLocked) == 1 ? true : false); }
unsigned int CVehicle::GetDamage() { return functions->GetVehicleDamageData(this->nVehicleId); }
bool CVehicle::GetAlarm() { return (functions->GetVehicleOption(this->nVehicleId, vcmpVehicleOptionAlarm) == 1 ? true : false); }
bool CVehicle::GetSiren() { return (functions->GetVehicleOption(this->nVehicleId, vcmpVehicleOptionSiren) == 1 ? true : false); }
bool CVehicle::GetLights() { return (functions->GetVehicleOption(this->nVehicleId, vcmpVehicleOptionLights) == 1 ? true : false); }

CPlayer * CVehicle::GetDriver()
{
	int driver = -1;
	for( int i = 0; i < functions->GetMaxPlayers(); i++ )
	{
		if( functions->IsPlayerConnected( i ) )
		{
			if( functions->GetPlayerVehicleId( i ) == this->nVehicleId
				&& functions->GetPlayerInVehicleSlot(i) == 0 )
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

void CVehicle::Fix()
{
	functions->SetVehicleHealth( this->nVehicleId, 1000 );
	functions->SetVehicleDamageData( this->nVehicleId, 0 );
}

void CVehicle::Respawn() { functions->RespawnVehicle( this->nVehicleId ); }
void CVehicle::Kill() { functions->ExplodeVehicle( this->nVehicleId ); }
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
	functions->GetVehicleRotation( this->nVehicleId, &x, &y, &z, &w );

	return EntityQuaternion(this->nVehicleId, ENTITY_VEHICLE, VEHQUAT_ANGLE, x, y, z, w);
}

EntityVector CVehicle::GetEulerRotation()
{
	float x, y, z;
	functions->GetVehicleRotationEuler( this->nVehicleId, &x, &y, &z );

	return EntityVector( this->nVehicleId, ENTITY_VEHICLE, VEHVECTOR_ANGLE, x, y, z );
}

EntityVector CVehicle::GetSpeed()
{
	float x, y, z;
	functions->GetVehicleSpeed( this->nVehicleId, &x, &y, &z, false );

	return EntityVector( this->nVehicleId, ENTITY_VEHICLE, VEHVECTOR_SPEED, x, y, z );
}

EntityVector CVehicle::GetRelativeSpeed()
{
	float x, y, z;
	functions->GetVehicleSpeed( this->nVehicleId, &x, &y, &z, true );

	return EntityVector( this->nVehicleId, ENTITY_VEHICLE, VEHVECTOR_RELSPEED, x, y, z );
}

EntityVector CVehicle::GetTurnSpeed()
{
	float x, y, z;
	functions->GetVehicleTurnSpeed( this->nVehicleId, &x, &y, &z, false );

	return EntityVector( this->nVehicleId, ENTITY_VEHICLE, VEHVECTOR_TURNSPEED, x, y, z );
}

EntityVector CVehicle::GetRelativeTurnSpeed()
{
	float x, y, z;
	functions->GetVehicleTurnSpeed( this->nVehicleId, &x, &y, &z, true );

	return EntityVector( this->nVehicleId, ENTITY_VEHICLE, VEHVECTOR_RELTURNSPEED, x, y, z );
}

void CVehicle::SetRotation( Quaternion rotation ) { functions->SetVehicleRotation( this->nVehicleId, rotation.x, rotation.y, rotation.z, rotation.w ); }
void CVehicle::SetEulerRotation( Vector rotation ) { functions->SetVehicleRotationEuler( this->nVehicleId, rotation.x, rotation.y, rotation.z ); }
void CVehicle::SetSpeed( Vector speed ) { functions->SetVehicleSpeed( this->nVehicleId, speed.x, speed.y, speed.z, false, false ); }
void CVehicle::SetRelativeSpeed( Vector speed ) { functions->SetVehicleSpeed( this->nVehicleId, speed.x, speed.y, speed.z, false, true ); }
void CVehicle::SetTurnSpeed( Vector speed ) { functions->SetVehicleTurnSpeed( this->nVehicleId, speed.x, speed.y, speed.z, false, false ); }
void CVehicle::SetRelativeTurnSpeed( Vector speed ) { functions->SetVehicleTurnSpeed( this->nVehicleId, speed.x, speed.y, speed.z, false, true ); }
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
	functions->SetVehicleSpeed( this->nVehicleId, speed.x, speed.y, speed.z, true, false );
}

void CVehicle::AddVehicleRelSpeed( Vector speed )
{
	functions->SetVehicleSpeed( this->nVehicleId, speed.x, speed.y, speed.z, true, true );
}

void CVehicle::AddVehicleTurnSpeed( Vector speed )
{
	functions->SetVehicleTurnSpeed( this->nVehicleId, speed.x, speed.y, speed.z, true, false );
}

void CVehicle::AddVehicleRelTurnSpeed( Vector speed )
{
	functions->SetVehicleTurnSpeed( this->nVehicleId, speed.x, speed.y, speed.z, true, true );
}

int CVehicle::GetRadio() { return functions->GetVehicleRadio(this->nVehicleId); }
void CVehicle::SetRadio(const int nRadioId) { functions->SetVehicleRadio(this->nVehicleId, nRadioId); }

bool CVehicle::GetRadioLockStatus() { return functions->GetVehicleOption(this->nVehicleId, vcmpVehicleOptionRadioLocked) == 1; }
void CVehicle::SetRadioLocked(const bool isLocked) { functions->SetVehicleOption(this->nVehicleId, vcmpVehicleOptionRadioLocked, isLocked); }

bool CVehicle::GetGhost() { return functions->GetVehicleOption(this->nVehicleId, vcmpVehicleOptionGhost) == 1; }
void CVehicle::SetGhost(const bool isGhost) { functions->SetVehicleOption(this->nVehicleId, vcmpVehicleOptionGhost, isGhost); }

void RegisterVehicle()
{
	Class <CVehicle> c(v, "CVehicle_INTERNAL");

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
		.Prop( _SC("Siren"), &CVehicle::GetSiren, &CVehicle::SetSiren )
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
		.Prop( _SC("RadioLocked"), &CVehicle::GetRadioLockStatus, &CVehicle::SetRadioLocked )
		.Prop( _SC("IsGhost"), &CVehicle::GetGhost, &CVehicle::SetGhost );

	// Read-only properties
	c
		.Prop( _SC("Model"), &CVehicle::GetModel )
		.Prop( _SC("Driver"), &CVehicle::GetDriver )
		.Prop( _SC("ID"), &CVehicle::GetID )
		.Prop( _SC("SyncSource"), &CVehicle::GetSyncSource )
		.Prop( _SC("SyncType"), &CVehicle::GetSyncType )
		.Prop(_SC("TurretRotation"), &CVehicle::GetTurretRotation)
		.Prop( _SC("Wrecked"), &CVehicle::GetWrecked );

	// Functions
	c
		.Func( _SC("Delete"), &CVehicle::Delete, 1, "x" )
		.Func( _SC("Remove"), &CVehicle::Delete, 1, "x" )
		.Func( _SC("Respawn"), &CVehicle::Respawn, 1, "x" )
		.Func( _SC("Kill"), &CVehicle::Kill, 1, "x" )
		.Func( _SC("KillEngine"), &CVehicle::Kill, 1, "x" )
		.Func( _SC("Fix"), &CVehicle::Fix, 1, "x")
		.Func( _SC("GetPart"), &CVehicle::GetPartStatus, 2, "xi" )
		.Func( _SC("SetPart"), &CVehicle::SetPartStatus, 3, "xii" )
		.Func( _SC("GetTyre"), &CVehicle::GetTyreStatus, 2 ,"xi" )
		.Func( _SC("SetTyre"), &CVehicle::SetTyreStatus, 3, "xii" )
		.Func( _SC("GetTire"), &CVehicle::GetTyreStatus, 2, "xi" )
		.Func( _SC("SetTire"), &CVehicle::SetTyreStatus, 3, "xii" )
		.Func( _SC("SetFlatTyres"), &CVehicle::SetFlatTyres, 2, "xb" )
		.Func( _SC("StreamedForPlayer"), &CVehicle::GetStreamedForPlayer, 2, "xx" )
		.Func( _SC("GetOccupant"), &CVehicle::GetOccupant, 2, "xi" )
		.Func( _SC("SetHandlingData"), &CVehicle::SetHandlingData, 3, "xin" )
		.Func( _SC("GetHandlingData"), &CVehicle::GetHandlingData, 2, "xi" )
		.Func( _SC("ResetHandlingData"), &CVehicle::ResetHandlingData, 2, "xi" )
		.Func( _SC("ResetAllHandling"), &CVehicle::ResetAllHandling, 1, "x" )
		.Func( _SC("IsHandlingSet"), &CVehicle::IsHandlingSet, 2, "xi" )
		.Func( _SC("AddSpeed"), &CVehicle::AddVehicleSpeed, 2, "xx" )
		.Func( _SC("AddRelSpeed"), &CVehicle::AddVehicleRelSpeed, 2, "xx" )
		.Func( _SC("AddTurnSpeed"), &CVehicle::AddVehicleTurnSpeed, 2, "xx" )
		.Func( _SC("AddRelTurnSpeed"), &CVehicle::AddVehicleRelTurnSpeed, 2, "xx" );

	RootTable(v).Bind( _SC("CVehicle"), c );
}
