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
		CTimer()
		{
			this->committingSeppuku = false;
			this->ticksElapsed = 0.0f;
			this->pulseCount = 0;
			this->isPaused = false;

			this->maxNumberOfPulses = 0;
			this->intervalInTicks = 0.0f;
			this->pFunc = NULL;
			this->paramCount = 0;

			this->params.clear();
		}

		~CTimer()
		{
			if( params.size() > 0 )
				params.clear();
		}
		
		bool Pulse( float elapsedTime );
		
		// Is this timer paused?
		bool isPaused;

		// The interval to run it at
		float intervalInTicks;

	public:
		float GetElapsedTicks();
		void Delete();

	public:
		// Ticks elapsed since last pulse
		float ticksElapsed;

		// Number of times to run, or 0 for an infinite number of runs.
		unsigned int maxNumberOfPulses;

		// How many times has this timer ran?
		unsigned int pulseCount;

		// The script function to use
		SQChar * pFunc;

		// The list of parameters
		std::vector<TimerParam> params;

		// The parameter count
		unsigned char paramCount;

		// Are we killing ourselves off?
		bool committingSeppuku;
};

void RegisterTimer();