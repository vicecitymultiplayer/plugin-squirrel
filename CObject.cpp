#include "CObject.h"
#include "CPlayer.h"
#include "main.h"

void CObject::SetWorld( int world ) { functions->SetObjectWorld( this->nObjectId, world ); }
void CObject::SetPos( Vector pos ) { functions->SetObjectPos( this->nObjectId, pos.x, pos.y, pos.z ); }

int CObject::GetModel() { return functions->GetObjectModel( this->nObjectId ); }
int CObject::GetAlpha() { return functions->GetObjectAlpha(this->nObjectId); }
int CObject::GetWorld() { return functions->GetObjectWorld(this->nObjectId); }

EntityVector CObject::GetPos()
{
	float x, y, z;
	functions->GetObjectPos( this->nObjectId, &x, &y, &z );

	return EntityVector(this->nObjectId, ENTITY_OBJECT, OBJVECTOR_POS, x, y, z);
}

EntityQuaternion CObject::GetRotation()
{
	float w, x, y, z;
	functions->GetObjectRot( this->nObjectId, &x, &y, &z, &w );

	return EntityQuaternion(this->nObjectId, ENTITY_OBJECT, -1, x, y, z, w);
}

EntityVector CObject::GetRotationEuler()
{
	float x, y, z;
	functions->GetObjectRotEuler( this->nObjectId, &x, &y, &z );

	return EntityVector(this->nObjectId, ENTITY_OBJECT, OBJVECTOR_ROTATION, x, y, z);
}

void CObject::Delete()
{
	// PS! this instance will be deleted due to a callback!!!
	functions->DeleteObject( this->nObjectId );
}

void CObject::MoveTo( Vector pos, int time )
{
	functions->MoveObjectTo( this->nObjectId, pos.x, pos.y, pos.z, time );
}

void CObject::MoveBy( Vector offset, int time )
{
	functions->MoveObjectBy( this->nObjectId, offset.x, offset.y, offset.z, time );
}

void CObject::RotateTo( Quaternion rotation, int time )
{
	functions->RotObjectTo( this->nObjectId, rotation.x, rotation.y, rotation.z, rotation.w, time );
}

void CObject::RotateBy( Quaternion rotOffset, int time )
{
	functions->RotObjectBy( this->nObjectId, rotOffset.x, rotOffset.y, rotOffset.z, rotOffset.w, time );
}

void CObject::RotateToEuler( Vector rotation, int time )
{
	functions->RotObjectToEuler( this->nObjectId, rotation.x, rotation.y, rotation.z, time );
}

void CObject::RotateByEuler( Vector rotOffset, int time )
{
	functions->RotObjectByEuler( this->nObjectId, rotOffset.x, rotOffset.y, rotOffset.z, time );
}

void CObject::SetAlpha( int alpha, int fadeTime ) { functions->SetObjectAlpha( this->nObjectId, alpha, fadeTime ); }
int CObject::GetID() { return this->nObjectId; }
bool CObject::StreamedToPlayer( CPlayer * player )
{
	if( player != NULL )
		return ( functions->IsObjectStreamedForPlayer( this->nObjectId, player->nPlayerId ) == 1 ? true : false );

	return false;
}

void CObject::SetReportingShots( bool toReport ) { functions->SetObjectShotReport( this->nObjectId, toReport ); }
void CObject::SetReportingBumps( bool toReport ) { functions->SetObjectBumpReport( this->nObjectId, toReport ); }
bool CObject::GetReportingShots() { return ( functions->IsObjectShotReport( this->nObjectId ) == 1 ? true : false ); }
bool CObject::GetReportingBumps() { return ( functions->IsObjectBumpReport( this->nObjectId ) == 1 ? true : false ); }

void RegisterObject()
{
	Class<CObject> c(v, "CObject_INTERNAL");

	// Read-write properties
	c
		.Prop( _SC("World"), &CObject::GetWorld, &CObject::SetWorld )
		.Prop( _SC("Pos"), &CObject::GetPos, &CObject::SetPos )
		.Prop( _SC("TrackingShots"), &CObject::GetReportingShots, &CObject::SetReportingShots )
		.Prop( _SC("TrackingBumps"), &CObject::GetReportingBumps, &CObject::SetReportingBumps );

	// Read-only properties
	c
		.Prop( _SC("Alpha"), &CObject::GetAlpha )
		.Prop( _SC("Model"), &CObject::GetModel )
		.Prop( _SC("Rotation"), &CObject::GetRotation )
		.Prop( _SC("RotationEuler"), &CObject::GetRotationEuler )
		.Prop( _SC("ID"), &CObject::GetID );

	// Functions
	c
		.Func( _SC("Delete"), &CObject::Delete, 1, "x" )
		.Func( _SC("MoveTo"), &CObject::MoveTo, 3, "xxi" )
		.Func( _SC("MoveBy"), &CObject::MoveBy, 3, "xxi" )
		.Func( _SC("RotateTo"), &CObject::RotateTo, 3, "xxi" )
		.Func( _SC("RotateBy"), &CObject::RotateBy, 3, "xxi" )
		.Func( _SC("RotateToEuler"), &CObject::RotateToEuler, 3, "xxi" )
		.Func( _SC("RotateByEuler"), &CObject::RotateByEuler, 3, "xxi" )
		.Func( _SC("SetAlpha"), &CObject::SetAlpha, 3, "xii" );

	RootTable(v).Bind( _SC("CObject"), c );
}
