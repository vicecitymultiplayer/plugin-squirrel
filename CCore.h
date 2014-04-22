#include "main.h"
#include "CPickup.h"
#include "CPlayer.h"
#include "CTimer.h"
#include "CVehicle.h"
#include "CObject.h"
#include "CSprite.h"
#include "CTextdraw.h"
#include "ConsoleUtils.h"

#include <sqstdio.h>
#include <sqstdmath.h>
#include <sqstdstring.h>
#include <sqstdaux.h>
#include <sqstdblob.h>
#include <sqstdsystem.h>
#include <array>

// Include this header only once
#pragma once

// Define the core class
class CCore
{
	public:
		static CCore * GetInstance()
		{
			if( pCoreInstance == nullptr )
			{
				// Create a new instance
				pCoreInstance = new CCore();
			}

			// Increase the number of references
			refCount++;

			// Return the instance
			return pCoreInstance;
		}
		
		~CCore();
		void AddTimer( CTimer * pTimer );
		void CleanWorld();
		void DropAllTimers();
		void LoadVM();
		void ProcessTimers( float elapsedTime );
		void RegisterEntities();
		void Release();
		void ScanForEntities();

		void LoadScript();
		bool ParseConfigLine( char * lineBuffer );

		void printf( char* pszFormat, ... );
		void rawprint(const char * pszOutput);

	public:
		FILE     * GetLogInstance();
		Script   * GetScript() { return this->script; }

		bool IsReloadingAllowed() { return this->canReload; }
		void ChangeReloadPermission(bool bCanReload) { this->canReload = bCanReload; }

	public:
		CObject * AllocateObject(int gObjectId, bool isOurs = true);
		CPickup * AllocatePickup(int gPickupId, bool isOurs = true);
		CPlayer * AllocatePlayer(int gPlayerId);
		CVehicle * AllocateVehicle(int gVehicleId, bool isOurs = true);

		CObject * RetrieveObject(int gObjectId);
		CPickup * RetrievePickup(int gPickupId);
		CPlayer * RetrievePlayer(int gPlayerId);
		CVehicle * RetrieveVehicle(int gVehicleId);

		void DereferenceObject(int gObjectId);
		void DereferencePickup(int gPickupId);
		void DereferencePlayer(int gPlayerId);
		void DereferenceVehicle(int gVehicleId);

	private:
		// Constructor
		CCore();

		// Don't implement these, the prototypes are
		// just to keep copies of the singleton from
		// appearing.
		CCore(CCore const&);
		void operator=(CCore const&);

		// The singleton instance itself
		static CCore * pCoreInstance;

		// Entity maps
		std::array<CPlayer *, MAX_PLAYERS> playerMap;
		std::array<CPickup *, MAX_PICKUPS> pickupMap;
		std::array<CObject *, MAX_OBJECTS> objectMap;
		std::array<CVehicle *, MAX_VEHICLES + 1> vehicleMap;

		// Our list of timers.
		static const int maxTimers = 255;
		CTimer * pTimerArray[maxTimers];

		// Reference count
		static unsigned short refCount;

		// Sqrat's script
		Script * script;

		// Can we reload the scripts?
		bool canReload;

		// VC:MP log file
		FILE * pLogFile;
};
