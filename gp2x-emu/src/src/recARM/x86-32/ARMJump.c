#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arm_emu.h>
#include <arm920t.h>
#include <ARMJump.h>
#include <x86.h>
#define JADDR (CPU.currentInst&0xffffffU)


u32 matchCondition(u32 );

void recB(void){

	CHECK_CONDITION(0)
	DEBUG_PRINT
	mov32ItoR(JADDR,EAX);
	mov32RtoR(EAX,ECX);
	shr32R(ECX,0x10U);
	and32ItoEAX(0x0000ffff);
	/* since x86 doesnt provice a instruction to sign extend
	 * 24bit operands we have to do that manually 
	 */
	movsxR8toR16(ECX,ECX);
	shl32R(ECX,0x10);
	or32RtoR(EAX,ECX);
	add32RtoM(ECX,&PC);
	x86SetJI8(x86Tmp[0]);
	return;
}



void recBL(void){

	CHECK_CONDITION(0)
	DEBUG_PRINT
	mov32ItoR(JADDR,EAX);
	mov32RtoR(EAX,ECX);
	shr32R(ECX,0x10);
	/*
	 * and32ItoR(ECX,0x0000ffffU);
	 * and32ItoR(0x0000ffffU,ECX);
	 *
	 */

	and32ItoEAX(0x0000ffff);
	/* 
	 * since x86 doesnt provide a instruction to sign extend 
	 * 24bit operands we have to do that manually 
	 *
	 */
	movsxR8toR16(ECX,ECX);
	shl32R(ECX,0x10);
	or32RtoR(EAX,ECX);
	mov32ItoR(PC.sVal,EDX);
	/* store old PC in LR */
	mov32RtoM(EDX,&LR);
	add32RtoM(ECX,&PC);
	x86SetJI8(x86Tmp[0]);
	return;
}


void recBX(void){
	
	CHECK_CONDITION(0)
	DEBUG_PRINT
	mov32ItoR(GPR(_Rm_).sVal,EAX);
	mov32RtoR(EAX,ECX);
	mov32ItoR(CPSR.sVal,EDX);
	bt32I8toR(0,EAX);
	x86Tmp[1]=jncI8(0);
	bts32I8toR(THUMB,EDX);
	x86SetJI8(x86Tmp[1]);
	/*btr();
	 */
	and32ItoEAX(0xfffffffe);
	mov32RtoM(EAX,&PC);
	x86SetJI8(x86Tmp[0]);
	return;
}



void recBLX(void){
	DEBUG_PRINT
}

void recBLXSpe(void){
	DEBUG_PRINT
}
