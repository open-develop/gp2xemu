#ifndef _arm920t_h_
#define _arm920t_h_
#include <arm_emu.h>


#ifdef _DEBUG_
#define  DEBUG_PRINT() do {printf("function: %s\n",__FUNCTION__);} while(0)
#else
#define DEBUG_PRINT() do{}while(0)
#endif



void armInit(void);
void armStart(void);
void armStop(void);

typedef struct {
	union reg{
		u32 uVal;
		s32 sVal;
		u32 *uPtr;
		s32 *sPtr;
	}reg;
}cpuRegister;

typedef struct {
	cpuRegister regs[6][16];
	cpuRegister spsr[5];
	cpuRegister cpsr;
	cpuRegister cp15[15];
	cpuRegister far,fsr;
}cpuRegs;

struct CPU {
	int mode;
	cpuRegs cpuRegs;
	u32 currentInst;
	void (*init)(void);
	void (*start)(void);
	void (*stop)(void);
}CPU;


#define GPR(x)		CPU.cpuRegs.regs[CPU.mode][x].reg
#define SPSR(x)		CPU.cpuRegs.spsr[CPU.mode][x].reg
#define CP15(x)		CPU.cpuRegs.cp15[x].reg
#define CPSR 		CPU.cpuRegs.cpsr.reg
#define EFLAGS 		CPU.cpuRegs.eflags
#define R0 GPR(0)
#define R1 GPR(1)
#define R2 GPR(2)
#define R3 GPR(3)
#define R4 GPR(4)
#define R5 GPR(5)
#define R6 GPR(6)
#define R7 GPR(7)
#define R8 GPR(8)
#define R9 GPR(9)
#define R10 GPR(10)
#define R11 GPR(11)
#define R12 GPR(12)
#define R13 GPR(13)
#define R14 GPR(14)
#define R15 GPR(15)
#define PC R15
#define SP R13
#define LR R14
#define FAR CPU.cpuRegs.far.reg
#define FSR CPU.cpuRegs.fsr.reg
/*----------------------------------------*/
#define CP15_0 	CP15(0)
#define CP15_1 	CP15(1)
#define CP15_2 	CP15(2)
#define CP15_3 	CP15(3)
#define CP15_4 	CP15(4)
#define CP15_5 	CP15(5)
#define CP15_6 	CP15(6)
#define CP15_7 	CP15(7)
#define CP15_8 	CP15(8)
#define CP15_9 	CP15(9)
#define CP15_10	CP15(10)
#define CP15_11	CP15(11)
#define CP15_12	CP15(12)
#define CP15_13	CP15(13)
#define CP15_14	CP15(14)
#define CP15_15	CP15(15)
#define TTB	CP15_2
/**/
#define SPSR0 SPSR(0)
#define SPSR1 SPSR(1)
#define SPSR2 SPSR(2)
#define SPSR3 SPSR(3)
#define SPSR4 SPSR(4)

#define MODE_USER	(0x10U)
#define MODE_FASTINT	(0x11U)
#define MODE_INTERRUPT 	(0x12U)
#define MODE_SUPERVISOR (0x13U)
#define MODE_ABORT	(0x17U)
#define MODE_UNDEFINED	(0x1BU)
#define MODE_SYSTEM	(0x1fU)

#define CINST CPU.currentInst

/*conditional bits   28:31 in the opcode */
#define SHIFT		28
#define EQUAL 		(0U<<SHIFT)
#define NEQUAL		(1U<<SHIFT)
#define HSAME		(2U<<SHIFT)
#define LOWER		(3U<<SHIFT)
#define	NEGATIVE	(4U<<SHIFT)
#define NNEGATIVE	(5U<<SHIFT)
#define OVERFLOW	(6U<<SHIFT)
#define NOVERFLOW	(7U<<SHIFT)
#define	HIGHER		(8U<<SHIFT)
#define SLOWER		(9U<<SHIFT)
#define SGEQUAL		(10U<<SHIFT)
#define SLESS		(11U<<SHIFT) 
#define SGREATER	(12U<<SHIFT)
#define SLEQUAL		(13U<<SHIFT)
#define	ALWAYS		(14U<<SHIFT)
#define NEVER		(15U<<SHIFT)

/* position of the condition code-flags in cpsr-register */
#define SIGN 	(31U)
#define ZERO	(30U)
#define CARRY	(29U)
#define OVERF	(28U)

#define QFLAG 	(27U)
#define THUMB	(5U)
#define FINT	(6U)
#define INT	(7U)

#define _NEG_SHFT_ 	(CPSR.uVal>>NEG)
#define _ZERO_SHIFT_ 	(CPSR.uVal>>ZERO)
#define _CARRY_SHIFT_	(CPSR.uVal>>CARRY)
#define _OVERF_SHIFT	(CPSR.uVal>>OVERF)
#define _QFLAG_SHIFT_	(CPSR.uVal>>QFLAG)

/*macros for extracting the operands from an instruction */

#define _IMMF_		((CPU.currentInst>>25)&1)
#define _UPDATE_FLAGS_ 	((CPU.currentInst>>20)&1U)
#define _Rd_ 		((CPU.currentInst>>12)&0x0fU)
#define _Rn_ 		((CPU.currentInst>>16)&0x0fU)
#define _Rm_		(CPU.currentInst&0x0fU)
#define _Rs_		((CPU.currentInst>>8)&(0x0fU))
#define _IMM_		(CPU.currentInst&(0xffU))
#define _W_		(CPU.currentInst&(1<<21))
#define _RORIMM_	(CPU.currentInst&(0x0f00U))

#define _COND_		((CPU.currentInst>>28))

#endif
