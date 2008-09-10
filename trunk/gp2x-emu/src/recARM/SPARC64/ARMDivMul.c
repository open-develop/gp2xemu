#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arm_emu.h>
#include <arm920t.h>
#include <ARMDivMul.h>
#include <sparc64.h>
/* since the ARM switched the position of Rd and Rn in multiply instructions i redefine them */ 
#undef _Rd_
#undef _Rn_
#define _Rd_ 	((CPU.currentInst>>16)&0x0fU)
#define _Rn_ 	((CPU.currentInst>>12)&0x0fU)
#define _Rdhi_ 	_Rd_
#define _Rdlo_ 	_Rn_





void recMUL(void){
}


void recMLA(void){

}


void recSMULL(void){

}

void recSMLAL(void){

}


void recUMULL(void){

}


void recUMLAL(void){

}
