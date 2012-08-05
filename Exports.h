/** Note that these exports are untested
    and unstable **/

// Include this header only once
#pragma once

// Include our main functions
#include "main.h"

// Define the only function we even have
typedef HSQUIRRELVM	*	( *Sq_GetSquirrelVM )	( void );

// Define the prototype for that implementation
HSQUIRRELVM * pfGetSquirrelVM();

// List of exports
struct SquirrelExports
{
	unsigned int		uStructSize;
	Sq_GetSquirrelVM	GetSquirrelVM;
};