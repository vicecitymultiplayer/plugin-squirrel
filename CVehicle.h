#include "main.h"
#pragma once

class CVehicle
{
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
		float GetHandlingData( int rule );
		void ResetHandlingData( int rule );
		void ResetAllHandling();
		bool IsHandlingSet( int rule );

	public:
		int nVehicleId;
};

void RegisterVehicle();