#include "CCore.h"
#include "CTimer.h"
#include <cassert>

// Tha core
extern CCore * pCore;

void  CTimer::Delete()          { this->committingSeppuku = true; }
SQFloat CTimer::GetElapsedTicks() { return this->ticksElapsed; }

void CTimer::Start() { this->isPaused = false; }
void CTimer::Stop() { this->isPaused = true; }

bool CTimer::Pulse( SQFloat elapsedTime )
{
	this->ticksElapsed += elapsedTime;

	if( this->committingSeppuku )
		return true;
	else if( this->ticksElapsed >= this->intervalInTicks )
	{
        Sqrat::Function callback = Sqrat::RootTable().GetFunction(funcName.c_str());

        if (!callback.IsNull())
        {
            switch(params.size())
            {
                case 0:
                    callback.Execute();
                break;
                case 1:
                    callback.Execute<Sqrat::Object &>(params[0]);
                break;
                case 2:
                    callback.Execute<Sqrat::Object &
                                    , Sqrat::Object &>
                    (params[0], params[1]);
                break;
                case 3:
                    callback.Execute<Sqrat::Object &
                                    , Sqrat::Object &
                                    , Sqrat::Object &>
                    (params[0], params[1], params[2]);
                break;
                case 4:
                    callback.Execute<Sqrat::Object &
                                    , Sqrat::Object &
                                    , Sqrat::Object &
                                    , Sqrat::Object &>
                    (params[0], params[1], params[2], params[3]);
                break;
                case 5:
                    callback.Execute<Sqrat::Object &
                                    , Sqrat::Object &
                                    , Sqrat::Object &
                                    , Sqrat::Object &
                                    , Sqrat::Object &>
                    (params[0], params[1], params[2], params[3], params[4]);
                break;
                case 6:
                    callback.Execute<Sqrat::Object &
                                    , Sqrat::Object &
                                    , Sqrat::Object &
                                    , Sqrat::Object &
                                    , Sqrat::Object &
                                    , Sqrat::Object &>
                    (params[0], params[1], params[2], params[3], params[4], params[5]);
                break;
                case 7:
                    callback.Execute<Sqrat::Object &
                                    , Sqrat::Object &
                                    , Sqrat::Object &
                                    , Sqrat::Object &
                                    , Sqrat::Object &
                                    , Sqrat::Object &
                                    , Sqrat::Object &>
                    (params[0], params[1], params[2], params[3], params[4], params[5], params[6]);
                break;
                case 8:
                    callback.Execute<Sqrat::Object &
                                    , Sqrat::Object &
                                    , Sqrat::Object &
                                    , Sqrat::Object &
                                    , Sqrat::Object &
                                    , Sqrat::Object &
                                    , Sqrat::Object &
                                    , Sqrat::Object &>
                    (params[0], params[1], params[2], params[3], params[4], params[5], params[6], params[7]);
                break;
                case 9:
                    callback.Execute<Sqrat::Object &
                                    , Sqrat::Object &
                                    , Sqrat::Object &
                                    , Sqrat::Object &
                                    , Sqrat::Object &
                                    , Sqrat::Object &
                                    , Sqrat::Object &
                                    , Sqrat::Object &
                                    , Sqrat::Object &>
                    (params[0], params[1], params[2], params[3], params[4], params[5], params[6], params[7], \
                     params[8]);
                break;
                case 10:
                    callback.Execute<Sqrat::Object &
                                    , Sqrat::Object &
                                    , Sqrat::Object &
                                    , Sqrat::Object &
                                    , Sqrat::Object &
                                    , Sqrat::Object &
                                    , Sqrat::Object &
                                    , Sqrat::Object &
                                    , Sqrat::Object &
                                    , Sqrat::Object &>
                    (params[0], params[1], params[2], params[3], params[4], params[5], params[6], params[7], \
                     params[8], params[9]);
                break;
                case 11:
                    callback.Execute<Sqrat::Object &
                                    , Sqrat::Object &
                                    , Sqrat::Object &
                                    , Sqrat::Object &
                                    , Sqrat::Object &
                                    , Sqrat::Object &
                                    , Sqrat::Object &
                                    , Sqrat::Object &
                                    , Sqrat::Object &
                                    , Sqrat::Object &
                                    , Sqrat::Object &>
                    (params[0], params[1], params[2], params[3], params[4], params[5], params[6], params[7], \
                     params[8], params[9], params[10]);
                break;
                default:
                    // Wrong arguments. Kill the timer.
                    this->committingSeppuku = true;
                    return true;
            }
        }
        else
        {
            // Function not found. Kill the timer.
            this->committingSeppuku = true;
            return true;
        }

		this->ticksElapsed = 0.0f;
		this->pulseCount++;

		if (this->maxNumberOfPulses > 0 && this->pulseCount >= this->maxNumberOfPulses)
		{
			// Assisted suicide
			return true;
		}
	}

	return false;
}

CTimer * CreateTimer(const Sqrat::string & fn, SQFloat tm, SQUnsignedInteger32 mp)
{
    CTimer * pTimer = new CTimer(fn, tm, mp, CTimer::ArgList());
    pCore->AddTimer(pTimer);
    return pTimer;
}

CTimer * CreateTimer(const Sqrat::string & fn, SQFloat tm, SQUnsignedInteger32 mp, \
                        const Sqrat::Object & a1)
{
    CTimer::ArgList args;
    args.push_back(a1);

    CTimer * pTimer = new CTimer(fn, tm, mp, args);
    pCore->AddTimer(pTimer);
    return pTimer;
}

CTimer * CreateTimer(const Sqrat::string & fn, SQFloat tm, SQUnsignedInteger32 mp, \
                        const Sqrat::Object & a1, \
                        const Sqrat::Object & a2)
{
    CTimer::ArgList args;
    args.push_back(a1);
    args.push_back(a2);

    CTimer * pTimer = new CTimer(fn, tm, mp, args);
    pCore->AddTimer(pTimer);
    return pTimer;
}

CTimer * CreateTimer(const Sqrat::string & fn, SQFloat tm, SQUnsignedInteger32 mp, \
                        const Sqrat::Object & a1, \
                        const Sqrat::Object & a2, \
                        const Sqrat::Object & a3)
{
    CTimer::ArgList args;
    args.push_back(a1);
    args.push_back(a2);
    args.push_back(a3);

    CTimer * pTimer = new CTimer(fn, tm, mp, args);
    pCore->AddTimer(pTimer);
    return pTimer;
}

CTimer * CreateTimer(const Sqrat::string & fn, SQFloat tm, SQUnsignedInteger32 mp, \
                        const Sqrat::Object & a1, \
                        const Sqrat::Object & a2, \
                        const Sqrat::Object & a3, \
                        const Sqrat::Object & a4)
{
    CTimer::ArgList args;
    args.push_back(a1);
    args.push_back(a2);
    args.push_back(a3);
    args.push_back(a4);

    CTimer * pTimer = new CTimer(fn, tm, mp, args);
    pCore->AddTimer(pTimer);
    return pTimer;
}

CTimer * CreateTimer(const Sqrat::string & fn, SQFloat tm, SQUnsignedInteger32 mp, \
                        const Sqrat::Object & a1, \
                        const Sqrat::Object & a2, \
                        const Sqrat::Object & a3, \
                        const Sqrat::Object & a4, \
                        const Sqrat::Object & a5)
{
    CTimer::ArgList args;
    args.push_back(a1);
    args.push_back(a2);
    args.push_back(a3);
    args.push_back(a4);
    args.push_back(a5);

    CTimer * pTimer = new CTimer(fn, tm, mp, args);
    pCore->AddTimer(pTimer);
    return pTimer;
}

CTimer * CreateTimer(const Sqrat::string & fn, SQFloat tm, SQUnsignedInteger32 mp, \
                        const Sqrat::Object & a1, \
                        const Sqrat::Object & a2, \
                        const Sqrat::Object & a3, \
                        const Sqrat::Object & a4, \
                        const Sqrat::Object & a5, \
                        const Sqrat::Object & a6)
{
    CTimer::ArgList args;
    args.push_back(a1);
    args.push_back(a2);
    args.push_back(a3);
    args.push_back(a4);
    args.push_back(a5);
    args.push_back(a6);

    CTimer * pTimer = new CTimer(fn, tm, mp, args);
    pCore->AddTimer(pTimer);
    return pTimer;
}

CTimer * CreateTimer(const Sqrat::string & fn, SQFloat tm, SQUnsignedInteger32 mp, \
                        const Sqrat::Object & a1, \
                        const Sqrat::Object & a2, \
                        const Sqrat::Object & a3, \
                        const Sqrat::Object & a4, \
                        const Sqrat::Object & a5, \
                        const Sqrat::Object & a6, \
                        const Sqrat::Object & a7)
{
    CTimer::ArgList args;
    args.push_back(a1);
    args.push_back(a2);
    args.push_back(a3);
    args.push_back(a4);
    args.push_back(a5);
    args.push_back(a6);
    args.push_back(a7);

    CTimer * pTimer = new CTimer(fn, tm, mp, args);
    pCore->AddTimer(pTimer);
    return pTimer;
}

CTimer * CreateTimer(const Sqrat::string & fn, SQFloat tm, SQUnsignedInteger32 mp, \
                        const Sqrat::Object & a1, \
                        const Sqrat::Object & a2, \
                        const Sqrat::Object & a3, \
                        const Sqrat::Object & a4, \
                        const Sqrat::Object & a5, \
                        const Sqrat::Object & a6, \
                        const Sqrat::Object & a7, \
                        const Sqrat::Object & a8)
{
    CTimer::ArgList args;
    args.push_back(a1);
    args.push_back(a2);
    args.push_back(a3);
    args.push_back(a4);
    args.push_back(a5);
    args.push_back(a6);
    args.push_back(a7);
    args.push_back(a8);

    CTimer * pTimer = new CTimer(fn, tm, mp, args);
    pCore->AddTimer(pTimer);
    return pTimer;
}

CTimer * CreateTimer(const Sqrat::string & fn, SQFloat tm, SQUnsignedInteger32 mp, \
                        const Sqrat::Object & a1, \
                        const Sqrat::Object & a2, \
                        const Sqrat::Object & a3, \
                        const Sqrat::Object & a4, \
                        const Sqrat::Object & a5, \
                        const Sqrat::Object & a6, \
                        const Sqrat::Object & a7, \
                        const Sqrat::Object & a8, \
                        const Sqrat::Object & a9)
{
    CTimer::ArgList args;
    args.push_back(a1);
    args.push_back(a2);
    args.push_back(a3);
    args.push_back(a4);
    args.push_back(a5);
    args.push_back(a6);
    args.push_back(a7);
    args.push_back(a8);
    args.push_back(a9);

    CTimer * pTimer = new CTimer(fn, tm, mp, args);
    pCore->AddTimer(pTimer);
    return pTimer;
}

CTimer * CreateTimer(const Sqrat::string & fn, SQFloat tm, SQUnsignedInteger32 mp, \
                        const Sqrat::Object & a1, \
                        const Sqrat::Object & a2, \
                        const Sqrat::Object & a3, \
                        const Sqrat::Object & a4, \
                        const Sqrat::Object & a5, \
                        const Sqrat::Object & a6, \
                        const Sqrat::Object & a7, \
                        const Sqrat::Object & a8, \
                        const Sqrat::Object & a9, \
                        const Sqrat::Object & a10)
{
    CTimer::ArgList args;
    args.push_back(a1);
    args.push_back(a2);
    args.push_back(a3);
    args.push_back(a4);
    args.push_back(a5);
    args.push_back(a6);
    args.push_back(a7);
    args.push_back(a8);
    args.push_back(a9);
    args.push_back(a10);

    CTimer * pTimer = new CTimer(fn, tm, mp, args);
    pCore->AddTimer(pTimer);
    return pTimer;
}

CTimer * CreateTimer(const Sqrat::string & fn, SQFloat tm, SQUnsignedInteger32 mp, \
                        const Sqrat::Object & a1, \
                        const Sqrat::Object & a2, \
                        const Sqrat::Object & a3, \
                        const Sqrat::Object & a4, \
                        const Sqrat::Object & a5, \
                        const Sqrat::Object & a6, \
                        const Sqrat::Object & a7, \
                        const Sqrat::Object & a8, \
                        const Sqrat::Object & a9, \
                        const Sqrat::Object & a10, \
                        const Sqrat::Object & a11)
{
    CTimer::ArgList args;
    args.push_back(a1);
    args.push_back(a2);
    args.push_back(a3);
    args.push_back(a4);
    args.push_back(a5);
    args.push_back(a6);
    args.push_back(a7);
    args.push_back(a8);
    args.push_back(a9);
    args.push_back(a10);
    args.push_back(a11);

    CTimer * pTimer = new CTimer(fn, tm, mp, args);
    pCore->AddTimer(pTimer);
    return pTimer;
}

void RegisterTimer()
{
	Sqrat::Class<CTimer> c(v, "CTimer_INTERNAL");

	// Read-only properties
	c
		.Prop( _SC("Elapsed"), &CTimer::GetElapsedTicks );

	// Functions
	c
		.Func( _SC("Delete"), &CTimer::Delete )
		.Func( _SC("Stop"), &CTimer::Stop )
		.Func( _SC("Start"), &CTimer::Start );

	// Freely editable variables
	c
		.Var( _SC("Interval"), &CTimer::intervalInTicks )
		.Var( _SC("Paused"), &CTimer::isPaused );

	Sqrat::RootTable(v).Bind( _SC("CTimer"), c );

    Sqrat::RootTable(v)

    .Overload<CTimer * (*)(const Sqrat::string &, SQFloat, SQUnsignedInteger32)>(_SC("NewTimer"), &CreateTimer)
    .Overload<CTimer * (*)(const Sqrat::string &, SQFloat, SQUnsignedInteger32, \
        const Sqrat::Object &)>(_SC("NewTimer"), &CreateTimer)
    .Overload<CTimer * (*)(const Sqrat::string &, SQFloat, SQUnsignedInteger32, \
        const Sqrat::Object &,
        const Sqrat::Object &)>(_SC("NewTimer"), &CreateTimer)
    .Overload<CTimer * (*)(const Sqrat::string &, SQFloat, SQUnsignedInteger32, \
        const Sqrat::Object &,
        const Sqrat::Object &,
        const Sqrat::Object &)>(_SC("NewTimer"), &CreateTimer)
    .Overload<CTimer * (*)(const Sqrat::string &, SQFloat, SQUnsignedInteger32, \
        const Sqrat::Object &,
        const Sqrat::Object &,
        const Sqrat::Object &,
        const Sqrat::Object &)>(_SC("NewTimer"), &CreateTimer)
    .Overload<CTimer * (*)(const Sqrat::string &, SQFloat, SQUnsignedInteger32, \
        const Sqrat::Object &,
        const Sqrat::Object &,
        const Sqrat::Object &,
        const Sqrat::Object &,
        const Sqrat::Object &)>(_SC("NewTimer"), &CreateTimer)
    .Overload<CTimer * (*)(const Sqrat::string &, SQFloat, SQUnsignedInteger32, \
        const Sqrat::Object &,
        const Sqrat::Object &,
        const Sqrat::Object &,
        const Sqrat::Object &,
        const Sqrat::Object &,
        const Sqrat::Object &)>(_SC("NewTimer"), &CreateTimer)
    .Overload<CTimer * (*)(const Sqrat::string &, SQFloat, SQUnsignedInteger32, \
        const Sqrat::Object &,
        const Sqrat::Object &,
        const Sqrat::Object &,
        const Sqrat::Object &,
        const Sqrat::Object &,
        const Sqrat::Object &,
        const Sqrat::Object &)>(_SC("NewTimer"), &CreateTimer)
    .Overload<CTimer * (*)(const Sqrat::string &, SQFloat, SQUnsignedInteger32, \
        const Sqrat::Object &,
        const Sqrat::Object &,
        const Sqrat::Object &,
        const Sqrat::Object &,
        const Sqrat::Object &,
        const Sqrat::Object &,
        const Sqrat::Object &,
        const Sqrat::Object &)>(_SC("NewTimer"), &CreateTimer)
    .Overload<CTimer * (*)(const Sqrat::string &, SQFloat, SQUnsignedInteger32, \
        const Sqrat::Object &,
        const Sqrat::Object &,
        const Sqrat::Object &,
        const Sqrat::Object &,
        const Sqrat::Object &,
        const Sqrat::Object &,
        const Sqrat::Object &,
        const Sqrat::Object &,
        const Sqrat::Object &)>(_SC("NewTimer"), &CreateTimer)
    .Overload<CTimer * (*)(const Sqrat::string &, SQFloat, SQUnsignedInteger32, \
        const Sqrat::Object &,
        const Sqrat::Object &,
        const Sqrat::Object &,
        const Sqrat::Object &,
        const Sqrat::Object &,
        const Sqrat::Object &,
        const Sqrat::Object &,
        const Sqrat::Object &,
        const Sqrat::Object &,
        const Sqrat::Object &)>(_SC("NewTimer"), &CreateTimer)
    .Overload<CTimer * (*)(const Sqrat::string &, SQFloat, SQUnsignedInteger32, \
        const Sqrat::Object &,
        const Sqrat::Object &,
        const Sqrat::Object &,
        const Sqrat::Object &,
        const Sqrat::Object &,
        const Sqrat::Object &,
        const Sqrat::Object &,
        const Sqrat::Object &,
        const Sqrat::Object &,
        const Sqrat::Object &,
        const Sqrat::Object &)>(_SC("NewTimer"), &CreateTimer);

}
