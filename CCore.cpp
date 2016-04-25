#include "CCore.h"
#include "Functions.h"
#include "ConsoleUtils.h"
#include "CStream.h"
#include <cassert>

// Static members
unsigned short   CCore::refCount;
CCore          * CCore::pCoreInstance;
extern CCore   * pCore;

// We have to make the VM a global variable, else the server will crash
// due to access violations in Sqrat when the VM pointer becomes NULL for
// no known reason.
HSQUIRRELVM v;

CCore::CCore()
{
	v           = NULL;
	script      = NULL;
	pLogFile    = NULL;

	// Create the entity arrays
	this->playerMap.fill(NULL);
	this->pickupMap.fill(NULL);
	this->objectMap.fill(NULL);
	this->vehicleMap.fill(NULL);
	this->checkpointMap.fill(NULL);

	// Construct all timer arrays
	unsigned int i;
	for( i = 0; i < this->maxTimers; i++ )
		this->pTimerArray[i] = NULL;

	canReload = false;
	pLogFile = fopen("server_log.txt", "a");
}

CCore::~CCore()
{
	if( script != NULL )
	{
		delete script;
		script = NULL;
	}

	// Release the VM if we can
	if( v != NULL )
	{
		sq_close( v );
		v = NULL;
	}

	// Throughout this entire ordeal, we don't actually kick players
	// or remove vehicles, objects, or pickups. Why not?
	//
	// The server is dying. We'd like to let it manage what to do with
	// entities, rather than manage it ourselves.
	unsigned int i;
	for (i = 0; i < MAX_PLAYERS; i++)
	{
		if (this->playerMap[i] != NULL)
		{
			delete this->playerMap[i];
			this->playerMap[i] = NULL;
		}
	}

	for (i = 0; i < MAX_OBJECTS; i++)
	{
		if (this->objectMap[i] != NULL)
		{
			delete this->objectMap[i];
			this->objectMap[i] = NULL;
		}
	}

	for (i = 0; i < MAX_PICKUPS; i++)
	{
		if (this->pickupMap[i] != NULL)
		{
			delete this->pickupMap[i];
			this->pickupMap[i] = NULL;
		}
	}

	for (i = 0; i < MAX_VEHICLES; i++)
	{
		if (this->vehicleMap[i] != NULL)
		{
			delete this->vehicleMap[i];
			this->vehicleMap[i] = NULL;
		}
	}

	for (i = 0; i < MAX_CHECKPOINTS; i++) {
		if (this->checkpointMap[i] != NULL) {
			delete this->checkpointMap[i];
			this->checkpointMap[i] = NULL;
		}
	}
}

void CCore::LoadVM()
{
	// Initialize the virtual machine
	v = sq_open( 2048 );
	sq_setprintfunc( v, printfunc, errorfunc );

	DefaultVM::Set( v );

	// Force Sqrat to enable error handling
	Sqrat::ErrorHandling::Enable(true);
	sq_pushroottable( v );

	// Register our entities so they're accessible by scripts
	this->RegisterEntities();

	// Signal outside plugins to register whatever the hell they want
	functions->SendPluginCommand(0x7D6E22D8, "");
}

// Look for entities such as vehicles and objects that were created by other plugins
void CCore::ScanForEntities()
{
	// Scan for vehicles
	unsigned int i;
	for( i = 0; i < MAX_VEHICLES; i++ )
	{
		if (functions->CheckEntityExists(vcmpEntityPoolVehicle, i))
			this->AllocateVehicle(i, false);
	}

	// Scan for pickups
	for( i = 0; i < MAX_PICKUPS; i++ )
	{
		if (functions->CheckEntityExists(vcmpEntityPoolPickup, i))
			this->AllocatePickup(i, false);
	}

	// Scan for objects
	for( i = 0; i < MAX_OBJECTS; i++ )
	{
		if (functions->CheckEntityExists(vcmpEntityPoolObject, i))
			this->AllocateObject(i, false);
	}

	// Scan for players
	for( i = 0; i < MAX_PLAYERS; i++ )
	{
		if (functions->IsPlayerConnected(i))
			this->AllocatePlayer(i);
	}

	for (i = 0; i < MAX_CHECKPOINTS; i++) {
		if (functions->CheckEntityExists(vcmpEntityPoolCheckPoint, i)) {
			this->AllocateCheckpoint(i, false);
		}
	}
}

// Process any timers
void CCore::AddTimer(CTimer * pTimer)
{
	for( int i = 0; i < this->maxTimers; i++ )
	{
		if( pTimerArray[i] == NULL )
		{
			pTimerArray[i] = pTimer;
			return;
		}
	}
}

void CCore::ProcessTimers(float elapsedTime)
{
	for( int i = 0; i < this->maxTimers; i++ )
	{
		if( pTimerArray[i] != NULL && !pTimerArray[i]->isPaused )
		{
			if( pTimerArray[i]->Pulse( elapsedTime * 1000.0f ) == true )
			{
				delete pTimerArray[i];
				pTimerArray[i] = NULL;
			}
		}
	}
}

void CCore::DropAllTimers()
{
	for( int i = 0; i < this->maxTimers; i++ )
	{
		if( pTimerArray[i] != NULL )
			pTimerArray[i]->committingSeppuku = true;
	}
}

void CCore::CleanWorld()
{
	unsigned int i;
	for( i = 0; i < MAX_VEHICLES; i++ )
	{
		if( vehicleMap[i] != NULL && vehicleMap[i]->isOurs )
		{
			vehicleMap[i]->Delete();
			vehicleMap[i] = NULL;
		}
	}

	for( i = 0; i < MAX_PICKUPS; i++ )
	{
		if( pickupMap[i] != NULL && pickupMap[i]->isOurs )
		{
			pickupMap[i]->Delete();
			pickupMap[i] = NULL;
		}
	}

	for( i = 0; i < MAX_OBJECTS; i++ )
	{
		if( objectMap[i] != NULL && objectMap[i]->isOurs )
		{
			objectMap[i]->Delete();
			objectMap[i] = NULL;
		}
	}

	for (i = 0; i < MAX_CHECKPOINTS; i++) {
		if (checkpointMap[i] != NULL && checkpointMap[i]->isOurs) {
			checkpointMap[i]->Delete();
			checkpointMap[i] = NULL;
		}
	}
}

// Register *everything*
void CCore::RegisterEntities()
{
	// Register all necessary core libraries
	if (SQ_FAILED(sqstd_register_bloblib(v)))
		OutputWarning("sqstd_bloblib failed to load.");

	if (SQ_FAILED(sqstd_register_iolib(v)))
		OutputWarning("sqstd_iolib failed to load.");

	if (SQ_FAILED(sqstd_register_mathlib(v)))
		OutputWarning("sqstd_mathlib failed to load.");

	if (SQ_FAILED(sqstd_register_stringlib(v)))
		OutputWarning("sqstd_stringlib failed to load.");

	if (SQ_FAILED(sqstd_register_systemlib(v)))
		OutputWarning("sqstd_systemlib failed to load.");

	RegisterStructures();
	RegisterGlobals();
	RegisterConstants();

	// Register the classes
	RegisterObject();
	RegisterPickup();
	RegisterPlayer();
	RegisterTimer();
	RegisterVehicle();
	RegisterCheckpoint();

	CStream::RegisterStream();

	// Set the default internal error handlers up
	sqstd_seterrorhandlers( v );
}

inline void ZeroBuffer( char * buffer, int size )
{
	for( int i = 0; i < size; i++ )
		buffer[i] = '\0';
}

void CCore::LoadScript()
{
	// Scan for entities that were already created
	this->ScanForEntities();

	// No reloading at this point
	this->canReload = false;
	bool scriptFound = false;
	FILE * file;

	file = fopen( "server.cfg", "r" );
	if( file == NULL )
		OutputError( "SqVCMP could not read server.cfg" );
	else
	{
		// Is this clean?
		int lineSize = 128;
		int elapsedLineSize = 0;
		char * lineBuffer = (char *)malloc( sizeof(char) * lineSize );

		// Did we do it?
		if( lineBuffer == NULL )
			OutputError( "SqVCMP could not allocate memory to read server.cfg" );
		else
		{
			ZeroBuffer(lineBuffer, lineSize);
			char ch = getc( file );

			while( ch != EOF )
			{
				if( ch == '\n' )
				{
					// End of the line. Parse it.
					if( this->ParseConfigLine( lineBuffer ) )
					{
						scriptFound = true;
						break;
					}

					ZeroBuffer(lineBuffer, lineSize);
					elapsedLineSize = 0;
				}
				else
				{
					lineBuffer[elapsedLineSize++] = ch;

					// If we've hit our limit on line size, stop reading the line.
					if( elapsedLineSize + 1 == lineSize )
					{
						// Parse it.
						if( this->ParseConfigLine( lineBuffer ) )
						{
							scriptFound = true;
							break;
						}

						// Go straight to the next one instead.
						while( ch != '\n' )
							ch = getc( file );

						ZeroBuffer(lineBuffer, lineSize);
						elapsedLineSize = 0;
					}
				}

				// Get the next character in the file.
				ch = getc( file );
			}
			
			if( !scriptFound && this->ParseConfigLine( lineBuffer ) )
				scriptFound = true;
		}

		// Clean up our shit
		free( lineBuffer );
	}
	
	// More cleaning
	fclose( file );

	// You are now free to move about the cabin.
	this->canReload = true;

	if( !scriptFound )
		OutputError( "No Squirrel gamemode was specified." );
}

bool CCore::ParseConfigLine( char * lineBuffer )
{
	char * gamemodeSearch = NULL;
	if( ( gamemodeSearch = strstr( lineBuffer, "sqgamemode " ) ) == NULL )
		return false;
	else if( strlen( gamemodeSearch ) < 1 )
		return false;
	else
	{
		// Ew.
		gamemodeSearch += sizeof("sqgamemode");
		this->script = new Script();

		try
		{
			this->script->CompileFile( gamemodeSearch );
			this->script->Run();
		}
		catch( Sqrat::Exception e )
		{
			char buf[145];
			sprintf( buf, "Could not load script '%s'", gamemodeSearch );

			OutputWarning( buf );
			OutputWarning( e.Message().c_str() );

			return false;
		}

		try
		{
			Function callback = RootTable(v).GetFunction(_SC("onScriptLoad"));
			if (!callback.IsNull())
				callback();

			callback.Release();
		}
		catch (Sqrat::Exception e)
		{
			OutputWarning("onScriptLoad failed to execute -- check the console for more details.");
		}

		return true;
	}
}

void CCore::printf(char* pszFormat, ...)
{
	char szInitBuffer[512];
	va_list va;

	va_start(va, pszFormat);
	{
		int nChars = vsnprintf(szInitBuffer, sizeof(szInitBuffer), pszFormat, va);
		if (nChars > sizeof(szInitBuffer) - 1)
		{
			char * szBuffer = new char[nChars + 1];
			vsnprintf(szBuffer, nChars, pszFormat, va);
			this->rawprint(szBuffer);

			delete[] szBuffer;
		}
		else
			this->rawprint(szInitBuffer);
	}
	va_end(va);
}

void CCore::rawprint(const char * pszOutput)
{
	fputs(pszOutput, stdout);
	if (this->pLogFile != NULL)
		fprintf(this->pLogFile, "%s", pszOutput);
}

// Release a core instance
void CCore::Release()
{
	// Decrease the number of references
	if( refCount > 0 )
		refCount--;
	
	// See if we should destroy our instance
	if( refCount <= 0 && pCoreInstance != NULL )
	{
		// Delete the core instance
		delete pCoreInstance;

		pCoreInstance = NULL;
		pCore = NULL;
	}
}

FILE * CCore::GetLogInstance()
{
	if (this->pLogFile == NULL)
		return NULL;

	return this->pLogFile;
}

CPlayer * CCore::AllocatePlayer(int gPlayerId)
{
	if (gPlayerId < 0 || gPlayerId > MAX_PLAYERS - 1)
		return NULL;
	else if (functions->IsPlayerConnected(gPlayerId) == 0)
		return NULL;
	else if (this->playerMap[gPlayerId] != NULL)
		return this->playerMap[gPlayerId];

	CPlayer * pPlayer = new CPlayer();
	pPlayer->nPlayerId = gPlayerId;

	this->playerMap[pPlayer->nPlayerId] = pPlayer;
	return pPlayer;
}

CObject * CCore::AllocateObject(int gObjectId, bool isOurs)
{
	if (gObjectId < 0 || gObjectId > MAX_OBJECTS - 1)
		return NULL;
	else if (!functions->CheckEntityExists(vcmpEntityPoolObject, gObjectId))
		return NULL;
	else if (this->objectMap[gObjectId] != NULL)
		return this->objectMap[gObjectId];

	CObject * pObject = new CObject();
	pObject->Init(gObjectId, isOurs);

	this->objectMap[pObject->nObjectId] = pObject;
	return pObject;
}

CPickup * CCore::AllocatePickup(int gPickupId, bool isOurs)
{
	if (gPickupId < 0 || gPickupId > MAX_PICKUPS - 1)
		return NULL;
	else if (!functions->CheckEntityExists(vcmpEntityPoolPickup, gPickupId))
		return NULL;
	else if (this->pickupMap[gPickupId] != NULL)
		return this->pickupMap[gPickupId];

	CPickup * pPickup = new CPickup();
	pPickup->Init(gPickupId, isOurs);

	this->pickupMap[pPickup->nPickupId] = pPickup;
	return pPickup;
}

CVehicle * CCore::AllocateVehicle(int gVehicleId, bool isOurs)
{
	if (gVehicleId <= 0 || gVehicleId > MAX_VEHICLES)
		return NULL;
	else if (!functions->CheckEntityExists(vcmpEntityPoolVehicle, gVehicleId))
		return NULL;
	else if (this->vehicleMap[gVehicleId] != NULL)
		return this->vehicleMap[gVehicleId];

	CVehicle * pVehicle = new CVehicle();
	pVehicle->Init(gVehicleId, isOurs);

	this->vehicleMap[pVehicle->nVehicleId] = pVehicle;
	return pVehicle;
}

CCheckpoint * CCore::AllocateCheckpoint(int gCheckpointId, bool isOurs)
{
	if (gCheckpointId < 0 || gCheckpointId >= MAX_CHECKPOINTS)
		return NULL;
	else if (!functions->CheckEntityExists(vcmpEntityPoolCheckPoint, gCheckpointId))
		return NULL;
	else if (this->checkpointMap[gCheckpointId] != NULL)
		return this->checkpointMap[gCheckpointId];

	CCheckpoint * pCheckpoint = new CCheckpoint();
	pCheckpoint->Init(gCheckpointId, isOurs);

	this->checkpointMap[pCheckpoint->nCheckpointId] = pCheckpoint;
	return pCheckpoint;
}

void CCore::DereferenceObject(int gObjectId)
{
	if (gObjectId < 0 || gObjectId > MAX_OBJECTS - 1)
		return;
	else if (this->objectMap[gObjectId] == NULL)
		return;
	else
	{
		CObject * pObject = this->objectMap[gObjectId];
		delete pObject;

		this->objectMap[gObjectId] = NULL;
	}
}

void CCore::DereferencePickup(int gPickupId)
{
	if (gPickupId < 0 || gPickupId > MAX_PICKUPS - 1)
		return;
	else if (this->pickupMap[gPickupId] == NULL)
		return;
	else
	{
		CPickup * pPickup = this->pickupMap[gPickupId];
		delete pPickup;

		this->pickupMap[gPickupId] = NULL;
	}
}

void CCore::DereferencePlayer(int gPlayerId)
{
	if (gPlayerId < 0 || gPlayerId > MAX_PLAYERS - 1)
		return;
	else if (this->playerMap[gPlayerId] == NULL)
		return;
	else
	{
		CPlayer * pPlayer = this->playerMap[gPlayerId];
		delete pPlayer;

		this->playerMap[gPlayerId] = NULL;
	}
}

void CCore::DereferenceVehicle(int gVehicleId)
{
	if (gVehicleId <= 0 || gVehicleId > MAX_VEHICLES)
		return;
	else if (this->vehicleMap[gVehicleId] == NULL)
		return;
	else
	{
		CVehicle * pVehicle = this->vehicleMap[gVehicleId];
		delete pVehicle;

		this->vehicleMap[gVehicleId] = NULL;
	}
}

void CCore::DereferenceCheckpoint(int gCheckpointId)
{
	if (gCheckpointId < 0 || gCheckpointId >= MAX_CHECKPOINTS)
		return;
	else if (this->checkpointMap[gCheckpointId] == NULL)
		return;
	else
	{
		CCheckpoint * pCheckpoint = this->checkpointMap[gCheckpointId];
		delete pCheckpoint;

		this->checkpointMap[gCheckpointId] = NULL;
	}
}

CObject * CCore::RetrieveObject(int gObjectId)
{
	if (gObjectId < 0 || gObjectId > MAX_OBJECTS - 1)
		return NULL;

	return this->objectMap[gObjectId];
}

CPickup * CCore::RetrievePickup(int gPickupId)
{
	if (gPickupId < 0 || gPickupId > MAX_PICKUPS - 1)
		return NULL;

	return this->pickupMap[gPickupId];
}

CPlayer * CCore::RetrievePlayer(int gPlayerId)
{
	if (gPlayerId < 0 || gPlayerId > MAX_PLAYERS - 1)
		return NULL;

	return this->playerMap[gPlayerId];
}

CVehicle * CCore::RetrieveVehicle(int gVehicleId)
{
	if (gVehicleId <= 0 || gVehicleId > MAX_VEHICLES)
		return NULL;

	return this->vehicleMap[gVehicleId];
}

CCheckpoint * CCore::RetrieveCheckpoint(int gCheckpointId)
{
	if (gCheckpointId < 0 || gCheckpointId >= MAX_CHECKPOINTS)
		return NULL;

	return this->checkpointMap[gCheckpointId];
}
