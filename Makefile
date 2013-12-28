Module_objs = CallbackHandler.o CCore.o CObject.o ConsoleUtils.o CPickup.o CPlayer.o CSprite.o CTimer.o CVehicle.o Exports.o FunctionHandler.o Functions.o main.o UtilStructs.o

CC = g++
CFLAGS = -fpermissive -Wall -O2 -DNDEBUG -fPIC -I. -I./sqrat -I./squirrel -I./sqrat/sqrat -std=c++11
SQLIB = squirrelsrc/lib/
LDFLAGS = -Wl,-Bsymbolic

all: squirrel04.so

default: all

squirrel04.so: $(Module_objs)
	$(CC) -o $@ $(Module_objs) $(SQLIB)libsqstdlib.a $(SQLIB)libsquirrel.a -shared -s $(LDFLAGS)

CallbackHandler.o: CallbackHandler.cpp CallbackHandler.h
	$(CC) $(CFLAGS) -c CallbackHandler.cpp -o $@

CCore.o: CCore.cpp CCore.h
	$(CC) $(CFLAGS) -c CCore.cpp -o $@

CObject.o: CObject.cpp CObject.h
	$(CC) $(CFLAGS) -c CObject.cpp -o $@

ConsoleUtils.o: ConsoleUtils.cpp ConsoleUtils.h
	$(CC) $(CFLAGS) -c ConsoleUtils.cpp -o $@

CPickup.o: CPickup.cpp CPickup.h
	$(CC) $(CFLAGS) -c CPickup.cpp -o $@

CPlayer.o: CPlayer.cpp CPlayer.h
	$(CC) $(CFLAGS) -c CPlayer.cpp -o $@

CSprite.o: CSprite.cpp CSprite.h
	$(CC) $(CFLAGS) -c CSprite.cpp -o $@

CTimer.o: CTimer.cpp CTimer.h
	$(CC) $(CFLAGS) -c CTimer.cpp -o $@

CVehicle.o: CVehicle.cpp CVehicle.h
	$(CC) $(CFLAGS) -c CVehicle.cpp -o $@

Exports.o: Exports.cpp Exports.h
	$(CC) $(CFLAGS) -c Exports.cpp -o $@

FunctionHandler.o: FunctionHandler.cpp FunctionHandler.h
	$(CC) $(CFLAGS) -c FunctionHandler.cpp -o $@

Functions.o: Functions.cpp Functions.h
	$(CC) $(CFLAGS) -c Functions.cpp -o $@

main.o: main.cpp main.h
	$(CC) $(CFLAGS) -c main.cpp -o $@

UtilStructs.o: UtilStructs.cpp UtilStructs.h
	$(CC) $(CFLAGS) -c UtilStructs.cpp -o $@

clean:
	rm -f $(Module_objs) squirrel04.so
