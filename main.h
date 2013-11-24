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

#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
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

			float Length(void) const { return sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2)); }
			float Distance(const Vector &v) const { return sqrt(pow(this->x - v.x, 2) + pow(this->y - v.y, 2) + pow(this->z - v.z, 2)); }
			float Dot(const Vector &v) { return (this->x * v.x) + (this->y * v.y) + (this->z * v.z); }
			Vector& Normalize(void)
			{
				float invLen = 1.0f / this->Length();
				this->x *= invLen;
				this->y *= invLen;
				this->z *= invLen;
				return *this;
			}

			bool operator ==(const Vector &v) const { return this->x == v.x && this->y == v.y && this->z == v.z; }
			Vector operator -(void) const { return Vector(-x, -y, -z); }
			Vector operator +(const Vector &v) const { return Vector(this->x + v.x, this->y + v.y, this->z + v.z); }
			Vector operator -(const Vector &v) const { return Vector(this->x - v.x, this->y - v.y, this->z - v.z); }
			Vector operator *(const float f) const { return Vector(this->x * f, this->y * f, this->z * f); }
			Vector operator /(const float f) const { return Vector(this->x / f, this->y / f, this->z / f); }
			Vector& operator =(const Vector &v) { this->x = v.x; this->y = v.y; this->z = v.z; return *this; }
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

			bool operator ==(const Quaternion &q) const { return this->w == q.w && this->x == q.x && this->y == q.y && this->z == q.z; }
			Quaternion operator -(void) const { return Quaternion(-w, -x, -y, -z); }
			Quaternion operator +(const Quaternion &q) const { return Quaternion(this->w + q.w, this->x + q.x, this->y + q.y, this->z + q.z); }
			Quaternion operator -(const Quaternion &q) const { return Quaternion(this->w - q.w, this->x - q.x, this->y - q.y, this->z - q.z); }
			Quaternion operator *(const float f) const { return Quaternion(this->w * f, this->x * f, this->y * f, this->z * f); }
			Quaternion operator /(const float f) const { return Quaternion(this->w / f, this->x / f, this->y / f, this->z / f); }
			Quaternion& operator =(const Quaternion &q) { this->w = q.w; this->x = q.x; this->y = q.y; this->z = q.z; return *this; }
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

			unsigned int toUInt() { return this->r << 24 | this->g << 16 | this->b << 8 | this->a; }
	};

	class cRGB
	{
		public:
			cRGB( int r, int g, int b ) { this->r = r; this->g = g; this->b = b; }
			cRGB() { }

			int r;
			int g;
			int b;

			unsigned int toUInt() { return this->r << 16 | this->g << 8 | this->b; }
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

			unsigned int toUInt() { return this->a << 24 | this->r << 16 | this->g << 8 | this->b; }
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

extern PluginFuncs*    functions;
extern HSQUIRRELVM     v;

// Functions
void printfunc(HSQUIRRELVM v, const SQChar *s, ...);
void errorfunc(HSQUIRRELVM v, const SQChar *s, ...);
void RegisterStructures();
