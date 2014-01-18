#include "ConsoleUtils.h"
#include "CCore.h"

extern CCore * pCore;
void OutputScriptInfo( const char * msg )
{
	#ifdef WIN32
		HANDLE hstdout = GetStdHandle( STD_OUTPUT_HANDLE );

		CONSOLE_SCREEN_BUFFER_INFO csbBefore;
		GetConsoleScreenBufferInfo( hstdout, &csbBefore );
		SetConsoleTextAttribute( hstdout, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY );
		pCore->rawprint("[SCRIPT]  ");

		SetConsoleTextAttribute( hstdout, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY );
		pCore->rawprint(msg);

		SetConsoleTextAttribute( hstdout, csbBefore.wAttributes );
		pCore->rawprint("\n");
	#else
		pCore->printf( "%c[0;36m[SCRIPT]%c[0;37m %s\n", 27, 27, msg );
	#endif
}

void OutputDebug( const char * msg )
{
	#ifdef _DEBUG
		OutputMessage( msg );
	#endif
}

void OutputMessage( const char * msg )
{
	#ifdef WIN32
		HANDLE hstdout = GetStdHandle( STD_OUTPUT_HANDLE );

		CONSOLE_SCREEN_BUFFER_INFO csbBefore;
		GetConsoleScreenBufferInfo( hstdout, &csbBefore );
		SetConsoleTextAttribute( hstdout, FOREGROUND_GREEN );
		pCore->rawprint("[MODULE]  ");
		
		SetConsoleTextAttribute( hstdout, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY );
		pCore->rawprint(msg);

		SetConsoleTextAttribute(hstdout, csbBefore.wAttributes);
		pCore->rawprint("\n");
	#else
		pCore->printf( "%c[0;32m[MODULE]%c[0;37m %s\n", 27, 27, msg );
	#endif
}

void OutputWarning( const char * msg )
{
	#ifdef WIN32
		HANDLE hstdout = GetStdHandle( STD_OUTPUT_HANDLE );

		CONSOLE_SCREEN_BUFFER_INFO csbBefore;
		GetConsoleScreenBufferInfo( hstdout, &csbBefore );
		SetConsoleTextAttribute( hstdout, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY );
		pCore->rawprint("[WARNING] ");
		
		SetConsoleTextAttribute( hstdout, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY );
		pCore->rawprint(msg);

		SetConsoleTextAttribute( hstdout, csbBefore.wAttributes );
		pCore->rawprint("\n");
	#else
		pCore->printf( "%c[0;30m[WARNING]%c[0;37m %s\n", 27, 27, msg );
	#endif
}

void OutputError( const char * msg )
{
	#ifdef WIN32
		HANDLE hstdout = GetStdHandle( STD_OUTPUT_HANDLE );

		CONSOLE_SCREEN_BUFFER_INFO csbBefore;
		GetConsoleScreenBufferInfo( hstdout, &csbBefore );
		SetConsoleTextAttribute( hstdout, FOREGROUND_RED | FOREGROUND_INTENSITY );
		pCore->rawprint("[ERROR]   ");
		
		SetConsoleTextAttribute( hstdout, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY );
		pCore->rawprint(msg);

		SetConsoleTextAttribute( hstdout, csbBefore.wAttributes );
		pCore->rawprint("\n");
	#else
		pCore->printf( "%c[0;30m[ERROR]%c[0;37m %s\n", 27, 27, msg );
	#endif
}