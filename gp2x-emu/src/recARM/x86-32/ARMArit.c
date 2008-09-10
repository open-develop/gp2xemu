#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arm_emu.h>
#include <ARMx86.h>
#include <ARMArit.h>
#include <x86.h>
/*#warning "S-flag still has to be added"
 */



/* table to get the right value to shift the operand 
 * only even values are allowed and we use the shift field in
 * the instruction as index for the table 
 */

const u32 shift_table[16]={0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30};
const u32 flagsTable[]={0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xa,0xb,0xc,0xd,0xe,0xf};


void (*shiftDispatch[])( x86GPReg ) = {
	leftShiftImm, leftShiftReg, rightShiftImm, rightShiftReg,
	aritShiftImm, aritShiftReg, rightRotImm, rightRotReg,
};

void leftShiftImm(x86GPReg reg){
	mov32ItoR((CPU.currentInst>>7)&0x1fU,ECX);
	shl32RCL(reg);
}


void rightShiftImm(x86GPReg reg){
	mov32ItoR((CPU.currentInst>>7)&0x1fU,ECX);
	shr32RCL(reg);
}

void leftShiftReg(x86GPReg reg){
	mov32ItoR(GPR(_Rs_).sVal,ECX);
	shl32RCL(reg);
}

void rightShiftReg(x86GPReg reg){
	mov32ItoR(GPR(_Rs_).sVal,ECX);
	shr32RCL(reg);
}

void aritShiftImm(x86GPReg reg){
	mov32ItoR((CPU.currentInst>>7)&0x1fu,ECX);
	sar32RCL(reg);
}

void aritShiftReg(x86GPReg reg){
	mov32ItoR(GPR(_Rs_).sVal,ECX);
	sar32RCL(reg);
}

void rightRotImm(x86GPReg reg){

	__register u32 imm=((CPU.currentInst>>7)&0x1fU);

	if(!imm)
		shr32R1(reg);

	else{
		mov32ItoR(imm,ECX);
		ror32RCL(reg);
	}
	return;
}

void rightRotReg(x86GPReg reg){
	mov32ItoR(GPR(_Rs_).sVal,ECX);
	ror32RCL(reg);
}




void recADDi(void){

	DEBUG_PRINT
	CHECK_CONDITION(0);
	mov32ItoR(_IMM_,EAX);
	ror32R(EAX,shift_table[_RORIMM_]);
	mov32ItoR(GPR(_Rn_).sVal,ECX);
	add32RtoR(EAX,ECX);
	
	if(_UPDATE_FLAGS_){
		UPDATE_CARRY(1);
		UPDATE_ZERO(1);
		UPDATE_OVERF(1);
		UPDATE_SIGN(1);
	}
	mov32RtoM(ECX,&GPR(_Rd_));
	x86SetJI8(x86Tmp[0]);
	return;
}

/* logical shifts */
void recADDs(void){
	
	__register u32 val=((CPU.currentInst>>4)&0x7U);
	/*__register u32 imm=((CPU.currentInst>>7)&0x1fU);
	 */

	/* preload Rm/Rn registers, and check condition 
	 */

	DEBUG_PRINT
	CHECK_CONDITION(0)
	mov32ItoR(GPR(_Rm_).sVal,EAX);
	mov32ItoR(GPR(_Rn_).sVal,EDX);
	shiftDispatch[val](EAX);
	add32RtoR(EAX,EDX);
	mov32RtoM(EDX,&GPR(_Rd_));

	if(_UPDATE_FLAGS_){
		UPDATE_CARRY(1);
		UPDATE_ZERO(1);
		UPDATE_OVERF(1);
		UPDATE_SIGN(1);
	}
	x86SetJI8(x86Tmp[0]);
	return;
}



void recADCi(void){
	
	DEBUG_PRINT
	CHECK_CONDITION(0)
	mov32ItoR(_IMM_,EAX);
	ror32R(EAX,shift_table[_RORIMM_]);
	mov32ItoR(GPR(_Rn_).sVal,ECX);
	bt32I8toM(CARRY,&CPSR);
	adc32RtoR(EAX,ECX);
	mov32RtoM(ECX,&GPR(_Rd_));

	if(_UPDATE_FLAGS_){

	}
	x86SetJI8(x86Tmp[0]);
	return;
}


void recADCs(void){

	__register u32 val=((CPU.currentInst>>4)&0x7U);
	/*__register u32 imm=((CPU.currentInst>>7)&0x1fU);
	 */

	/* preload Rm/Rn registers, and check condition
	 */
	DEBUG_PRINT
	CHECK_CONDITION(0)
	mov32ItoR(GPR(_Rm_).sVal,EAX);
	mov32ItoR(GPR(_Rn_).sVal,EDX);
	shiftDispatch[val](EAX);
	bt32I8toM(CARRY,&CPSR);
	adc32RtoR(EAX,EDX);
	mov32RtoM(EDX,&GPR(_Rd_));
	if(_UPDATE_FLAGS_){
	}
	x86SetJI8(x86Tmp[0]);
	return;
}


void recANDi(void){

	DEBUG_PRINT
	CHECK_CONDITION(0)
	mov32ItoR(_IMM_,EAX);
	ror32R(EAX,shift_table[_RORIMM_]);
	if(_UPDATE_FLAGS_)
		UPDATE_CARRY(1);

	mov32ItoR(GPR(_Rn_).sVal,ECX);
	and32RtoR(EAX,ECX);
	SAVE_CARRY(BL);
	mov32RtoM(ECX, &GPR(_Rd_));
	if(_UPDATE_FLAGS_){
		UPDATE_SIGN(1);
		UPDATE_ZERO(1);
	}
	x86SetJI8(x86Tmp[0]);
}


void recANDs(void){

	__register u32 val=((CPU.currentInst>>4)&0x7U);

	/* preload Rm/Rn registers, and check condition
	 */
	DEBUG_PRINT
	CHECK_CONDITION(0)
	mov32ItoR(GPR(_Rm_).sVal,EAX);
	mov32ItoR(GPR(_Rn_).sVal,EDX);
	shiftDispatch[val](EAX);
	if(_UPDATE_FLAGS_)
		UPDATE_CARRY(1);

	and32RtoR(EAX,EDX);
	mov32RtoM(EDX,&GPR(_Rd_));
	if(_UPDATE_FLAGS_){
		UPDATE_ZERO(1);
		UPDATE_SIGN(1);
	}
	x86SetJI8(x86Tmp[0]);
}




void recSUBi(void){

	DEBUG_PRINT
	CHECK_CONDITION(0)
	mov32ItoR(_IMM_,EAX);
	ror32R(EAX,shift_table[_RORIMM_]);
	mov32ItoR(GPR(_Rn_).sVal,ECX);
	sub32RfmR(EAX,ECX);
	mov32RtoM(ECX,&GPR(_Rd_));
	if(_UPDATE_FLAGS_){
		INVERSE_CARRY(1);
		UPDATE_OVERF(1);
		UPDATE_SIGN(1);
		UPDATE_ZERO(1);
	}
	x86SetJI8(x86Tmp[0]);
}


void recSUBs(void){

	__register u32 val=((CPU.currentInst>>4)&0x7U);

	/* preload Rm/Rn registers, and check condition*/
	CHECK_CONDITION(0)
	mov32ItoR(GPR(_Rm_).sVal,EAX);
	mov32ItoR(GPR(_Rn_).sVal,EDX);
	shiftDispatch[val](EAX);
	sub32RfmR(EAX,EDX);
	mov32RtoM(EDX,&GPR(_Rd_));
	if(_UPDATE_FLAGS_){
		INVERSE_CARRY(1);
		UPDATE_SIGN(1);
		UPDATE_OVERF(1);
		UPDATE_ZERO(1);
	}
	x86SetJI8(x86Tmp[0]);
}


	


void recEORi(void){

	DEBUG_PRINT
	CHECK_CONDITION(0)
	mov32ItoR(_IMM_,EAX);
	ror32R(EAX,shift_table[_RORIMM_]);
	if(_UPDATE_FLAGS_)
		UPDATE_CARRY(1);
	mov32ItoR(GPR(_Rn_).sVal,ECX);
	xor32RtoR(EAX,ECX);
	mov32RtoM(ECX,&GPR(_Rd_));
	if(_UPDATE_FLAGS_){
		UPDATE_SIGN(1);
		UPDATE_ZERO(1);
	}
	x86SetJI8(x86Tmp[0]);
}


void recEORs(void){

	__register u32 val=((CPU.currentInst>>4)&0x7U);
	/*__register u32 imm=((CPU.currentInst>>7)&0x1fU);
	 */

	/* preload Rm/Rn registers, and check condition*/
	DEBUG_PRINT
	CHECK_CONDITION(0)
	mov32ItoR(GPR(_Rm_).sVal,EAX);
	mov32ItoR(GPR(_Rn_).sVal,EDX);
	shiftDispatch[val](EAX);
	if(_UPDATE_FLAGS_)
		UPDATE_CARRY(1);
	xor32RtoR(EAX,EDX);
	mov32RtoM(EDX,&GPR(_Rd_));
	if(_UPDATE_FLAGS_){
		UPDATE_SIGN(1);
		UPDATE_ZERO(1);
	}
	x86SetJI8(x86Tmp[0]);
}

		
void recORRi(void){

	DEBUG_PRINT
	CHECK_CONDITION(0)
	mov32ItoR(_IMM_,EAX);
	ror32R(EAX,shift_table[_RORIMM_]);
	if(_UPDATE_FLAGS_)
		UPDATE_CARRY(1);
	mov32ItoR(GPR(_Rn_).sVal,ECX);
	or32RtoR(EAX,ECX);
	mov32RtoM(ECX,&GPR(_Rd_));
	if(_UPDATE_FLAGS_){
		UPDATE_SIGN(1);
		UPDATE_ZERO(1);
	}
	x86SetJI8(x86Tmp[0]);
	return;
}

void recORRs(void){

	__register u32 val=((CPU.currentInst>>4)&0x7U);
	/*__register u32 imm=((CPU.currentInst>>7)&0x1fU);
	 */

	/* preload Rm/Rn registers, and check condition*/
	DEBUG_PRINT
	CHECK_CONDITION(0)
	mov32ItoR(GPR(_Rm_).sVal,EAX);
	mov32ItoR(GPR(_Rn_).sVal,EDX);
	shiftDispatch[val](EAX);
	if(_UPDATE_FLAGS_)
		UPDATE_CARRY(1);
	or32RtoR(EAX,EDX);
	mov32RtoM(EDX,&GPR(_Rd_));
	if(_UPDATE_FLAGS_){
		UPDATE_SIGN(1);
		UPDATE_ZERO(1);
	}
	x86SetJI8(x86Tmp[0]);
	return;
}


void recRSBi(void){

	DEBUG_PRINT
	CHECK_CONDITION(0)
	mov32ItoR(_IMM_,EAX);
	ror32R(EAX,shift_table[_RORIMM_]);
	mov32ItoR(GPR(_Rn_).sVal,ECX);
	sub32RfmR(ECX,EAX);
	mov32RtoM(EAX,&GPR(_Rd_));
	if(_UPDATE_FLAGS_){
		INVERSE_CARRY(1);
		UPDATE_SIGN(1);
		UPDATE_ZERO(1);
		UPDATE_OVERF(1);
	}
	x86SetJI8(x86Tmp[0]);
	return;
}

void recRSBs(void){

	__register u32 val=((CPU.currentInst>>4)&0x7U);
	/*__register u32 imm=((CPU.currentInst>>7)&0x1fU);
	 */

	/* preload Rm/Rn registers, and check condition
	 */
	DEBUG_PRINT
	CHECK_CONDITION(0)
	mov32ItoR(GPR(_Rm_).sVal,EAX);
	mov32ItoR(GPR(_Rn_).sVal,EDX);
	shiftDispatch[val](EAX);
	sub32RfmR(EDX,EAX);
	mov32RtoM(EAX,&GPR(_Rd_));

	if(_UPDATE_FLAGS_){
		INVERSE_CARRY(1);
		UPDATE_SIGN(1);
		UPDATE_OVERF(1);
		UPDATE_ZERO(1);
	}
	x86SetJI8(x86Tmp[0]);
	return;
}


void recRSCi(void){

	DEBUG_PRINT
	CHECK_CONDITION(0)
	mov32ItoR(_IMM_,EAX);
	ror32R(EAX,shift_table[_RORIMM_]);
	mov32ItoR(GPR(_Rn_).sVal,ECX);
	bt32I8toM(CARRY,&CPSR);
	sbb32RfmR(ECX,EAX);
	mov32RtoM(EAX,&GPR(_Rd_));

	if(_UPDATE_FLAGS_){
		INVERSE_CARRY(1);
		UPDATE_SIGN(1);
		UPDATE_OVERF(1);
		UPDATE_ZERO(1);
	}
	x86SetJI8(x86Tmp[0]);
	return;
}

void recRSCs(void){

	__register u32 val=((CPU.currentInst>>4)&0x7U);
	/*__register u32 imm=((CPU.currentInst>>7)&0x1fU);
	 */

	/* preload Rm/Rn registers, and check condition*/
	DEBUG_PRINT
	CHECK_CONDITION(0)
	mov32ItoR(GPR(_Rm_).sVal,EAX);
	mov32ItoR(GPR(_Rn_).sVal,EDX);
	shiftDispatch[val](EAX);
	bt32I8toM(CARRY,&CPSR);
	sbb32RfmR(ECX,EAX);
	mov32RtoM(EAX,&GPR(_Rd_));

	if(_UPDATE_FLAGS_){
		INVERSE_CARRY(1);
		UPDATE_SIGN(1);
		UPDATE_OVERF(1);
		UPDATE_ZERO(1);
	}
	x86SetJI8(x86Tmp[0]);
	return;
}


void recSBCi(void){

	DEBUG_PRINT
	CHECK_CONDITION(0)
	mov32ItoR(_IMM_,EAX);
	ror32R(EAX,shift_table[_RORIMM_]);
	mov32ItoR(GPR(_Rn_).sVal,ECX);
	btc32I8toM(CARRY,&CPSR);
	btc32I8toM(CARRY,&CPSR);
	sbb32RfmR(EAX,ECX);
	mov32RtoM(ECX,&GPR(_Rd_));
	if(_UPDATE_FLAGS_){
		INVERSE_CARRY(1);
		UPDATE_ZERO(1);
		UPDATE_OVERF(1);
		UPDATE_ZERO(1);
	}
	x86SetJI8(x86Tmp[0]);
	return;

}

void recSBCs(void){

	__register u32 val=((CPU.currentInst>>4)&0x7U);
	/*__register u32 imm=((CPU.currentInst>>7)&0x1fU);
	 */

	/* preload Rm/Rn registers, and check condition*/
	DEBUG_PRINT
	CHECK_CONDITION(0)
	mov32ItoR(GPR(_Rm_).sVal,EAX);
	mov32ItoR(GPR(_Rn_).sVal,EDX);
	shiftDispatch[val](EAX);
	btc32I8toM(CARRY,&CPSR);
	btc32I8toM(CARRY,&CPSR);
	sbb32RfmR(EAX,EDX);
	mov32RtoM(EDX,&GPR(_Rd_));
	if(_UPDATE_FLAGS_){
		INVERSE_CARRY(1);
		UPDATE_SIGN(1);
		UPDATE_ZERO(1);
		UPDATE_OVERF(1);
	}
	x86SetJI8(x86Tmp[0]);
	return;
}


void recCLZ(void){
	DEBUG_PRINT
	CHECK_CONDITION(0)
	mov32ItoR(GPR(_Rm_).sVal,EAX);
	bsr32RtoR(EAX,ECX);
	sub32IfmR(32,ECX);
	neg32R(ECX);
	mov32RtoM(ECX,&GPR(_Rd_));
	x86SetJI8(x86Tmp[0]);
	return;
}

void recBICi(void){

	DEBUG_PRINT
	CHECK_CONDITION(0)
	mov32ItoR(_IMM_,EAX);
	ror32R(EAX,shift_table[_RORIMM_]);
	if(_UPDATE_FLAGS_)
		UPDATE_CARRY(1);
	mov32ItoR(GPR(_Rn_).sVal,ECX);
	not32R(EAX);
	and32RtoR(EAX,ECX);
	mov32RtoM(ECX,&GPR(_Rd_));
	if(_UPDATE_FLAGS_){
		/*UPDATE_CARRY(1);
		 */
		UPDATE_SIGN(1);
		UPDATE_ZERO(1);
	}
	x86SetJI8(x86Tmp[0]);
	return;
}


void recBICs(void){

	__register u32 val=((CPU.currentInst>>4)&0x7U);
	/*__register u32 imm=((CPU.currentInst>>7)&0x1fU);
	 */

	DEBUG_PRINT
	/* preload Rm/Rn registers, and check condition*/
	CHECK_CONDITION(0)
	mov32ItoR(GPR(_Rm_).sVal,EAX);
	mov32ItoR(GPR(_Rn_).sVal,EDX);
	shiftDispatch[val](EAX);
	if(_UPDATE_FLAGS_)
		UPDATE_CARRY(1);
	not32R(EAX);
	and32RtoR(EAX,EDX);
	mov32RtoM(EDX,&GPR(_Rd_));
	if(_UPDATE_FLAGS_){
		UPDATE_SIGN(1);
		UPDATE_ZERO(1);
	}
	x86SetJI8(x86Tmp[0]);
	return;
}

void recMOVi(void){

	CHECK_CONDITION(0);
	DEBUG_PRINT
	mov32ItoR(_IMM_,EAX);
	ror32R(EAX,shift_table[_RORIMM_]);
	if(_UPDATE_FLAGS_)
		UPDATE_CARRY(1);
	mov32RtoM(EAX,&GPR(_Rd_));
	if(_UPDATE_FLAGS_){
		test32RtoR(EAX,EAX);
		UPDATE_ZERO(1);
		UPDATE_SIGN(1);
	}
	x86SetJI8(x86Tmp[0]);
	return;
}


void recMOVs(void){

	__register u32 val=((CPU.currentInst>>4)&0x3U);
	/*__register u32 imm=((CPU.currentInst>>7)&0x1fU);
	 */


	DEBUG_PRINT
	CHECK_CONDITION(0);
	mov32ItoR(GPR(_Rm_).sVal,EAX);
#if 0
	switch(val){
		/* what to do if the shift is 0, actually we could omit shifting there! */
	case 0:case 2: 
			mov32ItoR(ECX,imm);
			val==0?shl32RCL(EAX):shr32RCL(EAX);break;
	case 1:case 3:
			mov32ItoR(ECX,GPR(_Rs_).sVal);
			val==1?shl32RCL(EAX):shr32RCL(EAX);break;
	case 4:
			mov32ItoR(ECX,imm);
			sar32RCL(EAX);break;
	case 5: 
			mov32ItoR(ECX,GPR(_Rs_).sVal);
			sar32RCL(EAX);break;
	/* rotations */
	case 6:
			if(!imm){
				//rcr32R1(EAX);
				shr32R1(EAX);
			}
			else{
				mov32ItoR(ECX,imm);
				ror32RCL(EAX);
			}break;
	case 7:
			mov32ItoR(ECX,GPR(_Rs_).sVal);
			ror32RCL(EAX);break;
	}
#endif
	shiftDispatch[val](EAX);
	if(_UPDATE_FLAGS_)
		UPDATE_CARRY(1);
	mov32RtoM(EAX,&GPR(_Rd_));
	if(_UPDATE_FLAGS_){
		test32RtoR(EAX,EAX);
		UPDATE_ZERO(1);
		UPDATE_SIGN(1);
	}
	x86SetJI8(x86Tmp[0]);
	return;
}




void recMVNi(void){
	
	CHECK_CONDITION(0);
	DEBUG_PRINT
	mov32ItoR(_IMM_,EAX);
	ror32R(EAX,shift_table[_RORIMM_]);
	if(_UPDATE_FLAGS_)
		UPDATE_CARRY(1);

	not32R(EAX);
	mov32RtoM(EAX,&GPR(_Rd_));
	if(_UPDATE_FLAGS_){
		test32RtoR(EAX,EAX);
		UPDATE_ZERO(1);
		UPDATE_SIGN(1);
	}
	x86SetJI8(x86Tmp[0]);
	return;
}

void recMVNs(void){

	__register u32 val=((CPU.currentInst>>4)&0x3U);
	/*__register u32 imm=((CPU.currentInst>>7)&0x1fU);
	 */

	DEBUG_PRINT

	CHECK_CONDITION(0);
	mov32ItoR(GPR(_Rm_).sVal,EAX);
#if 0 
	switch(val){
		/* what to do if the shift is 0, actually we could omit shifting there! */
	case 0:case 2: 
			mov32ItoR(ECX,imm);
			val==0?shl32RCL(EAX):shr32RCL(EAX);break;
	case 1:case 3:
			mov32ItoR(ECX,GPR(_Rs_).sVal);
			val==1?shl32RCL(EAX):shr32RCL(EAX);break;
	case 4:
			mov32ItoR(ECX,imm);
			sar32RCL(EAX);break;
	case 5: 
			mov32ItoR(ECX,GPR(_Rs_).sVal);
			sar32RCL(EAX);break;
	/* rotations */
	case 6:
			if(!imm){
				//rcr32R1(EAX);
				shr32R1(EAX);
			}
			else{
				mov32ItoR(ECX,imm);
				ror32RCL(EAX);
			}break;
	case 7:
			mov32ItoR(ECX,GPR(_Rs_).sVal);
			ror32RCL(EAX);break;
	}
#endif
	shiftDispatch[val](EAX);
	if(_UPDATE_FLAGS_)
		UPDATE_CARRY(1);
	not32R(EAX);
	mov32RtoM(EAX,&GPR(_Rd_));
	if(_UPDATE_FLAGS_){
		test32RtoR(EAX,EAX);
		UPDATE_ZERO(1);
		UPDATE_SIGN(1);
	}
	x86SetJI8(x86Tmp[0]);
	return;
}
