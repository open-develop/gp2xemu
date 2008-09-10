

DEVICES  := src/devices/
#RECARM	 := src/recARM/
INTERP   := src/interpARM
X8632	 := src/recARM/x86-32/
SRC	 := src/
OBJ	 := .obj/


ALLDIRS := $(DEVICES) $(INTERP) $(X8632) $(SPARC64)  $(SRC) $(OBJ) 


vpath %.c src:src/recARM:src/recARM/x86-32:src/devices:src/recARM/SPARC

all: $(ALLDIRS)


$(ALLDIRS):
	$(MAKE) -I$(PWD) --directory=$@



.PHONY: clean dis $(ALLDIRS)

clean:
	rm -rf *.o arm_emu src/*~ *~
	rm -rf .obj/*.o
	rm -rf arm_emu

dis:
	objdump -d arm_emu | less
