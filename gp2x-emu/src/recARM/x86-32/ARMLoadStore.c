#include <stdio.h>
#include <stdlib.h>
#include <arm_emu.h>
#include <ARMx86.h>
#include <x86.h>
#include <ARMArit.h>
#include <ARMLoadStore.h>
#include <MMU.h>

extern void (*shiftDispatch[])(x86GPReg);



static void loadMultRegs(u32 addr, u32 regNum){



	int counter=0;
	DEBUG_PRINT

	while(counter<16){

		if(CINST&(1<<counter)){
			if(counter == 15){
				fprintf(stderr,"loadMultRegs(): warning r15 overwritten\n");
			}
			GPR(counter).sVal=readMemU32(addr);	
			addr+=4;
		}
		counter++;
	}


	if( _W_ ){
		GPR(regNum).uVal=addr;
	}
}


static void storeMultRegs(u32 addr, u32 regNum){

	int counter=0;

	DEBUG_PRINT
	while(counter<16){
		
		if(CINST&(1<<counter)){
			writeMemU32(addr,GPR(counter).uVal);
			addr+=4;
		}
		counter++;
	}

	if( _W_ ){
		GPR(regNum).uVal=addr;
	}
}

void recLDM1(void){

	CHECK_CONDITION(0);
#ifdef _DEBUG_ 
	if( _Rn_ == 15){
		fprintf(stderr,"recLDM1(): _Rn_ == 15\n");
	}
#endif
	DEBUG_PRINT
	pushI32(_Rn_);
	push32M(&GPR(_Rn_).sVal);
	CALLFUNC(loadMultRegs);
	add32ItoR(8,ESP);
	x86SetJI8(x86Tmp[0]);
}



void recLDM2(void){

	CHECK_CONDITION(0);
#ifdef _DEBUG_ 
	if( _Rn_ == 15 ){
		fprintf(stderr,"recLDM2(): _Rn_ == 15\n");
	}
#endif 
	DEBUG_PRINT
	pushI32(_Rn_);
	push32M(&GPR(_Rn_).sVal);
	CALLFUNC(loadMultRegs);
	add32ItoR(8,ESP);
	x86SetJI8(x86Tmp[0]);
}


void recLDM3(void){

}


void recLDR(void){

	CHECK_CONDITION(0);
	DEBUG_PRINT

	mov32MtoR(&GPR(_Rm_),ECX);
	push32M(&GPR(_Rd_));
	sub32RfmM(ECX,&GPR(_Rd_));
	CALLFUNC(readMemU32);
	mov32RtoM(EAX,&GPR(_Rd_));

	x86SetJI8(x86Tmp[0]);
}
void recLDRu(void){

	CHECK_CONDITION(0);

	mov32MtoR(&GPR(_Rm_),ECX);
	push32M(&GPR(_Rd_));
	add32RtoM(ECX,&GPR(_Rd_));
	CALLFUNC(readMemU32);
	mov32RtoM(EAX,&GPR(_Rd_));

	x86SetJI8(x86Tmp[0]);
}

void recLDRp(void){

	CHECK_CONDITION(0);
	DEBUG_PRINT

	mov32MtoR(&GPR(_Rm_),ECX);
	sub32RfmM(ECX,&GPR(_Rd_));
	push32M(&GPR(_Rd_));
	CALLFUNC(readMemU32);
	mov32RtoM(EAX,&GPR(_Rd_));

	x86SetJI8(x86Tmp[0]);
}
void recLDRup(void){

	CHECK_CONDITION(0);
	DEBUG_PRINT

	mov32MtoR(&GPR(_Rm_),ECX);
	add32RtoM(ECX,&GPR(_Rd_));
	push32M(&GPR(_Rd_));
	CALLFUNC(readMemU32);
	mov32RtoM(EAX,&GPR(_Rd_));

	x86SetJI8(x86Tmp[0]);
}


void recLDRi(void){

	CHECK_CONDITION(0);
	DEBUG_PRINT

	mov32MtoR(&GPR(_Rm_),EAX);
	sub32RfmM(EAX,&GPR(_Rd_));
	shiftDispatch[(CINST>>4)&0x7](EAX);
	push32M(&GPR(_Rd_));
	CALLFUNC(readMemU32);
	mov32RtoM(EAX,&GPR(_Rd_));

	x86SetJI8(x86Tmp[0]);
}


void recLDRiu(void){

	CHECK_CONDITION(0);
	DEBUG_PRINT

	mov32MtoR(&GPR(_Rm_),EAX);
	shiftDispatch[(CINST>>4)&0x7](EAX);
	push32M(&GPR(_Rd_));
	add32RtoM(EAX,&GPR(_Rd_));
	CALLFUNC(readMemU32);
	mov32RtoM(EAX,&GPR(_Rd_));

	x86SetJI8(x86Tmp[0]);
}

void recLDRip(void){

	CHECK_CONDITION(0);
	DEBUG_PRINT

	mov32MtoR(&GPR(_Rm_),EAX);
	sub32RfmM(EAX,&GPR(_Rd_));
	shiftDispatch[(CINST>>4)&0x7](EAX);
	push32M(&GPR(_Rd_));
	CALLFUNC(readMemU32);
	mov32RtoM(EAX,&GPR(_Rd_));

	x86SetJI8(x86Tmp[0]);
}
void recLDRiup(void){

	CHECK_CONDITION(0);
	DEBUG_PRINT

	mov32MtoR(&GPR(_Rm_),EAX);
	add32RtoM(EAX,&GPR(_Rd_));
	shiftDispatch[(CINST>>4)&0x7](EAX);
	push32M(&GPR(_Rd_));
	CALLFUNC(readMemU32);
	mov32RtoM(EAX,&GPR(_Rd_));

	x86SetJI8(x86Tmp[0]);
}

void recSTR(void){
	DEBUG_PRINT
}
void recSTRu(void){
	DEBUG_PRINT
}
void recSTRp(void){
	DEBUG_PRINT
}
void recSTRup(void){
	DEBUG_PRINT
}

void recSTRi(void){
	DEBUG_PRINT
}
void recSTRiu(void){
	DEBUG_PRINT
}
void recSTRip(void){
	DEBUG_PRINT
}
void recSTRiup(void){
	DEBUG_PRINT
}


void recLDRB(void){
	DEBUG_PRINT
}
void recLDRBu(void){
	DEBUG_PRINT
}
void recLDRBp(void){
	DEBUG_PRINT
}
void recLDRBup(void){

	DEBUG_PRINT
}

void recLDRBi(void){
	DEBUG_PRINT
}
void recLDRBiu(void){
	DEBUG_PRINT
}
void recLDRBip(void){
	DEBUG_PRINT
}
void recLDRBiup(void){
	DEBUG_PRINT
}

void recSTRB(void){
	DEBUG_PRINT
}
void recSTRBu(void){
	DEBUG_PRINT
}
void recSTRBp(void){
	DEBUG_PRINT
}
void recSTRBup(void){
	DEBUG_PRINT
}

void recSTRBi(void){
	DEBUG_PRINT
}
void recSTRBiu(void){
	DEBUG_PRINT
}
void recSTRBip(void){
	DEBUG_PRINT
}
void recSTRBiup(void){
	DEBUG_PRINT
}


void recLDRH(void){
	DEBUG_PRINT
}
void recLDRHu(void){
	DEBUG_PRINT
}
void recLDRHp(void){
	DEBUG_PRINT
}
void recLDRHup(void){
	DEBUG_PRINT
}

void recLDRHi(void){
	DEBUG_PRINT
}
void recLDRHiu(void){
	DEBUG_PRINT
}
void recLDRHip(void){
	DEBUG_PRINT
}
void recLDRHiup(void){
	DEBUG_PRINT
}

void recSTRH(void){
	DEBUG_PRINT
}
void recSTRHu(void){
	DEBUG_PRINT
}
void recSTRHp(void){
	DEBUG_PRINT
}
void recSTRHup(void){
	DEBUG_PRINT
}

void recSTRHi(void){
	DEBUG_PRINT
}
void recSTRHiu(void){
	DEBUG_PRINT
}
void recSTRHip(void){
	DEBUG_PRINT
}
void recSTRHiup(void){
	DEBUG_PRINT
}



void recLDRSB(void){
	DEBUG_PRINT
}
void recLDRSBu(void){
	DEBUG_PRINT
}
void recLDRSBp(void){
	DEBUG_PRINT
}
void recLDRSBup(void){
	DEBUG_PRINT
}

void recLDRSBi(void){
	DEBUG_PRINT
}
void recLDRSBiu(void){
	DEBUG_PRINT
}
void recLDRSBip(void){
	DEBUG_PRINT
}
void recLDRSBiup(void){
	DEBUG_PRINT
}

void recLDRSH(void){
	DEBUG_PRINT
}
void recLDRSHu(void){
	DEBUG_PRINT
}
void recLDRSHp(void){
	DEBUG_PRINT
}
void recLDRSHup(void){
	DEBUG_PRINT
}

void recLDRSHi(void){
	DEBUG_PRINT
}
void recLDRSHiu(void){
	DEBUG_PRINT
}
void recLDRSHip(void){
	DEBUG_PRINT
}
void recLDRSHiup(void){
	DEBUG_PRINT
}
