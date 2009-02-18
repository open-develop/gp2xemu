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

#include "instrset_armv4.h"
#include "disasm_arm.h"
#include "peripherals/memory.h"
#include "cpu/cpu.h"
#include "assert.h"

typedef int (*instr_handler)(ARM_CPU*, ARM_Memory*, ARMV4_Instruction);

int CheckConditionFlag(ARM_CPU* cpu, int instr)
{
    int cond, ret, V,C,Z,N;
    cond = instr;
    ret = 0;
    ASSERT(cpu);
    if(!cpu)
        return -1;
    V = cpu->cpsr.f.V;
    C = cpu->cpsr.f.C;
    Z = cpu->cpsr.f.Z;
    N = cpu->cpsr.f.N;
    switch(cond)
    {
        case ARM_CondEQ:
            ret = Z;
        break;
        case ARM_CondNE:
            ret = !Z;
        break;
        case ARM_CondCS:
            ret = C;
        break;
        case ARM_CondCC:
            ret = !C;
        break;
        case ARM_CondMI:
            ret = N;
        break;
        case ARM_CondPL:
            ret = !N;
        break;
        case ARM_CondVS:
            ret = V;
        break;
        case ARM_CondVC:
            ret = !V;
        break;
        case ARM_CondHI:
            ret = C && !Z;
        break;
        case ARM_CondLS:
            ret = !C || Z;
        break;
        case ARM_CondGE:
            ret = (N == V);
        break;
        case ARM_CondLT:
            ret = (N != V);
        break;
        case ARM_CondGT:
            ret = (!Z && (N == V));
        break;
        case ARM_CondLE:
            ret = (Z || (N != V));
        break;
        case ARM_CondAL:
            ret = 1;
        break;
        case ARM_CondNV:
            ASSERT(!"Cond flag NV 0xb1111 not supported on ARMv4!\n");
            ret = 1;
        break;
    }
    return ret;
}

/* Addressing Mode 1, for data-processing operands. Refer to ARM Architecture Reference Manual, page A5-2 */
static void AddressingMode1(ARM_CPU* cpu, ARMV4_Instruction instr, ARM_Word* value, int* carry_out)
{
    ARM_Word rotate_imm;
    ARM_Word immediate;
    ARM_Word regval;
    uint32_t** reg;
    int mode;

    ASSERT(cpu);
    ASSERT(value);
    ASSERT(carry_out);
    
    GetStatusRegisterMode(cpu, CPSR, &mode);

    reg = &cpu->reg[mode][0];
    if(instr.word & (1<<25)){
        /* 32-bit shifted immediate*/
        rotate_imm.word = instr.dp_im.rotate * 2;
        immediate.word = instr.dp_im.immed;
        value->word = (immediate.word >> rotate_imm.word) | (immediate.word << (32 - rotate_imm.word)); /* right rotate */
        if(!rotate_imm.word){
            *carry_out = cpu->cpsr.f.C; /* CPSR carry if rotate amount is zero */
        }
        else
            *carry_out = value->bits.bit31; /* else, use the result sign */
    }
    else if( !(instr.word & (1<<25)) && !(instr.word & (1<<4))){ /* bit[25] = 0, bit[4] = 0 */
       /* Immediate shift with register */
        switch(instr.dp_is.shift)
        {
            case LSL:
                /*  Shifts left by immediate range [0 - 31] */
                if(!instr.dp_is.amount){
                    /*  A vanilla register as shifter_operand is
                        encoded as Rm LSL with immediate*/
                    *carry_out = cpu->cpsr.f.C ? 1 : 0;
                    value->word = (*reg)[instr.dp_is.Rm];
                    if(instr.dp_is.Rm == PC)
                        value->word += 8;
                }
                else {
                    /* Rm[32 - shift_imm]*/
                    if(instr.dp_is.Rm == PC){
                        /* The Rm value representation is the current instruction + 8 when Rm = PC
                           This is also true when Rn is PC, but is not handled by the barrel shifter */
                        *carry_out = (((*reg)[instr.dp_is.Rm] + 8) & (1<<(32 - instr.dp_is.amount)) ? 1 : 0);
                        value->word = ((*reg)[instr.dp_is.Rm] + 8) << instr.dp_is.amount;
                    }
                    else {
                        *carry_out = ((*reg)[instr.dp_is.Rm] & (1<<(32 - instr.dp_is.amount)) ? 1 : 0);
                        value->word = (*reg)[instr.dp_is.Rm] << instr.dp_is.amount;
                    }
                }
            break;
            case LSR:
                /*  Shifts right by immediate, range [1, 32]
                    A 32 bit shift is encoded as a shift with 0 */
                if(!instr.dp_is.amount){
                    /* Shift with 32, so carry out becomes Rm[31] */
                    if(instr.dp_is.Rm == PC){
                        *carry_out = (((*reg)[instr.dp_is.Rm] + 8) & (1<<31) ? 1 : 0);
                    }
                    else {
                        *carry_out = ((*reg)[instr.dp_is.Rm] & (1<<31) ? 1 : 0);
                    }
                    value->word = 0;
                }
                else {
                    if(instr.dp_is.Rm == PC){
                        /* Rm[shift_imm - 1] */
                        *carry_out = (((*reg)[instr.dp_is.Rm] + 8) & (1<<(instr.dp_is.amount - 1)) ? 1 : 0);
                        value->word = ((*reg)[instr.dp_is.Rm] + 8) >> instr.dp_is.amount;
                    }
                    else {
                        /* Rm[shift_imm - 1] */
                        *carry_out = ((*reg)[instr.dp_is.Rm] & (1<<(instr.dp_is.amount - 1)) ? 1 : 0);
                        value->word = (*reg)[instr.dp_is.Rm] >> instr.dp_is.amount;
                    }
                }
            break;
            case ASR:
                /*  Arithmetic shift right by immediate, range [1, 32]
                    A 32 bit shift is encoded as a shift with 0 */
                if(!instr.dp_is.amount){
                    if(instr.dp_is.Rm == PC){
                        /* handle sign flag, two's complement, 1 = negative 0 = positive
                            "zero" with sign as 1 is really -((2^30))*/
                        if(((*reg)[instr.dp_is.Rm] + 8) & (1<<31)){
                            *carry_out = 1;
                            value->word = 0xFFFFFFFF;
                        }
                        else {
                            *carry_out = 0;
                            value->word = 0;
                        }
                    }
                    else {
                        if(((*reg)[instr.dp_is.Rm]) & (1<<31)){
                            *carry_out = 1;
                            value->word = 0xFFFFFFFF;
                        }
                        else {
                            *carry_out = 0;
                            value->word = 0;
                        }
                    }
                }
                else { /* positive shift amount  */
                    if(instr.dp_is.Rm == PC){
                        /* Rm[shift_imm - 1] */
                        *carry_out = (((*reg)[instr.dp_is.Rm] + 8) & (1<<(instr.dp_is.amount - 1)) ? 1 : 0);
                        value->word = (signed)((*reg)[instr.dp_is.Rm] + 8) >> instr.dp_is.amount;
                    }
                    else {
                        /* Rm[shift_imm - 1] */
                        *carry_out = ((*reg)[instr.dp_is.Rm] & (1<<(instr.dp_is.amount - 1)) ? 1 : 0);
                        value->word = (signed)(*reg)[instr.dp_is.Rm] >> instr.dp_is.amount;
                    }
                }
            break;
            case ROR:
                if(!instr.dp_is.amount){
                    /* rotate right with extend */
                    if(instr.dp_is.Rm == PC){
                        value->word = (cpu->cpsr.f.C << 31) | (((*reg)[instr.dp_is.Rm] + 8) >> 1);
                        *carry_out = ((*reg)[instr.dp_is.Rm] + 8) & (1<<31) ? 1 : 0;
                    }
                    else {

                    }
                }
                else {
                    if(instr.dp_is.Rm == PC){
                        value->word = (((*reg)[instr.dp_is.Rm] + 8) >> instr.dp_is.amount) | (((*reg)[instr.dp_is.Rm] + 8) << (32 - instr.dp_is.amount));
                        *carry_out = (((*reg)[instr.dp_is.Rm] + 8) & (1<<(instr.dp_is.amount - 1)) ? 1 : 0);
                    }
                    else {
                        value->word = ((*reg)[instr.dp_is.Rm] >> instr.dp_is.amount) | ((*reg)[instr.dp_is.Rm] << (32 - instr.dp_is.amount));
                        *carry_out = ((*reg)[instr.dp_is.Rm] & (1<<(instr.dp_is.amount - 1)) ? 1 : 0);
                    }
                }
            break;
        }
    }
    else if( !(instr.word & (1<<25)) && (instr.word & (1<<4)) && !(instr.word & (1<<7))){
       /* Register shift with register */
        ASSERT(instr.dp_rs.Rn != PC);
        ASSERT(instr.dp_rs.Rd != PC);
        ASSERT(instr.dp_rs.Rs != PC);
        ASSERT(instr.dp_rs.Rm != PC);

        switch(instr.dp_rs.shift)
        {
            case LSL:
                /* Check if the 8 LSB bits in Rs are all zero*/
                if( !((*reg)[instr.dp_rs.Rs] & ((1<<8)-1)) ){
                    value->word = (*reg)[instr.dp_rs.Rm];
                    *carry_out = cpu->cpsr.f.C ? 1 : 0;
                }
                else if(((*reg)[instr.dp_rs.Rs] & ((1<<8)-1)) < 32){
                    value->word = (*reg)[instr.dp_rs.Rm] << ((*reg)[instr.dp_rs.Rs] & ((1<<8)-1));
                    *carry_out = (*reg)[instr.dp_rs.Rm] & (1<<(32 - ((*reg)[instr.dp_rs.Rs] & ((1<<8)-1)))) ? 1 : 0;
                }
                else if(((*reg)[instr.dp_rs.Rs] & ((1<<8)-1)) == 32){
                    value->word = 0;
                    *carry_out = (*reg)[instr.dp_rs.Rm] & 1;
                }
                else { /* > 32 */
                    value->word = 0;
                    *carry_out = 0;
                }
            break;
            case LSR:
                /* Check if the 8 LSB bits in Rs are all zero*/
                if( !((*reg)[instr.dp_rs.Rs] & ((1<<8)-1)) ){
                    value->word = (*reg)[instr.dp_rs.Rm];
                    *carry_out = cpu->cpsr.f.C ? 1 : 0;
                }
                else if(((*reg)[instr.dp_rs.Rs] & ((1<<8)-1)) < 32){
                    value->word = (*reg)[instr.dp_rs.Rm] >> ((*reg)[instr.dp_rs.Rs] & ((1<<8)-1));
                    *carry_out = (*reg)[instr.dp_rs.Rm] & (((*reg)[instr.dp_rs.Rs] & ((1<<8)-1)) - 1) ? 1 : 0;
                }
                else if(((*reg)[instr.dp_rs.Rs] & ((1<<8)-1)) == 32){
                    value->word = 0;
                    *carry_out = (*reg)[instr.dp_rs.Rm] & (1<<31);
                }
                else { /* > 32 */
                    value->word = 0;
                    *carry_out = 0;
                }
            break;
            case ASR:
                /* Check if the 8 LSB bits in Rs are all zero*/
                if( !((*reg)[instr.dp_rs.Rs] & ((1<<8)-1)) ){
                    value->word = (*reg)[instr.dp_rs.Rm];
                    *carry_out = cpu->cpsr.f.C ? 1 : 0;
                }
                else if(((*reg)[instr.dp_rs.Rs] & ((1<<8)-1)) < 32){
                    value->word = (signed)((*reg)[instr.dp_rs.Rm]) >> ((*reg)[instr.dp_rs.Rs] & ((1<<8)-1));
                    *carry_out = (*reg)[instr.dp_rs.Rm] & (((*reg)[instr.dp_rs.Rs] & ((1<<8)-1)) - 1) ? 1 : 0;
                }
                else { /* >= 32 */
                    if(!((*reg)[instr.dp_rs.Rm] & (1<<31))){
                        value->word = 0;
                        *carry_out = 0;
                    }
                    else { /* Rm[31] = 1 */
                        value->word = 0xFFFFFFFF;
                        *carry_out = 1;
                    }
                }
            break;
            case ROR:
                /* Check if the 8 LSB bits in Rs are all zero*/
                if(!((*reg)[instr.dp_rs.Rs] & ((1<<8)-1))){
                    value->word = (*reg)[instr.dp_rs.Rm];
                    *carry_out = cpu->cpsr.f.C ? 1 : 0;
                } /* same, but only the five LSB bits */
                else if(!((*reg)[instr.dp_rs.Rs] & ((1<<5)-1)) ){
                    value->word = (*reg)[instr.dp_rs.Rm];
                    *carry_out = ((*reg)[instr.dp_rs.Rm] & (1<<31)) ? 1 : 0;
                }
                else { /* Rm > 0 */
                    value->word = (*reg)[instr.dp_rs.Rm] >> ((*reg)[instr.dp_rs.Rs] & ((1<<5)-1)) |
                        (*reg)[instr.dp_rs.Rm] << (32 - ((*reg)[instr.dp_rs.Rs] & ((1<<5)-1)));
                    /* carry = Rm[Rs[4:0] - 1] */
                    *carry_out = ((*reg)[instr.dp_rs.Rm] & (((*reg)[instr.dp_rs.Rs] & ((1<<5)-1) ) - 1)) ? 1 : 0;
                }
            break;
        }
    }
    else {
        ASSERT(!"Invalid AddressMode1 path!\n");
    }
    return;
}

/* TODO INSTRUCTIONS:    "cycles" should be the computed cycle timings for the instruction
            Handle SPSR user and system mode with unpredictable flag instead of
            asserts.
*/


static int handler_and(ARM_CPU* cpu, ARM_Memory* mem, ARMV4_Instruction instr)
{
    uint32_t Rn, Rd, RnVal, *RdPtr, shifter_operand;
    int shifter_carry, mode, cycles;

    cycles = 0; /* Important to set anyway, or else we get an infinite loop */
    if( !CheckConditionFlag(cpu, instr.dp_im.cond) )
        return 0; /* noop */
    AddressingMode1(cpu, instr, (ARM_Word*)&shifter_operand, &shifter_carry);
    
    GetStatusRegisterMode(cpu, CPSR, &mode);
   
    Rn = instr.dp_im.Rn;
    Rd = instr.dp_im.Rd;
    
    RnVal = *cpu->reg[mode][Rn];
    if(Rn == PC)
        RnVal += 8;
    RdPtr = cpu->reg[mode][Rd];
    
    *RdPtr = RnVal & shifter_operand;

    /* Flush pipeline and disable implicit increment on branching */
    if(Rd == PC)
        FlushPipeline(cpu);

    if(instr.dp_im.S && Rd == PC){
        ASSERT(mode != ARM_CPU_MODE_SYS && mode != ARM_CPU_MODE_USR);        
        cycles = 0;
        cpu->cpsr = cpu->spsr[mode];    
    }
    else if(instr.dp_im.S){
        cycles = 0;
        cpu->cpsr.f.N = (signed)*RdPtr < 0;
        cpu->cpsr.f.Z = !(*RdPtr);
        cpu->cpsr.f.C = shifter_carry;
        /* cpu->cpsr.f.V leave alone */
    }

    return cycles;
}

static int handler_eor(ARM_CPU* cpu, ARM_Memory* mem, ARMV4_Instruction instr)
{
    uint32_t Rn, Rd, RnVal, *RdPtr, shifter_operand;
    int shifter_carry, mode, cycles;

    cycles = 0; /* Important to set anyway, or else we get an infinite loop */
    if( !CheckConditionFlag(cpu, instr.dp_im.cond) )
        return 0; /* noop */
    AddressingMode1(cpu, instr, (ARM_Word*)&shifter_operand, &shifter_carry);
    
    GetStatusRegisterMode(cpu, CPSR, &mode);
   
    Rn = instr.dp_im.Rn;
    Rd = instr.dp_im.Rd;
    
    RnVal = *cpu->reg[mode][Rn];
    if(Rn == PC)
        RnVal += 8;
    RdPtr = cpu->reg[mode][Rd];
    
    *RdPtr = RnVal ^ shifter_operand;

    /* Flush pipeline and disable implicit increment on branching */
    if(Rd == PC)
        FlushPipeline(cpu);

    if(instr.dp_im.S && Rd == PC){
        ASSERT(mode != ARM_CPU_MODE_SYS && mode != ARM_CPU_MODE_USR);
        cycles = 0;
        cpu->cpsr = cpu->spsr[mode];    
    }
    else if(instr.dp_im.S){
        cycles = 0;
        cpu->cpsr.f.N = (signed)*RdPtr < 0;
        cpu->cpsr.f.Z = !(*RdPtr);
        cpu->cpsr.f.C = shifter_carry;
        /* cpu->cpsr.f.V leave alone */
    }

    return cycles;
}

static int handler_sub(ARM_CPU* cpu, ARM_Memory* mem, ARMV4_Instruction instr)
{
    uint32_t Rn, Rd, RnVal, *RdPtr, shifter_operand;
    int shifter_carry, mode, cycles;

    cycles = 0; /* Important to set anyway, or else we get an infinite loop */
    if( !CheckConditionFlag(cpu, instr.dp_im.cond) )
        return 0; /* noop */
    AddressingMode1(cpu, instr, (ARM_Word*)&shifter_operand, &shifter_carry);
    
    GetStatusRegisterMode(cpu, CPSR, &mode);
   
    Rn = instr.dp_im.Rn;
    Rd = instr.dp_im.Rd;
    
    RnVal = *cpu->reg[mode][Rn];
    if(Rn == PC)
        RnVal += 8;
    RdPtr = cpu->reg[mode][Rd];
    
    *RdPtr = RnVal - shifter_operand;

    /* Flush pipeline and disable implicit increment on branching */
    if(Rd == PC)
        FlushPipeline(cpu);

    if(instr.dp_im.S && Rd == PC){
        ASSERT(mode != ARM_CPU_MODE_SYS && mode != ARM_CPU_MODE_USR);
        cycles = 0;
        cpu->cpsr = cpu->spsr[mode];    
    }
    else if(instr.dp_im.S){
        cycles = 0;
        cpu->cpsr.f.N = (signed)*RdPtr < 0;
        cpu->cpsr.f.Z = !(*RdPtr);
        cpu->cpsr.f.C = !(RnVal < shifter_operand); /* NOT borrow from. Compensated for in SBC and RSC */
        cpu->cpsr.f.V = ((signed)*RdPtr < 0) != ((signed)RnVal < (signed)shifter_operand);
    }

    return cycles;
}

static int handler_rsb(ARM_CPU* cpu, ARM_Memory* mem, ARMV4_Instruction instr)
{
    uint32_t Rn, Rd, RnVal, *RdPtr, shifter_operand;
    int shifter_carry, mode, cycles;

    cycles = 0; /* Important to set anyway, or else we get an infinite loop */
    if( !CheckConditionFlag(cpu, instr.dp_im.cond) )
        return 0; /* noop */
    AddressingMode1(cpu, instr, (ARM_Word*)&shifter_operand, &shifter_carry);
    
    GetStatusRegisterMode(cpu, CPSR, &mode);
   
    Rn = instr.dp_im.Rn;
    Rd = instr.dp_im.Rd;
    
    RnVal = *cpu->reg[mode][Rn];
    if(Rn == PC)
        RnVal += 8;
    RdPtr = cpu->reg[mode][Rd];
    
    *RdPtr = shifter_operand - RnVal;

    /* Flush pipeline and disable implicit increment on branching */
    if(Rd == PC)
        FlushPipeline(cpu);

    if(instr.dp_im.S && Rd == PC){
        ASSERT(mode != ARM_CPU_MODE_SYS && mode != ARM_CPU_MODE_USR);
        cycles = 0;
        cpu->cpsr = cpu->spsr[mode];    
    }
    else if(instr.dp_im.S){
        cycles = 0;
        cpu->cpsr.f.N = (signed)*RdPtr < 0;
        cpu->cpsr.f.Z = !(*RdPtr);
        cpu->cpsr.f.C = !(shifter_operand < RnVal); /* NOT borrow from. Compensated for in SBC and RSC */
        cpu->cpsr.f.V = ((signed)*RdPtr < 0) != ((signed)shifter_operand < (signed)RnVal);
    }

    return cycles;
}

static int handler_add(ARM_CPU* cpu, ARM_Memory* mem, ARMV4_Instruction instr)
{
    uint32_t Rn, Rd, RnVal, *RdPtr, shifter_operand;
    int shifter_carry, mode, cycles;

    cycles = 0; /* Important to set anyway, or else we get an infinite loop */
    if( !CheckConditionFlag(cpu, instr.dp_im.cond) )
        return 0; /* noop */
    AddressingMode1(cpu, instr, (ARM_Word*)&shifter_operand, &shifter_carry);
    
    GetStatusRegisterMode(cpu, CPSR, &mode);
   
    Rn = instr.dp_im.Rn;
    Rd = instr.dp_im.Rd;
    
    RnVal = *cpu->reg[mode][Rn];
    if(Rn == PC)
        RnVal += 8;
    RdPtr = cpu->reg[mode][Rd];
    
    *RdPtr = RnVal + shifter_operand;

    /* Flush pipeline and disable implicit increment on branching */
    if(Rd == PC)
        FlushPipeline(cpu);

    if(instr.dp_im.S && Rd == PC){
        ASSERT(mode != ARM_CPU_MODE_SYS && mode != ARM_CPU_MODE_USR);
        cycles = 0;
        cpu->cpsr = cpu->spsr[mode];    
    }
    else if(instr.dp_im.S){
        cycles = 0;
        cpu->cpsr.f.N = (signed)*RdPtr < 0;
        cpu->cpsr.f.Z = !(*RdPtr);
        cpu->cpsr.f.C = (*RdPtr < RnVal);
        cpu->cpsr.f.V = ((signed)*RdPtr < (signed)RnVal) != ((signed)shifter_operand < 0);
    }

    return cycles;
}

static int handler_adc(ARM_CPU* cpu, ARM_Memory* mem, ARMV4_Instruction instr)
{
    uint32_t Rn, Rd, RnVal, *RdPtr, shifter_operand;
    int shifter_carry, mode, cycles;

    cycles = 0; /* Important to set anyway, or else we get an infinite loop */
    if( !CheckConditionFlag(cpu, instr.dp_im.cond) )
        return 0; /* noop */
    AddressingMode1(cpu, instr, (ARM_Word*)&shifter_operand, &shifter_carry);
    
    GetStatusRegisterMode(cpu, CPSR, &mode);
   
    Rn = instr.dp_im.Rn;
    Rd = instr.dp_im.Rd;
    
    RnVal = *cpu->reg[mode][Rn];
    if(Rn == PC)
        RnVal += 8;
    RdPtr = cpu->reg[mode][Rd];
    
    *RdPtr = RnVal + shifter_operand + cpu->cpsr.f.C;

    /* Flush pipeline and disable implicit increment on branching */
    if(Rd == PC)
        FlushPipeline(cpu);

    if(instr.dp_im.S && Rd == PC){
        ASSERT(mode != ARM_CPU_MODE_SYS && mode != ARM_CPU_MODE_USR);
        cycles = 0;
        cpu->cpsr = cpu->spsr[mode]; 
    }
    else if(instr.dp_im.S){
        cycles = 0;
        cpu->cpsr.f.N = (signed)*RdPtr < 0;
        cpu->cpsr.f.Z = !(*RdPtr);
        cpu->cpsr.f.C = (*RdPtr < RnVal);
        cpu->cpsr.f.V = ((signed)*RdPtr < (signed)RnVal) != ((signed)shifter_operand < 0);
    }

    return cycles;
}

static int handler_sbc(ARM_CPU* cpu, ARM_Memory* mem, ARMV4_Instruction instr)
{
    uint32_t Rn, Rd, RnVal, *RdPtr, shifter_operand;
    int shifter_carry, mode, cycles;

    cycles = 0; /* Important to set anyway, or else we get an infinite loop */
    if( !CheckConditionFlag(cpu, instr.dp_im.cond) )
        return 0; /* noop */
    AddressingMode1(cpu, instr, (ARM_Word*)&shifter_operand, &shifter_carry);
    
    GetStatusRegisterMode(cpu, CPSR, &mode);
   
    Rn = instr.dp_im.Rn;
    Rd = instr.dp_im.Rd;
    
    RnVal = *cpu->reg[mode][Rn];
    if(Rn == PC)
        RnVal += 8;
    RdPtr = cpu->reg[mode][Rd];
    
    /* Carry flipped to compensate */
    *RdPtr = RnVal - shifter_operand - (uint32_t)(!cpu->cpsr.f.C);

    /* Flush pipeline and disable implicit increment on branching */
    if(Rd == PC)
        FlushPipeline(cpu);

    if(instr.dp_im.S && Rd == PC){
        ASSERT(mode != ARM_CPU_MODE_SYS && mode != ARM_CPU_MODE_USR);
        cycles = 0;
        cpu->cpsr = cpu->spsr[mode];    
    }
    else if(instr.dp_im.S){
        cycles = 0;
        cpu->cpsr.f.N = (signed)*RdPtr < 0;
        cpu->cpsr.f.Z = !(*RdPtr);
        cpu->cpsr.f.C = !(RnVal < shifter_operand); /* NOT borrow from. Compensated for in SBC and RSC */
        cpu->cpsr.f.V = ((signed)*RdPtr < 0) != ((signed)RnVal < (signed)shifter_operand);
    }

    return cycles;
}

static int handler_rsc(ARM_CPU* cpu, ARM_Memory* mem, ARMV4_Instruction instr)
{
    uint32_t Rn, Rd, RnVal, *RdPtr, shifter_operand;
    int shifter_carry, mode, cycles;

    cycles = 0; /* Important to set anyway, or else we get an infinite loop */
    if( !CheckConditionFlag(cpu, instr.dp_im.cond) )
        return 0; /* noop */
    AddressingMode1(cpu, instr, (ARM_Word*)&shifter_operand, &shifter_carry);
    
    GetStatusRegisterMode(cpu, CPSR, &mode);
   
    Rn = instr.dp_im.Rn;
    Rd = instr.dp_im.Rd;
    
    RnVal = *cpu->reg[mode][Rn];
    if(Rn == PC)
        RnVal += 8;
    RdPtr = cpu->reg[mode][Rd];
    
    /* Carry (borrow) flipped to compensate */
    *RdPtr = shifter_operand - RnVal - (uint32_t)(!cpu->cpsr.f.C);

    /* Flush pipeline and disable implicit increment on branching */
    if(Rd == PC)
        FlushPipeline(cpu);

    if(instr.dp_im.S && Rd == PC){
        ASSERT(mode != ARM_CPU_MODE_SYS && mode != ARM_CPU_MODE_USR);
        cycles = 0;
        cpu->cpsr = cpu->spsr[mode];    
    }
    else if(instr.dp_im.S){
        cycles = 0;
        cpu->cpsr.f.N = (signed)*RdPtr < 0;
        cpu->cpsr.f.Z = !(*RdPtr);
        cpu->cpsr.f.C = !(shifter_operand < RnVal); /* NOT borrow from. Compensated for in SBC and RSC */
        cpu->cpsr.f.V = ((signed)*RdPtr < 0) != ((signed)shifter_operand < (signed)RnVal);
    }

    return cycles;
}

/* TODO: Is r15 really allowed as Rn or shifter_operand?
        Assume so, since ARMARM doesn't explicitly mention otherwise. */
static int handler_tst(ARM_CPU* cpu, ARM_Memory* mem, ARMV4_Instruction instr)
{
    uint32_t Rn, RnVal, alu_out, shifter_operand;
    int shifter_carry, mode, cycles;

    cycles = 0; /* Important to set anyway, or else we get an infinite loop */
    if( !CheckConditionFlag(cpu, instr.dp_im.cond) )
        return 0; /* noop */
    AddressingMode1(cpu, instr, (ARM_Word*)&shifter_operand, &shifter_carry);
    
    GetStatusRegisterMode(cpu, CPSR, &mode);
   
    Rn = instr.dp_im.Rn;
    
    RnVal = *cpu->reg[mode][Rn];
    if(Rn == PC)
        RnVal += 8;
   
    alu_out = RnVal & shifter_operand;

    cycles = 0;
    cpu->cpsr.f.N = (signed)alu_out < 0;
    cpu->cpsr.f.Z = !alu_out;
    cpu->cpsr.f.C = shifter_carry;
    /* cpu->cpsr.f.V = ((signed)*RdPtr < 0) != ((signed)RnVal < (signed)shifter_operand); */

    return cycles;
}

static int handler_teq(ARM_CPU* cpu, ARM_Memory* mem, ARMV4_Instruction instr)
{
    uint32_t Rn, RnVal, alu_out, shifter_operand;
    int shifter_carry, mode, cycles;

    cycles = 0; /* Important to set anyway, or else we get an infinite loop */
    if( !CheckConditionFlag(cpu, instr.dp_im.cond) )
        return 0; /* noop */
    AddressingMode1(cpu, instr, (ARM_Word*)&shifter_operand, &shifter_carry);
    
    GetStatusRegisterMode(cpu, CPSR, &mode);
   
    Rn = instr.dp_im.Rn;
    
    RnVal = *cpu->reg[mode][Rn];
    if(Rn == PC)
        RnVal += 8;
   
    alu_out = RnVal ^ shifter_operand;

    cycles = 0;
    cpu->cpsr.f.N = (signed)alu_out < 0;
    cpu->cpsr.f.Z = !alu_out;
    cpu->cpsr.f.C = shifter_carry;
    /* cpu->cpsr.f.V = ((signed)*RdPtr < 0) != ((signed)RnVal < (signed)shifter_operand); */

    return cycles;
}

static int handler_cmp(ARM_CPU* cpu, ARM_Memory* mem, ARMV4_Instruction instr)
{
    uint32_t Rn, RnVal, alu_out, shifter_operand;
    int shifter_carry, mode, cycles;

    cycles = 0; /* Important to set anyway, or else we get an infinite loop */
    if( !CheckConditionFlag(cpu, instr.dp_im.cond) )
        return 0; /* noop */
    AddressingMode1(cpu, instr, (ARM_Word*)&shifter_operand, &shifter_carry);
    
    GetStatusRegisterMode(cpu, CPSR, &mode);
   
    Rn = instr.dp_im.Rn;
    
    RnVal = *cpu->reg[mode][Rn];
    if(Rn == PC)
        RnVal += 8;

    alu_out = RnVal - shifter_operand;

    cycles = 0;
    cpu->cpsr.f.N = (signed)alu_out < 0;
    cpu->cpsr.f.Z = !alu_out;
    cpu->cpsr.f.C = !(RnVal < shifter_operand); /* NOT borrow from. Compensated for in SBC and RSC */
    cpu->cpsr.f.V = ((signed)alu_out < 0) != ((signed)RnVal < (signed)shifter_operand);

    return cycles;
}

static int handler_cmn(ARM_CPU* cpu, ARM_Memory* mem, ARMV4_Instruction instr)
{
    uint32_t Rn, RnVal, alu_out, shifter_operand;
    int shifter_carry, mode, cycles;

    cycles = 0; /* Important to set anyway, or else we get an infinite loop */
    if( !CheckConditionFlag(cpu, instr.dp_im.cond) )
        return 0; /* noop */
    AddressingMode1(cpu, instr, (ARM_Word*)&shifter_operand, &shifter_carry);
    
    GetStatusRegisterMode(cpu, CPSR, &mode);
   
    Rn = instr.dp_im.Rn;
    
    RnVal = *cpu->reg[mode][Rn];
    if(Rn == PC)
        RnVal += 8;

    alu_out = RnVal + shifter_operand;

    cycles = 0;
    cpu->cpsr.f.N = (signed)alu_out < 0;
    cpu->cpsr.f.Z = !alu_out;
    cpu->cpsr.f.C = (alu_out < RnVal);
    cpu->cpsr.f.V = ((signed)alu_out < (signed)RnVal) != ((signed)shifter_operand < 0);

    return cycles;
}

static int handler_orr(ARM_CPU* cpu, ARM_Memory* mem, ARMV4_Instruction instr)
{
    uint32_t Rn, Rd, RnVal, *RdPtr, shifter_operand;
    int shifter_carry, mode, cycles;

    cycles = 0; /* Important to set anyway, or else we get an infinite loop */
    if( !CheckConditionFlag(cpu, instr.dp_im.cond) )
        return 0; /* noop */
    AddressingMode1(cpu, instr, (ARM_Word*)&shifter_operand, &shifter_carry);
    
    GetStatusRegisterMode(cpu, CPSR, &mode);
   
    Rn = instr.dp_im.Rn;
    Rd = instr.dp_im.Rd;
    
    RnVal = *cpu->reg[mode][Rn];
    if(Rn == PC)
        RnVal += 8;
    RdPtr = cpu->reg[mode][Rd];
    
    *RdPtr = RnVal | shifter_operand;

    /* Flush pipeline and disable implicit increment on branching */
    if(Rd == PC)
        FlushPipeline(cpu);

    if(instr.dp_im.S && Rd == PC){
        ASSERT(mode != ARM_CPU_MODE_SYS && mode != ARM_CPU_MODE_USR);        
        cycles = 0;
        cpu->cpsr = cpu->spsr[mode];    
    }
    else if(instr.dp_im.S){
        cycles = 0;
        cpu->cpsr.f.N = (signed)*RdPtr < 0;
        cpu->cpsr.f.Z = !(*RdPtr);
        cpu->cpsr.f.C = shifter_carry;
        /* cpu->cpsr.f.V leave alone */
    }

    return cycles;
}

static int handler_mov(ARM_CPU* cpu, ARM_Memory* mem, ARMV4_Instruction instr)
{
    uint32_t Rd, *RdPtr, shifter_operand;
    int shifter_carry, mode, cycles;

    cycles = 0; /* Important to set anyway, or else we get an infinite loop */
    if( !CheckConditionFlag(cpu, instr.dp_im.cond) )
        return 0; /* noop */
    AddressingMode1(cpu, instr, (ARM_Word*)&shifter_operand, &shifter_carry);
    
    GetStatusRegisterMode(cpu, CPSR, &mode);
   
    Rd = instr.dp_im.Rd;
    
    RdPtr = cpu->reg[mode][Rd];
    
    *RdPtr = shifter_operand;

    /* Flush pipeline and disable implicit increment on branching */
    if(Rd == PC)
        FlushPipeline(cpu);

    if(instr.dp_im.S && Rd == PC){
        ASSERT(mode != ARM_CPU_MODE_SYS && mode != ARM_CPU_MODE_USR);        
        cycles = 0;
        cpu->cpsr = cpu->spsr[mode];    
    }
    else if(instr.dp_im.S){
        cycles = 0;
        cpu->cpsr.f.N = (signed)*RdPtr < 0;
        cpu->cpsr.f.Z = !(*RdPtr);
        cpu->cpsr.f.C = shifter_carry;
        /* cpu->cpsr.f.V leave alone */
    }

    return cycles;
}

static int handler_bic(ARM_CPU* cpu, ARM_Memory* mem, ARMV4_Instruction instr)
{
    uint32_t Rn, Rd, RnVal, *RdPtr, shifter_operand;
    int shifter_carry, mode, cycles;

    cycles = 0; /* Important to set anyway, or else we get an infinite loop */
    if( !CheckConditionFlag(cpu, instr.dp_im.cond) )
        return 0; /* noop */
    AddressingMode1(cpu, instr, (ARM_Word*)&shifter_operand, &shifter_carry);
    
    GetStatusRegisterMode(cpu, CPSR, &mode);
   
    Rn = instr.dp_im.Rn;
    Rd = instr.dp_im.Rd;
    
    RnVal = *cpu->reg[mode][Rn];
    if(Rn == PC)
        RnVal += 8;
    RdPtr = cpu->reg[mode][Rd];
    
    *RdPtr = RnVal & ~shifter_operand;

    /* Flush pipeline and disable implicit increment on branching */
    if(Rd == PC)
        FlushPipeline(cpu);

    if(instr.dp_im.S && Rd == PC){
        ASSERT(mode != ARM_CPU_MODE_SYS && mode != ARM_CPU_MODE_USR);        
        cycles = 0;
        cpu->cpsr = cpu->spsr[mode];    
    }
    else if(instr.dp_im.S){
        cycles = 0;
        cpu->cpsr.f.N = (signed)*RdPtr < 0;
        cpu->cpsr.f.Z = !(*RdPtr);
        cpu->cpsr.f.C = shifter_carry;
        /* cpu->cpsr.f.V leave alone */
    }

    return cycles;
}

static int handler_mvn(ARM_CPU* cpu, ARM_Memory* mem, ARMV4_Instruction instr)
{
    uint32_t Rd, *RdPtr, shifter_operand;
    int shifter_carry, mode, cycles;

    cycles = 0; /* Important to set anyway, or else we get an infinite loop */
    if( !CheckConditionFlag(cpu, instr.dp_im.cond) )
        return 0; /* noop */
    AddressingMode1(cpu, instr, (ARM_Word*)&shifter_operand, &shifter_carry);
    
    GetStatusRegisterMode(cpu, CPSR, &mode);
   
    Rd = instr.dp_im.Rd;
    
    RdPtr = cpu->reg[mode][Rd];
    
    *RdPtr = ~shifter_operand;

    /* Flush pipeline and disable implicit increment on branching */
    if(Rd == PC)
        FlushPipeline(cpu);

    if(instr.dp_im.S && Rd == PC){
        ASSERT(mode != ARM_CPU_MODE_SYS && mode != ARM_CPU_MODE_USR);        
        cycles = 0;
        cpu->cpsr = cpu->spsr[mode];    
    }
    else if(instr.dp_im.S){
        cycles = 0;
        cpu->cpsr.f.N = (signed)*RdPtr < 0;
        cpu->cpsr.f.Z = !(*RdPtr);
        cpu->cpsr.f.C = shifter_carry;
        /* cpu->cpsr.f.V leave alone */
    }

    return cycles;
}

int ARMV4_ExecuteInstruction(ARM_CPU* cpu, ARM_Memory* mem, ARMV4_Instruction instr, int type)
{
    /*  TODO: Add function calls which actually 'handles' S ?
        Right now, we check for S inside the handler as well!
    */

    const instr_handler datapr[32] = {
        handler_and /* S = 0 */, handler_and, /* S=1 */
        handler_eor /* S = 0 */, handler_eor, /* S=1 */
        handler_sub /* S = 0 */, handler_sub, /* S=1 */
        handler_rsb /* S = 0 */, handler_rsb, /* S=1 */
        handler_add /* S = 0 */, handler_add, /* S=1 */
        handler_adc /* S = 0 */, handler_adc, /* S=1 */
        handler_sbc /* S = 0 */, handler_sbc, /* S=1 */
        handler_rsc /* S = 0 */, handler_rsc, /* S=1 */
        NULL /* No TST with S = 0 */, handler_tst,
        NULL /* No TEQ with S = 0 */, handler_teq,
        NULL /* No CMP with S = 0 */, handler_cmp,
        NULL /* No CMN with S = 0 */, handler_cmn,
        handler_orr /* S = 0 */, handler_orr, /* S=1 */
        handler_mov /* S = 0 */, handler_mov, /* S=1 */
        handler_bic /* S = 0 */, handler_bic, /* S=1 */
        handler_mvn /* S = 0 */, handler_mvn /* S=1 */
    };
    int index;

    switch(type)
    {
        case ARMV4_TypeUndefined:
            return 0;
        case ARMV4_TypeUnpredictable:
            return -1;
        case ARMV4_TypeDataProcessing:
            index = (instr.dp_is.opcode1<<1) | instr.dp_is.S;
            return datapr[index](cpu, mem, instr);
        default:
            ASSERT(!"Instruction not yet implemented.\n");
    }

    return 0;
}
