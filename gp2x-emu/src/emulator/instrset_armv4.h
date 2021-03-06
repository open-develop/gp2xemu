/*
Copyright (c) 2009,
Mads Andreas Elvheim

Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files, to deal in the software without
restriction, including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the software, and to permit persons to whom the
software is furnished to do so, subject to the following
conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef INSTRSET_ARM_H_INCLUDED
#define INSTRSET_ARM_H_INCLUDED
#include <stdint.h>
#include "disasm_arm.h"
#include "cpu/cpu.h"
#include "peripherals/memory.h"

/*************************************************************************
*************Addressing mode1, data processing operations*****************
*************************************************************************/

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

typedef enum ARMV4_AddressModeShiftType
{
    LSL = 0,
    LSR,
    ASR,
    ROR,
    RRX
} ARMV4_AddressModeShiftType;

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

/***********************************************************************
************ Addressing Mode 2 Load/Store unsigned byte/word ***********
************************************************************************/

typedef struct ARMV4_Instr_LoadStore_ImmediateOffset
{
    uint32_t offset12 : 12;
    uint32_t Rd : 4;
    uint32_t Rn : 4;
    uint32_t L  : 1;
    uint32_t W  : 1;
    uint32_t B  : 1;
    uint32_t U  : 1;
    uint32_t P  : 1;
    uint32_t opcode0 : 3;
    uint32_t cond : 4;
} ARMV4_Instr_LoadStore_ImmediateOffset;

/* scaled, also register base and register offset is a special case
    with shift (LSL) and shift_imm as zero*/
typedef struct ARMV4_Instr_LoadStore_RegisterOffset
{
    uint32_t Rm : 4;
    uint32_t SBZ : 1;
    uint32_t shift : 2;
    uint32_t shift_imm : 5;
    uint32_t Rd : 4;
    uint32_t Rn : 4;
    uint32_t L  : 1;
    uint32_t W  : 1;
    uint32_t B  : 1;
    uint32_t U  : 1;
    uint32_t P  : 1;
    uint32_t opcode0 : 3;
    uint32_t cond : 4;
} ARMV4_Instr_LoadStore_RegisterOffset;

typedef enum ARMV4_LoadStoreMode
{
    ARM_LoadStore_PostIndexed = 0,
    ARM_LoadStore_PostIndexed_T = 1,
    ARM_LoadStore_Offset = 2,
    ARM_LoadStore_PreIndexed = 3
} ARMV4_LoadStoreMode;

/**************************************************************************************** 
*****Addressing Mode 3 Load/Store halfword, load signed byte, load/store doubleword *****
******************************************************************************************/
typedef struct ARMV4_Instr_LoadStore_Half_RegisterOffset
{
        uint32_t Rm     : 4;
        uint32_t opcode2: 1;
        uint32_t H      : 1;
        uint32_t S      : 1;
        uint32_t opcode1: 1;
        uint32_t SBZ    : 4;
        uint32_t Rd     : 4;
        uint32_t Rn     : 4;
        uint32_t L      : 1;
        uint32_t W      : 1;
        uint32_t B      : 1; /* differs between register and immediate */
        uint32_t U      : 1;
        uint32_t P      : 1;
        uint32_t opcode0: 3;
        uint32_t cond   : 4;
} ARMV4_Instr_LoadStore_Half_RegisterOffset;

typedef struct ARMV4_Instr_LoadStore_Half_ImmediateOffset
{
        uint32_t LoOff  : 4;
        uint32_t opcode2: 1;
        uint32_t H      : 1;
        uint32_t S      : 1;
        uint32_t opcode1: 1;
        uint32_t HiOff  : 4;
        uint32_t Rd     : 4;
        uint32_t Rn     : 4;
        uint32_t L      : 1;
        uint32_t W      : 1;
        uint32_t B      : 1;    /* differs between register and immediate */
        uint32_t U      : 1;
        uint32_t P      : 1;
        uint32_t opcode0: 3;
        uint32_t cond   : 4;
} ARMV4_Instr_LoadStore_Half_ImmediateOffset;

typedef enum ARMV4_LoadStoreMultipleMode
{
    ARM_LoadStoreMultiple_DecrementAfter = 0,   /* Same as Full  Ascending P=0, U=0 */
    ARM_LoadStoreMultiple_IncrementAfter,       /* Same as Full  Descending P=0, U=0 */
    ARM_LoadStoreMultiple_DecrementBefore,      /* Same as Empty Ascending P=0, U=0 */
    ARM_LoadStoreMultiple_IncrementBefore        /* Same as Empty Descending P=0, U=0 */
} ARMV4_LoadStoreMultipleMode;

typedef struct ARMV4_Instr_LoadStoreMultiple
{
    uint32_t register_list  : 16;
    uint32_t Rn             : 4;
    uint32_t L              : 1;
    uint32_t W              : 1;
    uint32_t S              : 1;
    uint32_t U              : 1;
    uint32_t P              : 1;
    uint32_t opcode0        : 3;
    uint32_t cond           : 4;
} ARMV4_Instr_LoadStoreMultiple;

typedef struct ARMV4_Instr_Branch
{
    uint32_t immed24    : 24; /* signed */
    uint32_t L          : 1;
    uint32_t opcode0    : 3;
    uint32_t cond       : 4;
} ARMV4_Instr_Branch;

typedef struct ARMV4_Instr_MRS
{
    uint32_t SBZ    : 12;
    uint32_t Rd     : 4;
    uint32_t SBO    : 4;
    uint32_t opcode1: 2;
    uint32_t R      : 1;
    uint32_t opcode0: 5;
    uint32_t cond   : 4;
} ARMV4_Instr_MRS;

typedef struct ARMV4_Instr_MSR_Immediate
{
    uint32_t immed      : 8;
    uint32_t rotate_imm : 4;
    uint32_t SBO        : 4;
    uint32_t fieldmask  : 4;
    uint32_t opcode1    : 2;
    uint32_t R          : 1;
    uint32_t opcode0    : 5;
    uint32_t cond       : 4;
} ARMV4_Instr_MSR_Immediate;

typedef struct ARMV4_Instr_MSR_Register
{
    uint32_t Rm         : 4;
    uint32_t SBZ        : 8;
    uint32_t SBO        : 4;
    uint32_t fieldmask  : 4;
    uint32_t opcode1    : 2;
    uint32_t R          : 1;
    uint32_t opcode0    : 5;
    uint32_t cond       : 4;
} ARMV4_Instr_MSR_Register;

typedef struct ARMV4_Instr_Swap
{
    uint32_t Rm         : 4;
    uint32_t opcode1    : 4;
    uint32_t SBZ        : 4;
    uint32_t Rd         : 4;
    uint32_t Rn         : 4;
    uint32_t opcode0    : 8;
    uint32_t cond       : 4;
} ARMV4_Instr_Swap;

typedef union ARMV4_Instruction
{
    ARMV4_Instr_DataProc_Immediate                      dp_im;
    ARMV4_Instr_DataProc_Immed_Shift                    dp_is;
    ARMV4_Instr_DataProc_Register_Shift                 dp_rs;

    ARMV4_Instr_Multiply                                mul;

    ARMV4_Instr_LoadStore_ImmediateOffset               ls_io;
    ARMV4_Instr_LoadStore_RegisterOffset                ls_ro;

    ARMV4_Instr_LoadStore_Half_ImmediateOffset          lsh_io;
    ARMV4_Instr_LoadStore_Half_RegisterOffset           lsh_ro;
    
    ARMV4_Instr_LoadStoreMultiple                       lsm;
    ARMV4_Instr_Branch                                  branch;
    
    ARMV4_Instr_MRS                                     mrs;
    ARMV4_Instr_MSR_Immediate                           msr_im;
    ARMV4_Instr_MSR_Register                            msr_rs;
    ARMV4_Instr_Swap                                    swap;
    
    uint32_t word;
} ARMV4_Instruction;


/* function pointer type for instruction handlers */
typedef int (*instr_handler)(ARM_CPU*, ARM_Memory*, ARMV4_Instruction);

/** Addressing modes **/
void AddressingMode1(ARM_CPU* cpu, ARMV4_Instruction instr, ARM_Word* value, int* carry_out);
void AddressingMode2(ARM_CPU* cpu, ARMV4_Instruction instr, uint32_t* index);
void AddressingMode3(ARM_CPU* cpu, ARMV4_Instruction instr, uint32_t* index);
int CheckConditionFlag(ARM_CPU* cpu, int instr);

/** Misc **/
int ARMV4_ExecuteInstruction(ARM_CPU* cpu, ARM_Memory* mem, ARMV4_Instruction instr, int type);

#endif
