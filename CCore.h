#include "main.h"
#include "CPickup.h"
#include "CPlayer.h"
#include "CVehicle.h"
#include "ConsoleUtils.h"

// Include this header only once
#pragma once

// Define a structure for timer maps
struct Timer
{
	// The interval to run it at

	// The script function to use
};

// Define the core class
class CCore
{
	public:
		static CCore * GetInstance()
		{
			if( pCoreInstance == NULL )
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
		void LoadScript();
		void LoadVM();
		void Release();

		// Class maps
		CPlayer  * playerMap[MAX_PLAYERS];
		CPickup  * pickupMap[MAX_PICKUPS];
		CVehicle * vehicleMap[MAX_VEHICLES];

		// Can we reload the scripts?
		bool canReload;

	protected:
		// Sqrat's script
		Script * script;

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

		// Reference count
		static unsigned short refCount;
};