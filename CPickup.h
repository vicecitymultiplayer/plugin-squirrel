#include "main.h"
#include "CPlayer.h"
#pragma once

class CPickup
{
	public:
		void Init( int lnPickupId, bool lIsOurs = true ) { this->isOurs = lIsOurs; this->nPickupId = lnPickupId; }

	public:
		void SetWorld( const int world );
		void SetAlpha( const int alpha );
		void SetAuto( const bool automatic );
		void SetAutoTimer( const int timer );
		void SetPos( const Vector pos );

	public:
		int GetWorld() const;
		int GetAlpha() const;
		bool GetAuto() const;
		int GetAutoTimer() const;
		Vector GetPos() const;
		int GetModel() const;
		int GetQuantity() const;
		int GetID() const;

	public:
		void Delete();
		bool StreamedToPlayer( CPlayer * player ) const;
			
	public:
		int nPickupId;
		bool isOurs;
};

void RegisterPickup();