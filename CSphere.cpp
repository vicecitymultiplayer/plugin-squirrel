#include "CCore.h"
#include "CSphere.h"
#include "main.h"

// Core instance
extern CCore * pCore;

void CSphere::SetWorld( int world ) { functions->SetSphereWorld( this->nSphereId, world ); }
void CSphere::SetColor( cRGB color ) {
	functions->SetSphereColor( this->nSphereId, color.r, color.g, color.b );
}

void CSphere::SetRadius( float radius ) { functions->SetSphereRadius( this->nSphereId, radius ); }
void CSphere::SetPos( Vector pos ) { functions->SetSpherePos( this->nSphereId, pos.x, pos.y, pos.z ); }

int CSphere::GetWorld() { return functions->GetSphereWorld( this->nSphereId ); }
cRGB CSphere::GetColor() {
	unsigned int r, g, b, a;
	functions->GetSphereColor(this->nSphereId, &r, &g, &b);

	return cRGB(r, g, b);
}

float CSphere::GetRadius() { return (functions->GetSphereRadius(this->nSphereId)); }
EntityVector CSphere::GetPos()
{
	float x, y, z;
	functions->GetSpherePos( this->nSphereId, &x, &y, &z );

	return EntityVector( this->nSphereId, ENTITY_SPHERE, -1, x, y, z );
}

void CSphere::Delete()
{
	//PS! this instance will be deleted due to a callback!!!
	functions->DeleteSphere( this->nSphereId );
}

int CSphere::GetID() { return this->nSphereId; }
bool CSphere::StreamedToPlayer(CPlayer * player) { return (functions->IsSphereStreamedForPlayer(this->nSphereId, player->nPlayerId) == 1 ? true : false); }

void RegisterSphere()
{
	Class<CSphere> c(v, "CSphere_INTERNAL");

	// Read-write properties
	c
		.Prop( _SC("World"), &CSphere::GetWorld, &CSphere::SetWorld )
		.Prop( _SC("Color"), &CSphere::GetColor, &CSphere::SetColor )
		.Prop( _SC("Radius"), &CSphere::GetRadius, &CSphere::SetRadius )
		.Prop( _SC("Pos"), &CSphere::GetPos, &CSphere::SetPos );

	// Read-only properties
	c
		.Prop( _SC("ID"), &CSphere::GetID )
		.Prop(_SC("Owner"), &CCheckpoint::GetOwner);

	// Functions
	c
		.Func( _SC("Remove"), &CSphere::Delete )
		.Func( _SC("StreamedToPlayer"), &CSphere::StreamedToPlayer );

	RootTable(v).Bind( _SC("CSphere"), c );
}
