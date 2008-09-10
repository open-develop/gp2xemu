#ifndef _ARMX86_H_
#define _ARMX86_H_

#include <arm920t.h>
#include <x86.h>

#define CHECK_CONDITION(slot)	{\
			pushI32(_COND_);\
			callRel32((u32)matchCondition-((u32)(X86CODE+5)));\
			add32ItoR(4,ESP);\
			and32RtoR(EAX,EAX);\
			x86Tmp[slot]=jnzI8(0);}


#define UPDATE_FLAG(flag,slot) {\
			bts32I8toM(flag,&CPSR);\
			x86SetJI8(x86Tmp[slot]);\
			btr32I8toM(flag,&CPSR); }


#define UPDATE_CARRY(slot) {\
			x86Tmp[slot]=jncI8(0);\
			UPDATE_FLAG(CARRY,slot) }

#define UPDATE_ZERO(slot) {\
			x86Tmp[slot]=jnzI8(0);\
			UPDATE_FLAG(ZERO,slot) }

#define UPDATE_OVERF(slot) {\
			x86Tmp[slot]=jnoI8(0);\
			UPDATE_FLAG(OVERF,slot) }

#define UPDATE_SIGN(slot) {\
			x86Tmp[slot]=jnsI8(0);\
			UPDATE_FLAG(SIGN,slot) }



#define INVERSE_UPDATE(flag,slot) {\
			btr32I8toM(flag,&CPSR);\
			x86SetJI8(x86Tmp[slot]);\
			bts32I8toM(flag,&CPSR); }

#define INVERSE_CARRY(slot) { \
			x86Tmp[slot]=jncI8(0);\
			INVERSE_UPDATE(CARRY,slot)}

#define INVERSE_ZERO(slot) {\
			x86Tmp[slot]=jnzI8(0);\
			INVERSE_UPDATE(ZERO,slot)}

#define INVERSE_SIGN(slot) {\
			x86Tmp[slot]=jnsI8(0);\
			INVERSE_UPDATE(SIGN,slot)}

#define INVERSE_OVERF(slot) {\
			x86Tmp[slot]=jnoI8(0);\
			INVERSE_UPDATE(OVERF,slot)}

#define SAVE_CARRY(reg) { setc(reg);}


#define SAVE_ZERO(reg) { setz(reg);}


#define SAVE_SIGN(reg) {sets(reg);}

#define SAVE_OVERF(reg) { seto(reg);}


u32 matchCondition(u32 );



void leftShiftImm(x86GPReg);
void rightShiftImm(x86GPReg );
void leftShiftReg(x86GPReg );
void rightShiftReg(x86GPReg );
void aritShiftImm(x86GPReg );
void aritShiftReg(x86GPReg );
void rightRotImm(x86GPReg );
void rightRotReg(x86GPReg );

#endif
