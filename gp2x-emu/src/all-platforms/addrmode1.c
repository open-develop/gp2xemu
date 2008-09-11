#include "adrmode1.h"

shifter_result adr1_immediate(u32 instruction, cpu_t* cpu)
{
    rotate_imm, immed8;
    shifter_result out;

    rotate_imm = ((instruction >> 8) & 0xF);
    rotate_imm << 1; /* only even rotate immediates are allowed */
    immed8 = instruction & 0xFF;

    if(!rotate_imm){
        out.shifter_carry_out = PSR_C_FLAG(cpu->regs.cpsr);
        return immed8;
    }
    rotate_imm <<= 1;
    out.shifter_operand = (immed8 >> rotate_imm) | (immed8 << (32 - rotate_imm));
    out.shifter_carry_out = out.shifter_operand & (1<<31) ? 1 : 0;
    return out;
}

/* This is really just adr1_lsl_imm with zero as immediate. See below. */
shifter_result adr1_reg(u32 instruction, cpu_t* cpu)
{
    u32 index, regval;
    shifter_result out;

    out.shifter_carry_out = PSR_C_FLAG(cpu->regs.cpsr);
    index = instruction & 0xF;
    regval = *(cpu->regs.r[index]);
    if(index == 15){
        out.shifter_operand = regval + 8;
        return out;
    }
    out.shifter_operand = regval;
    return out;
}

shifter_result adr1_lsl_imm(u32 instruction, cpu_t* cpu)
{
    u32 shift_imm, index, regval;
    shifter_result out;
    
    shift_imm = (instruction >> 7) & 0x1F;
    index = instruction & 0xF;
    regval = (*(cpu->regs.r[index]);
    if(index == 15)
        regval += 8;
    if(!shift_imm){
        out.shifter_carry_out = PSR_C_FLAG(cpu->regs.cpsr);
        out.shifter_operand = regval;
        return out;
    }
    out.shifter_carry_out = regval & (1<<(32 - shift_imm))) ? 1 : 0;
    out.shifter_operand = regval << shift_imm;
    return out;
}

shifter_result adr1_lsl_reg(u32 instruction, cpu_t* cpu)
{
    u32 index1, index2, regval1. regval2;
    shifter_result out;
    
    index1 = (instruction >> 8) & 0xF; /* Rs index */
    index2 = instruction & 0xF; /* Rm index */
    regval1 = (*(cpu->regs.r[index1]) & 0xFF;
    regval2 = (*(cpu->regs.r[index2]);
#if 0
    if(index1 == 15 || index2 == 15)
        ASSERT(!"Using R15 with this address mode is UNPREDICTABLE");
#endif
    if(!regval1){
        out.shifter_carry_out = PSR_C_FLAG(cpu->regs.cpsr);
        out.shifter_operand = regval2;
    } else if(regval1 < 32) {
        out.shifter_carry_out = regval2 & (1<<(32 - regval1)) ? 1 : 0;
        out.shifter_operand = regval2 << regval1;
    } else if(regval1 == 32){
        out.shifter_carry_out = regval2 & 1;
        out.shifter_operand = 0;
    } else if(regval1 > 32){
        out.shifter_carry_out = 0;
        out.shifter_operand = 0;
    }
    return out;
}

shifter_result adr1_lsr_imm(u32 instruction, cpu_t* cpu)
{
    u32 shift_imm, index, regval;
    shifter_result out;
    
    shift_imm = (instruction >> 7) & 0x1F;
    index = instruction & 0xF;
    regval = (*(cpu->regs.r[index]);
    if(index == 15)
        regval += 8;
    if(!shift_imm){
        out.shifter_carry_out = regval & (1<<31) ? 1 : 0;
        out.shifter_operand = 0;
        return out;
    }
    out.shifter_carry_out = regval & (1<<(shift_imm - 1))) ? 1 : 0;
    out.shifter_operand = regval >> shift_imm;
    return out;
}

shifter_result adr1_lsr_reg(u32 instruction, cpu_t* cpu)
{
    u32 index1, index2, regval1. regval2;
    shifter_result out;
    
    index1 = (instruction >> 8) & 0xF; /* Rs index */
    index2 = instruction & 0xF; /* Rm index */
    regval1 = (*(cpu->regs.r[index1]) & 0xFF;
    regval2 = (*(cpu->regs.r[index2]);
#if 0
    if(index1 == 15 || index2 == 15)
        ASSERT(!"Using R15 with this address mode is UNPREDICTABLE");
#endif
    if(!regval1){
        out.shifter_carry_out = PSR_C_FLAG(cpu->regs.cpsr);
        out.shifter_operand = regval2;
    } else if(regval1 < 32) {
        out.shifter_carry_out = regval2 & (1<<(regval1 - 1)) ? 1 : 0;
        out.shifter_operand = regval2 >> regval1;
    } else if(regval1 == 32){
        out.shifter_carry_out = regval2 & (1<<31) ? 1 : 0;
        out.shifter_operand = 0;
    } else if(regval1 > 32){
        out.shifter_carry_out = 0;
        out.shifter_operand = 0;
    }
    return out;
}


