#include "CCore.h"
#include "CCheckpoint.h"
#include "main.h"

// Core instance
extern CCore * pCore;

void CCheckpoint::SetWorld( int world ) { functions->SetCheckpointWorld( this->nCheckpointId, world ); }
void CCheckpoint::SetColor( ARGB color ) {
	functions->SetCheckpointColor( this->nCheckpointId, color.r, color.g, color.b, color.a );
}

void CCheckpoint::SetRadius( float radius ) { functions->SetCheckpointRadius( this->nCheckpointId, radius ); }
void CCheckpoint::SetPos( Vector pos ) { functions->SetCheckpointPos( this->nCheckpointId, pos.x, pos.y, pos.z ); }

int CCheckpoint::GetWorld() { return functions->GetCheckpointWorld( this->nCheckpointId ); }
ARGB CCheckpoint::GetColor() {
	unsigned int r, g, b, a;
	functions->GetCheckpointColor(this->nCheckpointId, &r, &g, &b, &a);

	return ARGB(a, r, g, b);
}

float CCheckpoint::GetRadius() { return (functions->GetCheckpointRadius(this->nCheckpointId)); }
EntityVector CCheckpoint::GetPos()
{
	float x, y, z;
	functions->GetCheckpointPos( this->nCheckpointId, &x, &y, &z );

	return EntityVector( this->nCheckpointId, ENTITY_CHECKPOINT, -1, x, y, z );
}

void CCheckpoint::Delete()
{
	//PS! this instance will be deleted due to a callback!!!
	functions->DeleteCheckpoint( this->nCheckpointId );
}

int CCheckpoint::GetID() { return this->nCheckpointId; }
bool CCheckpoint::StreamedToPlayer(CPlayer * player) { return (functions->IsCheckpointStreamedForPlayer(this->nCheckpointId, player->nPlayerId) == 1 ? true : false); }
CPlayer* CCheckpoint::GetOwner(void) { return pCore->RetrievePlayer(this->nOwnerId); }

void RegisterCheckpoint()
{
	Class<CCheckpoint> c(v, "CCheckpoint_INTERNAL");

	// Read-write properties
	c
		.Prop( _SC("World"), &CCheckpoint::GetWorld, &CCheckpoint::SetWorld )
		.Prop( _SC("Color"), &CCheckpoint::GetColor, &CCheckpoint::SetColor )
		.Prop( _SC("Radius"), &CCheckpoint::GetRadius, &CCheckpoint::SetRadius )
		.Prop( _SC("Pos"), &CCheckpoint::GetPos, &CCheckpoint::SetPos );

	// Read-only properties
	c
		.Prop( _SC("ID"), &CCheckpoint::GetID )
		.Prop( _SC("Owner"), &CCheckpoint::GetOwner );

	// Functions
	c
		.Func( _SC("Remove"), &CCheckpoint::Delete )
		.Func( _SC("StreamedToPlayer"), &CCheckpoint::StreamedToPlayer );

	RootTable(v).Bind( _SC("CCheckpoint"), c );
}
