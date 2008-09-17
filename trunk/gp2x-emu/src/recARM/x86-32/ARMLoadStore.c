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
	DEBUG_PRINT();

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

	DEBUG_PRINT();
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
	DEBUG_PRINT();
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
	DEBUG_PRINT();
	pushI32(_Rn_);
	push32M(&GPR(_Rn_).sVal);
	CALLFUNC(loadMultRegs);
	add32ItoR(8,ESP);
	x86SetJI8(x86Tmp[0]);
}


void recLDM3(void){

}


void recLDR(void){

	DEBUG_PRINT();
	CHECK_CONDITION(0);

	mov32MtoR(&GPR(_Rm_),ECX);
	push32M(&GPR(_Rn_));
	sub32RfmM(ECX,&GPR(_Rd_));
	CALLFUNC(readMemU32);
	mov32RtoM(EAX,&GPR(_Rd_));

	x86SetJI8(x86Tmp[0]);
}
void recLDRu(void){

	DEBUG_PRINT();
	CHECK_CONDITION(0);

	mov32MtoR(&GPR(_Rm_),ECX);
	push32M(&GPR(_Rn_));
	add32RtoM(ECX,&GPR(_Rn_));
	CALLFUNC(readMemU32);
	mov32RtoM(EAX,&GPR(_Rd_));

	x86SetJI8(x86Tmp[0]);
}

void recLDRp(void){

	CHECK_CONDITION(0);
	DEBUG_PRINT();

	mov32MtoR(&GPR(_Rm_),ECX);
	sub32RfmM(ECX,&GPR(_Rn_));
	push32M(&GPR(_Rn_));
	CALLFUNC(readMemU32);
	mov32RtoM(EAX,&GPR(_Rd_));

	x86SetJI8(x86Tmp[0]);
}
void recLDRup(void){

	CHECK_CONDITION(0);
	DEBUG_PRINT();

	mov32MtoR(&GPR(_Rm_),ECX);
	add32RtoM(ECX,&GPR(_Rn_));
	push32M(&GPR(_Rn_));
	CALLFUNC(readMemU32);
	mov32RtoM(EAX,&GPR(_Rd_));

	x86SetJI8(x86Tmp[0]);
}


void recLDRi(void){

	CHECK_CONDITION(0);
	DEBUG_PRINT();

	mov32MtoR(&GPR(_Rm_),EAX);
	sub32RfmM(EAX,&GPR(_Rn_));
	shiftDispatch[(CINST>>4)&0x7](EAX);
	push32M(&GPR(_Rn_));
	CALLFUNC(readMemU32);
	mov32RtoM(EAX,&GPR(_Rd_));

	x86SetJI8(x86Tmp[0]);
}


void recLDRiu(void){

	CHECK_CONDITION(0);
	DEBUG_PRINT();

	mov32MtoR(&GPR(_Rm_),EAX);
	shiftDispatch[(CINST>>4)&0x7](EAX);
	push32M(&GPR(_Rn_));
	add32RtoM(EAX,&GPR(_Rn_));
	CALLFUNC(readMemU32);
	mov32RtoM(EAX,&GPR(_Rd_));

	x86SetJI8(x86Tmp[0]);
}

void recLDRip(void){

	CHECK_CONDITION(0);
	DEBUG_PRINT();

	mov32MtoR(&GPR(_Rm_),EAX);
	sub32RfmM(EAX,&GPR(_Rn_));
	shiftDispatch[(CINST>>4)&0x7](EAX);
	push32M(&GPR(_Rn_));
	CALLFUNC(readMemU32);
	mov32RtoM(EAX,&GPR(_Rd_));

	x86SetJI8(x86Tmp[0]);
}
void recLDRiup(void){

	CHECK_CONDITION(0);
	DEBUG_PRINT();

	mov32MtoR(&GPR(_Rm_),EAX);
	add32RtoM(EAX,&GPR(_Rn_));
	shiftDispatch[(CINST>>4)&0x7](EAX);
	push32M(&GPR(_Rn_));
	CALLFUNC(readMemU32);
	mov32RtoM(EAX,&GPR(_Rd_));

	x86SetJI8(x86Tmp[0]);
}


void recSTR(void){

	CHECK_CONDITION(0);
	DEBUG_PRINT();

	mov32MtoR(&GPR(_Rm_),ECX);
	push32M(&GPR(_Rd_));
	push32M(&GPR(_Rn_));
	sub32RfmM(ECX,&GPR(_Rn_));
	CALLFUNC(writeMemU32);

	x86SetJI8(x86Tmp[0]);
}


void recSTRu(void){

	DEBUG_PRINT();
	CHECK_CONDITION(0);

	mov32MtoR(&GPR(_Rm_), ECX);
	push32M(&GPR(_Rd_));
	push32M(&GPR(_Rn_));
	add32RtoM(ECX,&GPR(_Rn_));
	CALLFUNC(writeMemU32);
	x86SetJI8(x86Tmp[0]);
}



void recSTRp(void){

	DEBUG_PRINT();
	CHECK_CONDITION(0);

	mov32MtoR(&GPR(_Rm_),ECX);
	sub32RfmM(ECX,&GPR(_Rn_));
	push32M(&GPR(_Rd_));
	push32M(&GPR(_Rn_));
	CALLFUNC(writeMemU32);

	x86SetJI8(x86Tmp[0]);
}



void recSTRup(void){
	DEBUG_PRINT();
	CHECK_CONDITION(0);

	mov32MtoR(&GPR(_Rm_),ECX);
	add32RtoM(ECX,&GPR(_Rn_));
	push32M(&GPR(_Rd_));
	push32M(&GPR(_Rn_));
	CALLFUNC(writeMemU32);

	x86SetJI8(x86Tmp[0]);

}

void recSTRi(void){

	CHECK_CONDITION(0);
	DEBUG_PRINT();

	push32M(&GPR(_Rd_));
	mov32MtoR(&GPR(_Rm_),EAX);
	push32M(&GPR(_Rn_));
	shiftDispatch[(CINST>>4)&0x7](EAX);
	sub32RfmM(EAX,&GPR(_Rn_));
	CALLFUNC(writeMemU32);

	x86SetJI8(x86Tmp[0]);

}
void recSTRiu(void){

	CHECK_CONDITION(0)
	DEBUG_PRINT();

	push32M(&GPR(_Rd_));
	mov32MtoR(&GPR(_Rm_),EAX);
	push32M(&GPR(_Rn_));
	shiftDispatch[(CINST>>4)&0x7](EAX);
	add32RtoM(EAX,&GPR(_Rn_));
	CALLFUNC(writeMemU32);
	
	x86SetJI8(x86Tmp[0]);
}


void recSTRip(void){

	CHECK_CONDITION(0);
	DEBUG_PRINT();

	push32M(&GPR(_Rd_));
	mov32MtoR(&GPR(_Rm_),EAX);
	shiftDispatch[(CINST>>4)&0x7](EAX);
	sub32RfmM(EAX,&GPR(_Rn_));
	push32M(&GPR(_Rn_));
	CALLFUNC(writeMemU32);

	x86SetJI8(x86Tmp[0]);
}

void recSTRiup(void){

	CHECK_CONDITION(0);
	DEBUG_PRINT();

	push32M(&GPR(_Rd_));
	mov32MtoR(&GPR(_Rm_),EAX);
	shiftDispatch[(CINST>>4)&0x7](EAX);
	add32RtoM(EAX,&GPR(_Rn_));
	push32M(&GPR(_Rn_));
	CALLFUNC(writeMemU32);

	x86SetJI8(x86Tmp[0]);
}


void recLDRB(void){

	CHECK_CONDITION(0);
	DEBUG_PRINT();

	mov32MtoR(&GPR(_Rm_),ECX);
	push32M(&GPR(_Rn_));
	sub32RfmM(ECX,&GPR(_Rn_));
	CALLFUNC(readMemU8);
	movzxR8toR32(AL,EAX);
	mov32RtoM(EAX,&GPR(_Rd_));

	x86SetJI8(x86Tmp[0]);
}

void recLDRBu(void){

	DEBUG_PRINT();
	CHECK_CONDITION(0);

	mov32MtoR(&GPR(_Rm_),ECX);
	push32M(&GPR(_Rn_));
	add32RtoM(ECX,&GPR(_Rn_));
	CALLFUNC(readMemU8);
	movzxR8toR32(AL,EAX);
	mov32RtoM(EAX,&GPR(_Rd_));

	x86SetJI8(x86Tmp[0]);
}
void recLDRBp(void){

	CHECK_CONDITION(0);
	DEBUG_PRINT();

	mov32MtoR(&GPR(_Rm_),ECX);
	sub32RfmM(ECX,&GPR(_Rn_));
	push32M(&GPR(_Rn_));
	CALLFUNC(readMemU8);
	movzxR8toR32(AL,EAX);
	mov32RtoM(EAX,&GPR(_Rd_));

	x86SetJI8(x86Tmp[0]);
}
void recLDRBup(void){

	CHECK_CONDITION(0);
	DEBUG_PRINT();

	mov32MtoR(&GPR(_Rm_),ECX);
	add32RtoM(ECX,&GPR(_Rn_));
	push32M(&GPR(_Rn_));
	CALLFUNC(readMemU8);
	movzxR8toR32(AL,EAX);
	mov32RtoM(EAX,&GPR(_Rd_));

	x86SetJI8(x86Tmp[0]);
}

void recLDRBi(void){

	CHECK_CONDITION(0);
	DEBUG_PRINT();

	mov32MtoR(&GPR(_Rm_),EAX);
	sub32RfmM(EAX,&GPR(_Rn_));
	shiftDispatch[(CINST>>4)&0x7](EAX);
	push32M(&GPR(_Rn_));
	CALLFUNC(readMemU8);
	movzxR8toR32(AL,EAX);
	mov32RtoM(EAX,&GPR(_Rd_));

	x86SetJI8(x86Tmp[0]);
}

void recLDRBiu(void){

	CHECK_CONDITION(0);
	DEBUG_PRINT();

	mov32MtoR(&GPR(_Rm_),EAX);
	shiftDispatch[(CINST>>4)&0x7](EAX);
	push32M(&GPR(_Rn_));
	add32RtoM(EAX,&GPR(_Rn_));
	CALLFUNC(readMemU8);
	movzxR8toR32(AL,EAX);
	mov32RtoM(EAX,&GPR(_Rd_));

	x86SetJI8(x86Tmp[0]);
}

void recLDRBip(void){

	CHECK_CONDITION(0);
	DEBUG_PRINT();

	mov32MtoR(&GPR(_Rm_),EAX);
	sub32RfmM(EAX,&GPR(_Rn_));
	shiftDispatch[(CINST>>4)&0x7](EAX);
	push32M(&GPR(_Rn_));
	CALLFUNC(readMemU8);
	movzxR8toR32(AL,EAX);
	mov32RtoM(EAX,&GPR(_Rd_));

	x86SetJI8(x86Tmp[0]);
}

void recLDRBiup(void){

	CHECK_CONDITION(0);
	DEBUG_PRINT();

	mov32MtoR(&GPR(_Rm_),EAX);
	add32RtoM(EAX,&GPR(_Rn_));
	shiftDispatch[(CINST>>4)&0x7](EAX);
	push32M(&GPR(_Rn_));
	CALLFUNC(readMemU8);
	movzxR8toR32(AL,EAX);
	mov32RtoM(EAX,&GPR(_Rd_));

	x86SetJI8(x86Tmp[0]);
}

void recSTRB(void){

	CHECK_CONDITION(0);
	DEBUG_PRINT();

	mov32MtoR(&GPR(_Rm_),ECX);
	push32M(&GPR(_Rd_));
	push32M(&GPR(_Rn_));
	sub32RfmM(ECX,&GPR(_Rn_));
	CALLFUNC(writeMemU8);

	x86SetJI8(x86Tmp[0]);
}

void recSTRBu(void){

	DEBUG_PRINT();
	CHECK_CONDITION(0);

	mov32MtoR(&GPR(_Rm_), ECX);
	push32M(&GPR(_Rd_));
	push32M(&GPR(_Rn_));
	add32RtoM(ECX,&GPR(_Rn_));
	CALLFUNC(writeMemU8);
	x86SetJI8(x86Tmp[0]);
}

void recSTRBp(void){

	DEBUG_PRINT();
	CHECK_CONDITION(0);

	mov32MtoR(&GPR(_Rm_),ECX);
	sub32RfmM(ECX,&GPR(_Rn_));
	push32M(&GPR(_Rd_));
	push32M(&GPR(_Rn_));
	CALLFUNC(writeMemU8);

	x86SetJI8(x86Tmp[0]);
}

void recSTRBup(void){
	DEBUG_PRINT();
	CHECK_CONDITION(0);

	mov32MtoR(&GPR(_Rm_),ECX);
	add32RtoM(ECX,&GPR(_Rn_));
	push32M(&GPR(_Rd_));
	push32M(&GPR(_Rn_));
	CALLFUNC(writeMemU8);

	x86SetJI8(x86Tmp[0]);
}

void recSTRBi(void){
	CHECK_CONDITION(0);
	DEBUG_PRINT();

	push32M(&GPR(_Rd_));
	mov32MtoR(&GPR(_Rm_),EAX);
	push32M(&GPR(_Rn_));
	shiftDispatch[(CINST>>4)&0x7](EAX);
	sub32RfmM(EAX,&GPR(_Rn_));
	CALLFUNC(writeMemU8);

	x86SetJI8(x86Tmp[0]);
}

void recSTRBiu(void){
	CHECK_CONDITION(0);
	DEBUG_PRINT();

	push32M(&GPR(_Rd_));
	push32M(&GPR(_Rn_));
	mov32MtoR(&GPR(_Rm_),EAX);
	shiftDispatch[(CINST>>4)&0x7](EAX);
	add32RtoM(EAX,&GPR(_Rn_));
	CALLFUNC(writeMemU8);

	x86SetJI8(x86Tmp[0]);
}
void recSTRBip(void){

	CHECK_CONDITION(0);
	DEBUG_PRINT();

	push32M(&GPR(_Rd_));
	mov32MtoR(&GPR(_Rm_),EAX);
	shiftDispatch[(CINST>>4)&0x7](EAX);
	sub32RfmM(EAX,&GPR(_Rn_));
	push32M(&GPR(_Rn_));
	CALLFUNC(writeMemU8);

	x86SetJI8(x86Tmp[0]);
}
void recSTRBiup(void){

	CHECK_CONDITION(0);
	DEBUG_PRINT();

	push32M(&GPR(_Rd_));
	mov32MtoR(&GPR(_Rm_),EAX);
	shiftDispatch[(CINST>>4)&0x7](EAX);
	add32RtoM(EAX,&GPR(_Rn_));
	push32M(&GPR(_Rn_));
	CALLFUNC(writeMemU8);

	x86SetJI8(x86Tmp[0]);
}

void recLDRH(void){

	DEBUG_PRINT();
	CHECK_CONDITION(0);

	mov32MtoR(&GPR(_Rm_),ECX);
	push32M(&GPR(_Rn_));
	sub32RfmM(ECX,&GPR(_Rd_));
	CALLFUNC(readMemU16);
	movzxR16toR32(AX,EAX);
	mov32RtoM(EAX,&GPR(_Rd_));

	x86SetJI8(x86Tmp[0]);
}
void recLDRHu(void){

	CHECK_CONDITION(0);
	DEBUG_PRINT();

	mov32MtoR(&GPR(_Rm_),ECX);
	push32M(&GPR(_Rn_));
	sub32RfmM(ECX,&GPR(_Rn_));
	CALLFUNC(readMemU16);
	movzxR16toR32(AX,EAX);
	mov32RtoM(EAX,&GPR(_Rd_));

	x86SetJI8(x86Tmp[0]);
}
void recLDRHp(void){

	CHECK_CONDITION(0);
	DEBUG_PRINT();

	mov32MtoR(&GPR(_Rm_),ECX);
	sub32RfmM(ECX,&GPR(_Rn_));
	push32M(&GPR(_Rn_));
	CALLFUNC(readMemU16);
	movzxR16toR32(AX,EAX);
	mov32RtoM(EAX,&GPR(_Rd_));

	x86SetJI8(x86Tmp[0]);
}
void recLDRHup(void){

	CHECK_CONDITION(0);
	DEBUG_PRINT();

	mov32MtoR(&GPR(_Rm_),ECX);
	add32RtoM(ECX,&GPR(_Rn_));
	push32M(&GPR(_Rn_));
	CALLFUNC(readMemU16);
	movzxR16toR32(AX,EAX);
	mov32RtoM(EAX,&GPR(_Rd_));

	x86SetJI8(x86Tmp[0]);
}

void recLDRHi(void){

	CHECK_CONDITION(0);
	DEBUG_PRINT();

	mov32MtoR(&GPR(_Rm_),EAX);
	sub32RfmM(EAX,&GPR(_Rn_));
	shiftDispatch[(CINST>>4)&0x7](EAX);
	push32M(&GPR(_Rn_));
	CALLFUNC(readMemU16);
	movzxR16toR32(AX,EAX);
	mov32RtoM(EAX,&GPR(_Rd_));

	x86SetJI8(x86Tmp[0]);
}
void recLDRHiu(void){

	CHECK_CONDITION(0);
	DEBUG_PRINT();

	mov32MtoR(&GPR(_Rm_),EAX);
	shiftDispatch[(CINST>>4)&0x7](EAX);
	push32M(&GPR(_Rn_));
	add32RtoM(EAX,&GPR(_Rn_));
	CALLFUNC(readMemU16);
	movzxR16toR32(AX,EAX);
	mov32RtoM(EAX,&GPR(_Rd_));

	x86SetJI8(x86Tmp[0]);
}
void recLDRHip(void){

	CHECK_CONDITION(0);
	DEBUG_PRINT();

	mov32MtoR(&GPR(_Rm_),EAX);
	sub32RfmM(EAX,&GPR(_Rn_));
	shiftDispatch[(CINST>>4)&0x7](EAX);
	push32M(&GPR(_Rn_));
	CALLFUNC(readMemU16);
	movzxR16toR32(AX,EAX);
	mov32RtoM(EAX,&GPR(_Rd_));

	x86SetJI8(x86Tmp[0]);
}
void recLDRHiup(void){

	CHECK_CONDITION(0);
	DEBUG_PRINT();

	mov32MtoR(&GPR(_Rm_),EAX);
	add32RtoM(EAX,&GPR(_Rn_));
	shiftDispatch[(CINST>>4)&0x7](EAX);
	push32M(&GPR(_Rn_));
	CALLFUNC(readMemU16);
	movzxR16toR32(AX,EAX);
	mov32RtoM(EAX,&GPR(_Rd_));

	x86SetJI8(x86Tmp[0]);
}

void recSTRH(void){

	CHECK_CONDITION(0);
	DEBUG_PRINT();

	mov32MtoR(&GPR(_Rm_),ECX);
	push32M(&GPR(_Rd_));
	push32M(&GPR(_Rn_));
	sub32RfmM(ECX,&GPR(_Rn_));
	CALLFUNC(writeMemU16);

	x86SetJI8(x86Tmp[0]);
}
void recSTRHu(void){

	DEBUG_PRINT();
	CHECK_CONDITION(0);

	mov32MtoR(&GPR(_Rm_), ECX);
	push32M(&GPR(_Rd_));
	push32M(&GPR(_Rn_));
	add32RtoM(ECX,&GPR(_Rn_));
	CALLFUNC(writeMemU16);

	x86SetJI8(x86Tmp[0]);
}

void recSTRHp(void){

	DEBUG_PRINT();
	CHECK_CONDITION(0);

	mov32MtoR(&GPR(_Rm_),ECX);
	sub32RfmM(ECX,&GPR(_Rn_));
	push32M(&GPR(_Rd_));
	push32M(&GPR(_Rn_));
	CALLFUNC(writeMemU16);

	x86SetJI8(x86Tmp[0]);
}

void recSTRHup(void){

	DEBUG_PRINT();
	CHECK_CONDITION(0);

	mov32MtoR(&GPR(_Rm_),ECX);
	add32RtoM(ECX,&GPR(_Rn_));
	push32M(&GPR(_Rd_));
	push32M(&GPR(_Rn_));
	CALLFUNC(writeMemU16);

	x86SetJI8(x86Tmp[0]);
}

void recSTRHi(void){

	CHECK_CONDITION(0);
	DEBUG_PRINT();

	push32M(&GPR(_Rd_));
	mov32MtoR(&GPR(_Rm_),EAX);
	push32M(&GPR(_Rn_));
	shiftDispatch[(CINST>>4)&0x7](EAX);
	sub32RfmM(EAX,&GPR(_Rn_));
	CALLFUNC(writeMemU32);

	x86SetJI8(x86Tmp[0]);
}

void recSTRHiu(void){

	CHECK_CONDITION(0)
	DEBUG_PRINT();

	push32M(&GPR(_Rd_));
	mov32MtoR(&GPR(_Rm_),EAX);
	push32M(&GPR(_Rn_));
	shiftDispatch[(CINST>>4)&0x7](EAX);
	add32RtoM(EAX,&GPR(_Rn_));
	CALLFUNC(writeMemU16);
	
	x86SetJI8(x86Tmp[0]);
}

void recSTRHip(void){

	CHECK_CONDITION(0);
	DEBUG_PRINT();

	push32M(&GPR(_Rd_));
	mov32MtoR(&GPR(_Rm_),EAX);
	shiftDispatch[(CINST>>4)&0x7](EAX);
	sub32RfmM(EAX,&GPR(_Rn_));
	push32M(&GPR(_Rn_));
	CALLFUNC(writeMemU16);

	x86SetJI8(x86Tmp[0]);
}
void recSTRHiup(void){

	CHECK_CONDITION(0);
	DEBUG_PRINT();

	push32M(&GPR(_Rd_));
	mov32MtoR(&GPR(_Rm_),EAX);
	shiftDispatch[(CINST>>4)&0x7](EAX);
	add32RtoM(EAX,&GPR(_Rn_));
	push32M(&GPR(_Rn_));
	CALLFUNC(writeMemU16);

	x86SetJI8(x86Tmp[0]);
}

void recLDRSB(void){

	CHECK_CONDITION(0);
	DEBUG_PRINT();

	mov32MtoR(&GPR(_Rm_),ECX);
	push32M(&GPR(_Rn_));
	sub32RfmM(ECX,&GPR(_Rn_));
	CALLFUNC(readMemU8);
	movsxR8toR32(AL,EAX);
	mov32RtoM(EAX,&GPR(_Rd_));

	x86SetJI8(x86Tmp[0]);
}
void recLDRSBu(void){

	CHECK_CONDITION(0);
	DEBUG_PRINT();

	mov32MtoR(&GPR(_Rm_),ECX);
	push32M(&GPR(_Rn_));
	add32RtoM(ECX,&GPR(_Rn_));
	CALLFUNC(readMemU8);
	movsxR8toR32(AL,EAX);
	mov32RtoM(EAX,&GPR(_Rd_));

	x86SetJI8(x86Tmp[0]);

}

void recLDRSBp(void){

	CHECK_CONDITION(0);
	DEBUG_PRINT();

	mov32MtoR(&GPR(_Rm_),ECX);
	sub32RfmM(ECX,&GPR(_Rn_));
	push32M(&GPR(_Rn_));
	CALLFUNC(readMemU8);
	movsxR8toR32(AL,EAX);
	mov32RtoM(EAX,&GPR(_Rd_));

	x86SetJI8(x86Tmp[0]);

}
void recLDRSBup(void){

	mov32MtoR(&GPR(_Rm_),ECX);
	add32RtoM(ECX,&GPR(_Rn_));
	push32M(&GPR(_Rn_));
	CALLFUNC(readMemU8);
	movsxR8toR32(AL,EAX);
	mov32RtoM(EAX,&GPR(_Rd_));

	x86SetJI8(x86Tmp[0]);
}

void recLDRSBi(void){

	CHECK_CONDITION(0);
	DEBUG_PRINT();

	mov32MtoR(&GPR(_Rm_),EAX);
	push32M(&GPR(_Rn_));
	shiftDispatch[(CINST>>4)&0x7](EAX);
	sub32RfmM(EAX,&GPR(_Rn_));
	CALLFUNC(readMemU8);
	movsxR8toR32(AL,EAX);
	mov32RtoM(EAX,&GPR(_Rd_));

	x86SetJI8(x86Tmp[0]);
}

void recLDRSBiu(void){

	CHECK_CONDITION(0);
	DEBUG_PRINT();

	mov32MtoR(&GPR(_Rm_),EAX);
	push32M(&GPR(_Rn_));
	shiftDispatch[(CINST>>4)&0x7](EAX);
	add32RtoM(EAX,&GPR(_Rn_));
	CALLFUNC(readMemU8);
	movsxR8toR32(AL,EAX);
	mov32RtoM(EAX,&GPR(_Rd_));

	x86SetJI8(x86Tmp[0]);
}

void recLDRSBip(void){

	CHECK_CONDITION(0);
	DEBUG_PRINT();

	mov32MtoR(&GPR(_Rm_),EAX);
	sub32RfmM(EAX,&GPR(_Rn_));
	shiftDispatch[(CINST>>4)&0x7](EAX);
	push32M(&GPR(_Rn_));
	CALLFUNC(readMemU8);
	movsxR8toR32(AL,EAX);
	mov32RtoM(EAX,&GPR(_Rd_));

	x86SetJI8(x86Tmp[0]);
}
void recLDRSBiup(void){

	CHECK_CONDITION(0);
	DEBUG_PRINT();

	mov32MtoR(&GPR(_Rm_),EAX);
	add32RtoM(EAX,&GPR(_Rn_));
	shiftDispatch[(CINST>>4)&0x7](EAX);
	push32M(&GPR(_Rn_));
	CALLFUNC(readMemU8);
	movsxR8toR32(AL,EAX);
	mov32RtoM(EAX,&GPR(_Rd_));

	x86SetJI8(x86Tmp[0]);
}

void recLDRSH(void){

	DEBUG_PRINT();
	CHECK_CONDITION(0);

	mov32MtoR(&GPR(_Rm_),ECX);
	push32M(&GPR(_Rn_));
	sub32RfmM(ECX,&GPR(_Rd_));
	CALLFUNC(readMemU16);
	movsxR16toR32(AX,EAX);
	mov32RtoM(EAX,&GPR(_Rd_));

	x86SetJI8(x86Tmp[0]);
}

void recLDRSHu(void){

	CHECK_CONDITION(0);
	DEBUG_PRINT();

	mov32MtoR(&GPR(_Rm_),ECX);
	push32M(&GPR(_Rn_));
	add32RtoM(ECX,&GPR(_Rn_));
	CALLFUNC(readMemU16);
	movsxR16toR32(AX,EAX);
	mov32RtoM(EAX,&GPR(_Rd_));

	x86SetJI8(x86Tmp[0]);
}
void recLDRSHp(void){

	CHECK_CONDITION(0);
	DEBUG_PRINT();

	mov32MtoR(&GPR(_Rm_),ECX);
	sub32RfmM(ECX,&GPR(_Rn_));
	push32M(&GPR(_Rn_));
	CALLFUNC(readMemU16);
	movsxR16toR32(AX,EAX);
	mov32RtoM(EAX,&GPR(_Rd_));

	x86SetJI8(x86Tmp[0]);
}

void recLDRSHup(void){

	CHECK_CONDITION(0);
	DEBUG_PRINT();

	mov32MtoR(&GPR(_Rm_),ECX);
	add32RtoM(ECX,&GPR(_Rn_));
	push32M(&GPR(_Rn_));
	CALLFUNC(readMemU16);
	movsxR16toR32(AX,EAX);
	mov32RtoM(EAX,&GPR(_Rd_));

	x86SetJI8(x86Tmp[0]);
}

void recLDRSHi(void){

	CHECK_CONDITION(0);
	DEBUG_PRINT();

	mov32MtoR(&GPR(_Rm_),EAX);
	push32M(&GPR(_Rn_));
	shiftDispatch[(CINST>>4)&0x7](EAX);
	sub32RfmM(EAX,&GPR(_Rn_));
	CALLFUNC(readMemU16);
	movsxR16toR32(AX,EAX);
	mov32RtoM(EAX,&GPR(_Rd_));

	x86SetJI8(x86Tmp[0]);
}
void recLDRSHiu(void){

	CHECK_CONDITION(0);
	DEBUG_PRINT();

	mov32MtoR(&GPR(_Rm_),EAX);
	push32M(&GPR(_Rn_));
	shiftDispatch[(CINST>>4)&0x7](EAX);
	add32RtoM(EAX,&GPR(_Rn_));
	CALLFUNC(readMemU16);
	movsxR16toR32(AX,EAX);
	mov32RtoM(EAX,&GPR(_Rd_));

	x86SetJI8(x86Tmp[0]);
}
void recLDRSHip(void){

	CHECK_CONDITION(0);
	DEBUG_PRINT();

	mov32MtoR(&GPR(_Rm_),EAX);
	shiftDispatch[(CINST>>4)&0x7](EAX);
	sub32RfmM(EAX,&GPR(_Rn_));
	push32M(&GPR(_Rn_));
	CALLFUNC(readMemU16);
	movsxR16toR32(AX,EAX);
	mov32RtoM(EAX,&GPR(_Rd_));

	x86SetJI8(x86Tmp[0]);
}
void recLDRSHiup(void){

	CHECK_CONDITION(0);
	DEBUG_PRINT();

	mov32MtoR(&GPR(_Rm_),EAX);
	shiftDispatch[(CINST>>4)&0x7](EAX);
	add32RtoM(EAX,&GPR(_Rn_));
	push32M(&GPR(_Rn_));
	CALLFUNC(readMemU16);
	movsxR16toR32(AX,EAX);
	mov32RtoM(EAX,&GPR(_Rd_));

	x86SetJI8(x86Tmp[0]);
}
