#include "Exports.h"
#include "CCore.h"

// Externalize the virtual machine
extern HSQUIRRELVM v;

HSQUIRRELVM * pfGetSquirrelVM()
{
	// Just return whatever we have
	return &v;
}