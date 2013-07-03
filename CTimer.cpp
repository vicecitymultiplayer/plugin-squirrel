#include "CCore.h"
#include "CTimer.h"
#include <cassert>

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
						switch( itr->datatype )
						{
							case OT_INTEGER:
								sq_pushinteger( v, (SQInteger)itr->pData );
								break;

							case OT_FLOAT:
								float fTmp;
								assert( sizeof( float ) == sizeof( itr->pData ) );
								memcpy( &fTmp, &itr->pData, sizeof( float ) );

								sq_pushfloat( v, fTmp );
								break;

							case OT_BOOL:
								sq_pushbool( v, (SQBool)itr->pData );
								break;

							case OT_STRING:
								sq_pushstring( v, reinterpret_cast<const SQChar *>(itr->pData), -1 );
								break;

							case OT_TABLE:
							case OT_ARRAY:
							case OT_CLOSURE:
							case OT_NATIVECLOSURE:
								HSQOBJECT oTmp;
								assert( sizeof( HSQOBJECT ) == sizeof( itr->pData ) );
								memcpy( &oTmp, &itr->pData, sizeof( float ) );

								sq_pushobject( v, oTmp );
								break;
								
							case OT_INSTANCE:
								sq_createinstance( v, -1 );
								sq_setinstanceup( v, -1, itr->pData );
								break;

							case OT_USERDATA:
							case OT_USERPOINTER:
								sq_pushuserpointer( v, (SQUserPointer)itr->pData );
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
		.Func( _SC("Delete"), &CTimer::Delete, 1, "t" );

	// Freely editable variables
	c
		.Var( _SC("Interval"), &CTimer::intervalInTicks )
		.Var( _SC("Paused"), &CTimer::isPaused );

	RootTable(v).Bind( _SC("CTimer"), c );
}
