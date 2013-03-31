#include "main.h"
#pragma once

// Define structures for timer maps
typedef struct
{
	void * pData;
	unsigned char datatype; // This is some shitty programming yo
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
		}

		~CTimer()
		{
			if( params != NULL )
				delete [] params;

			this->pFunc.Release();
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
		Sqrat::Function pFunc;

		// The list of parameters
		TimerParam * params;

	private:
		bool committingSeppuku;
};

void RegisterTimer();