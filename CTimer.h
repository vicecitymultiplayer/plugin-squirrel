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
			this->pFunc = nullptr;
			this->paramCount = 0;

			this->params.clear();
		}

		~CTimer()
		{
/*			for (unsigned int i = 0; i < params.size(); i++)
			{
				if (this->params[i].pData != nullptr)
				{
					switch (this->params[i].datatype)
					{
						case OT_INTEGER:
							delete static_cast<SQInteger *>(this->params[i].pData);
							break;

						case OT_FLOAT:
							delete static_cast<SQFloat *>(this->params[i].pData);
							break;

						case OT_BOOL:
							delete static_cast<SQBool *>(this->params[i].pData);
							break;

						case OT_STRING:
							delete static_cast<Sqrat::Var<string> *>(this->params[i].pData);
							break;

						case OT_TABLE:
							delete static_cast<Sqrat::Var<Sqrat::Table> *>(this->params[i].pData);
							break;

						case OT_ARRAY:
							delete static_cast<Sqrat::Var<Sqrat::Array> *>(this->params[i].pData);
							break;

						case OT_USERDATA:
						case OT_USERPOINTER:
						case OT_CLASS:
						case OT_INSTANCE:
							delete static_cast<Sqrat::Var<Sqrat::Object> *>(this->params[i].pData);
							break;

						case OT_CLOSURE:
						case OT_NATIVECLOSURE:
							delete static_cast<Sqrat::Var<Sqrat::Function> *>(this->params[i].pData);
							break;

						case OT_NULL:
						default:
							break;
					}
				}
			}*/

			if( this->params.size() > 0 )
				this->params.clear();
		}
		
		bool Pulse( float elapsedTime );
		
		// Is this timer paused?
		bool isPaused;

		// The interval to run it at
		float intervalInTicks;

	public:
		float GetElapsedTicks();
		void Delete();
		void Start();
		void Stop();

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