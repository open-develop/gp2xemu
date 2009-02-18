#ifndef CPU_H_INCLUDED
#define CPU_H_INCLUDED
/* need uint32_t */
#include <stdint.h>

#define ARM_CPU_MODE_COUNT 7

/* When assigning these to ARM_StatusRegister::mode, we add an implicit bit 5
    to reflect the real ARM cpu mode values. */
#define ARM_CPU_MODE_USR 0x0
#define ARM_CPU_MODE_FIQ 0x1
#define ARM_CPU_MODE_IRQ 0x2
#define ARM_CPU_MODE_SVC 0x3
#define ARM_CPU_MODE_ABT 0x7
#define ARM_CPU_MODE_UND 0xB
#define ARM_CPU_MODE_SYS 0xF

/*  These are constant for now. Perhaps we could implement them as runtime
    variables later, to support High Vectors starting at 0xFFFF0000
*/  
#define EXCEPTION_VECTOR_TABLE_RESET    0x0
#define EXCEPTION_VECTOR_TABLE_UND      0x4
#define EXCEPTION_VECTOR_TABLE_SWI      0x8
#define EXCEPTION_VECTOR_TABLE_IABT     0xC     /*prefetch abort */
#define EXCEPTION_VECTOR_TABLE_DABT     0x10    /* data abort */
#define EXCEPTION_VECTOR_TABLE_IRQ      0x18
#define EXCEPTION_VECTOR_TABLE_FIQ      0x1C

#define SP 13
#define LR 14
#define PC 15
#define CPSR 0
#define SPSR 1

typedef union ARM_StatusRegister
{
    struct {
        uint32_t mode   : 5;
        uint32_t thumb  : 1;
        uint32_t fiq    : 1;
        uint32_t irq    : 1;
        uint32_t unused : 20;
        uint32_t V      : 1;
        uint32_t C      : 1;
        uint32_t Z      : 1;
        uint32_t N      : 1;
    } f;
    uint32_t value;
} ARM_StatusRegister;

typedef enum ARM_Exception
{
    ARM_Exception_None = 0x0,
    ARM_Exception_Reset = 0x1,
    ARM_Exception_Undefined = 0x2,
    ARM_Exception_Software_Interrupt = 0x4,
    ARM_Exception_Prefetch_Abort = 0x8,
    ARM_Exception_Data_Abort = 0x10,
    ARM_Exception_Interrupt = 0x20,
    ARM_Exception_Fast_Interrupt = 0x40,
    ARM_Exception_All = 0x7F,
    /* Not a part of the others. Unpredictable is an unrepairable state
        which makes the emulator close. */
    ARM_Exception_Unpredictable = 0x80
} ARM_Exception;

/* ARM_CPU is just a structure for storing all the registers,
 * as well as the co-processors (including CP15, the system co-processor */

typedef struct ARM_CPU
{
    /* regs[mode][reg]. Only seven modes, but 16 lets us map mode bitcodes directly */
    uint32_t* reg[16][16]; /* pointer indirection to handle banking */
    uint32_t regval[31]; /* actual register 'slots' */
    ARM_StatusRegister spsr[16]; /* 16 here, so we can use the mode flag as indices */
    ARM_StatusRegister cpsr; /* Shared by all modes */
    /* Exception list containing the enum values in ARM_Exception. Signaled by memory fetches,
        ARM/THUMB instructions, coprocessors and peripherals */
    int exception;
    /*  Cycles to wait (CPU stall) after each instruction
        Used to emulate correct timings. CPUs, Coprocessors
        and peripherals are independent.*/
    int cpubusywait;
    /* true after a branch. Flush the pipeline */
    int shouldflush;
} ARM_CPU;

void ResetCPU(ARM_CPU*);
void GetStatusRegisterMode(ARM_CPU* cpu, int which, int* result);
uint32_t* GetProgramCounter(ARM_CPU* cpu);
void RaiseException(ARM_CPU* cpu, ARM_Exception which);
void ClearException(ARM_CPU* cpu, ARM_Exception which);
ARM_Exception HandleException(ARM_CPU* cpu);
void FlushPipeline(ARM_CPU* cpu);
#endif // CPU_H_INCLUDED
