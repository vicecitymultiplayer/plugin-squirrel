#include "main.h"
#include "CPlayer.h"
#include "UtilStructs.h"
#pragma once

class CSphere
{
	public:
		void Init( int lnSphereId, bool lbIsOurs = true ) { this->isOurs = lbIsOurs; this->nSphereId = lnSphereId; }

	public:
		void SetWorld( int world );
		void SetColor( cRGB color );
		void SetPos( Vector pos );
		void SetRadius( float radius );

	public:
		int GetWorld();
		cRGB GetColor();
		EntityVector GetPos();
		float GetRadius();
		int GetID();
		CPlayer* GetOwner();

	public:
		void Delete();
		bool StreamedToPlayer( CPlayer * player );
			
	public:
		int nSphereId;
		int nOwnerId;
		bool isOurs;
};

void RegisterSphere();