#include <stdio.h>
#include <stdlib.h>
#include <arm_emu.h>
#include <x86.h>
#include <x86FPU.h>

extern u8 *code_ptr;

void f2xm1(void){
	WRITE16(0xf0d9);
	return;
}

void fabs(void){
	WRITE16(0xe1d9);
	return;
}

void faddST0(x86FPUReg from ){
	WRITE8(0xd8);
	WRITE8(0xc0+from);
	return;
}

void faddSTi(x86FPUReg to){
	WRITE8(0xdc);
	WRITE8(0xc0+to);
	return;
}

void faddpSTi(x86FPUReg to){
	WRITE8(0xde);
	WRITE8(0xc0+to);
	return;
}
void faddp(void){
	WRITE16(0xc1de);
	return;
}


