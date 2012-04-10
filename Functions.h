#include "main.h"
#include "FunctionHandler.h"
#define Register( x )	sq_pushstring( v, _SC("x"), -1 ); \
						sq_newclosure( v, &x, 0 ); \
						sq_newslot( v, -3, 0 );

void RegisterGlobals();
void RegisterConstants();