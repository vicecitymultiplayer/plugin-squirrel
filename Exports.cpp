#include "Exports.h"
#include "CCore.h"

// God have mercy on our souls
#define SQAPI(sz) sq-> ## sz = sq_ ## sz
extern HSQAPI sq;
extern HSQUIRRELVM v;

void InitSQAPI()
{
	if (sq == nullptr)
		sq = new sq_api();

	// VM management
	SQAPI(open);
	SQAPI(newthread);
	SQAPI(seterrorhandler);
	SQAPI(close);
	SQAPI(setforeignptr);
	SQAPI(getforeignptr);
	SQAPI(setprintfunc);
	SQAPI(getprintfunc);
	SQAPI(suspendvm);
	SQAPI(wakeupvm);
	SQAPI(getvmstate);

	// Compiler
	SQAPI(compile);
	SQAPI(compilebuffer);
	SQAPI(enabledebuginfo);
	SQAPI(notifyallexceptions);
	SQAPI(setcompilererrorhandler);

	// Stack operations
	SQAPI(push);
	SQAPI(pop);
	SQAPI(poptop);
	SQAPI(remove);
	SQAPI(gettop);
	SQAPI(settop);
	SQAPI(reservestack);
	SQAPI(cmp);
	SQAPI(move);

	// Object creation handling
	SQAPI(newuserdata);
	SQAPI(newtable);
	SQAPI(newarray);
	SQAPI(newclosure);
	SQAPI(setparamscheck);
	SQAPI(bindenv);
	
	SQAPI(pushstring);
	SQAPI(pushfloat);
	SQAPI(pushinteger);
	SQAPI(pushbool);
	SQAPI(pushuserpointer);
	SQAPI(pushnull);
	
	SQAPI(gettype);
	SQAPI(getsize);
	SQAPI(getbase);
	SQAPI(instanceof);

	SQAPI(tostring);
	SQAPI(tobool);
	SQAPI(getstring);
	SQAPI(getinteger);
	SQAPI(getfloat);
	SQAPI(getbool);
	SQAPI(getthread);
	SQAPI(getuserpointer);
	SQAPI(getuserdata);
	SQAPI(settypetag);
	SQAPI(gettypetag);

	SQAPI(setreleasehook);
	SQAPI(getscratchpad);
	SQAPI(getclosureinfo);
	SQAPI(setnativeclosurename);
	SQAPI(setinstanceup);
	SQAPI(getinstanceup);
	SQAPI(setclassudsize);
	SQAPI(newclass);
	SQAPI(createinstance);
	SQAPI(setattributes);
	SQAPI(getattributes);
	SQAPI(getclass);
	SQAPI(weakref);
	SQAPI(getdefaultdelegate);

	// Object manipulation
	SQAPI(pushroottable);
	SQAPI(pushregistrytable);
	SQAPI(pushconsttable);
	SQAPI(setroottable);
	SQAPI(setconsttable);
	SQAPI(newslot);
	SQAPI(deleteslot);
	SQAPI(set);
	SQAPI(get);
	SQAPI(rawget);
	SQAPI(rawset);
	SQAPI(rawdeleteslot);
	
	SQAPI(arrayappend);
	SQAPI(arraypop);
	SQAPI(arrayresize);
	SQAPI(arrayreverse);
	SQAPI(arrayremove);
	SQAPI(arrayinsert);

	SQAPI(setdelegate);
	SQAPI(getdelegate);
	SQAPI(clone);
	SQAPI(setfreevariable);
	SQAPI(next);
	SQAPI(getweakrefval);
	SQAPI(clear);

	// Calls
	SQAPI(call);
	SQAPI(resume);
	SQAPI(getlocal);
	SQAPI(getfreevariable);
	SQAPI(throwerror);
	SQAPI(reseterror);
	SQAPI(getlasterror);

	// Raw object handling
	SQAPI(getstackobj);
	SQAPI(pushobject);
	SQAPI(addref);
	SQAPI(release);
	SQAPI(resetobject);
	SQAPI(objtostring);
	SQAPI(objtobool);
	SQAPI(objtointeger);
	SQAPI(objtofloat);
	SQAPI(getobjtypetag);

	// Garbage collection
	SQAPI(collectgarbage);

	// Serialization
	SQAPI(writeclosure);
	SQAPI(readclosure);

	// Memory allocation
	SQAPI(malloc);
	SQAPI(realloc);
	SQAPI(free);

	// Debugging
	SQAPI(stackinfos);
	SQAPI(setdebughook);
}

HSQAPI * pfGetSquirrelAPI()
{
	// Just return whatever we have
	return &sq;
}

HSQUIRRELVM * pfGetSquirrelVM()
{
	// Same as pfGetSquirrelAPI, just a different variable
	return &v;
}