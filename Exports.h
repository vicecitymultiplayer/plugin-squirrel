#pragma once
#include "main.h"
#include "SQModule.h"

void InitSQAPI();

typedef HSQAPI * ( *Sq_GetSquirrelAPI ) ( void );
typedef HSQUIRRELVM * (*Sq_GetSquirrelVM) (void);

HSQAPI * pfGetSquirrelAPI();
HSQUIRRELVM * pfGetSquirrelVM();

struct SquirrelExports
{
	unsigned int		uStructSize;
	Sq_GetSquirrelAPI	GetSquirrelAPI;
	Sq_GetSquirrelVM	GetSquirrelVM;
};