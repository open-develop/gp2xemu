.SUFFIXES: .S .s

%.o:%.c
	$(CC) $(CFLAGS) $@ $<

%.o:%.S
	$(AS) $(ASFLAGS) $@ $<

vpath %.c src:src/recARM:src/recARM/x86-32:src/devices:src/recARM/SPARC

ROOTPATH = $(HOME)/c_projects/arm_emu
SRCDIR = $(ROOTPATH)/src
INCLUDEDIR = -I$(ROOTPATH)/include 
OBJECTS = main.o arm920t.o x86.o ARMrec.o x86FPU.o ARMArit.o ARMJump.o ARMDivMul.o ARMMisc.o  ARMLoadStore.o ARMasm.o ARMrec.o MMU.o 

GNUCC=f
SPARC=f
DEFINES= -D_X86_ -D_DEBUG_


ifdef SPARC
vpath %.S src/recARM/SPARC
else
vpath %.S src/recARM/x86-32
endif

ifdef GNUCC
CC = gcc
LD = gcc
AS = as
OPTIMIZE=-march=pentium3m -mregparm=3 -mtune=pentium3m -Os -fomit-frame-pointer
CFLAGS= -gdwarf-2 -W $(DEFINES) $(INCLUDEDIR) -Wall -ansi -pedantic -c -o
ASFLAGS = -gdwarf-2 -Iinclude -o 
else 
CC = suncc
LD = ld
AS = as
ASFLAGS = -gdwarf-2 -Iinclude -o 
CFLAGS =  -Xa  $(DEFINES) -xdebugformat=dwarf $(INCLUDEDIR) -g -xchip=ultra2i  -xtarget=ultra2i -xc99=none  -c -o
endif


#CFLAGS = -Wall -fno-builtin -ansi -pedantic -gstabs+ $(INCLUDEDIR) -c
#CFLAGS = -O3  -fomit-frame-pointer -fno-builtin -ansi -march=pentium3m -pedantic $(INCLUDEDIR) -std=c99 -c 
LDFLAGS =   -o $@


arm_emu: $(OBJECTS)
	$(CC) $(CFLAGS) sparc64.o src/sparc64.c
	$(CC) $(LDFLAGS) $^

main.o:main.c

arm920t.o:arm920t.c

x86.o:x86.c

#sparc64.o:sparc64.c

x86FPU.o:x86FPU.c

ARMArit.o:ARMArit.c

ARMJump.o:ARMJump.c

ARMDivMul.o:ARMDivMul.c

ARMrec.o:ARMrec.c

ARMMisc.o:ARMMisc.c

ARMLoadStore.o:ARMLoadStore.c

MMU.o:MMU.c

ARMasm.o:ARMasm.S


.PHONY: clean dis
clean:
	rm -rf *.o arm_emu src/*~ *~
	rm -rf arm_emu

dis:
	objdump -d arm_emu | less
