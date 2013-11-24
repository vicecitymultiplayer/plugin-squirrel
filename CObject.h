#include "main.h"
#pragma once

class CObject
{
	public:
		void Init( int lnObjectId, bool lIsOurs = true ) { this->isOurs = lIsOurs; this->nObjectId = lnObjectId; }

	public:
		void SetWorld( const int world );
		void SetPos( const Vector pos );
		void SetReportingShots( const bool toReport );
		void SetReportingBumps( const bool toReport );

	public:
		int GetModel() const;
		int GetAlpha() const;
		int GetWorld() const;
		Vector GetPos() const;
		Quaternion GetRotation() const;
		Vector GetRotationEuler() const;
		int GetID() const;
		bool GetReportingShots() const;
		bool GetReportingBumps() const;

	public:
		void Delete();
		void MoveTo( Vector pos, int time ) const;
		void MoveBy( Vector offset, int time ) const;
		void RotateTo( Quaternion rotation, int time ) const;
		void RotateBy( Quaternion rotOffset, int time ) const;
		void RotateToEuler( Vector rotation, int time ) const;
		void RotateByEuler( Vector rotOffset, int time ) const;
		void SetAlpha( int alpha, int fadeTime ) const;
		bool StreamedToPlayer( CPlayer * player ) const;
			
	public:
		int nObjectId;
		bool isOurs;
};

void RegisterObject();