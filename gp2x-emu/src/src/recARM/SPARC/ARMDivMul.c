#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arm_emu.h>
#include <arm920t.h>
#include <ARMDivMul.h>
#include <x86.h>
/* since the ARM switched the position of Rd and Rn in multiply instructions i redefine them */ 
#undef _Rd_
#undef _Rn_
#define _Rd_ 	((CPU.currentInst>>16)&0x0fU)
#define _Rn_ 	((CPU.currentInst>>12)&0x0fU)
#define _Rdhi_ 	_Rd_
#define _Rdlo_ 	_Rn_





void recMUL(void){

	CHECK_CONDITION(0)
	mov32ItoR(GPR(_Rs_).sVal,EAX);
	mov32ItoR(GPR(_Rm_).sVal,ECX);
	imul32RtoR(EAX,ECX);
	mov32RtoM(ECX,&GPR(_Rd_));
	if(_UPDATE_FLAGS_){
		UPDATE_SIGN(1);
		UPDATE_ZERO(1);
	}
	x86SetJI8(x86Tmp[0]);
	return;
}


void recMLA(void){

	CHECK_CONDITION(0)
	mov32ItoR(GPR(_Rs_).sVal,EAX);
	mov32ItoR(GPR(_Rm_).sVal,ECX);
	imul32RtoR(EAX,ECX);
	mov32ItoR(GPR(_Rn_).sVal,EDX);
	add32RtoR(ECX,EDX);
	mov32RtoM(EDX,&GPR(_Rd_));
	if(_UPDATE_FLAGS_){
		UPDATE_SIGN(1);
		UPDATE_ZERO(1);
	}
	x86SetJI8(x86Tmp[0]);
	return;
}


void recSMULL(void){

	CHECK_CONDITION(0)
	
	mov32ItoR(GPR(_Rm_).sVal,EAX);
	mov32ItoR(GPR(_Rs_).sVal,ECX);
	imul32R(ECX);
	mov32RtoM(EAX,&GPR(_Rdlo_));
	mov32RtoM(EDX,&GPR(_Rdhi_));
	if(_UPDATE_FLAGS_){
		test32RtoR(EDX,EDX);
		UPDATE_SIGN(1);
		test32RtoR(EAX,EDX);
		UPDATE_ZERO(1);
	}
	x86SetJI8(x86Tmp[0]);
	return;
}

void recSMLAL(void){

	CHECK_CONDITION(0)
	mov32ItoR(GPR(_Rm_).sVal,EAX);
	mov32ItoR(GPR(_Rs_).sVal,ECX);
	mov32ItoR(GPR(_Rdhi_).sVal,ESI);
	mov32ItoR(GPR(_Rdlo_).sVal,EDI);
	imul32R(ECX);
	add32RtoR(EDI,EAX);
	adc32RtoR(ESI,EDX);
	mov32RtoM(EAX,&GPR(_Rdlo_));
	mov32RtoM(EDX,&GPR(_Rdhi_));
	if(_UPDATE_FLAGS_){
		test32RtoR(EDX,EDX);
		UPDATE_SIGN(1);
		test32RtoR(EAX,EDX);
		UPDATE_ZERO(1);
	}
	x86SetJI8(x86Tmp[0]);
	return;
}


void recUMULL(void){

	CHECK_CONDITION(0)
	mov32ItoR(GPR(_Rm_).sVal,EAX);
	mov32ItoR(GPR(_Rs_).sVal,ECX);
	mul32R(ECX);
	mov32RtoM(EAX,&GPR(_Rdlo_));
	mov32RtoM(EDX,&GPR(_Rdhi_));
	if(_UPDATE_FLAGS_){
		test32RtoR(EDX,EDX);
		UPDATE_SIGN(1);
		test32RtoR(EAX,EDX);
		UPDATE_ZERO(1);
	}
	x86SetJI8(x86Tmp[0]);
	return;
}


void recUMLAL(void){

	CHECK_CONDITION(0)
	mov32ItoR(GPR(_Rm_).sVal,EAX);
	mov32ItoR(GPR(_Rs_).sVal,ECX);
	mov32ItoR(GPR(_Rdhi_).sVal,ESI);
	mov32ItoR(GPR(_Rdlo_).sVal,EDI);
	mul32R(ECX);
	add32RtoR(EDI,EAX);
	adc32RtoR(ESI,EDX);
	mov32RtoM(EAX,&GPR(_Rdlo_));
	mov32RtoM(EDX,&GPR(_Rdhi_));
	if(_UPDATE_FLAGS_){
		test32RtoR(EDX,EDX);
		UPDATE_SIGN(1);
		test32RtoR(EAX,EDX);
		UPDATE_ZERO(1);
	}
	x86SetJI8(x86Tmp[0]);
	return;
}
