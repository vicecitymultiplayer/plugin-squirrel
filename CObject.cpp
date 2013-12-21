#include "CObject.h"
#include "CPlayer.h"
#include "main.h"

void CObject::SetWorld( const int world ) { functions->SetObjectWorld( this->nObjectId, world ); }
void CObject::SetPos( const Vector pos ) { functions->SetObjectPos( this->nObjectId, pos.x, pos.y, pos.z ); }

int CObject::GetModel() const { return functions->GetObjectModel( this->nObjectId ); }
int CObject::GetAlpha() const { return functions->GetObjectAlpha(this->nObjectId); }
int CObject::GetWorld() const { return functions->GetObjectWorld(this->nObjectId); }

Vector CObject::GetPos() const
{
	float x, y, z;
	functions->GetObjectPos( this->nObjectId, &x, &y, &z );

	Vector p(x, y, z);
	return p;
}

Quaternion CObject::GetRotation() const
{
	float w, x, y, z;
	functions->GetObjectRot( this->nObjectId, &x, &y, &z, &w );

	Quaternion q( w, x, y, z );
	return q;
}

Vector CObject::GetRotationEuler() const
{
	float x, y, z;
	functions->GetObjectRotEuler( this->nObjectId, &x, &y, &z );

	Vector e( x, y, z );
	return e;
}

void CObject::Delete()
{
	// PS! this instance will be deleted due to a callback!!!
	functions->DeleteObject( this->nObjectId );
}

void CObject::MoveTo( Vector pos, int time ) const
{
	functions->MoveObjectTo( this->nObjectId, pos.x, pos.y, pos.z, time );
}

void CObject::MoveBy( Vector offset, int time ) const
{
	functions->MoveObjectBy( this->nObjectId, offset.x, offset.y, offset.z, time );
}

void CObject::RotateTo( Quaternion rotation, int time ) const
{
	functions->RotObjectTo( this->nObjectId, rotation.x, rotation.y, rotation.z, rotation.w, time );
}

void CObject::RotateBy( Quaternion rotOffset, int time ) const
{
	functions->RotObjectBy( this->nObjectId, rotOffset.x, rotOffset.y, rotOffset.z, rotOffset.w, time );
}

void CObject::RotateToEuler( Vector rotation, int time ) const
{
	functions->RotObjectToEuler( this->nObjectId, rotation.x, rotation.y, rotation.z, time );
}

void CObject::RotateByEuler( Vector rotOffset, int time ) const
{
	functions->RotObjectByEuler( this->nObjectId, rotOffset.x, rotOffset.y, rotOffset.z, time );
}

void CObject::SetAlpha( int alpha, int fadeTime ) const { functions->SetObjectAlpha( this->nObjectId, alpha, fadeTime ); }
int CObject::GetID() const { return this->nObjectId; }
bool CObject::StreamedToPlayer( CPlayer * player ) const
{
	if( player != NULL )
		return ( functions->IsObjectStreamedForPlayer( this->nObjectId, player->nPlayerId ) == 1 ? true : false );

	return false;
}

void CObject::SetReportingShots( const bool toReport ) { functions->SetObjectShotReport( this->nObjectId, toReport ); }
void CObject::SetReportingBumps( const bool toReport ) { functions->SetObjectBumpReport( this->nObjectId, toReport ); }
bool CObject::GetReportingShots() const { return ( functions->IsObjectShotReport( this->nObjectId ) == 1 ? true : false ); }
bool CObject::GetReportingBumps() const { return ( functions->IsObjectBumpReport( this->nObjectId ) == 1 ? true : false ); }

void RegisterObject()
{
	Class<CObject> c(v);

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
		.Func( _SC("Delete"), &CObject::Delete )
		.Func( _SC("MoveTo"), &CObject::MoveTo )
		.Func( _SC("MoveBy"), &CObject::MoveBy )
		.Func( _SC("RotateTo"), &CObject::RotateTo )
		.Func( _SC("RotateBy"), &CObject::RotateBy )
		.Func( _SC("RotateToEuler"), &CObject::RotateToEuler )
		.Func( _SC("RotateByEuler"), &CObject::RotateByEuler )
		.Func( _SC("SetAlpha"), &CObject::SetAlpha );

	RootTable(v).Bind( _SC("CObject"), c );
}