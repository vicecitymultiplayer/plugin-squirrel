SQUIRREL= ..


OUT= $(SQUIRREL)/bin/sq$(BITCOUNT)
INCZ= -I$(SQUIRREL)/include -I. -I$(SQUIRREL)/sqlibs
LIBZ= -L$(SQUIRREL)/lib 
LIB= -lsquirrel$(BITCOUNT) -lsqstdlib$(BITCOUNT)

OBJS= sq.o
	
SRCS= sq.c
	
	
sq32:
	$(eval BITCOUNT:=32)
	g++ -O2 -s -m32 -fno-exceptions -fno-rtti -o $(OUT) $(SRCS) $(INCZ) $(LIBZ) $(LIB)

sqprof:
	$(eval BITCOUNT:=32)
	g++ -O2 -pg -m32 -fno-exceptions -fno-rtti -pie -gstabs -g3 -o $(OUT) $(SRCS) $(INCZ) $(LIBZ) $(LIB)
	
sq64:
	$(eval BITCOUNT:=64)
	g++ -O2 -s -m64 -fno-exceptions -fno-rtti -D_SQ64 -o $(OUT) $(SRCS) $(INCZ) $(LIBZ) $(LIB)
