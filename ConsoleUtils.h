#ifdef WIN32
	#include <Windows.h>
#endif
#include <iostream>
#include <stdio.h>

void OutputScriptInfo ( char * msg );
void OutputDebug      ( char * msg );
void OutputMessage    ( char * msg );
void OutputWarning    ( char * msg );
void OutputError      ( char * msg );