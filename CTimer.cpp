#include "CCore.h"
#include "CTimer.h"
#include <cassert>

void  CTimer::Delete()          { this->committingSeppuku = true; }
float CTimer::GetElapsedTicks() { return this->ticksElapsed; }

void CTimer::Start() { this->isPaused = false; }
void CTimer::Stop() { this->isPaused = true; }

bool CTimer::Pulse( float elapsedTime )
{
	this->ticksElapsed += elapsedTime;

	if( this->committingSeppuku )
		return true;
	else if( this->ticksElapsed >= this->intervalInTicks )
	{
		int top = sq_gettop( v );

		// Push a new environment for the function call
		sq_pushroottable( v );
		sq_pushstring( v, this->pFunc, -1 );

		if( SQ_SUCCEEDED( sq_get( v, -2 ) ) )
		{
			sq_pushroottable( v );
			int nArgs = this->paramCount + 1; // +1 for the root table

			if( this->paramCount > 0 )
			{
				// for(int i = paramCount - 1; i > 0; i--)
				void * pData;
				SQObjectType type;

				for (int i = 0; i < paramCount; i++)
				{
					pData = this->params[i].pData;
					type  = this->params[i].datatype;
					switch (type)
					{
						case OT_INTEGER:
							Sqrat::PushVar(v, *(Sqrat::Var<SQInteger> *)(pData));
							break;

						case OT_FLOAT:
							Sqrat::PushVar(v, *(Sqrat::Var<SQFloat> *)(pData));
							break;

						case OT_BOOL:
							Sqrat::PushVar(v, *(Sqrat::Var<bool> *)(pData));
							break;

						case OT_STRING:
							Sqrat::PushVar(v, *(Sqrat::Var<string> *)(pData));
							break;

						case OT_TABLE:
							Sqrat::PushVar(v, *(Sqrat::Var<Sqrat::Table> *)(pData));

						case OT_ARRAY:
							Sqrat::PushVar(v, *(Sqrat::Var<Sqrat::Array> *)(pData));
							break;

						case OT_USERDATA:
						case OT_USERPOINTER:
						case OT_CLASS:
						case OT_INSTANCE:
							Sqrat::PushVar(v, *(Sqrat::Var<Sqrat::Object> *)(pData));
							break;

						case OT_CLOSURE:
						case OT_NATIVECLOSURE:
							Sqrat::PushVar(v, *(Sqrat::Var<Sqrat::Function> *)(pData));
							break;

						case OT_NULL:
							sq_pushnull(v);
							break;

						default:
							break;
					}
				}
			}

			sq_call(v, nArgs, 0, 1);
		}
		else
		{
			// Restore the previous environment
			sq_settop( v, top );
			
			// Function not found. Kill the timer.
			this->committingSeppuku = true;
			return true;
		}

		// Restore the previous environment
		sq_settop(v, top);

		this->ticksElapsed = 0.0f;
		this->pulseCount++;

		if (this->maxNumberOfPulses > 0 && this->pulseCount >= this->maxNumberOfPulses)
		{
			// Assisted suicide
			return true;
		}
	}

	return false;
}

void RegisterTimer()
{
	Class<CTimer> c(v, "CTimer_INTERNAL");
		
	// Read-only properties
	c
		.Prop( _SC("Elapsed"), &CTimer::GetElapsedTicks );

	// Functions
	c
		.Func( _SC("Delete"), &CTimer::Delete )
		.Func( _SC("Stop"), &CTimer::Stop )
		.Func( _SC("Start"), &CTimer::Start );

	// Freely editable variables
	c
		.Var( _SC("Interval"), &CTimer::intervalInTicks )
		.Var( _SC("Paused"), &CTimer::isPaused );

	RootTable(v).Bind( _SC("CTimer"), c );
}
