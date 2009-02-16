#ifndef INSTRSET_ARM_H_INCLUDED
#define INSTRSET_ARM_H_INCLUDED
#include <stdint.h>
#include "disasm_arm.h"
#include "cpu/cpu.h"
#include "peripherals/memory.h"

/* 32-bit immediate */
typedef struct ARMV4_Instr_DataProc_Immediate
{
    uint32_t immed  : 8;
    uint32_t rotate : 4;
    uint32_t Rd     : 4;
    uint32_t Rn     : 4;
    uint32_t S      : 1;
    uint32_t opcode1: 4;
    uint32_t opcode0: 3;
    uint32_t cond   : 4;
} ARMV4_Instr_DataProc_Immediate;

/* rotate register by immediate */
typedef struct ARMV4_Instr_DataProc_Immed_Shift
{
    uint32_t Rm     : 4;
    uint32_t SBZ    : 1;
    uint32_t shift  : 2;
    uint32_t amount : 5;
    uint32_t Rd     : 4;
    uint32_t Rn     : 4;
    uint32_t S      : 1;
    uint32_t opcode1: 4;
    uint32_t opcode0: 3;
    uint32_t cond   : 4;
} ARMV4_Instr_DataProc_Immed_Shift;

/* register shift by register */
typedef struct ARMV4_Instr_DataProc_Register_Shift
{
    uint32_t Rm     : 4;
    uint32_t SBO    : 1;
    uint32_t shift  : 2;
    uint32_t SBZ    : 1;
    uint32_t Rs     : 4;
    uint32_t Rd     : 4;
    uint32_t Rn     : 4;
    uint32_t S      : 1;
    uint32_t opcode1: 4;
    uint32_t opcode0: 3;
    uint32_t cond   : 4;
} ARMV4_Instr_DataProc_Register_Shift;

typedef enum ARMV4_AddressMode1ShiftType
{
    LSL = 0,
    LSR,
    ASR,
    ROR
} ARMV4_AddressMode1ShiftType;

typedef struct ARMV4_Instr_Multiply
{
    uint32_t Rm     : 4;
    uint32_t opcode1: 4;
    uint32_t Rs     : 4;
    uint32_t Rn     : 4;
    uint32_t Rd     : 4;
    uint32_t S      : 1;
    uint32_t A      : 1;
    uint32_t U      : 1;
    uint32_t islong : 1;
    uint32_t opcode0: 4;
    uint32_t cond   : 4;
} ARMV4_Instr_Multiply;

typedef struct ARMV4_Instr_LoadStore_Half_RegisterOffset
{
        uint32_t Rm     : 4;
        uint32_t opcode1: 4;
        uint32_t SBZ    : 4;
        uint32_t Rd     : 4;
        uint32_t Rn     : 4;
        uint32_t L      : 1;
        uint32_t W      : 1;
        uint32_t B      : 1; /* Must be zero*/
        uint32_t U      : 1;
        uint32_t P      : 1;
        uint32_t opcode0: 3;
        uint32_t cond   : 4;
} ARMV4_Instr_LoadStore_Half_RegisterOffset;

typedef struct ARMV4_Instr_LoadStore_Half_ImmediateOffset
{
        uint32_t LoOff  : 4;
        uint32_t opcode1: 4;
        uint32_t HiOff  : 4;
        uint32_t Rd     : 4;
        uint32_t Rn     : 4;
        uint32_t L      : 1;
        uint32_t W      : 1;
        uint32_t B      : 1; /* Must be one*/
        uint32_t U      : 1;
        uint32_t P      : 1;
        uint32_t opcode0: 3;
        uint32_t cond   : 4;
} ARMV4_Instr_LoadStore_Half_ImmediateOffset;


typedef struct ARMV4_Instr_LoadStore_Signed_Half_RegisterOffset
{
        uint32_t Rm     : 4;
        uint32_t opcode2: 1;
        uint32_t H      : 1;
        uint32_t opcode1: 2;
        uint32_t SBZ    : 4;
        uint32_t Rd     : 4;
        uint32_t Rn     : 4;
        uint32_t L      : 1; /* Must be one. Load only */
        uint32_t W      : 1;
        uint32_t B      : 1; /* Must be zero */
        uint32_t U      : 1;
        uint32_t P      : 1;
        uint32_t opcode0: 3;
        uint32_t cond   : 4;
} ARMV4_Instr_LoadStore_Signed_Half_RegisterOffset;

typedef struct ARMV4_Instr_LoadStore_Signed_Half_ImmediateOffset
{
        uint32_t LoOff  : 4;
        uint32_t opcode2: 1;
        uint32_t H      : 1;
        uint32_t opcode1: 2;
        uint32_t HiOff  : 4;
        uint32_t Rd     : 4;
        uint32_t Rn     : 4;
        uint32_t L      : 1; /* Must be one. Load only */
        uint32_t W      : 1;
        uint32_t B      : 1; /* Must be one */
        uint32_t U      : 1;
        uint32_t P      : 1;
        uint32_t opcode0: 3;
        uint32_t cond   : 4;
} ARMV4_Instr_LoadStore_Signed_Half_ImmediateOffset;


typedef union ARMV4_Instruction
{
    /* 'shift' is 00 = LSL, LSR, ASR, ROR */
    ARMV4_Instr_DataProc_Immediate          dp_im;
    ARMV4_Instr_DataProc_Immed_Shift        dp_is;  /* also rrx (shift=0b11), and pure register operand (shift=0b00)*/
    ARMV4_Instr_DataProc_Register_Shift     dp_rs;

    ARMV4_Instr_Multiply                    mul;
    uint32_t word;
} ARMV4_Instruction;

int CheckConditionFlag(ARM_CPU* cpu, int instr);
int ARMV4_ExecuteInstruction(ARM_CPU* cpu, ARM_Memory* mem, ARMV4_Instruction instr, int type);
#endif
