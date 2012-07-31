#include "main.h"
#pragma once

class CObject
{
	public:
		void SetWorld( int world );
		void SetPos( Vector pos );
		void SetReportingShots( bool toReport );
		void SetReportingBumps( bool toReport );

	public:
		int GetModel();
		int GetAlpha();
		int GetWorld();
		Vector GetPos();
		Quaternion GetRotation();
		Vector GetRotationEuler();
		int GetID();
		bool GetReportingShots();
		bool GetReportingBumps();

	public:
		void Delete();
		void MoveTo( Vector pos, int time );
		void MoveBy( Vector offset, int time );
		void RotateTo( Quaternion rotation, int time );
		void RotateBy( Quaternion rotOffset, int time );
		void RotateToEuler( Vector rotation, int time );
		void RotateByEuler( Vector rotOffset, int time );
		void SetAlpha( int alpha, int fadeTime );
		bool StreamedToPlayer( CPlayer * player );
			
	public:
		int nObjectId;
};

void RegisterObject();