#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <arm_emu.h>
#include <x86.h>

/* x86 functions which write the opcodes into memory, still incomplete though */


extern u8 *code_ptr;


__inline void ModRM(u32 rm,u32 reg,u32 mod){
	WRITE8( ((mod&3)<<6) | ((reg&7)<<3) | (rm&7) );
	return;
}

__inline void Sib(u32 base, u32 index,u32 scale){
	WRITE8( ((scale&3)<<6) | ((index&7)<<3)  | (base&7));
	return;
}


__inline void adc32ItoEAX(s32 imm){
	WRITE8(0x16);
	WRITE32(imm);
	return;
}

__inline void adc16ItoAX(s16 imm){
	WRITE16((0x16<<8|OP_SIZE));
	WRITE16(imm);
	return;
}

__inline void adc8ItoAL(s8 imm){
	WRITE8(0x14);
	WRITE8(imm);
	return;
}

__inline void adc32RtoR(x86GPReg to ,x86GPReg from){
	WRITE8(0x11);
	ModRM(to,from,3);
	return;
}

__inline void adc32RtoM(x86GPReg from, void *to){
	WRITE8(0x11);
	ModRM(DISP32,from,0);
	WRITE32(to);
	return;
}

__inline void adc32RtoRm(x86GPReg from, x86GPReg base,x86GPReg index,u32 scale){
	WRITE8(0x11);
	if(index==NONE){
		ModRM(base,from,0);
	}
	else {
		ModRM(SIB,from,0);
		Sib(base,index,scale);
	}
	return;
}

__inline void adc32ItoR(s32 imm, x86GPReg to){
	WRITE8(0x81);
	ModRM(to,EDX,3);
	WRITE32(imm);
	return;
}

__inline void adc32ItoM(s32 imm, void *to){
	WRITE8(0x81);
	ModRM(DISP32,EDX,0);
	WRITE32(to);
	return;
}

__inline void adc32ItoRm(s32 imm,x86GPReg base, x86GPReg index, u32 scale){
	WRITE8(0x81);
	if(index==NONE){
		ModRM(base,EDX,0);
	}
	else{
		ModRM(SIB,EDX,0);
		Sib(base,index,scale);
	}
	WRITE32(imm);
	return;
}

__inline void adc32RmtoR(x86GPReg base , x86GPReg index , u32 scale, x86GPReg to ){
	WRITE8(0x13);
	if(index==NONE){
		ModRM(base,to,0);
	}
	else{
		ModRM(SIB,to,0);
		Sib(base,index,scale);
	}
	return;
}


/*-----------------------------------------------------------------------------*/
__inline void add32ItoEAX(s32 imm){
	WRITE8(0x05);
	WRITE32(imm);
	return;
}

__inline void add16ItoAX(s16 imm){
	WRITE8(OP_SIZE);
	WRITE8(0x05);
	WRITE16(imm);
	return;
}

__inline void add32I8toR(s8 imm,x86GPReg to){
	WRITE8(0x83);
	ModRM(to,EAX,3);
	WRITE8(imm);
	return;
}

__inline void add32I8toM(s8 imm, void *to){
	WRITE8(0x83);
	ModRM(DISP32,EAX,0);
	WRITE32(to);
	WRITE8(imm);
	return;

}

__inline void add32I8toRm(s8 imm,x86GPReg base, x86GPReg index, u32 scale ){
	WRITE8(0x38);
	if(index==NONE){
		ModRM(base,EAX,0);
	}
	else{
		ModRM(SIB,EAX,0);
		Sib(base,index,scale);
	}
	WRITE8(imm);
	return;
}

/* addl %from,(%base,%index,scale) */
__inline void add32RtoRm(x86GPReg from, x86GPReg base, x86GPReg index, u32 scale){
	WRITE8(0x1);
	if(index==NONE){
		ModRM(base,from,0);
	}
	else{
		ModRM(SIB,from,0);
		Sib(base,index,scale);
	}
	return ;
}

__inline void add32RmtoR(x86GPReg base,x86GPReg index, u32 scale, x86GPReg to ){	
	WRITE8(0x3);
	if(index==NONE){
		ModRM(to,base,3);
	}
	else{
		ModRM(SIB,to,0);
		Sib(base,index,scale);
	}
	return;
}

__inline void add32ItoRm(s32 imm,x86GPReg base, x86GPReg index, u32 scale){
	WRITE8(0x81);
	if(index==NONE){
		ModRM(base,EAX,0);
	}
	else {
		ModRM(SIB,EAX,0);
		Sib(base,index,scale);
	}
	WRITE32(imm);
	return ;
}

__inline void add32RtoR(x86GPReg from, x86GPReg to){
	WRITE8(0x1);
	ModRM(to,from,3);
	return;
}

__inline void add32ItoR(s32 imm, x86GPReg to){
	WRITE8(0x81);
	ModRM(to,EAX,3);
	WRITE32(imm);
	return;
}

__inline void add32MtoR(void *from, x86GPReg to){
	WRITE8(0x03);	
	ModRM(DISP32,to,0);
	WRITE32(from);
	return;
}

__inline void add32RtoM(x86GPReg from, void *to){
	WRITE8(0x01);
	ModRM(DISP32,from,0);
	WRITE32(to);
	return;
}

__inline void xadd32RtoR(x86GPReg from, x86GPReg to){
	WRITE16(0xc10f);
	ModRM(to,from,3);
	return;
}

__inline void xadd32RtoM(x86GPReg from, void *to){
	WRITE16(0xc10f);
	ModRM(DISP32,from,0);
	WRITE32(to);
	return;
}

__inline void xadd32RtoRm(x86GPReg from, x86GPReg base, x86GPReg index,u32 scale){
	WRITE16(0xc10f);
	if(index==NONE){
		ModRM(base,from,0);
	}
	else{
		ModRM(SIB,from,0);
		Sib(base,index,scale);
	}
	return;
}

/*-----------------------------------------------------------*/

__inline void xchg16RtoAX(x86GPReg from){
	WRITE8(OP_SIZE);
	WRITE8(0x90+(from&7));
	return;
}

__inline void xchg32RtoEAX(x86GPReg from){
	WRITE8(0x90+(from&7));
	return;

}

__inline void xchg32RtoR(x86GPReg from, x86GPReg to){
	WRITE8(0x87);
	ModRM(to,from,3);
	return;
}

__inline void xchg32RtoM(x86GPReg from, void *to){
	WRITE8(0x87);
	ModRM(DISP32,from,0);
	WRITE32(to);
	return;
}

__inline void xchg32RtoRm(x86GPReg from, x86GPReg base , x86GPReg index, u32 scale){
	WRITE8(0x87);
	if(index==NONE){
		ModRM(base,from,0);
	}
	else{
		ModRM(SIB,from,0);
		Sib(base,index,scale);
	}
	return;
}

__inline void xchg32MtoR(void *from, x86GPReg to){
	WRITE8(0x87);
	ModRM(DISP32,to,0);
	WRITE32(to);
	return;
}

__inline void xchg32RmtoR(x86GPReg base, x86GPReg index, u32 scale, x86GPReg to){
	WRITE8(0x87);
	if(index==NONE){
		ModRM(base,to,0);
	}
	else{
		ModRM(SIB,to,0);
		Sib(base,index,scale);
	}
	return;
}

/*-----------------------------------------------------------*/
__inline void sub16IfmAX(s16 imm){
	WRITE16((0x2d<<8)&OP_SIZE);
	WRITE16(imm);
	return;
}
__inline void sub32IfmEAX(s32 imm){
	WRITE8(0x2d);
	WRITE32(imm);
	return;
}

__inline void sub32IfmR(s32 imm, x86GPReg from){
	WRITE8(0x81);
	ModRM(from,EBP,3);
	WRITE32(imm);
	return;
}

__inline void sub32IfmM(s32 imm, void *from){
	WRITE8(0x81);
	ModRM(DISP32,EBP,0);
	WRITE32(from);
	WRITE32(imm);
	return;
}

__inline void sub32IfmRm(x86GPReg base, x86GPReg index, u32 scale, s32 imm){
	WRITE8(0x81);
	if(index==NONE){
		ModRM(base,EBP,0);
	}
	else{
		ModRM(SIB,EBP,0);
		Sib(base,index,scale);
	}
	WRITE32(imm);
	return;
}

__inline void sub32RfmR(x86GPReg to ,x86GPReg from){
	WRITE8(0x29);
	ModRM(from,to,3);
	return;
}

__inline void sub32RfmM(x86GPReg to, void *from){
	WRITE8(0x29);
	ModRM(DISP32,to,0);
	WRITE32(from);
	return;
}

__inline void sub32RfmRm(x86GPReg to,x86GPReg base, x86GPReg index, u32 scale){
	WRITE8(0x29);
	if(index==NONE){
		ModRM(base,to,0);

	}
	else {
		ModRM(SIB,to,0);
		Sib(base,index,scale);
	}
	return;
}

__inline void sub32MfmR(void *to,x86GPReg from){
	WRITE8(0x2b);
	ModRM(DISP32,from,0);
	WRITE32(to);
	return;
}

__inline void sub32RmfmR(x86GPReg base, x86GPReg index, u32 scale, x86GPReg from ){
	WRITE8(0x2b);
	if(index==NONE){
		ModRM(DISP32,from,0);
	}
	else{
		ModRM(SIB,from,0);
		Sib(base,index,scale);
	}
	return;
}
/*----------------------------------------------------------------------------*/
__inline void sbb8IfmAL(s8 imm){
	WRITE8(0x1c);
	WRITE8(imm);
	return;
}
__inline void sbb16IfmAX(s16 imm){
	WRITE8(OP_SIZE);
	WRITE8(0x1d);
	WRITE16(imm);
	return;
}

__inline void sbb32IfmEAX(s32 imm){
	WRITE8(0x1d);
	WRITE32(imm);
	return;
}


__inline void sbb32IfmR(s32 imm,x86GPReg from){
	WRITE8(0x81);
	ModRM(from,EBX,3);
	WRITE32(imm);
	return;
}

__inline void sbb32IfmM(s32 imm, void *from){
	WRITE8(0x81);
	ModRM(DISP32,EBX,0);
	WRITE32(from);
	WRITE32(imm);
	return;
}

__inline void sbb32RfmR(x86GPReg to, x86GPReg from){
	WRITE8(0x19);
	ModRM(from,to,3);
	return;
}


__inline void sbb32RfmM(x86GPReg to, void *from){
	WRITE8(0x19);
	ModRM(DISP32,to,0);
	WRITE32(from);
	return;
}

__inline void sbb32RfmRm(x86GPReg to, x86GPReg base, x86GPReg index, u32 scale){
	WRITE8(0x19);
	if(index==NONE){
		ModRM(base,to,0);	
	}
	else{
		ModRM(SIB,to,0);
		Sib(base,index,scale);
	}
	return;
}

__inline void sbb32MfmR(void *to, x86GPReg from){
	WRITE8(0x1b);
	ModRM(DISP32,from,0);
	WRITE32(to);
	return;
}

__inline void sbb32RmfmR(x86GPReg base, x86GPReg index, u32 scale, x86GPReg from){
	WRITE8(0x1b);
	if(index==NONE){
		ModRM(base,from,0);
	}
	else{
		ModRM(SIB,from,0);
		Sib(base,index,scale);
	}
	return;
}

/*-------------------------------------------------------------------*/
__inline void lea32RmtoR(x86GPReg base, x86GPReg index, u32 scale, x86GPReg to){
	WRITE8(0x8d);
	if(index==NONE){
		ModRM(base,to,0);
	}
	else{
		ModRM(SIB,to,0);
		Sib(base,index,scale);
	}
	return;
}


/*-------------------------------------------------------------------*/
__inline void and16ItoAX(s16 imm){
	WRITE16((0x25<<8)&OP_SIZE);
	WRITE16(imm);
	return;
}

__inline void and32ItoEAX(s32 imm){
	WRITE8(0x25);
	WRITE32(imm);
	return;
}


__inline void and32ItoR(s32 imm,x86GPReg to ){
	WRITE8(0x81);
	ModRM(to,ESP,3);
	WRITE32(imm);
	return;
}

__inline void and32ItoM(s32 imm,void *to){
	WRITE8(0x81);
	ModRM(DISP32,ESP,0);
	WRITE32(to);
	WRITE32(imm);
	return;
}

__inline void and32ItoRm(s32 imm,x86GPReg base ,x86GPReg index ,u32 scale){
	WRITE8(0x81); 
	if(index==NONE){
		ModRM(base,ESP,0);
	}
	else {
		ModRM(SIB,ESP,0);
		Sib(base,index,scale);

	}
	WRITE32(imm);
	return;
}


__inline void and32RtoR(x86GPReg from, x86GPReg to){
	WRITE8(0x21);
	ModRM(to,from,3);
	return;
}

__inline void and32RtoM(x86GPReg from, void *to){
	WRITE8(0x21);
	ModRM(DISP32,from,0);
	WRITE32(to);
	return;
}

__inline void and32RtoRm(x86GPReg from, x86GPReg base, x86GPReg index, u32 scale ){
	WRITE8(0x21);
	if(index==NONE){
		ModRM(base,from,0);
	}
	else {
		ModRM(SIB,from,0);
		Sib(base,index,scale);
	}
	return;
}


__inline void and32RmtoR(x86GPReg base, x86GPReg index, u32 scale, x86GPReg to){
	WRITE8(0x23);
	if(index==NONE){
		ModRM(base,to,0);
	}
	else {
		ModRM(SIB,to,0);
		Sib(base,index,scale);
	}
	return;
}

__inline void and32MtoR(void *from, x86GPReg to){
	WRITE8(0x23);
	ModRM(DISP32,to,0);
	WRITE32(from);
	return;
}
/*------------------------------------------------------*/

__inline void or16ItoAX(s16 imm ){
	WRITE8(OP_SIZE);
	WRITE8(0x0d);
	WRITE16(imm);
	return;
}

__inline void or32ItoEAX(s32  imm){
	WRITE8(0x0d);
	WRITE32(imm);
	return;
}

__inline void or32ItoR(s32 imm,x86GPReg to){
	WRITE8(0x81);
	ModRM(to,ECX,3);
	WRITE32(imm);
	return;
}

__inline void or32ItoM(s32 imm,void *to){
	WRITE8(0x81);
	ModRM(DISP32,ECX,0);
	WRITE32(to);
	WRITE32(imm);
	return;
}

__inline void or32ItoRm(s32 imm,x86GPReg base, x86GPReg index, u32 scale){
	WRITE8(0x81);
	if(index==NONE){
		ModRM(base,ECX,0);
	}
	else {
		ModRM(SIB,ECX,0);
		Sib(base,index,scale);

	}
	WRITE32(imm);
	return;
}

__inline void or32RtoR(x86GPReg from, x86GPReg to){
	WRITE8(0x09);
	ModRM(to,from,3);
	return;
}

__inline void or32RtoM(x86GPReg from, void *to){
	WRITE8(0x09);
	ModRM(DISP32,from,0);
	WRITE32(to);
	return;
}

__inline void or32RtoRm(x86GPReg from, x86GPReg base, x86GPReg index, u32 scale){
	WRITE8(0x09);
	if(index==NONE){
		ModRM(base,from,0);
	}
	else {
		ModRM(SIB,from,0);
		Sib(base,index,scale);
	}
	return;
}

__inline void or32MtoR(void *from, x86GPReg to){
	WRITE8(0x0b)
	ModRM(DISP32,to,0);
	WRITE32(from);
	return;
}

__inline void or32RmtoR(x86GPReg base,x86GPReg index, u32 scale, x86GPReg to){
	WRITE8(0x0b);
	if(index==NONE){
		ModRM(base,to,0);		
	}
	else {
		ModRM(SIB,to,0);
		Sib(base,index,scale);
	}
	return;
} 

/*----------------------------------------------------------------------*/
__inline void neg16R(x86GPReg to){
	WRITE8(OP_SIZE);
	WRITE8(0xf6);
	ModRM(to,EBX,3);
	return;
}

__inline void neg16M(void *to){
	WRITE8(OP_SIZE);
	WRITE8(0xf6);
	ModRM(DISP32,EBX,0);
	WRITE32(to);
	return;
}

__inline void neg16Rm(x86GPReg base, x86GPReg index, u32 scale){
	WRITE8(OP_SIZE);
	WRITE8(0xf6);
	if(index==NONE){
		ModRM(base,EBX,0);
	}
	else{
		ModRM(SIB,EBX,0);
		Sib(base,index,scale);
	}
	return;
}

__inline void neg32R(x86GPReg to){
	WRITE8(0xf6);
	ModRM(to,EBX,0);
	return;
}

__inline void neg32M(void *to){
	WRITE8(0xf6);
	ModRM(DISP32,EBX,0);
	WRITE32(to);
	return;
}

__inline void neg32Rm(x86GPReg base, x86GPReg index, u32 scale){
	WRITE8(0xf6);
	if(index==NONE){
		ModRM(base,EBX,0);
	}
	else{
		ModRM(SIB,EBX,0);
		Sib(base,index,scale);
	}
	return;
}

/*--------------------------------------------------------------------------*/
__inline void not32R(x86GPReg to){
	WRITE8(0xf7);
	ModRM(to,EDX,3);
	return;
}

__inline void not32M(void *to){
	WRITE8(0xf7);
	ModRM(DISP32,EDX,0);
	WRITE32(to);
	return;
}

__inline void not32Rm(x86GPReg base, x86GPReg index, u32 scale){
	WRITE8(0xf7);
	if(index==NONE){
		ModRM(base,EDX,0);
	}
	else {
		ModRM(SIB,EDX,0);
		Sib(base,index,scale);
	}
	return;
}
/*--------------------------------------------------------------------------*/
__inline void xor16ItoAX(s16 imm){
	WRITE8(OP_SIZE);
	WRITE8(0x35);
	WRITE16(imm);
	return;
}

__inline void xor32ItoEAX(s32 imm){
	WRITE8(0x35);
	WRITE32(imm);
	return;
}

__inline void xor32ItoR(s32 imm,x86GPReg to){
	WRITE8(0x81);
	ModRM(to,ESI,3);
	WRITE32(imm);
	return;
}

__inline void xor32ItoM(s32 imm, void *to){
	WRITE8(0x81);
	ModRM(DISP32,ESI,0);
	WRITE32(to);
	WRITE32(imm);
	return;
}

__inline void xor32ItoRm(s32 imm, x86GPReg base, x86GPReg index, u32 scale){
	WRITE8(0x81);
	if(index==NONE){
		ModRM(base,ESI,0);	
	}
	else{
		ModRM(SIB,ESI,0);
		Sib(base,index,scale);
	}
	WRITE32(imm);
	return;
}

__inline void xor32RtoR(x86GPReg from, x86GPReg to){
	WRITE8(0x31);
	ModRM(to,from,3);
	return;
}

__inline void xor32RtoM(x86GPReg from, void *to){
	WRITE8(0x31);
	ModRM(DISP32,from,0);
	WRITE32(to);
	return;
}

__inline void xor32RtoRm(x86GPReg from, x86GPReg base, x86GPReg index, u32 scale){
	WRITE8(0x31);
	if(index==NONE){
		ModRM(base,from,0);
	}
	else{
		ModRM(SIB,from,0);
		Sib(base,index,scale);
	}
	return;
}


__inline void xor32MtoR(void *from, x86GPReg to){
	WRITE8(0x33);
	ModRM(DISP32,to,0);
	WRITE32(from);
	return;
}

__inline void xor32RmtoR(x86GPReg base, x86GPReg index, u32 scale, x86GPReg to){
	WRITE8(0x33);
	if(index==NONE){
		ModRM(base,to,0);
	}
	else{
		ModRM(SIB,to,0);
		Sib(base,index,scale);
	}
	return;
}

/*--------------------------------------------------------------------------*/



__inline void mul32R(x86GPReg to){
	WRITE8(0xf7);
	ModRM(to,ESP,3);
	return;
}

__inline void mul32M(void *from){
	WRITE8(0xf7);
	ModRM(DISP32,ESP,0);
	WRITE32(from);
	return;
}

__inline void mul32Rm(x86GPReg base, x86GPReg index, u32 scale){
	WRITE8(0xf7);
	if(index==NONE){
		ModRM(base,ESP,0);
	}
	else{
		ModRM(SIB,ESP,0);
		Sib(base,index,scale);
	}
	return;
}


__inline void imul32R(x86GPReg to){
	WRITE8(0xf7);
	ModRM(to,EBP,3);
	return;
}

__inline void imul32RtoR(x86GPReg from, x86GPReg to){
	WRITE16(0xaf0f);
	ModRM(from,to,3);
	return;
}

__inline void imul32MtoR(void *from, x86GPReg to){
	WRITE16(0xaf0f);
	ModRM(DISP32,to,0);
	WRITE32(from);
	return;
}


__inline void imul32RmtoR(x86GPReg base, x86GPReg index, u32 scale, x86GPReg to){
	WRITE16(0xaf0f);
	if(index==NONE){
		ModRM(base,to,0);
	}
	else{
		ModRM(SIB,to,0);
		Sib(base,index,scale);
	}
	return;
}


/*--------------------------------------------------------------------------*/
__inline void div32R(x86GPReg from ){
	WRITE8(0xf7);
	ModRM(from,ESI,3);
	return;
}

__inline void div32M(void *from){
	WRITE8(0xf7);
	ModRM(DISP32,ESI,0);
	WRITE32(from);
	return;

}


__inline void div32Rm(x86GPReg base, x86GPReg index, u32 scale){
	WRITE8(0xf7);
	if(index==NONE){
		ModRM(base,ESI,0);
	}
	else{
		ModRM(SIB,ESI,0);
		Sib(base,index,scale);
	}
	return;

}

__inline void idiv32R(x86GPReg from){
	WRITE8(0xf7);
	ModRM(from,EDI,3);
	return;
}

__inline void idiv32M(void *from){
	WRITE8(0xf7);
	ModRM(DISP32,EDI,0);
	WRITE32(from);
	return;
}

__inline void idiv32Rm(x86GPReg base, x86GPReg index, u32 scale){
	WRITE8(0xf7);
	if(index==NONE){
		ModRM(base,EDI,0);
	}
	else {
		ModRM(SIB,EDI,0);
		Sib(base,index,scale);
	}
	return;
}

/*--------------------------------------------------------------------------*/
__inline void mov32RtoR(x86GPReg from, x86GPReg to ){
	WRITE8(0x89);
	ModRM(to,from,3);
	return;
}


__inline void mov32RtoM(x86GPReg from, void *to){
	WRITE8(0x89);
	ModRM(DISP32,from,0);
	WRITE32(to);
	return;

}

__inline void mov32RmtoR(x86GPReg base, x86GPReg index, u32 scale, x86GPReg to){
	WRITE8(0x8b);
	if(index==NONE){
		ModRM(base,to,0);
	}
	else {
		ModRM(SIB,to,0);
		Sib(base,index,scale);
	}
	return;
}

__inline void mov32RtoRm(x86GPReg from, x86GPReg base, x86GPReg index, u32 scale){
	WRITE8(0x89);
	if(index==NONE){
		ModRM(base,from,0);
	}
	else{
		ModRM(SIB,from,0);
		Sib(base,index,scale);
	}
	return;

}


__inline void mov32MtoR(void *from, x86GPReg to){
	WRITE8(0x8b);
	ModRM(DISP32,to,0);
	WRITE32(to);
	return;
}

__inline void mov32ItoR(s32 imm, x86GPReg to){
	WRITE8(0xb8|(to&0x7));
	WRITE32(imm);
	return;
}

__inline void mov32ItoM(s32 imm, void *to){
	WRITE8(0xc7);
	ModRM(DISP32,0,0);
	WRITE32(to);
	WRITE32(imm);
	return;
}

__inline void movzxR8toR32(x86GPReg from, x86GPReg to){
	WRITE8(0xb60f);
	ModRM(from,to,3);
	return;
}

__inline void movzxM8toR32(void *from, x86GPReg to){
	WRITE8(0xb60f);
	ModRM(DISP32,to,0);
	WRITE32(from);
	return;
}

__inline void movzxR8toR16(x86GPReg from, x86GPReg to){
	WRITE8(OP_SIZE);
	WRITE16(0xb60f);
	ModRM(from,to,3);
	return;
}

__inline void movzxM8toR16(void *from, x86GPReg to){
	WRITE8(OP_SIZE);
	WRITE16(0xb60f);
	ModRM(DISP32,to,0);
	WRITE32(from);
	return;
}

__inline void movzxR16toR32(x86GPReg from, x86GPReg to){
	WRITE16(0xb70f);
	ModRM(from,to,3);
	return;
}

__inline void movzxM16toR32(void *from, x86GPReg to){
	WRITE16(0xb70f);
	ModRM(DISP32,to,0);
	WRITE32(from);
	return;
}


__inline void movsxR8toR32(x86GPReg from, x86GPReg to){
	WRITE16(0xbe0f);
	ModRM(from,to,3);
	return;
}

__inline void movsxM8toR32(void *from, x86GPReg to){
	WRITE16(0xbe0f);
	ModRM(DISP32,to,0);
	WRITE32(from);
	return;
}

__inline void movsxR8toR16(x86GPReg from, x86GPReg to){
	WRITE8(OP_SIZE);
	WRITE16(0xbe0f);
	ModRM(from,to,3);
	return;
}

__inline void movsxM8toR16(void *from, x86GPReg to){
	WRITE8(OP_SIZE);
	WRITE16(0xbe0f);
	ModRM(DISP32,to,0);
	WRITE32(from);
	return;
}

__inline void movsxR16toR32(x86GPReg from, x86GPReg to){
	WRITE16(0xbf0f);
	ModRM(from,to,3);
	return;
}

__inline void movsxM16toR32(void *from, x86GPReg to){
	WRITE16(0xbf0f);
	ModRM(DISP32,to,0);
	WRITE32(from);
	return;
}

/*-------------------------------------------------------------------*/
__inline void ror32M(void *to,s8 rot){
	WRITE8(0xc1);
	ModRM(DISP32,ECX,0); /* actually we dont use a register here*/
	WRITE32(to);
	WRITE8(rot);
	return;
}


__inline void ror32R(x86GPReg to,s8 rot){
	WRITE8(0xc1);
	ModRM(to,ECX,3);
	WRITE8(rot);
	return;
}

__inline void ror32R1(x86GPReg to){
	WRITE8(0xd1);
	ModRM(to,ECX,3);
	return;
}

__inline void ror32M1(void *to){
	WRITE8(0xd1)
	ModRM(DISP32,ECX,0);
	WRITE32(to);
	return;
}


__inline void ror32RCL(x86GPReg to){
	WRITE8(0xd3);
	ModRM(to,ECX,3);
	return;
}


__inline void ror32MCL(void *to){
	WRITE8(0xd3);
	ModRM(DISP32,ECX,0);
	WRITE32(to);
	return;
}

__inline void rol32R1(x86GPReg to){
	WRITE8(0xd1);
	ModRM(to,EAX,3);
	return;
}

__inline void rol32M1(void *to){
	WRITE8(0xd1);
	ModRM(DISP32,EAX,0);
	WRITE32(to);
	return;
}

__inline void rol32RCL(x86GPReg to){
	WRITE8(0xd3);
	ModRM(to,EAX,3);
	return;
}

__inline void rol32MCL(void *to){
	WRITE8(0xd3);
	ModRM(DISP32,EAX,0);
	WRITE32(to);
	return;
}


__inline void rol32R(x86GPReg to,s8 rot){
	WRITE8(0xc1);
	ModRM(to,EAX,3);
	WRITE8(rot);
	return;
}

__inline void rol32M(void *to,s8 rot){
	WRITE8(0xc1);
	ModRM(DISP32,EAX,0);
	WRITE32(to);
	WRITE8(rot);
	return;
}


__inline void shl32R1(x86GPReg to){
	WRITE8(0xd1);
	ModRM(to,ESP,3);	
	return;

}

__inline void shl32M1(void *to ){
	WRITE8(0xd1);
	ModRM(DISP32,ESP,0);
	WRITE32(to);
	return;
}

__inline void shl32RCL(x86GPReg to){
	WRITE8(0xd3);
	ModRM(to,ESP,3);
	return;
}

__inline void shl32MCL(void *to){
	WRITE8(0xd3);
	ModRM(DISP32,ESP,0);
	WRITE32(to);
	return;
}

__inline void shl32R(x86GPReg to,s8 shift){
	WRITE8(0xc1);
	ModRM(to,ESP,3);
	WRITE8(shift);
	return;
}

__inline void shl32M(void *to,s8 shift){
	WRITE8(0xc1);
	ModRM(DISP32,ESP,0);
	WRITE32(to);
	WRITE8(shift);
	return;
}


__inline void shr32R1(x86GPReg to){
	WRITE8(0xd1);
	ModRM(to,EBP,3);
	return;
}


__inline void shr32M1(void *to){
	WRITE8(0xd1);
	ModRM(DISP32,EBP,0);
	WRITE32(to);
	return;

}

__inline void shr32RCL(x86GPReg to){
	WRITE8(0xd3);
	ModRM(to,EBP,3);
	return;
}

__inline void shr32MCL(void *to){
	WRITE8(0xd3);
	ModRM(DISP32,EBP,3);
	WRITE32(to);
	return;
}

__inline void shr32R(x86GPReg to,s8 shift){
	WRITE8(0xc1);
	ModRM(to,EBP,3);
	WRITE8(shift);
	return;
}

__inline void shr32M(void *to, s8 shift){
	WRITE8(0xc1);
	ModRM(DISP32,EBP,0);
	WRITE32(to);
	WRITE8(shift);
	return;
}

__inline void sar32R1(x86GPReg to){
	WRITE8(0xd1);
	ModRM(to,EDI,3);
	return;
}

__inline void sar32M1(void *to){
	WRITE8(0xd1);
	ModRM(DISP32,EDI,0);
	WRITE32(to);
	return;
}

__inline void sar32RCL(x86GPReg to){
	WRITE8(0xd3);
	ModRM(to,EDI,3);
	return;
}

__inline void sar32MCL(void *to){
	WRITE8(0xd3);
	ModRM(DISP32,EDI,0);
	WRITE32(to);
	return;
}

__inline void sar32R(x86GPReg to, s8 imm){
	WRITE8(0xc1);
	ModRM(to,EDI,3);
	WRITE8(imm);
	return;
}


__inline void sar32M(void *to, s8 imm){
	WRITE8(0xc1);
	ModRM(DISP32,EDI,3);
	WRITE32(to);
	WRITE8(imm);
}

__inline void rcl32R1(x86GPReg to){
	WRITE8(0xd1)
	ModRM(to,EDX,3);
	return;
}

__inline void rcl32M1(void *to){
	WRITE8(0xd1);
	ModRM(DISP32,EDX,0);
	WRITE32(to);
	return;
}

__inline void rcl32RCL(x86GPReg to){
	WRITE8(0xd3);
	ModRM(to,EDX,3);
	return;
}

__inline void rcl32MCL(void *to){
	WRITE8(0xd3);
	ModRM(DISP32,EDX,0);
	WRITE32(to);
	return;
}

__inline void rcl32R(x86GPReg to, s8 imm){
	WRITE8(0xc1);
	ModRM(to,EDX,3);
	WRITE8(imm);
	return;
}

__inline void rcl32M(void *to, s8 imm){
	WRITE8(0xc1);
	ModRM(DISP32,EDX,0);
	WRITE32(to);
	WRITE8(imm);
	return;
}

__inline void rcr32R1(x86GPReg to){
	WRITE8(0xd1);
	ModRM(to,EBX,3);
	return;
}

__inline void rcr32M1(void *to){
	WRITE8(0xd1);
	ModRM(DISP32,EBX,0);
	WRITE32(to);
	return;
}

__inline void rcr32RCL(x86GPReg to){
	WRITE8(0xd3);
	ModRM(to,EBX,3);
	return;
}

__inline void rcr32MCL(void *to){ 
	WRITE8(0xd3);
	ModRM(DISP32,EBX,0);
	WRITE32(to);
	return;
}

__inline void rcr32R(x86GPReg to,s8 imm){
	WRITE8(0xc1);
	ModRM(to,EBX,3);
	WRITE8(imm);
	return;

}

__inline void rcr32M(void *to,s8 imm){
	WRITE8(0xc1);
	ModRM(DISP32,EBX,0);
	WRITE32(to);
	WRITE8(imm);
	return;
}

/*------------------------------------------------------------*/
__inline void test16ItoAX(s16 imm){
	WRITE8(OP_SIZE);
	WRITE8(0xa9);
	WRITE16(imm);
	return;
}

__inline void test32ItoEAX(s32 imm){
	WRITE8(0xa9);
	WRITE32(imm);
	return;
}

__inline void test32ItoR(s32 imm, x86GPReg to){
	WRITE8(0xf7);
	ModRM(to,EAX,3);
	WRITE32(imm);
	return;
}

__inline void test32ItoM(s32 imm, void *to){
	WRITE8(0xf7);
	ModRM(DISP32,EAX,3);
	WRITE32(to);
	WRITE32(imm);
	return;
}

__inline void test32ItoRm(s32 imm, x86GPReg base, x86GPReg index, u32 scale){
	WRITE8(0xf7);
	if(index==NONE){
		ModRM(base,EAX,0);
	}
	else{
		ModRM(SIB,EAX,0);
		Sib(base,index,scale);
	}
	WRITE32(imm);
	return;
}


__inline void test32RtoR(x86GPReg from, x86GPReg to){
	WRITE8(0x85);
	ModRM(to,from,3);
	return;
}

__inline void test32RtoM(x86GPReg from, void *to){
	WRITE8(0x85);
	ModRM(DISP32,from,0);
	WRITE32(to);
	return;
}

__inline void test32RtoRm(x86GPReg from, x86GPReg base, x86GPReg index, u32 scale){
	WRITE8(0x85);
	if(index==NONE){
		ModRM(base,from,0);
	}
	else{
		ModRM(SIB,from,0);
		Sib(base,index,scale);
	}
	return;
}



/*------------------------------------------------------------*/
__inline void cmp16ItoAX(s16 imm){
	WRITE16((0x3d<<8)&OP_SIZE);
	WRITE32(imm);
	return;
}

__inline void cmp32ItoEAX(s32 imm){
	WRITE8(0x3d);
	WRITE32(imm);
	return;
}

__inline void cmp32ItoR(s32 imm, x86GPReg to){
	WRITE8(0x81);
	ModRM(to,EDI,3);
	WRITE32(imm);
	return;

}

__inline void cmp32ItoM(s32 imm, void *to ){
	WRITE8(0x81);
	ModRM(DISP32,EDI,0);
	WRITE32(to);
	WRITE32(imm);
	return;
}

__inline void cmp32ItoRm(s32 imm, x86GPReg base, x86GPReg index, u32 scale){
	WRITE8(0x81);
	if(index==NONE){
		ModRM(base,EDI,0);
	}
	else {
		ModRM(SIB,EDI,0);
		Sib(base,index,scale);
	}
	WRITE32(imm);
	return;
}

__inline void cmp32RtoR(x86GPReg from, x86GPReg to){
	WRITE8(0x39);
	ModRM(to,from,3);
	return;

}

__inline void cmp32RtoM(x86GPReg from, void *to){
	WRITE8(0x39);
	ModRM(DISP32,from,0);
	WRITE32(to);
	return;
}

__inline void cmp32RtoRm(x86GPReg from, x86GPReg base, x86GPReg index , u32 scale ){
	WRITE8(0x39);
	if(index==NONE){
		ModRM(base,from,0);
	}
	else{
		ModRM(SIB,from,0);
		Sib(base,index,scale);

	}
	return;
}

__inline void cmp32MtoR(void *from, x86GPReg to){
	WRITE8(0x3b);
	ModRM(DISP32,to,0);
	WRITE32(from);
	return;
}

__inline void cmp32RmtoR(x86GPReg base, x86GPReg index, u32 scale, x86GPReg to){
	WRITE8(0x3b);
	if(index==NONE){
		ModRM(base,to,0);

	}
	else{
		ModRM(SIB,to,0);
		Sib(base,index,scale);
	}
	return;
}

__inline void cmpsw(void){
	WRITE8(OP_SIZE);
	WRITE8(0xa7);
	return;

}

__inline void cmpsd(void ){
	WRITE8(0xa7);
	return;
}

/*--------------------------------------------------------------------------*/

__inline void inc32R(x86GPReg to ){
	WRITE8(0x40+(to&0x7));
	return;
}

__inline void inc32M(void *to ){
	WRITE8(0xff);
	ModRM(DISP32,EAX,0);
	WRITE32(to);
	return;
}

__inline void inc32Rm(x86GPReg base, x86GPReg index, u32 scale){
	WRITE8(0xff);
	if(index==NONE){
		ModRM(base,EAX,0);
	}
	else {
		ModRM(SIB,EAX,0);
		Sib(base,index,scale);
	}
	return;
}


__inline void dec32R(x86GPReg to){
	WRITE8(0x48+(to&0x7));
	return;
}


__inline void dec32M(void *to){
	WRITE8(0xff);
	ModRM(DISP32,ECX,0);
	WRITE32(to);
	return;
}

__inline void dec32Rm(x86GPReg base, x86GPReg index, u32 scale){
	WRITE8(0xff);
	if(index==NONE){
		ModRM(base,ECX,0);
	}
	else {
		ModRM(SIB,ECX,0);
		Sib(base,index,scale);
	}
	return;
}

__inline void push16R(x86GPReg reg){
	WRITE8(OP_SIZE);
	WRITE8(0x50+(reg&7));
	return;
}

__inline void push32R(x86GPReg reg){
	WRITE8(0x50+(reg&7));
	return;	
}

__inline void pushI8(s8 imm){
	WRITE8(0x6a);
	WRITE8(imm);
	return;
}

__inline void pushI16(s16 imm){
	WRITE8(OP_SIZE);
	WRITE8(0x68);
	WRITE16(imm);
	return;
}

__inline void pushI32(s32 imm){
	WRITE8(0x68);
	WRITE32(imm);
	return;
}

__inline void push32M(void *mem){
	WRITE8(0xff);
	ModRM(DISP32,ESI,0);
	WRITE32(mem);
	return;
}

__inline void pusha(void){
	WRITE8(OP_SIZE);
	WRITE8(0x60);
	return;
}

__inline void pushad(void){
	WRITE8(0x60);
	return;
}


__inline void pushf(void){
	WRITE8(OP_SIZE);
	WRITE8(0x9c);
	return;
}

__inline void pushfd(void){
	WRITE8(0x9c);
	return;
}

__inline void pop16R(x86GPReg reg){
	WRITE8(OP_SIZE);
	WRITE8(0x58+(reg&7));
	return;
}

__inline void pop32R(x86GPReg reg){
	WRITE8(0x58+(reg&7));
	return;
}

__inline void pop32M(void *mem){
	WRITE8(0x8f);
	ModRM(DISP32,EAX,0);
	WRITE32(mem);
	return;
}

__inline void popa(void){
	WRITE8(OP_SIZE);
	WRITE8(0x61);
	return;

}

__inline void popad(void){
	WRITE8(0x61);
	return;
}


__inline void nop(void){
	WRITE8(0x90);
	return;
}

__inline void ret(void){
	WRITE8(0xc3);
	return;
}

__inline void stc(void){
	WRITE8(0xf9);
	return;
}

__inline void std(void){
	WRITE8(0xfd);
	return;
}

__inline void sti(void){
	WRITE8(0xfb);
	return;
}
__inline void clc(void){
	WRITE8(0xf8);
	return;
}

__inline void cld(void){
	WRITE8(0xfc);
	return;
}

__inline void cli(void){
	WRITE8(0xfa);
	return;
}

__inline void callRel16(s16 imm){
	WRITE8(OP_SIZE);
	WRITE8(0xe8);
	WRITE16(imm);
	return;
}

__inline void callRel32(s32 imm){
	WRITE8(0xe8);
	WRITE32(imm);
	return;
}

__inline void call32R(x86GPReg reg){
	WRITE8(0xff);
	ModRM(reg,EDX,3);
	return;
}


__inline void call32M(void *addr){
	WRITE8(0xff);
	ModRM(DISP32,EDX,3);
	WRITE32(addr);
	return;
}

__inline void call32Rm(x86GPReg base, x86GPReg index, u32 scale){
	WRITE8(0xff);
	if(index==NONE){
		ModRM(base,EDX,0);
	}
	else{
		ModRM(SIB,EDX,0);
		Sib(base,index,scale);
	}
	return;
}

__inline void call32SegOff(u16 segment, u32 offset ){
	WRITE8(0x9a);
	WRITE32(offset);
	WRITE32(segment);
	return;
}

__inline void cbw(void){
	WRITE8(0x98);
	return;
}

__inline void cdq(void){
	WRITE8(0x99);
	return;
}


__inline void bt32I8toR(s8 imm, x86GPReg to){
	WRITE16(0xba0f);
	ModRM(to,ESP,0);
	WRITE8(imm);
	return;
}

__inline void bt32I8toM(s8 imm, void *to){
	WRITE16(0xba0f);
	ModRM(DISP32,ESP,0);
	WRITE32(to);
	WRITE8(imm);
	return;
}

__inline void bt32I8toRm(s8 imm, x86GPReg base, x86GPReg index,u32 scale){
	WRITE16(0xba0f);
	if(index==NONE){
		ModRM(base,ESP,0);	
	}
	else{
		ModRM(SIB,ESP,0);
		Sib(base,index,scale);
	}
	WRITE8(imm);
	return;
}

__inline void bt32RtoR(x86GPReg8 from, x86GPReg to){
	WRITE16(0xa30f);
	ModRM(to,from,3);
	return;
}

__inline void bt32RtoM(x86GPReg8 from, void *to){
	WRITE16(0xa30f);
	ModRM(DISP32,from,0);
	WRITE32(to); 
	return;
}


__inline void bt32RtoRm(x86GPReg8 from, x86GPReg base, x86GPReg index, u32 scale){
	WRITE16(0xa30f);
	if(index==NONE){
		ModRM(base,from,0);
	}
	else{
		ModRM(SIB,from,0);
		Sib(base,index,scale);
	}
	return;
}

__inline void bts32I8toR(s8 imm, x86GPReg to){
	WRITE16(0xab0f);
	ModRM(to,ESI,3);
	WRITE8(imm);
	return;
}

__inline void bts32I8toM(s8 imm, void *to){
	WRITE16(0xab0f);
	ModRM(DISP32,ESI,0);
	WRITE32(to);
	WRITE8(imm);
	return;
}


__inline void bts32I8toRm(s8 imm, x86GPReg base, x86GPReg index, u32 scale){
	WRITE16(0xab0f);
	if(index==NONE){
		ModRM(base,ESI,0);

	}
	else{
		ModRM(SIB,ESI,0);
		Sib(base,index,scale);
	}
	WRITE8(imm);
	return;
}

__inline void bts32RtoR(x86GPReg8 from, x86GPReg to){
	WRITE16(0xbb0f);
	ModRM(to,from,3);
	return;
}


__inline void bts32RtoM(x86GPReg8 from, void  *to){
	WRITE16(0xbb0f);
	ModRM(DISP32,from,0);
	WRITE32(to);
	return;
}

__inline void bts32RtoRm(x86GPReg8 from, x86GPReg base, x86GPReg index, u32 scale){
	WRITE16(0xbb0f);
	if(index==NONE){
		ModRM(base,from,0);
	}
	else{
		ModRM(SIB,from,0);
		Sib(base,index,scale);
	}
	return;
}

__inline void bsr32RtoR(x86GPReg from, x86GPReg to){
	WRITE16(0x0fbd);
	ModRM(from,to,3);
	return;
}


__inline void bsr32MtoR(void *from, x86GPReg to){
	WRITE16(0x0fbd);
	ModRM(DISP32,to,0);
	WRITE32(from);
	return;

}


__inline void bsr32RmtoR(x86GPReg base, x86GPReg index, u32 scale, x86GPReg to){
	WRITE16(0x0fbd);
	if(index==NONE){
		ModRM(base,to,0);
	}
	else{
		ModRM(SIB,to,0);
		Sib(base,index,scale);
	}
	return;

}


__inline void btr32I8toR(s8 imm, x86GPReg to){
	WRITE16(0xba0f);
	ModRM(to,ESI,3);
	WRITE8(imm);
	return;
}

__inline void btr32I8toM(s8 imm, void *to){
	WRITE16(0xba0f);
	ModRM(DISP32,ESI,0);
	WRITE32(to);
	WRITE8(imm);
	return;
}

__inline void btr32I8toRm(s8 imm, x86GPReg base, x86GPReg index, u32 scale){
	WRITE16(0xba0f);
	if(index==NONE){
		ModRM(base,ESI,0);
	}
	else{
		ModRM(SIB,ESI,0);
		Sib(base,index,scale);

	}
	WRITE8(imm);
	return;
}

__inline void btr32RtoR(x86GPReg8 from, x86GPReg to){
	WRITE16(0xb30f);
	ModRM(to,from,3);
	return;
}

__inline void btr32RtoM(x86GPReg8 from, void *to){
	WRITE16(0xb30f);
	ModRM(DISP32,from,0);
	WRITE32(to);
	return;

}

__inline void btr32RtoRm(x86GPReg8 from,x86GPReg base, x86GPReg index, u32 scale){
	WRITE16(0xb30f);
	if(index==NONE){
		ModRM(base,from,0);
	}
	else{
		ModRM(SIB,from,0);
		Sib(base,index,scale);
	}
	return;

}

__inline void btc32I8toR(s8 imm, x86GPReg to){
	WRITE16(0xba0f);
	ModRM(to,EDI,3);
	WRITE8(imm);
	return;

}

__inline void btc32I8toM(s8 imm, void *to){
	WRITE16(0xba0f);
	ModRM(DISP32,EDI,0);
	WRITE32(to);
	WRITE8(imm);
	return;
}

__inline void btc32I8toRm(s8 imm, x86GPReg base, x86GPReg index, u32 scale){
	WRITE16(0xba0f);
	if(index==NONE){
		ModRM(base,EDI,0);
	}
	else{
		ModRM(SIB,EDI,0);
		Sib(base,index,scale);
	}
	WRITE8(imm);
	return;
}


__inline void btc32RtoR(x86GPReg8 from, x86GPReg to){
	WRITE16(0xbb0f);
	ModRM(to,from,3);
	return;
}

__inline void btc32RtoM(x86GPReg8 from ,void *to){
	WRITE16(0xbb0f);
	ModRM(DISP32,from,0);
	WRITE32(to);
	return;
}

__inline void btc32RtoRm(x86GPReg8 from, x86GPReg base, x86GPReg index, u32 scale){
	WRITE16(0xbb0f);
	if(index==NONE){
		ModRM(base,from,0);
	}
	else{
		ModRM(SIB,from,0);
		Sib(base,index,scale);
	}
		
}
__inline void bswap(x86GPReg to){
	WRITE8(0x0f);
	WRITE8(0xc8+(to&7));
	return;

}
/*--------------------------------------------------------------------------------------*/

__inline void set8R(u32 cc, x86GPReg8 to){
	WRITE8(0x0f);
	WRITE8(cc);
	WRITE8(0xc0|(to&7));
	return;
}

__inline void seta(x86GPReg8 to){
	set8R(0x97,to);
	return;
}

__inline void setae(x86GPReg8 to){
	set8R(0x93,to);
	return;
}


__inline void setb(x86GPReg8 to){
	set8R(0x92,to);
	return;
}

__inline void setbe(x86GPReg8 to){
	set8R(0x96,to);
	return;
}

__inline void setc(x86GPReg8 to){
	set8R(0x92,to);
	return;
}

__inline void sete(x86GPReg8 to){
	set8R(0x94,to);
	return;
}

__inline void setg(x86GPReg8 to){
	set8R(0x9f,to);
	return;
}

__inline void setge(x86GPReg8 to){
	set8R(0x9d,to);
	return;
}

__inline void setl(x86GPReg8 to){
	set8R(0x9c,to);
	return;
}

__inline void setle(x86GPReg8 to){
	set8R(0x9e,to);
	return;
}


__inline void setna(x86GPReg8 to){
	set8R(0x96,to);
	return;
}

__inline void setnae(x86GPReg8 to){
	set8R(0x92,to);
	return;	
}

__inline void setnb(x86GPReg8 to){
	set8R(0x93,to);
	return;
}

__inline void setnbe(x86GPReg8 to){
	set8R(0x97,to);
	return;
}

__inline void setnc(x86GPReg8 to){
	set8R(0x93,to);
	return;
}


__inline void setne(x86GPReg8 to){
	set8R(0x95,to);
	return;
}

__inline void setng(x86GPReg8 to ){
	set8R(0x9e,to);
	return;
}

__inline void setnge(x86GPReg8 to){
	set8R(0x9c,to);
	return;
}

__inline void setnl(x86GPReg8 to){
	set8R(0x9d,to);
	return;
}

__inline void setnle(x86GPReg8 to){
	set8R(0x9f,to);
	return;
}

__inline void setno(x86GPReg8 to){
	set8R(0x91,to);
	return;
}

__inline void setnp(x86GPReg8 to){
	set8R(0x9b,to);
	return;
}

__inline void setns(x86GPReg8 to){
	set8R(0x99,to);
	return;
}

__inline void setnz(x86GPReg8 to){
	set8R(0x95,to);
	return;
}

__inline void seto(x86GPReg8 to){
	set8R(0x90,to);
	return;
}

__inline void setp(x86GPReg8 to){
	set8R(0x9a,to);
	return;
}
/* really 0x9a? */
__inline void setpe(x86GPReg8 to){
	set8R(0x9a,to);
	return;
}

__inline void setpo(x86GPReg8 to){
	set8R(0x9b,to);
	return;
}

__inline void sets(x86GPReg8 to){
	set8R(0x98,to);
	return;
}

__inline void setz(x86GPReg8 to){
	set8R(0x94,to);
	return;
}

/*--------------------------------------------------------------------------------------*/

__inline void x86SetJI8(u8 *ptr){
	u32 tmp=(X86CODE-ptr);

	tmp--;
	if(tmp>0x7f){
		assert(0);
		printf("j8 greater than 0x7f");
	}
	*ptr=(u8)tmp;
	return;
}


__inline void jmp32R(x86GPReg reg){
	WRITE8(0xff);
	ModRM(reg,ESP,3);
	return;
}


__inline u8 *jmpI8(s8 offset){
	WRITE8(0xeb);
	WRITE8(offset);
	return (X86CODE-1);
}

__inline u8 *jmpI16(s16 offset){
	WRITE8(OP_SIZE);
	WRITE8(0xe9);
	WRITE16(offset);
	return (X86CODE-2);
}

__inline u8 *jmpI32(s32 offset){
	WRITE8(0xe9);
	WRITE32(offset);
	return (X86CODE-4);
}

__inline u8* setJmpI16(u32 cc, s16 offset){
	WRITE8(OP_SIZE);
	WRITE16(0x000f|(cc<<8));
	WRITE16(offset);
	return (X86CODE-2);
}

__inline u8* setJmpI32(u32 cc, s32 offset){
	WRITE16(0x000f|(cc<<8));
	WRITE32(offset);
	return(X86CODE-4);
}

__inline u8 *jaI8(s8 offset){
	WRITE8(0x77);
	WRITE8(offset);
	return(X86CODE-1);
}

__inline u8 *jaI16(s16 offset){
	return setJmpI16(0x87,offset);
}

__inline u8 *jaI32(s32 offset){
	return setJmpI32(0x87,offset);
}

__inline u8 *jeI8(s8 offset){
	WRITE8(0x74);
	WRITE8(offset);
	return(X86CODE-1);

}

__inline u8 *jeI16(s16 offset){
	return setJmpI16(0x84,offset);
}

__inline u8 *jeI32(s32 offset){
	return setJmpI32(0x84,offset);
}

__inline u8 *jzI8(s8 offset){
	WRITE8(0x74);
	WRITE8(offset);
	return(X86CODE-1);
}

__inline u8 *jzI16(s16 offset){
	return setJmpI16(0x84,offset);
}

__inline u8 *jzI32(s32 offset){
	return setJmpI32(0x84,offset);
}


__inline u8 *jcI8(s8 offset){
	WRITE8(0x72);
	WRITE8(offset);
	return(X86CODE-1);
}

__inline u8 *jcI16(s16 offset){
	return setJmpI16(0x82,offset);
}

__inline u8* jcI32(s32 offset){
	return setJmpI32(0x82,offset);
}

__inline u8 *jsI8(s8 offset){
	WRITE8(0x78);
	WRITE8(offset);
	return(X86CODE-1);
}

__inline u8 *jsI16(s16 offset){
	return setJmpI16(0x8b,offset);
}

__inline u8 *jsI32(s32 offset){
	return setJmpI32(0x8b,offset);
}

__inline u8 *joI8(s8 offset){
	WRITE8(0x70);
	WRITE8(offset);
	return(X86CODE-1);
}

__inline u8 *jo16(s16 offset){
	return setJmpI16(0x80,offset);
}

__inline u8 *jo32(s32 offset){
	return setJmpI32(0x80,offset);
}

__inline u8 *jnzI8(s8 offset){
	WRITE8(0x75);
	WRITE8(offset);
	return(X86CODE-1);
}

__inline u8 *jnzI16(s16 offset){
	return setJmpI16(0x85,offset);
}

__inline u8 *jnzI32(s32 offset){
	return setJmpI32(0x85,offset);
}

__inline u8 *jnsI8(s8 offset){
	WRITE8(0x79);
	WRITE8(offset);
	return(X86CODE-1);
}

__inline u8 *jnsI16(s16 offset){
	return setJmpI16(0x89,offset);
}

__inline u8 *jnsI32(s32 offset){
	return setJmpI32(0x89,offset);
}

__inline u8 *jnoI8(s8 offset){
	WRITE8(0x71);
	WRITE8(offset);
	return (X86CODE-1);
}

__inline u8 *jnoI16(s16 offset){
	return	setJmpI16(0x81,offset);
}

__inline u8 *jnoI32(s32 offset){
	return setJmpI32(0x81,offset);
}

__inline u8 *jncI8(s8 offset){
	WRITE8(0x73);
	WRITE8(offset);
	return(X86CODE-1);
}

__inline u8 *jncI16(s16 offset){
	return setJmpI16(0x83,offset);
}

__inline u8 *jncI32(s32 offset){
	return setJmpI32(0x83,offset);
}
/*-----------conditional mov's with 32bit-operands-----------------------------------
 * 
 * Since its always the same i wrote a macro which expands to the three functions  and takes
 * as parameter the name of the cond. mov and the opcode. See x86.h
 * Of course iam aware that functions with the same opcodes but differnet names are redundant
 * but for completeness i also included them
 */

CMOV32ALL(cmova,0x470f)

CMOV32ALL(cmovae,0x430f)

CMOV32ALL(cmovb,0x420f)

CMOV32ALL(cmovbe,0x460f)

CMOV32ALL(cmovc,0x420f)

CMOV32ALL(cmove,0x440f)

CMOV32ALL(cmovg,0x4f0f)

CMOV32ALL(cmovge,0x4d0f)

CMOV32ALL(cmovl,0x4c0f)

CMOV32ALL(cmovle,0x4e0f)

CMOV32ALL(cmovna,0x460f)

CMOV32ALL(cmovnae,0x420f)

CMOV32ALL(cmovnb,0x430f)

CMOV32ALL(cmovnbe,0x470f)

CMOV32ALL(cmovnc,0x430f)

CMOV32ALL(cmovne,0x450f)

CMOV32ALL(cmovng,0x4e0f)

CMOV32ALL(cmovnge,0x4c0f)

CMOV32ALL(cmovnl,0x4d0f)

CMOV32ALL(cmovnle,0x4f0f)

CMOV32ALL(cmovno,0x410f)

CMOV32ALL(cmovnp,0x4b0f)

CMOV32ALL(cmovns,0x490f)

CMOV32ALL(cmovnz,0x450f)

CMOV32ALL(cmovo,0x400f)

CMOV32ALL(cmovp,0x4a0f)

CMOV32ALL(cmovpe,0x4a0f)

CMOV32ALL(cmovpo,0x4b0f)

CMOV32ALL(cmovs,0x480f)

CMOV32ALL(cmovz,0x440f)

/*------------------------------------------------------------------*/
