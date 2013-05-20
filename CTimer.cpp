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
			sq_pushstring( v, this->pFunc, -1 );

			// Check if we found the function
			if( SQ_SUCCEEDED( sq_get( v, -2 ) ) )
			{
				// Push a new root table for this function
				sq_pushroottable( v );
				
				// Count the number of arguments that we have so far
				// The root table counts as an argument.
				int nArgs = 1 + this->paramCount;

				// See if we have any parameters to pass along
				if( this->paramCount > 0 )
				{
					// Create a vector iterator
					std::vector<TimerParam>::iterator itr;

					// Iterate through the vector of parameters
					for( itr = this->params.begin(); itr < this->params.end(); ++itr )
					{
						printf( "Pushed type %d, pointer %p\n", itr->datatype, itr->pData );
						switch( itr->datatype )
						{
							case OT_INTEGER:
								printf( "Pushed integer, pointer %p\n", itr->pData );
								sq_pushinteger( v, (SQInteger)itr->pData );
								break;

							case OT_FLOAT:
								printf( "Pushed float, pointer %p\n", itr->pData );
								sq_pushfloat( v, *(SQFloat *)(itr->pData) );
								break;

							case OT_BOOL:
								printf( "Pushed boolean, pointer %p\n", itr->pData );
								sq_pushbool( v, (SQBool)itr->pData );
								break;

							case OT_STRING:
								printf( "Pushed string, pointer %p\n", itr->pData );
								sq_pushstring( v, reinterpret_cast<const SQChar *>(itr->pData), -1 );
								printf( "%s\n", (SQChar *)itr->pData );
								break;

							case OT_TABLE:
							case OT_ARRAY:
							case OT_CLASS:
							case OT_CLOSURE:
							case OT_GENERATOR:
							case OT_WEAKREF:
								printf( "Pushed object, pointer %p\n", itr->pData );
								sq_pushobject( v, *(HSQOBJECT *)itr->pData );
								break;
								
							case OT_INSTANCE:
								sq_createinstance( v, -1 );
								sq_setinstanceup( v, -1, itr->pData );
								break;

							case OT_USERDATA:
							case OT_USERPOINTER:
							case OT_NATIVECLOSURE:
								printf( "Pushed closure/instance, pointer %p\n", itr->pData );
								sq_pushuserpointer( v, (SQUserPointer)itr->pData );
								break;

							case OT_NULL:
								printf( "Pushed null, pointer %p\n", itr->pData );
								sq_pushnull( v );
								break;

							default:
								printf( "UNKNOWN PUSH TYPE\n" );
								break;
						}
					}
				}
				
				// Call the function
				printf( "Arg count: %d\n", nArgs );
				sq_call( v, nArgs, 0, 1 );
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
			sq_settop( v, top );
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