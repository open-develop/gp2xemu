#include <stdio.h>
#include <stdlib.h>
#include <arm_emu.h>
#include <arm920t.h>
#include <x86.h>
#include <ARMArit.h>
#include <ARMMisc.h>


void recNULL(void){

	/* should write nop's? 
	 */
	printf("ARMMisc.c: recNULL() fixme\n");
}



void recSWI(void){

}


void recSWP(void){

	CHECK_CONDITION(0);

	/*mov32ItoR(GPR(_Rn_).sVal,EAX);*/
	mov32ItoR(GPR(_Rm_).sVal,EAX);
	xchg32RtoM(EAX,GPR(_Rn_).sPtr);
	mov32RtoM(EAX,&GPR(_Rd_));
}


void recSWPB(void){


	fprintf(stderr,"ARMMisc: recSWPB()\n");
}

void recTEQi(void){

	CHECK_CONDITION(0);
	mov32ItoR(_IMM_,EAX);
	mov32ItoR(GPR(_Rn_).sVal,ECX);
	ror32R(EAX,shift_table[_RORIMM_]);
	UPDATE_CARRY(1);
	xor32RtoR(EAX,ECX);
	UPDATE_SIGN(1);
	UPDATE_ZERO(1);
	x86SetJI8(x86Tmp[0]);
}


void recTEQs(void){

	__register u32 val=((CPU.currentInst>>4)&0x7U);

	CHECK_CONDITION(0);
	mov32ItoR(GPR(_Rm_).sVal,EAX);
	mov32ItoR(GPR(_Rn_).sVal,EDX);
	shiftDispatch[val](EAX);
	UPDATE_CARRY(1);
	xor32RtoR(EAX,EDX);
	UPDATE_SIGN(1);
	UPDATE_ZERO(1);
	x86SetJI8(x86Tmp[0]);
	return;
}


void recTSTi(void){

	CHECK_CONDITION(0);
	mov32ItoR(_IMM_,EAX);
	ror32R(EAX,shift_table[_RORIMM_]);
	test32RtoM(EAX,&GPR(_Rn_));
	UPDATE_CARRY(1);
	UPDATE_SIGN(1);
	UPDATE_ZERO(1);
	x86SetJI8(x86Tmp[0]);
	return;

}

void recTSTs(void){

	__register u32 val=((CPU.currentInst>>4)&0x7U);

	CHECK_CONDITION(0);
	mov32ItoR(GPR(_Rm_).sVal,EAX);
	shiftDispatch[val](EAX);
	UPDATE_CARRY(1);
	test32RtoM(EAX,&GPR(_Rn_));
	UPDATE_ZERO(1);
	UPDATE_SIGN(1);
	x86SetJI8(x86Tmp[0]);
	return;

}

void recCDP(void){
	printf("fixme: recCDP()\ncoprocessor\n");
	return ;
}


void recCMPi(void){
	
	CHECK_CONDITION(0);
	mov32ItoR(_IMM_,EAX);
	ror32R(EAX,shift_table[_RORIMM_]);
	cmp32RtoM(EAX,&GPR(_Rn_));
	INVERSE_CARRY(1);
	UPDATE_SIGN(1);
	UPDATE_ZERO(1);
	UPDATE_OVERF(1);
	x86SetJI8(x86Tmp[0]);
	return;
}


void recCMPs(void){

	__register u32 val=((CPU.currentInst>>4)&0x7U);

	CHECK_CONDITION(0);
	mov32ItoR(GPR(_Rm_).sVal,EAX);
	shiftDispatch[val](EAX);
	cmp32RtoM(EAX,&GPR(_Rn_));
	INVERSE_CARRY(1);
	UPDATE_SIGN(1);
	UPDATE_ZERO(1);
	UPDATE_OVERF(1);
	x86SetJI8(x86Tmp[0]);
	return;
}


void recCMNi(void){

	CHECK_CONDITION(0)
	mov32ItoR(_IMM_,EAX);
	mov32ItoR(GPR(_Rn_).sVal,ECX);
	neg32R(EAX);
	add32RtoR(EAX,ECX);
	if(_UPDATE_FLAGS_){
		UPDATE_CARRY(1);
		UPDATE_SIGN(1);
		UPDATE_OVERF(1);
		UPDATE_ZERO(1);
	}
	x86SetJI8(x86Tmp[0]);
	return;
}



void recCMNs(void){

	__register u32 val=((CPU.currentInst>>4)&0x7U);
	/*__register u32 imm=((CPU.currentInst>>7)&0x1fU);
	 */

	/* preload Rm/Rn registers, and check condition*/
	CHECK_CONDITION(0)
	mov32ItoR(GPR(_Rm_).sVal,EAX);
	mov32ItoR(GPR(_Rn_).sVal,EDX);
	shiftDispatch[val](EAX);
	neg32R(EAX);
	add32RtoR(EAX,EDX);
	if(_UPDATE_FLAGS_){
		UPDATE_CARRY(1);
		UPDATE_SIGN(1);
		UPDATE_OVERF(1);
		UPDATE_ZERO(1);
	}
	return;
}

