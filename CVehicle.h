#include "main.h"
#pragma once

class CVehicle
{
	public:
		void Init( int lnVehicleId, bool lIsOurs = true ) { this->isOurs = lIsOurs; this->nVehicleId = lnVehicleId; }

	public:
		void SetWorld( int world );
		void SetImmunity( int immunity );
		void SetPosition( Vector pos );
		void SetAngle( float angle );
		void SetSpawnPos( Vector pos );
		void SetSpawnAngle( Quaternion angle );
		void SetSpawnAngleEuler( Vector angle );
		void SetIdleRespawnTimer( unsigned int time );
		void SetHealth( float health );
		void SetColour1( int colour1 );
		void SetColour2( int colour2 );
		void SetLocked( bool isLocked );
		void SetDamage( unsigned int damage );
		void SetLightFlags( unsigned int flags );
		void SetAlarm(bool isAlarmOn);
		void SetSiren(bool isSirenOn);
		void SetLights( bool lightsOn );
		void SetRotation( Quaternion rotation );
		void SetEulerRotation( Vector angle );
		void SetSpeed( Vector speed );
		void SetRelativeSpeed( Vector speed );
		void SetTurnSpeed( Vector speed );
		void SetRelativeTurnSpeed( Vector speed );
		void SetRadio( int nRadioId );
		void SetRadioLocked( bool isRadioLocked );
		void SetGhost( bool isGhost );
		void SetSingleUse( bool isSingleUse );
		void SetTaxiLight(bool hasTaxiLight);

	public:
		int GetWorld();
		int GetModel();
		int GetImmunity();
		EntityVector GetPosition();
		EntityVector GetSpawnPos();
		EntityQuaternion GetSpawnAngle();
		EntityVector GetSpawnAngleEuler();
		unsigned int GetIdleRespawnTimer();
		float GetHealth();
		int GetColour1();
		int GetColour2();
		bool GetLocked();
		unsigned int GetDamage();
		unsigned int GetLightFlags();
		bool GetAlarm();
		bool GetSiren();
		bool GetLights();
		CPlayer * GetDriver();
		int GetID();
		int GetSyncSource();
		int GetSyncType();
		bool GetWrecked();
		EntityQuaternion GetRotation();
		EntityVector GetEulerRotation();
		EntityVector GetSpeed();
		EntityVector GetRelativeSpeed();
		EntityVector GetTurnSpeed();
		EntityVector GetRelativeTurnSpeed();
		int GetRadio();
		bool GetRadioLockStatus();
		bool GetGhost();
		Vector GetTurretRotation();
		bool GetSingleUse(void);
		bool GetTaxiLight(void);

	public:
		void Delete();
		void Fix();
		void Respawn();
		void Kill();
		void SetFlatTyres( bool isFlat );
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

		void AddVehicleSpeed( Vector speed );
		void AddVehicleRelSpeed( Vector speed );
		void AddVehicleTurnSpeed( Vector speed );
		void AddVehicleRelTurnSpeed( Vector speed );

	public:
		bool isOurs;
		int nVehicleId;
};

void RegisterVehicle();
