#include "main.h"
#include <stdlib.h>
#include <vector>
#pragma once

// Define structures for timer maps
typedef struct
{
	void * pData;
	SQObjectType datatype; // This is some shitty programming yo
} TimerParam;

class CTimer
{
	public:
        typedef std::vector<Sqrat::Object> ArgList;

		CTimer(const Sqrat::string & fn, SQFloat, SQInteger, const ArgList & args)
            : isPaused(false)
            , intervalInTicks(0.0)
            , ticksElapsed(0.0)
            , maxNumberOfPulses(0)
            , pulseCount(0)
            , funcName(fn)
            , params(args)
            , committingSeppuku(false)
		{

		}

		~CTimer()
		{

		}

		bool Pulse( SQFloat elapsedTime );

		// Is this timer paused?
		bool isPaused;

		// The interval to run it at
		SQFloat intervalInTicks;

	public:
		SQFloat GetElapsedTicks();
		void Delete();
		void Start();
		void Stop();

	public:
		// Ticks elapsed since last pulse
		SQFloat ticksElapsed;

		// Number of times to run, or 0 for an infinite number of runs.
		unsigned int maxNumberOfPulses;

		// How many times has this timer ran?
		unsigned int pulseCount;

		// The script function to use
		Sqrat::string funcName;

		// The list of parameters
		ArgList params;

		// Are we killing ourselves off?
		bool committingSeppuku;
};

CTimer * CreateTimer(const Sqrat::string & fn, SQFloat tm, SQUnsignedInteger32 mp);

CTimer * CreateTimer(const Sqrat::string & fn, SQFloat tm, SQUnsignedInteger32 mp, \
                        const Sqrat::Object & a1);

CTimer * CreateTimer(const Sqrat::string & fn, SQFloat tm, SQUnsignedInteger32 mp, \
                        const Sqrat::Object & a1, \
                        const Sqrat::Object & a2);

CTimer * CreateTimer(const Sqrat::string & fn, SQFloat tm, SQUnsignedInteger32 mp, \
                        const Sqrat::Object & a1, \
                        const Sqrat::Object & a2, \
                        const Sqrat::Object & a3);

CTimer * CreateTimer(const Sqrat::string & fn, SQFloat tm, SQUnsignedInteger32 mp, \
                        const Sqrat::Object & a1, \
                        const Sqrat::Object & a2, \
                        const Sqrat::Object & a3, \
                        const Sqrat::Object & a4);

CTimer * CreateTimer(const Sqrat::string & fn, SQFloat tm, SQUnsignedInteger32 mp, \
                        const Sqrat::Object & a1, \
                        const Sqrat::Object & a2, \
                        const Sqrat::Object & a3, \
                        const Sqrat::Object & a4, \
                        const Sqrat::Object & a5);

CTimer * CreateTimer(const Sqrat::string & fn, SQFloat tm, SQUnsignedInteger32 mp, \
                        const Sqrat::Object & a1, \
                        const Sqrat::Object & a2, \
                        const Sqrat::Object & a3, \
                        const Sqrat::Object & a4, \
                        const Sqrat::Object & a5, \
                        const Sqrat::Object & a6);

CTimer * CreateTimer(const Sqrat::string & fn, SQFloat tm, SQUnsignedInteger32 mp, \
                        const Sqrat::Object & a1, \
                        const Sqrat::Object & a2, \
                        const Sqrat::Object & a3, \
                        const Sqrat::Object & a4, \
                        const Sqrat::Object & a5, \
                        const Sqrat::Object & a6, \
                        const Sqrat::Object & a7);

CTimer * CreateTimer(const Sqrat::string & fn, SQFloat tm, SQUnsignedInteger32 mp, \
                        const Sqrat::Object & a1, \
                        const Sqrat::Object & a2, \
                        const Sqrat::Object & a3, \
                        const Sqrat::Object & a4, \
                        const Sqrat::Object & a5, \
                        const Sqrat::Object & a6, \
                        const Sqrat::Object & a7, \
                        const Sqrat::Object & a8);

CTimer * CreateTimer(const Sqrat::string & fn, SQFloat tm, SQUnsignedInteger32 mp, \
                        const Sqrat::Object & a1, \
                        const Sqrat::Object & a2, \
                        const Sqrat::Object & a3, \
                        const Sqrat::Object & a4, \
                        const Sqrat::Object & a5, \
                        const Sqrat::Object & a6, \
                        const Sqrat::Object & a7, \
                        const Sqrat::Object & a8, \
                        const Sqrat::Object & a9);

CTimer * CreateTimer(const Sqrat::string & fn, SQFloat tm, SQUnsignedInteger32 mp, \
                        const Sqrat::Object & a1, \
                        const Sqrat::Object & a2, \
                        const Sqrat::Object & a3, \
                        const Sqrat::Object & a4, \
                        const Sqrat::Object & a5, \
                        const Sqrat::Object & a6, \
                        const Sqrat::Object & a7, \
                        const Sqrat::Object & a8, \
                        const Sqrat::Object & a9, \
                        const Sqrat::Object & a10);

CTimer * CreateTimer(const Sqrat::string & fn, SQFloat tm, SQUnsignedInteger32 mp, \
                        const Sqrat::Object & a1, \
                        const Sqrat::Object & a2, \
                        const Sqrat::Object & a3, \
                        const Sqrat::Object & a4, \
                        const Sqrat::Object & a5, \
                        const Sqrat::Object & a6, \
                        const Sqrat::Object & a7, \
                        const Sqrat::Object & a8, \
                        const Sqrat::Object & a9, \
                        const Sqrat::Object & a10, \
                        const Sqrat::Object & a11);

void RegisterTimer();