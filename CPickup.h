#include "main.h"
#include "CPlayer.h"
#pragma once

class CPickup
{
	public:
		void Init( int lnPickupId, bool lIsOurs = true ) { this->isOurs = lIsOurs; this->nPickupId = lnPickupId; }

	public:
		void SetWorld( int world );
		void SetAlpha( int alpha );
		void SetAuto( bool automatic );
		void SetAutoTimer( int timer );
		void SetPos( Vector pos );
		void SetSingleUse(bool bSingleUse);

	public:
		int GetWorld();
		int GetAlpha();
		bool GetAuto();
		int GetAutoTimer();
		EntityVector GetPos();
		int GetModel();
		int GetQuantity();
		int GetID();
		bool GetSingleUse();

	public:
		void Delete();
		void Respawn();
		bool StreamedToPlayer( CPlayer * player );
			
	public:
		int nPickupId;
		bool isOurs;
};

void RegisterPickup();