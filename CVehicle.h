#include "main.h"
#pragma once

class CVehicle
{
	public:
		void Init( int lnVehicleId, bool lIsOurs = true ) { this->isOurs = lIsOurs; this->nVehicleId = lnVehicleId; }

	public:
		void SetWorld( const int world );
		void SetImmunity( const int immunity );
		void SetPosition( const Vector pos );
		void SetAngle( const float angle );
		void SetSpawnPos( const Vector pos );
		void SetSpawnAngle( const float angle );
		void SetIdleRespawnTimer( const unsigned int time );
		void SetHealth( const float health );
		void SetColour1( const int colour1 );
		void SetColour2( const int colour2 );
		void SetLocked( const bool isLocked );
		void SetDamage( const unsigned int damage );
		void SetAlarm( const bool isAlarmOn );
		void SetLights( const bool lightsOn );
		void SetRotation( const Quaternion rotation );
		void SetEulerRotation( const Vector angle );
		void SetSpeed( const Vector speed );
		void SetRelativeSpeed( const Vector speed );
		void SetTurnSpeed( const Vector speed );
		void SetRelativeTurnSpeed( const Vector speed );
		void SetRadio( const int nRadioId );
		void SetRadioLocked( const bool isRadioLocked );

	public:
		int GetWorld() const;
		int GetModel() const;
		int GetImmunity() const;
		Vector GetPosition() const;
		Vector GetSpawnPos() const;
		float GetSpawnAngle() const;
		unsigned int GetIdleRespawnTimer() const;
		float GetHealth() const;
		int GetColour1() const;
		int GetColour2() const;
		bool GetLocked() const;
		unsigned int GetDamage() const;
		bool GetAlarm() const;
		bool GetLights() const;
		CPlayer * GetDriver() const;
		int GetID() const;
		int GetSyncSource() const;
		int GetSyncType() const;
		bool GetWrecked() const;
		Quaternion GetRotation() const;
		Vector GetEulerRotation() const;
		Vector GetSpeed() const;
		Vector GetRelativeSpeed() const;
		Vector GetTurnSpeed() const;
		Vector GetRelativeTurnSpeed() const;
		int GetRadio() const;
		bool GetRadioLockStatus() const;

	public:
		void Delete();
		void Respawn() const;
		void Kill() const;
		void SetFlatTyres( bool isFlat ) const;
		int GetPartStatus( int part ) const;
		void SetPartStatus( int part, int status ) const;
		int GetTyreStatus( int tyre ) const;
		void SetTyreStatus( int part, int status ) const;
		bool GetStreamedForPlayer( CPlayer * player ) const;
		CPlayer * GetOccupant( int slot ) const;
		int SetHandlingData( int rule, float value ) const;
		double GetHandlingData( int rule ) const;
		void ResetHandlingData( int rule ) const;
		void ResetAllHandling() const;
		bool IsHandlingSet( int rule ) const;

		void AddVehicleSpeed( Vector speed ) const;
		void AddVehicleTurnSpeed( Vector speed ) const;
		void AddVehicleRelTurnSpeed( Vector speed ) const;

	public:
		bool isOurs;
		int nVehicleId;
};

void RegisterVehicle();