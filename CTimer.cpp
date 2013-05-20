#include "CCore.h"
#include "CTimer.h"

void  CTimer::Delete()          { this->committingSeppuku = true; }
float CTimer::GetElapsedTicks() { return this->ticksElapsed; }

bool CTimer::Pulse( float elapsedTime )
{
	this->ticksElapsed += elapsedTime;

	if( this->committingSeppuku )
		return true;
	else if( this->ticksElapsed >= this->intervalInTicks )
	{
		// Start ridiculous block of timer call code
		{
			int top = sq_gettop( v );

			// Push a new environment for the function call
			sq_pushroottable( v );
			sq_pushstring( v, _SC(this->pFunc), -1 );

			// Check if we found the function
			if( SQ_SUCCEEDED( sq_get( v, -2 ) ) )
			{
				// Push a new root table for this function
				sq_pushroottable( v );
				
				// Count the number of arguments that we have so far
				// The root table counts as an argument.
				int nArgs = 1;

				// See if we have any parameters to pass along
				if( this->paramCount > 0 )
				{
					for( unsigned char i = 0; i < paramCount; i++ )
					{
						printf( "Pushed type %d, pointer %p\n", this->params[i].datatype, this->params[i].pData );
						switch( this->params[i].datatype )
						{
							case OT_INTEGER:
								sq_pushinteger( v, *(SQInteger *)this->params[i].pData );
								break;

							case OT_FLOAT:
								sq_pushfloat( v, *(SQFloat *)this->params[i].pData );
								break;

							case OT_BOOL:
								sq_pushbool( v, *(SQBool *)this->params[i].pData );
								break;

							case OT_STRING:
								sq_pushstring( v, reinterpret_cast<const SQChar *>(this->params[i].pData), -1 );
								printf( "%s\n", *(SQChar *)(this->params[i].pData) );
								break;

							case OT_TABLE:
							case OT_ARRAY:
							case OT_CLASS:
							case OT_CLOSURE:
							case OT_GENERATOR:
							case OT_WEAKREF:
								sq_pushobject( v, *(HSQOBJECT *)this->params[i].pData );
								break;
								
							case OT_INSTANCE:
							case OT_USERDATA:
							case OT_USERPOINTER:
							case OT_NATIVECLOSURE:
								sq_pushuserpointer( v, (SQUserPointer *)this->params[i].pData );
								break;

							case OT_NULL:
								sq_pushnull( v );
								break;

							default:
								break;
						}
					}
				}
				
				// Call the function
				sq_call( v, 4, 0, 1 );
			}
			else
			{
				// Restore the previous environment
				sq_settop( v, top );

				// Function not found. Kill the timer.
				this->committingSeppuku = true;
				return true;
			}
		}

		this->ticksElapsed = 0.0f;
		this->pulseCount++;

		if( this->maxNumberOfPulses > 0 && this->pulseCount >= this->maxNumberOfPulses )
		{
			// Assisted suicide
			return true;
		}
	}

	return false;
}

void RegisterTimer()
{
	Class<CTimer> c(v);
		
	// Read-only properties
	c
		.Prop( _SC("Elapsed"), &CTimer::GetElapsedTicks );

	// Functions
	c
		.Func( _SC("Delete"), &CTimer::Delete );

	// Freely editable variables
	c
		.Var( _SC("Interval"), &CTimer::intervalInTicks )
		.Var( _SC("Paused"), &CTimer::isPaused );

	RootTable(v).Bind( _SC("CTimer"), c );
}