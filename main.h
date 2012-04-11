#ifdef WIN32
	#define WIN32_LEANANDMEAN
	#include <Windows.h>

	#define EXPORT __declspec(dllexport)
#else
	#define EXPORT
#endif

#include "VCMP.h"

#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <wchar.h>

#include <iostream>
#include <map>

// Squirrel
extern "C"
{
	#include "squirrel/squirrel.h"
	#include "squirrel/sqstdaux.h"
	#include "squirrel/sqstdio.h"
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
class CVehicle;

// Structure definitions
#ifndef types
	class Vector
	{
		public:
			Vector( float x, float y, float z ) { this->x = x; this->y = y; this->z = z; }
			Vector() { }
			float x;
			float y;
			float z;
	};

	class Quaternion
	{
		public:
			Quaternion( float w, float x, float y, float z ) { this->w = w; this->x = x; this->y = y; this->z = z; }
			Quaternion() { }
			float w;
			float x;
			float y;
			float z;
	};

	class RGBa
	{
		public:
			RGBa( int r, int g, int b, int a ) { this->r = r; this->g = g; this->b = b; this->a = a; }
			RGBa() { }

			int r;
			int g;
			int b;
			int a;
	};

	class cRGB
	{
		public:
			cRGB( int r, int g, int b ) { this->r = r; this->g = g; this->b = b; }
			cRGB() { }

			int r;
			int g;
			int b;
	};
	
	class ARGB
	{
		public:
			ARGB( int a, int r, int g, int b ) { this->r = r; this->g = g; this->b = b; this->a = a; }
			ARGB() { }
			
			int a;
			int r;
			int g;
			int b;
	};

	class Bounds
	{
		public:
			Bounds( float maxX, float minX, float maxY, float minY )
			{
				this->maxX = maxX;
				this->minX = minX;
				this->maxY = maxY;
				this->minY = minY;
			}

			Bounds() { }

			float maxX;
			float minX;
			float maxY;
			float minY;
	};

	class WastedSettings
	{
		public:
			WastedSettings
			(
				int deathTime,
				int fadeTime,
				float fadeInSpeed,
				float fadeOutSpeed,
				cRGB fadeColour,
				int corpseFadeDelay,
				int corpseFadeTime
			)
			{
				this->deathTime       = deathTime;
				this->fadeTime        = fadeTime;
				this->fadeInSpeed     = fadeInSpeed;
				this->fadeOutSpeed    = fadeOutSpeed;
				this->fadeColour      = fadeColour;
				this->corpseFadeDelay = corpseFadeDelay;
				this->corpseFadeTime  = corpseFadeTime;
			}

			WastedSettings() { }

			int deathTime;
			int fadeTime;
			float fadeInSpeed;
			float fadeOutSpeed;
			cRGB fadeColour;
			int corpseFadeDelay;
			int corpseFadeTime;
	};

	#define types
#endif

// Definitions
#define _SQ( x ) SQInteger x( HSQUIRRELVM v )

extern PluginFuncs*              functions;
extern HSQUIRRELVM               v;

// Player map
extern std::map<int, CPlayer> playerMap;