.SUFFIXES: .S .s



%.o:%.S
	$(AS) $(ASFLAGS) $(OUTPUT)/$@ $<

%.o:%.c
	$(CC) $(CFLAGS) $(OUTPUT)/$@ $<

TARGET := arm_emu


ROOTPATH := $(PWD)
SRCDIR := $(ROOTPATH)/src
INCLUDEDIR := -I$(ROOTPATH)/include 
OUTPUT := $(ROOTPATH)/.obj
#OBJECTS := main.o arm920t.o x86.o ARMrec.o x86FPU.o ARMArit.o ARMJump.o ARMDivMul.o ARMMisc.o  ARMLoadStore.o ARMasm.o ARMrec.o MMU.o 
DEFINES := -D_X86_ -D_DEBUG_

CC := gcc
LD := gcc
AS := as
OPTIMIZE :=  -march=pentium3m -mregparm=3 -mtune=pentium3m -Os -fomit-frame-pointer
CFLAGS := -m32 -gdwarf-2 -W $(DEFINES) $(INCLUDEDIR) -Wall -ansi -pedantic -c -o
ASFLAGS := --32 -gdwarf-2 $(INCLUDEDIR) -o 
LDFLAGS :=   -m32 -o

