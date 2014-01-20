CC      := g++
DIRS    := .
SOURCES := $(foreach dir, $(DIRS), $(wildcard $(dir)/*.cpp))
PROJNAME := squirrel04

OBJS = $(patsubst %.cpp, %.$(BUILDTYPE)$(BITCOUNT).o, $(SOURCES))
PROG = $(PROJNAME)$(BUILDTYPE)$(BITCOUNT).so

LIBDIRS = -L./squirrelsrc/lib
STCLIBS = -lsquirrel$(BITCOUNT) -lsqstdlib$(BITCOUNT)
DYNLIBS = -ldl -lpthread

CFLAGS  = -fpermissive -Wall -O2 -lm -fPIC -c -D_WCHAR_T_EXISTS -DLINUX -D_SQ64 -DNDEBUG -I. -I./squirrel -std=c++11
LDFLAGS = -Wl,-Bsymbolic $(LIBDIRS) -shared
LDLIBS = -Wl,-Bstatic $(STCLIBS) -Wl,-Bdynamic -ldl $(DYNLIBS)
COMMONFLAGS = -m$(BITCOUNT) 

ifeq ($(BUILDTYPE), dbg)
	COMMONFLAGS += -g
else
	COMMONFLAGS += -s
endif

all: build

build: build32 build64
build32:
	$(MAKE) BITCOUNT=32 BUILDTYPE=rel xbuild
build64:
	$(MAKE) BITCOUNT=64 BUILDTYPE=rel xbuild

debug: debug32 debug64
debug32:
	$(MAKE) BITCOUNT=32 BUILDTYPE=dbg xbuild
debug64:
	$(MAKE) BITCOUNT=64 BUILDTYPE=dbg xbuild

xbuild: $(PROG)
	cp $(PROG) ../build/$(PROG)
ifeq ($(BUILDTYPE), rel)
	cd ../build; touch ./package.py; chmod +x ./package.py; ./package.py $(PROG); cd -
endif

$(PROG): $(OBJS)
	$(CC) $(LDFLAGS) $(COMMONFLAGS) -o $(PROG) $(OBJS) $(LDLIBS)

%.$(BUILDTYPE)$(BITCOUNT).o: %.cpp
	$(CC) $(CFLAGS) $(COMMONFLAGS) -c $< -o $@

clean:
	-rm *.o *.so
