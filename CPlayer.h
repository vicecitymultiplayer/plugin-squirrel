#include "main.h"
#pragma once

class CPlayer
{
	public:
		void SetPosition( const Vector pos );
		void SetHealth( const float health );
		void SetArmour( const float armour );
		void SetAdmin( const bool toSetAdmin );
		void SetWorld( const int world );
		void SetSecWorld( const int world );
		void SetTeam( const int team );
		void SetSkin( const int skin );
		void SetColour( const cRGB colour );
		void SetMoney( const int money );
		void SetScore( const int score );
		void SetImmunity( const unsigned int immunity );
		void SetHeading( const float heading );
		void SetVehicle( CVehicle * vehiclePointer );
		void SetFrozen( const bool toFreeze );
		void SetDrivebyEnabled( const bool canDb );
		void SetWhiteScanlines( const bool hasWhiteScan );
		void SetGreenScanlines( const bool hasGreenScan );
		void SetWidescreen( const bool hasWidescreen );
		void SetOnRadar( const bool showOnRadar );
		void SetCanAttack( const bool canAttack );
		void SetWeaponSlot( const int slot );
		void ShowMarkers( const bool setMarkers );
		void SetSpectateTarget( CPlayer * pPlayer );
		void SetMarkerVisible( const bool isMarkerVisible );
		void SetCanUseColors( const bool canUseColors );
		void SetDrunkStatus( const bool isDrunk );

	public:
		Vector GetPosition() const;
		int GetClass() const;
		bool GetAdmin() const;
		SQChar * GetIP() const;
		bool GetSpawned() const;
		int GetWorld() const;
		int GetSecWorld() const;
		int GetUniqueWorld() const;
		int GetState() const;
		SQChar * GetName() const;
		int GetTeam() const;
		int GetSkin() const;
		cRGB GetColour() const;
		int GetMoney() const;
		int GetScore() const;
		int GetPing() const;
		float GetHealth() const;
		float GetArmour() const;
		unsigned int GetImmunity() const;
		float GetHeading() const;
		CVehicle * GetVehicle() const;
		bool GetFrozen() const;
		bool GetDrivebyEnabled() const;
		bool GetWhiteScanlines() const;
		bool GetGreenScanlines() const;
		bool GetWidescreen() const;
		bool GetOnRadar() const;
		bool GetCanAttack() const;
		int GetWeaponSlot() const;
		int GetWeapon() const;
		int GetWeaponAmmo() const;
		int GetAlpha() const;
		int GetID() const;
		bool Typing() const;
		bool ShowingMarkers() const;
		bool GetCameraLocked() const;
		int GetKey() const;
		bool GetAwayStatus() const;
		CPlayer * GetSpectateTarget() const;
		bool GetCanUseColors() const;
		bool GetMarkerVisible() const;
		bool GetDrunkStatus() const;

	public:
		void Kick();
		void Ban();
		void Spawn() const;
		void GiveMoney( int money ) const;
		void AddSpeed( Vector speed ) const;
		void SetInterior( int interior ) const;
		void Eject() const;
		void SetWantedLevel( int wantedLevel ) const;
		void LaySpike() const;
		void SetCameraPos( Vector pos, Vector look ) const;
		void SetCameraFollow( bool toFollow ) const;
		void Disarm() const;
		void CompatAnimation( int anim ) const;
		void Animation( int group, int anim ) const;
		CVehicle * StandingOnVehicle() const;
		CObject * StandingOnObject() const;
		void GiveWeapon( int weapon, int ammo ) const;
		void SetWeapon( int weapon, int ammo ) const;
		void RemoveWeapon( int weapon ) const;
		int GetWeaponAtSlot( int slot ) const;
		int GetAmmoAtSlot( int slot ) const;
		void SetAlpha( int alpha, int fadeTime ) const;
		bool StreamedToPlayer( CPlayer * player ) const;
		void Select() const;
		void RestoreCamera() const;
		void RemoveMarker() const;
		void SetMarker( int nDummy ) const;
		void SetDrunkLevel( int visuals, int handling ) const;

	public:
		int nPlayerId;
};

void RegisterPlayer();