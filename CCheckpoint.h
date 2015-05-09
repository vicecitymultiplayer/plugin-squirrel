#include "main.h"
#include "CPlayer.h"
#include "UtilStructs.h"
#pragma once

class CCheckpoint
{
	public:
		void Init( int lnCheckpointId, bool lbIsOurs = true ) { this->isOurs = lbIsOurs; this->nCheckpointId = lnCheckpointId; }

	public:
		void SetWorld( int world );
		void SetColor( ARGB color );
		void SetPos( Vector pos );
		void SetRadius( float radius );

	public:
		int GetWorld();
		ARGB GetColor();
		EntityVector GetPos();
		float GetRadius();
		int GetID();

	public:
		void Delete();
		bool StreamedToPlayer( CPlayer * player );
			
	public:
		int nCheckpointId;
		bool isOurs;
};

void RegisterCheckpoint();