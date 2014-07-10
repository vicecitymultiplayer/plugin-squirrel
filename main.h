#ifdef WIN32
	#define WIN32_LEANANDMEAN
	#include <Windows.h>

	#define EXPORT __declspec(dllexport)
#else
	#define EXPORT
	typedef unsigned int DWORD;
#endif

#include "Constants.h"
#include "VCMP.h"
#include "UtilStructs.h"

#include <math.h>
#include <stdarg.h>
#include <stdio.h>
//#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
//#include <crtdbg.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#include <iostream>
#include <map>

// Squirrel
extern "C"
{
	#include "squirrel/squirrel.h"
	#include "squirrel/sqstdaux.h"
	#include "squirrel/sqstdblob.h"
	#include "squirrel/sqstdio.h"
	#include "squirrel/sqstdmath.h"
	#include "squirrel/sqstdstring.h"
}

// A definition needed for Squirrel's print function
#ifdef SQUNICODE 
	#define scvprintf vwprintf 
#else 
	#define scvprintf vprintf 
#endif

// Sqrat
#include "sqrat/sqrat.h"

// Use the Sqrat namespace.
using namespace Sqrat;

// Forward our classes
class CObject;
class CPickup;
class CPlayer;
class CTimer;
class CVehicle;

// Definitions
#define _SQ( x ) SQInteger x( HSQUIRRELVM v )

extern PluginFuncs*    functions;
extern HSQUIRRELVM     v;

// Functions
void printfunc(HSQUIRRELVM v, const SQChar *s, ...);
void errorfunc(HSQUIRRELVM v, const SQChar *s, ...);
void RegisterStructures();
