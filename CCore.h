#include "main.h"
#include "CPickup.h"
#include "CPlayer.h"
#include "CTimer.h"
#include "CVehicle.h"
#include "CObject.h"
#include "ConsoleUtils.h"

#include <sqstdio.h>
#include <sqstdmath.h>
#include <sqstdstring.h>
#include <sqstdaux.h>
#include <sqstdblob.h>
#include <sqstdsystem.h>

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

	public:
		FILE     * GetLogInstance();
		Script   * GetScript() { return this->script; }

		bool IsReloadingAllowed() { return this->canReload; }
		void ChangeReloadPermission(bool bCanReload) { this->canReload = bCanReload; }

		// Entity maps
		std::vector<CPlayer *> playerMap;
		std::vector<CPickup *> pickupMap;
		std::vector<CObject *> objectMap;
		std::vector<CVehicle *> vehicleMap;

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
