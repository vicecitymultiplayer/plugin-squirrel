#ifdef WIN32
	#include <Windows.h>
#endif
#include <iostream>
#include <stdio.h>

void OutputScriptInfo ( const char * msg );
void OutputDebug      ( const char * msg );
void OutputMessage    ( const char * msg );
void OutputWarning    ( const char * msg );
void OutputError      ( const char * msg );