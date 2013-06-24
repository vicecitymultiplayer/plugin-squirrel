#include "main.h"
#pragma once

class CVehicle
{
	public:
		CVehicle( int lnVehicleId, bool lIsOurs = true ) { this->isOurs = lIsOurs; this->nVehicleId = lnVehicleId; }

	public:
		void SetWorld( int world );
		void SetImmunity( int immunity );
		void SetPosition( Vector pos );
		void SetAngle( float angle );
		void SetSpawnPos( Vector pos );
		void SetSpawnAngle( float angle );
		void SetIdleRespawnTimer( unsigned int time );
		void SetHealth( float health );
		void SetColour1( int colour1 );
		void SetColour2( int colour2 );
		void SetLocked( bool isLocked );
		void SetDamage( unsigned int damage );
		void SetAlarm( bool isAlarmOn );
		void SetLights( bool lightsOn );
		void SetRotation( Quaternion rotation );
		void SetSpeed( Vector speed );
		void SetRelativeSpeed( Vector speed );
		void SetTurnSpeed( Vector speed );
		void SetRelativeTurnSpeed( Vector speed );

	public:
		int GetWorld();
		int GetModel();
		int GetImmunity();
		Vector GetPosition();
		Vector GetSpawnPos();
		float GetSpawnAngle();
		unsigned int GetIdleRespawnTimer();
		float GetHealth();
		int GetColour1();
		int GetColour2();
		bool GetLocked();
		unsigned int GetDamage();
		bool GetAlarm();
		bool GetLights();
		CPlayer * GetDriver();
		int GetID();
		int GetSyncSource();
		int GetSyncType();
		bool GetWrecked();
		Quaternion GetRotation();
		Vector GetSpeed();
		Vector GetRelativeSpeed();
		Vector GetTurnSpeed();
		Vector GetRelativeTurnSpeed();

	public:
		void Delete();
		void Respawn();
		void Kill();
		int GetPartStatus( int part );
		void SetPartStatus( int part, int status );
		int GetTyreStatus( int tyre );
		void SetTyreStatus( int part, int status );
		bool GetStreamedForPlayer( CPlayer * player );
		CPlayer * GetOccupant( int slot );
		int SetHandlingData( int rule, float value );
		double GetHandlingData( int rule );
		void ResetHandlingData( int rule );
		void ResetAllHandling();
		bool IsHandlingSet( int rule );

	public:
		bool isOurs;
		int nVehicleId;
};

void RegisterVehicle();