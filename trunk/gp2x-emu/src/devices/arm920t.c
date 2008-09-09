#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <arm_emu.h>
#include <arm920t.h>
#include <MMU.h>


extern MEMBLOCK physMem;
extern MEMBLOCK	recMem;

void armInit(void){

	CPU.init  = armInit;
	CPU.start = armStart;
	CPU.stop  = armStop;
}


void armStart(void){

}


void armStop(void){

}
