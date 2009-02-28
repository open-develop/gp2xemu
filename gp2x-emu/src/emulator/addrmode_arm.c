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
            ret = 0;
            RaiseException(cpu, ARM_Exception_Unpredictable);
        break;
    }
    return ret;
}

/*  Addressing Mode 1, for data-processing operands.
    Refer to ARM Architecture Reference Manual, page A5-2, revision A */
void AddressingMode1(ARM_CPU* cpu, ARMV4_Instruction instr, ARM_Word* value, int* carry_out)
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
    /* just a handy pointer to access the register file */
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
        if(instr.dp_rs.Rn == PC || instr.dp_rs.Rd == PC ||
            instr.dp_rs.Rs == PC || instr.dp_rs.Rm == PC){
            ASSERT(!"Illegal use of PC with addressing mode 1\n");
            RaiseException(cpu, ARM_Exception_Unpredictable);
            return;
        }

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

/*
    Addressing mode 2 for Load and Store word or unsigned byte.
    Refer to ARM Architecture Reference Manual page A5-18, revision A
    TODO: Implement the T-versions (P==0, W==1). This mode does user-priviledged
    lookups and needs the MMU/MPU interface.

    == Cheat-sheet ==
    With opcode0 == 2 ( immediate offset / index):
    P = 0 && W = 0 immediate post-indexed without translation
    P = 0 && W = 1 immediate post-indexed with translation (T mode)
    P = 1 && W = 0 immediate offset (no writeback)
    P = 1 && W = 1 immediate pre-indexed (with writeback)
*/

void AddressingMode2(ARM_CPU* cpu, ARMV4_Instruction instr, uint32_t* index)
{
    uint32_t Rm, Rn, RmVal;
    int mode;

    ASSERT(index);

    *index = 0;
    
    if(instr.ls_io.opcode0 == 0x2){
        /* immediate, so just pass it on*/
        *index = instr.ls_io.offset12;

    }
    else if(instr.ls_io.opcode0 == 0x3){
        /* Register offset (scaled) with shifts */
        Rm = instr.ls_ro.Rm;
        Rn = instr.ls_ro.Rn;
        if(Rm == PC){
            ASSERT(!"Illegal use of PC with addressing mode 2\n");
            RaiseException(cpu, ARM_Exception_Unpredictable);
            return;
        }

        if(Rn == Rm){
            ASSERT(!"Rn == Rm is unpredictable\n");
            RaiseException(cpu, ARM_Exception_Unpredictable);
            return;
        }
        
        GetStatusRegisterMode(cpu, CPSR, &mode);
        RmVal = *cpu->reg[mode][Rm];
        
        switch(instr.ls_ro.shift)
        {
            case LSL:
                if(!instr.ls_ro.shift_imm){
                    /* Register offset, i.e just the Rm */
                    *index = RmVal;
                    break;
                }
                *index = RmVal << instr.ls_ro.shift_imm;
            break;

            case LSR:
                if(!instr.ls_ro.shift_imm)
                    *index = RmVal = 0;
                else
                    *index = RmVal >> instr.ls_ro.shift_imm;
            break;

            case ASR:
                if(!instr.ls_ro.shift_imm){
                    if(RmVal & (1<<31UL))
                        *index = 0xFFFFFFFF;
                    else
                        *index = 0;
                    break;
                }
                *index = (int32_t)RmVal >> instr.ls_ro.shift_imm;
            break;

            case ROR:
                if(!instr.ls_ro.shift_imm){
                    /* RRX Rotate Right with extend */
                    *index = (cpu->cpsr.f.C << 31UL) | (RmVal >> 1UL);
                    break;
                }
                *index = (RmVal >> instr.ls_ro.shift_imm) | (RmVal << (32UL - instr.ls_ro.shift_imm));
            break;
        }
    }
    return;
}

/*  Addressing mode 3 - Miscellaneous Loads and Stores 
    Load/Store halfword and load signed halfword/byte
    Refer to ARM Architecture Reference Manual page A5-34, revision A
*/
void AddressingMode3(ARM_CPU* cpu, ARMV4_Instruction instr, uint32_t* index)
{
/* members: lsh_io  and lsh_ro
    B = 0 means register
    B = 1 means immediate
    PUBWL
*/
    uint32_t Rm, RmVal;
    int mode;

    ASSERT(index);

    *index = 0;

    if(instr.lsh_io.B){
        /* immediate */
        *index = (instr.lsh_io.HiOff << 4) | instr.lsh_io.LoOff;
    }
    else {
        /* register */
        Rm = instr.lsh_ro.Rm;
        if(Rm == PC){
            ASSERT(!"Illegal use of PC with addressing mode 3\n");
            RaiseException(cpu, ARM_Exception_Unpredictable);
            return;
        }
        GetStatusRegisterMode(cpu, CPSR, &mode);
        RmVal = *cpu->reg[mode][Rm];
        *index = RmVal;
    }
    return;
}

