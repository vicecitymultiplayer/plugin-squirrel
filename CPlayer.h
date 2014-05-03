#include "main.h"
#pragma once

class CPlayer
{
	private:
		Vector * pos;
	
	public:
		CPlayer() { pos = new Vector(); }
		~CPlayer() { delete pos; }

	public:
		void SetPosition( Vector pos );
		void SetHealth( float health );
		void SetArmour( float armour );
		void SetAdmin( bool toSetAdmin );
		void SetWorld( int world );
		void SetSecWorld( int world );
		void SetTeam( int team );
		void SetSkin( int skin );
		void SetColour( cRGB colour );
		void SetMoney( int money );
		void SetScore( int score );
		void SetImmunity( unsigned int immunity );
		void SetHeading( float heading );
		void SetVehicle( CVehicle * vehiclePointer );
		void SetFrozen( bool toFreeze );
		void SetDrivebyEnabled( bool canDb );
		void SetWhiteScanlines( bool hasWhiteScan );
		void SetGreenScanlines( bool hasGreenScan );
		void SetWidescreen( bool hasWidescreen );
		void SetOnRadar( bool showOnRadar );
		void SetCanAttack( bool canAttack );
		void SetWeaponSlot( int slot );
		void ShowMarkers( bool setMarkers );
		void SetSpectateTarget( CPlayer * pPlayer );
		void SetMarkerVisible( bool isMarkerVisible );
		void SetCanUseColors( bool canUseColors );
		void SetDrunkStatus( bool isDrunk );

	public:
		EntityVector GetPosition();
		int GetClass();
		bool GetAdmin();
		SQChar * GetIP();
		bool GetSpawned();
		int GetWorld();
		int GetSecWorld();
		int GetUniqueWorld();
		int GetState();
		SQChar * GetName();
		int GetTeam();
		int GetSkin();
		EntityRGB GetColour();
		int GetMoney();
		int GetScore();
		int GetPing();
		float GetHealth();
		float GetArmour();
		unsigned int GetImmunity();
		float GetHeading();
		CVehicle * GetVehicle();
		bool GetFrozen();
		bool GetDrivebyEnabled();
		bool GetWhiteScanlines();
		bool GetGreenScanlines();
		bool GetWidescreen();
		bool GetOnRadar();
		bool GetCanAttack();
		int GetWeaponSlot();
		int GetWeapon();
		int GetWeaponAmmo();
		int GetAlpha();
		int GetID();
		bool Typing();
		bool ShowingMarkers();
		bool GetCameraLocked();
		int GetKey();
		bool GetAwayStatus();
		CPlayer * GetSpectateTarget();
		bool GetCanUseColors();
		bool GetMarkerVisible();
		bool GetDrunkStatus();
		double GetFPS();
		SQChar * GetUniqueID();

	public:
		void Kick();
		void Ban();
		void Spawn();
		void GiveMoney( int money );
		void AddSpeed( Vector speed );
		void SetInterior( int interior );
		void Eject();
		void SetWantedLevel( int wantedLevel );
		void LaySpike();
		void SetCameraPos( Vector pos, Vector look );
		void SetCameraFollow( bool toFollow );
		void Disarm();
		void CompatAnimation( int anim );
		void Animation( int group, int anim );
		CVehicle * StandingOnVehicle();
		CObject * StandingOnObject();
		void GiveWeapon( int weapon, int ammo );
		void SetWeapon( int weapon, int ammo );
		void RemoveWeapon( int weapon );
		int GetWeaponAtSlot( int slot );
		int GetAmmoAtSlot( int slot );
		void SetAlpha( int alpha, int fadeTime );
		bool StreamedToPlayer( CPlayer * player );
		void Select();
		void RestoreCamera();
		void RemoveMarker();
		void SetMarker( int nDummy );
		void SetDrunkLevel( int visuals, int handling );

	public:
		int nPlayerId;
};

void RegisterPlayer();