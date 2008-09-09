#ifndef _x86_h_
#define _x86_h_
#include <arm_emu.h>
#define DISP32 	5
#define SIB 	4
#define OP_SIZE 	0x66
#define ADDR_SIZE 	0x67

/* position of the flags in EFLAGS */
#define X86CARRY	(0)
#define X86ZERO		(1<<6)
#define X86SIGN		(1<<7)
#define X86OVERF	(1<<11)



#ifdef DEBUG
#define WRITE8(data)  { printf("%p\n",X86CODE); \
			(*(u8 *)X86CODE)=(u8)data; \
			X86CODE++;}

#define WRITE16(data) { printf("%p\n",X86CODE); \
			(*(u16 *)X86CODE)=(u16)data; \
			X86CODE+=2;}

#define WRITE32(data) { printf("%p\n",X86CODE); \
			(*(u32 *)X86CODE)=(u32)data; \
			X86CODE+=4;}

#define WRITE64(data) { (*(u64 *)X86CODE)=(u64)data; \
			X86CODE+=8;}
#else 
#define WRITE8(data)  { (*(u8 *)X86CODE)=(u8)data; \
			X86CODE++;}

#define WRITE16(data) { (*(u16 *)X86CODE)=(u16)data; \
			X86CODE+=2;}

#define WRITE32(data) { (*(u32 *)X86CODE)=(u32)data; \
			X86CODE+=4;}

#define WRITE64(data) { (*(u64 *)X86CODE)=(u64)data; \
			X86CODE+=8;}


#define CALLFUNC(func)\
			callRel32((u32)func-(u32)X86CODE+5)

#endif
#define X86CODE code_ptr

u8 *code_ptr;

typedef enum {
	NONE=-1,
	EAX=0,
	ECX,
	EDX,
	EBX,
	ESP,
	EBP,
	ESI,
	EDI
}x86GPReg;


typedef enum {
	AL=0,
	CL,
	DL,
	BL,
	AH,
	CH,
	DH,
	BH
}x86GPReg8;

/*  since the constants in the reg field dont match the ones from the [extended] registers
 *  we need a seperate enum for 8bit regs
 */


typedef enum {
	MM0=0,
	MM1,
	MM2,
	MM3,
	MM4,
	MM5,
	MM6,
	MM7
}x86MMXReg;


typedef enum {
	XMM0=0,
	XMM1,
	XMM2,
	XMM3,
	XMM4,
	XMM5,
	XMM6,
	XMM7
}x86XMMReg;

u8 *x86Tmp[32];

/*---------------------------------------*/
__inline void ModRM(u32 ,u32,u32);
__inline void Sib(u32 ,u32 ,u32 );
/*---------------------------------------------------------------*/
void adc32ItoEAX(s32 );
void adc16ItoAX(s16 );
void adc8ItoAL(s8 );
void adc32RtoR(x86GPReg, x86GPReg);
void adc32RtoM(x86GPReg, void *);
void adc32ItoR(s32, x86GPReg );
void adc32ItoM(s32, void *);
void adc32ItoRm(s32, x86GPReg, x86GPReg,u32);
void adc32RtoRm(x86GPReg , x86GPReg ,x86GPReg ,u32 );
void adc32RmtoR(x86GPReg, x86GPReg, u32 , x86GPReg);
/*-------------------------------------------------------*/
void add32ItoEAX(s32 );
void add16ItoAX(s16 );
void add32I8toR(s8, x86GPReg);
void add32I8toM(s8,void *);
void add32I8toRm(s8,x86GPReg ,x86GPReg ,u32 );
void add32ItoR(s32 ,x86GPReg);
void add32ItoRm(s32 , x86GPReg, x86GPReg, u32 );
void add32RtoR(x86GPReg, x86GPReg);
void add32MtoR(void *, x86GPReg );
void add32RmtoR(x86GPReg,x86GPReg,u32, x86GPReg  );
void add32RtoM(x86GPReg, void *);
void add32RtoRm(x86GPReg, x86GPReg, x86GPReg, u32 );
void xadd32RtoR(x86GPReg, x86GPReg );
void xadd32RtoM(x86GPReg, void *);
void xadd32RtoRm(x86GPReg, x86GPReg, x86GPReg, u32 );
/*----------------------------------------------------------*/
void xchg16RtoAX(x86GPReg );
void xchg32RtoEAX(x86GPReg );
void xchg32RtoR(x86GPReg ,x86GPReg);
void xchg32RtoM(x86GPReg ,void *);
void xchg32RtoRm(x86GPReg, x86GPReg, x86GPReg , u32 );
void xchg32MtoR(void *, x86GPReg );
void xchg32RmtoR(x86GPReg, x86GPReg, u32, x86GPReg);
/*----------------------------------------------------------*/
void sub16IfmAX(s16 );
void sub32IfmEAX(s32 );
void sub32IfmR(s32, x86GPReg ) ;
void sub32IfmM(s32, void *);
void sub32IfmRm(x86GPReg, x86GPReg, u32 ,s32 );
void sub32RfmR(x86GPReg ,x86GPReg);
void sub32RfmM(x86GPReg, void *);
void sub32RfmRm(x86GPReg, x86GPReg , x86GPReg, u32);
void sub32MfmR(void *, x86GPReg );
void sub32RmfmR(x86GPReg, x86GPReg ,u32 , x86GPReg );
/*---------------------------------------------------------*/
void sbb8IfmAL(s8 );
void sbb16IfmAX(s16 );
void sbb32IfmEAX(s32 );
void sbb32IfmR(s32 , x86GPReg );
void sbb32IfmM(s32 , void *);
void sbb32RfmR(x86GPReg, x86GPReg );
void sbb32RfmM(x86GPReg, void *);
void sbb32RfmRm(x86GPReg, x86GPReg, x86GPReg, u32);
void sbb32MfmR(void *, x86GPReg );
void sbb32RmfmR(x86GPReg, x86GPReg, u32, x86GPReg );

/*---------------------------------------------------------*/
void lea32RmtoR(x86GPReg, x86GPReg, u32 , x86GPReg);
/*---------------------------------------------------------*/
void and16ItoAX(s16);
void and32ItoEAX(s32 );
void and32ItoR(s32, x86GPReg);
void and32ItoM(s32 ,void *);
void and32ItoRm(s32, x86GPReg , x86GPReg ,u32 );
void and32RtoR(x86GPReg, x86GPReg);
void and32RtoM(x86GPReg, void *);
void and32RtoRm(x86GPReg, x86GPReg, x86GPReg, u32 );
void and32RmtoR(x86GPReg ,x86GPReg, u32, x86GPReg);
void and32MtoR(void *, x86GPReg);
/*---------------------------------------------------------*/
void or16ItoAX(s16 );
void or32ItoEAX(s32 );
void or32ItoR(s32 ,x86GPReg );
void or32ItoM(s32 ,void *);
void or32ItoRm(s32,x86GPReg, x86GPReg, u32 );
void or32RtoR(x86GPReg ,x86GPReg);
void or32RtoM(x86GPReg, void *);
void or32RtoRm(x86GPReg, x86GPReg ,x86GPReg, u32);
void or32MtoR(void *, x86GPReg );
void or32RmtoR(x86GPReg, x86GPReg , u32, x86GPReg );
/*---------------------------------------------------------*/
void neg16R(x86GPReg );
void neg16M(void *);
void neg32Rm(x86GPReg, x86GPReg, u32);
void neg32R(x86GPReg);
void neg32M(void *);
void neg32Rm(x86GPReg, x86GPReg ,u32 );

/*---------------------------------------------------------*/
void not32R(x86GPReg );
void not32M(void *);
void not32Rm(x86GPReg ,x86GPReg, u32 );
/*---------------------------------------------------------*/
void xor16ItoAX(s16 );
void xor32ItoEAX(s32);
void xor32ItoR(s32, x86GPReg );
void xor32ItoM(s32, void *);
void xor32ItoRm(s32,x86GPReg, x86GPReg, u32);
void xor32RtoR(x86GPReg, x86GPReg);
void xor32RtoM(x86GPReg, void *);
void xor32RtoRm(x86GPReg, x86GPReg, x86GPReg, u32);
void xor32MtoR(void *, x86GPReg );
void xo32RmtoR(x86GPReg, x86GPReg, u32, x86GPReg );
/*---------------------------------------------------------*/
void mul32R(x86GPReg );
void mul32M(void *);
void mul32Rm(x86GPReg , x86GPReg , u32 );
void imul32R(x86GPReg );
void imul32MtoR(void *, x86GPReg );
void imul32RtoR(x86GPReg, x86GPReg );
void imul32RmtoR(x86GPReg, x86GPReg, u32 scale, x86GPReg );
/*---------------------------------------------------------*/
void div32R(x86GPReg );
void div32M(void *);
void div32Rm(x86GPReg ,x86GPReg ,u32);
void idiv32R(x86GPReg );
void idiv32M(void *);
void idiv32Rm(x86GPReg , x86GPReg ,u32 );
/*---------------------------------------------------------*/
void mov32RtoR(x86GPReg , x86GPReg);
void mov32RtoM(x86GPReg, void *);
void mov32RmtoR(x86GPReg, x86GPReg , u32, x86GPReg  );
void mov32RtoRm(x86GPReg, x86GPReg ,x86GPReg , u32);
void mov32MtoR(void *, x86GPReg );
void mov32ItoR(s32, x86GPReg  );
void mov32ItoM(s32, void *);

void movzxR8toR32(x86GPReg ,x86GPReg );
void movzxM8toR32(void *, x86GPReg );
void movzxR8toR16(x86GPReg, x86GPReg);
void movzxM8toR16(void *, x86GPReg );
void movzxR16toR32(x86GPReg, x86GPReg );
void movzxM16toR32(void *, x86GPReg );

void movsxR8toR16(x86GPReg, x86GPReg );
void movsxM8toR16(void *, x86GPReg );
void movsxR8toR32(x86GPReg ,x86GPReg);
void movsxM8toR32(void *, x86GPReg );
void movsxR16toR32(x86GPReg ,x86GPReg );
void movsxM16toR32(void *, x86GPReg );
/*---------------------------------------------------------*/
void ror32M(void *, s8);
void ror32R(x86GPReg, s8);
void ror32R1(x86GPReg );
void ror32M1(void *);
void ror32RCL(x86GPReg);
void ror32MCL(void *);
void rol32R1(x86GPReg );
void rol32M1(void *);
void rol32RCL(x86GPReg );
void rol32MCL(void *);
void rol32R(x86GPReg ,s8);
void rol32M(void *,s8);
void rcl32R1(x86GPReg );
void rcl32M1(void *);
void rcl32RCL(x86GPReg );
void rcl32MCL(void *);
void rcl32R(x86GPReg , s8);
void rcl32M(void * , s8);
void rcr32R1(x86GPReg );
void rcr32M1(void *);
void rcr32RCL(x86GPReg );
void rcr32MCL(void *);
void rcr32R(x86GPReg , s8);
void rcr32M(void *, s8);
/*---------------------------------------------------------------*/
void shl32R1(x86GPReg );
void shl32M1(void *);
void shl32RCL(x86GPReg );
void shl32MCL(void * );
void shl32R(x86GPReg,s8 );
void shl32M(void *to,s8 );
void shr32R1(x86GPReg );
void shr32M1(void *);
void shr32RCL(x86GPReg );
void shr32MCL(void *);
void shr32R(x86GPReg ,s8 );
void shr32M(void *,s8);
void sar32R1(x86GPReg );
void sar32M1(void * );
void sar32RCL(x86GPReg );
void sar32MCL(void *);
void sar32R(x86GPReg , s8);
void sar32M(void *, s8);
/*--------------------------------------------------*/
void test16ItoAX(s16);
void test32ItoEAX(s32 );
void test32ItoR(s32, x86GPReg);
void test32ItoM(s32, void *);
void test32ItoRm(s32, x86GPReg, x86GPReg, u32);
void test32RtoR(x86GPReg, x86GPReg );
void test32RtoM(x86GPReg, void *);
void test32RtoRm(x86GPReg, x86GPReg, x86GPReg, u32 );
/*--------------------------------------------------*/
void cmp16ItoAX(s16 );
void cmp32ItoEAX(s32 );
void cmp32ItoR(s32 , x86GPReg );
void cmp32ItoM(s32, void *);
void cmp32ItoRm(s32 , x86GPReg, x86GPReg, u32 );
void cmp32RtoR(x86GPReg, x86GPReg );
void cmp32RtoM(x86GPReg, void *);
void cmp32RtoRm(x86GPReg ,x86GPReg ,x86GPReg ,u32 );
void cmp32MtoR(void *, x86GPReg );
void cmp32RmtoR(x86GPReg ,x86GPReg ,u32, x86GPReg  );
void cmpsw(void);
void cmpsd(void);
/*----------------------------------------------------------*/
void inc32R(x86GPReg );
void inc32M(void *);
void inc32Rm(x86GPReg , x86GPReg ,u32 );
void dec32R(x86GPReg );
void dec32M(void *);
void dec32Rm(x86GPReg, x86GPReg, u32);
void nop(void);
void ret(void);
void stc(void);
void std(void);
void sti(void);
void clc(void);
void cld(void);
void cli(void);
void push16R(x86GPReg );
void push32R(x86GPReg);
void pushI8(s8);
void pushI16(s16);
void pushI32(s32);
void push32M(void *);
void pusha(void);
void pushad(void);
void pushf(void);
void pushfd(void);
void pop16R(x86GPReg );
void pop32R(x86GPReg );
void callRel16(s16 );
void callRel32(s32 );
void call32R(x86GPReg );
void call32M(void *);
void call32Rm(x86GPReg, x86GPReg, u32 );
void call32SegOff(u16,u32);
void cbw(void);
void cdq(void);
void bt32I8toR(s8, x86GPReg );
void bt32I8toM(s8, void *);
void bt32I8toRm(s8, x86GPReg ,x86GPReg ,u32);
void bt32RtoR(x86GPReg8 , x86GPReg );
void bt32RtoM(x86GPReg8 , void *);
void bt32RtoRm(x86GPReg8, x86GPReg ,x86GPReg , u32);


void bts32I8toR(s8, x86GPReg);
void bts32I8toM(s8, void *);
void bts32I8toRm(s8, x86GPReg, x86GPReg, u32);
void bts32RtoR(x86GPReg8, x86GPReg);
void bts32RtoM(x86GPReg8,void *);
void bts32RtoRm(x86GPReg8, x86GPReg, x86GPReg, u32);

void bsr32RtoR(x86GPReg, x86GPReg );
void bsr32MtoR(void *, x86GPReg );
void bsr32RmtoR(x86GPReg ,x86GPReg, u32, x86GPReg);

void btr32I8toR(s8, x86GPReg );
void btr32I8toM(s8, void *);
void btr32I8toRm(s8, x86GPReg, x86GPReg, u32 );
void btr32RtoR(x86GPReg8, x86GPReg );
void btr32RtoM(x86GPReg8, void *);
void btr32RtoRm(x86GPReg8, x86GPReg, x86GPReg, u32);

void btc32I8toR(s8, x86GPReg );
void btc32I8toM(s8, void *);
void btc32I8toRm(s8, x86GPReg, x86GPReg, u32);
void btc32RtoR(x86GPReg8, x86GPReg );
void btc32RtoM(x86GPReg8, void *);
void btc32RtoRm(x86GPReg8, x86GPReg, x86GPReg, u32);

void bswap(x86GPReg );
/*-------------------------------------------------------------------*/
/* always operate on 8-bit-registers 
 * i dont implement memory operands here 
 */

void set8R(u32, x86GPReg8 );
void seta(x86GPReg8);
void setae(x86GPReg8);
void setb(x86GPReg8);
void setbe(x86GPReg8);
void setc(x86GPReg8);
void sete(x86GPReg8 );
void setg(x86GPReg8 );
void setge(x86GPReg8 );
void setl(x86GPReg8 );
void setle(x86GPReg8 );
void setna(x86GPReg8 );
void setnae(x86GPReg8 );
void setnb(x86GPReg8 );
void setnbe(x86GPReg8 );
void setnc(x86GPReg8 );
void setne(x86GPReg8 );
void setng(x86GPReg8 );
void setnge(x86GPReg8 );
void setnl(x86GPReg8 );
void setnle(x86GPReg8 );
void setno(x86GPReg8 );
void setnp(x86GPReg8 );
void setns(x86GPReg8 );
void setnz(x86GPReg8 );
void seto(x86GPReg8 );
void setp(x86GPReg8 );
void setpe(x86GPReg8 );
void setpo(x86GPReg8 );
void sets(x86GPReg8 );
void setz(x86GPReg8 );

/*---------------------------------------------------------------*/
void x86SetJI8(u8 *);
void jmp32R(x86GPReg );

u8 *setJmpI16(u32 , s16 );
u8 *setJmpI32(u32 , s32 );
u8 *jmpI8(s8 );
u8 *jmpI16(s16 );
u8 *jmpI32(s32 );

u8 *jaI8(s8 );
u8 *jaI16(s16);
u8 *jaI32(s32 );

u8 *jeI8(s8 );
u8 *jeI16(s16 );
u8 *jeI32(s32 );

u8 *jzI8(s8 );
u8 *jzI16(s16 );
u8 *jzI32(s32 );

u8 *jcI8(s8 );
u8 *jcI16(s16 );
u8 *jcI32(s32 );

u8 *jsI8(s8 );
u8 *jsI16(s16 );
u8 *jsI32(s32 );

u8 *joI8(s8 );
u8 *joI16(s16 );
u8 *joI32(s32 );

u8 *jnzI8(s8 );
u8 *jnzI16(s16 );
u8 *jnzI32(s32 );

u8 *jnoI8(s8 );
u8 *jnoI16(s16 );
u8 *jnoI32(s32 );

u8 *jncI8(s8 );
u8 *jncI16(s16 );
u8 *jncI32(s32 );

u8 *jnsI8(s8 );
u8 *jnsI16(s16 );
u8 *jnsI32(s32 );
/*---------------------------------------------------------------*/
void cmova32RtoR(x86GPReg , x86GPReg );
void cmova32MtoR(void *, x86GPReg );
void comva32RmtoR(x86GPReg, x86GPReg, u32, x86GPReg);

void cmovae32RtoR(x86GPReg, x86GPReg );
void cmovae32MtoR(void *, x86GPReg );
void cmovae32RmtoR(x86GPReg, x86GPReg, u32, x86GPReg );

void cmovb32RtoR(x86GPReg ,x86GPReg );
void cmovb32MtoR(void *, x86GPReg );
void cmovb32RmtoR(x86GPReg, x86GPReg, u32, x86GPReg );

void cmovbe32RtoR(x86GPReg ,x86GPReg );
void cmovbe32MtoR(void *, x86GPReg );
void cmovbe32RmtoR(x86GPReg, x86GPReg, u32, x86GPReg );

void cmovc32RtoR(x86GPReg ,x86GPReg );
void cmovc32MtoR(void *, x86GPReg );
void cmovc32RmtoR(x86GPReg, x86GPReg, u32, x86GPReg );

void cmove32RtoR(x86GPReg ,x86GPReg );
void cmove32MtoR(void *, x86GPReg );
void cmove32RmtoR(x86GPReg, x86GPReg, u32, x86GPReg );

void cmovg32RtoR(x86GPReg ,x86GPReg );
void cmovg32MtoR(void *, x86GPReg );
void cmovg32RmtoR(x86GPReg, x86GPReg, u32, x86GPReg );


void cmovge32RtoR(x86GPReg ,x86GPReg );
void cmovge32MtoR(void *, x86GPReg );
void cmovge32RmtoR(x86GPReg, x86GPReg, u32, x86GPReg );


void cmovl32RtoR(x86GPReg ,x86GPReg );
void cmovl32MtoR(void *, x86GPReg );
void cmovl32RmtoR(x86GPReg, x86GPReg, u32, x86GPReg );


void cmovle32RtoR(x86GPReg ,x86GPReg );
void cmovle32MtoR(void *, x86GPReg );
void cmovle32RmtoR(x86GPReg, x86GPReg, u32, x86GPReg );


void cmovna32RtoR(x86GPReg ,x86GPReg );
void cmovna32MtoR(void *, x86GPReg );
void cmovna32RmtoR( x86GPReg, x86GPReg, u32, x86GPReg  );

void cmovnae32RtoR(x86GPReg ,x86GPReg );
void cmovnae32MtoR(void *,x86GPReg );
void cmovnae32RmtoR(x86GPReg, x86GPReg, u32, x86GPReg );

void cmovnb32RtoR(x86GPReg ,x86GPReg );
void cmovnb32MtoR(void *,x86GPReg );
void cmovnb32RmtoR(x86GPReg, x86GPReg, u32, x86GPReg );

void cmovnbe32RtoR(x86GPReg ,x86GPReg );
void cmovnbe32MtoR(void *, x86GPReg );
void cmovnbe32RmtoR(x86GPReg, x86GPReg, u32, x86GPReg );

void cmovnc32RtoR(x86GPReg ,x86GPReg );
void cmovnc32MtoR(void *, x86GPReg);
void cmovnc32RmtoR(x86GPReg, x86GPReg, u32, x86GPReg  );

void cmovne32RtoR(x86GPReg ,x86GPReg );
void cmovne32MtoR(void *,x86GPReg);
void cmovne32RmtoR(x86GPReg, x86GPReg, u32, x86GPReg  );

void cmovng32RtoR(x86GPReg ,x86GPReg );
void cmovng32MtoR(void *, x86GPReg );
void cmovng32RmtoR(x86GPReg, x86GPReg, u32, x86GPReg  );

void cmovnge32RtoR(x86GPReg ,x86GPReg );
void cmovnge32MtoR(void *, x86GPReg );
void cmovnge32RmtoR(x86GPReg, x86GPReg, u32, x86GPReg  );

void cmovnl32RtoR(x86GPReg ,x86GPReg );
void cmovnl32MtoR(void *, x86GPReg );
void cmovnl32RmtoR(x86GPReg, x86GPReg, u32, x86GPReg );


void cmovnle32RtoR(x86GPReg ,x86GPReg );
void cmovnle32MtoR(void *, x86GPReg );
void cmovnle32RmtoR(x86GPReg, x86GPReg, u32, x86GPReg );

void cmovno32RtoR(x86GPReg ,x86GPReg );
void cmovno32MtoR(void *, x86GPReg );
void cmovno32RmtoR(x86GPReg, x86GPReg, u32, x86GPReg  );


void cmovnp32RtoR(x86GPReg ,x86GPReg );
void cmovnp32MtoR(void *, x86GPReg );
void cmovnp32RmtoR(x86GPReg, x86GPReg, u32, x86GPReg );


void cmovns32RtoR(x86GPReg ,x86GPReg );
void cmovns32MtoR(void *, x86GPReg );
void cmovns32RmtoR(x86GPReg, x86GPReg, u32, x86GPReg );


void cmovnz32RtoR(x86GPReg ,x86GPReg );
void cmovnz32MtoR(void *, x86GPReg );
void cmovnz32RmtoR(x86GPReg, x86GPReg, u32, x86GPReg );


void cmovo32RtoR(x86GPReg ,x86GPReg );
void cmovo32MtoR(void *, x86GPReg );
void cmovo32RmtoR(x86GPReg, x86GPReg, u32,x86GPReg );

void cmovp32RtoR(x86GPReg ,x86GPReg );
void cmovp32MtoR(void *, x86GPReg );
void cmovp32RmtoR(x86GPReg, x86GPReg, u32, x86GPReg );

void cmovpe32RtoR(x86GPReg ,x86GPReg );
void cmovpe32MtoR(void *, x86GPReg );
void cmovpe32RmtoR(x86GPReg, x86GPReg, u32, x86GPReg );

void cmovpo32RtoR(x86GPReg ,x86GPReg );
void cmovpo32MtoR(void *, x86GPReg );
void cmovpo32RmtoR(x86GPReg, x86GPReg, u32, x86GPReg );

void cmovs32RtoR(x86GPReg ,x86GPReg );
void cmovs32MtoR(void *, x86GPReg );
void cmovs32RmtoR(x86GPReg, x86GPReg, u32, x86GPReg );

void cmovz32RtoR(x86GPReg ,x86GPReg );
void cmovz32MtoR(void *, x86GPReg );
void cmovz32RmtoR(x86GPReg, x86GPReg, u32, x86GPReg );
/*-----------------------------------------------------------------*/



#define CMOV32RtoR(name,opcode) __inline void name##32RtoR(x86GPReg from ,x86GPReg to){\
					WRITE16(opcode);\
					ModRM(from,to,3);\
					return;}
					
#define CMOV32MtoR(name,opcode) __inline void name##32MtoR(void *from, x86GPReg to){\
					WRITE16(opcode);\
					ModRM(DISP32,to,0);\
					WRITE32(from);\
					return;}

#define CMOV32RmtoR(name,opcode) __inline void name##32RmtoR(x86GPReg base, x86GPReg index, u32 scale, x86GPReg to){\
					WRITE16(opcode);\
					if(index==NONE){\
						ModRM(base,to,0);\
					}\
					else {\
						ModRM(SIB,to,0);\
						Sib(base,index,scale==0?1:scale&3U);\
					}\
					return;}
				
#define CMOV32ALL(name,opcode) 	CMOV32RtoR(name,opcode)\
			       	CMOV32MtoR(name,opcode)\
				CMOV32RmtoR(name,opcode)



#endif
