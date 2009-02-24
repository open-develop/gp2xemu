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
   
    /* check if addressing mode set an unpredictable flag */
    if(GetException(cpu, ARM_Exception_Unpredictable)){
        return 0;
    }

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
        if(mode == ARM_CPU_MODE_SYS || mode == ARM_CPU_MODE_USR){
            ASSERT(!"Unpredictable use of dataproc. \
                S flag and PC used, but no SPSR\n");
            RaiseException(cpu, ARM_Exception_Unpredictable);
            return 0;
        }
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

    /* check if addressing mode set an unpredictable flag */
    if(GetException(cpu, ARM_Exception_Unpredictable)){
        return 0;
    }

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
        if(mode == ARM_CPU_MODE_SYS || mode == ARM_CPU_MODE_USR){
            ASSERT(!"Unpredictable use of dataproc. \
                S flag and PC used, but no SPSR\n");
            RaiseException(cpu, ARM_Exception_Unpredictable);
            return 0;
        }
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

    /* check if addressing mode set an unpredictable flag */
    if(GetException(cpu, ARM_Exception_Unpredictable)){
        return 0;
    }
   
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
        if(mode == ARM_CPU_MODE_SYS || mode == ARM_CPU_MODE_USR){
            ASSERT(!"Unpredictable use of dataproc. \
                S flag and PC used, but no SPSR\n");
            RaiseException(cpu, ARM_Exception_Unpredictable);
            return 0;
        }
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

    /* check if addressing mode set an unpredictable flag */
    if(GetException(cpu, ARM_Exception_Unpredictable)){
        return 0;
    }
   
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
        if(mode == ARM_CPU_MODE_SYS || mode == ARM_CPU_MODE_USR){
            ASSERT(!"Unpredictable use of dataproc. \
                S flag and PC used, but no SPSR\n");
            RaiseException(cpu, ARM_Exception_Unpredictable);
            return 0;
        }
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

    /* check if addressing mode set an unpredictable flag */
    if(GetException(cpu, ARM_Exception_Unpredictable)){
        return 0;
    }
   
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
        if(mode == ARM_CPU_MODE_SYS || mode == ARM_CPU_MODE_USR){
            ASSERT(!"Unpredictable use of dataproc. \
                S flag and PC used, but no SPSR\n");
            RaiseException(cpu, ARM_Exception_Unpredictable);
            return 0;
        }
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

    /* check if addressing mode set an unpredictable flag */
    if(GetException(cpu, ARM_Exception_Unpredictable)){
        return 0;
    }
   
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
        if(mode == ARM_CPU_MODE_SYS || mode == ARM_CPU_MODE_USR){
            ASSERT(!"Unpredictable use of dataproc. \
                S flag and PC used, but no SPSR\n");
            RaiseException(cpu, ARM_Exception_Unpredictable);
            return 0;
        }
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

    /* check if addressing mode set an unpredictable flag */
    if(GetException(cpu, ARM_Exception_Unpredictable)){
        return 0;
    }

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
        if(mode == ARM_CPU_MODE_SYS || mode == ARM_CPU_MODE_USR){
            ASSERT(!"Unpredictable use of dataproc. \
                S flag and PC used, but no SPSR\n");
            RaiseException(cpu, ARM_Exception_Unpredictable);
            return 0;
        }
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

    /* check if addressing mode set an unpredictable flag */
    if(GetException(cpu, ARM_Exception_Unpredictable)){
        return 0;
    }
   
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
        if(mode == ARM_CPU_MODE_SYS || mode == ARM_CPU_MODE_USR){
            ASSERT(!"Unpredictable use of dataproc. \
                S flag and PC used, but no SPSR\n");
            RaiseException(cpu, ARM_Exception_Unpredictable);
            return 0;
        }
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

    /* check if addressing mode set an unpredictable flag */
    if(GetException(cpu, ARM_Exception_Unpredictable)){
        return 0;
    }
   
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

    /* check if addressing mode set an unpredictable flag */
    if(GetException(cpu, ARM_Exception_Unpredictable)){
        return 0;
    }
   
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

    /* check if addressing mode set an unpredictable flag */
    if(GetException(cpu, ARM_Exception_Unpredictable)){
        return 0;
    }
   
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

    /* check if addressing mode set an unpredictable flag */
    if(GetException(cpu, ARM_Exception_Unpredictable)){
        return 0;
    }
   
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

    /* check if addressing mode set an unpredictable flag */
    if(GetException(cpu, ARM_Exception_Unpredictable)){
        return 0;
    }
   
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
        if(mode == ARM_CPU_MODE_SYS || mode == ARM_CPU_MODE_USR){
            ASSERT(!"Unpredictable use of dataproc. \
                S flag and PC used, but no SPSR\n");
            RaiseException(cpu, ARM_Exception_Unpredictable);
            return 0;
        }
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

    /* check if addressing mode set an unpredictable flag */
    if(GetException(cpu, ARM_Exception_Unpredictable)){
        return 0;
    }
   
    Rd = instr.dp_im.Rd;
    
    RdPtr = cpu->reg[mode][Rd];
    
    *RdPtr = shifter_operand;

    /* Flush pipeline and disable implicit increment on branching */
    if(Rd == PC)
        FlushPipeline(cpu);

    if(instr.dp_im.S && Rd == PC){
        if(mode == ARM_CPU_MODE_SYS || mode == ARM_CPU_MODE_USR){
            ASSERT(!"Unpredictable use of dataproc. \
                S flag and PC used, but no SPSR\n");
            RaiseException(cpu, ARM_Exception_Unpredictable);
            return 0;
        }
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

    /* check if addressing mode set an unpredictable flag */
    if(GetException(cpu, ARM_Exception_Unpredictable)){
        return 0;
    }
   
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
        if(mode == ARM_CPU_MODE_SYS || mode == ARM_CPU_MODE_USR){
            ASSERT(!"Unpredictable use of dataproc. \
                S flag and PC used, but no SPSR\n");
            RaiseException(cpu, ARM_Exception_Unpredictable);
            return 0;
        }
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

    /* check if addressing mode set an unpredictable flag */
    if(GetException(cpu, ARM_Exception_Unpredictable)){
        return 0;
    }
   
    Rd = instr.dp_im.Rd;
    
    RdPtr = cpu->reg[mode][Rd];
    
    *RdPtr = ~shifter_operand;

    /* Flush pipeline and disable implicit increment on branching */
    if(Rd == PC)
        FlushPipeline(cpu);

    if(instr.dp_im.S && Rd == PC){
        if(mode == ARM_CPU_MODE_SYS || mode == ARM_CPU_MODE_USR){
            ASSERT(!"Unpredictable use of dataproc. \
                S flag and PC used, but no SPSR\n");
            RaiseException(cpu, ARM_Exception_Unpredictable);
            return 0;
        }
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

/*
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

*/

/* NOTE: The carry flag is really unpredictable on ARMv4 and earlier.
        We leave carry unaffected now instead of tracking carry reads
        after multiplications, unless someone has a strong argument against this.
        PC/r15 is not allowed for any operands for any of the multiplication
        instructions. Rd, RdHi, RdLo and Rm *must* be seperate registers.
*/

static int handler_mul(ARM_CPU* cpu, ARM_Memory* mem, ARMV4_Instruction instr)
{
    uint32_t Rd, Rm, Rs, *RdPtr, RmVal, RsVal;
    int cycles, mode;

    cycles = 0;
    
    if( !CheckConditionFlag(cpu, instr.mul.cond) )
        return 0; /* no-op */

    GetStatusRegisterMode(cpu, CPSR, &mode);
    
    Rd = instr.mul.Rd;
    Rm = instr.mul.Rm;
    Rs = instr.mul.Rs;

    /* PC branching not allowed */
    if(Rd == PC || Rm == PC || Rs == PC){
        ASSERT(!"Unpredictable use of multiplication.\n \
                PC is not allowed\n");
        RaiseException(cpu, ARM_Exception_Unpredictable);
        return 0;
    }

    /* Operand restrictions */
    if(Rd == Rm){
        ASSERT(!"Unpredictable use of multiplication.\n \
                Rd and Rm must differ.\n");
        RaiseException(cpu, ARM_Exception_Unpredictable);
        return 0;
    }

    RdPtr = cpu->reg[mode][Rd];
    RmVal = *cpu->reg[mode][Rm];
    RsVal = *cpu->reg[mode][Rs];
    
    *RdPtr = RmVal * RsVal;
    
    if(instr.mul.S){
        cpu->cpsr.f.N = (signed)*RdPtr < 0;
        cpu->cpsr.f.Z = !(*RdPtr);
        /* regarding C and V, see note above */
    }

    return cycles;
}

static int handler_mla(ARM_CPU* cpu, ARM_Memory* mem, ARMV4_Instruction instr)
{
    uint32_t Rd, Rm, Rs, Rn, *RdPtr, RmVal, RsVal, RnVal;
    int cycles, mode;

    cycles = 0;

    if( !CheckConditionFlag(cpu, instr.mul.cond) )
        return 0; /* no-op */

    GetStatusRegisterMode(cpu, CPSR, &mode);
   
    Rd = instr.mul.Rd;
    Rm = instr.mul.Rm;
    Rs = instr.mul.Rs;
    Rn = instr.mul.Rn;

    /* PC branching not allowed */
    if(Rd == PC || Rm == PC || Rs == PC|| Rn == PC){
        ASSERT(!"Unpredictable use of multiplication.\n \
                PC is not allowed\n");
        RaiseException(cpu, ARM_Exception_Unpredictable);
        return 0;
    }

    /* Operand restrictions */
    if(Rd == Rm){
        ASSERT(!"Unpredictable use of multiplication.\n \
                Rd and Rm must differ.\n");
        RaiseException(cpu, ARM_Exception_Unpredictable);
        return 0;
    }

    RdPtr = cpu->reg[mode][Rd];
    RmVal = *cpu->reg[mode][Rm];
    RsVal = *cpu->reg[mode][Rs];
    RnVal = *cpu->reg[mode][Rn];

    *RdPtr = RmVal * RsVal + RnVal;

    if(instr.mul.S){
        cpu->cpsr.f.N = (signed)*RdPtr < 0;
        cpu->cpsr.f.Z = !(*RdPtr);
        /* regarding C and V, see note above */
    }

    return cycles;
}

static int handler_smull(ARM_CPU* cpu, ARM_Memory* mem, ARMV4_Instruction instr)
{
    uint32_t Rd, Rm, Rn, Rs, *RdPtr, *RnPtr, RmVal, RsVal;
    int64_t result64;    
    int cycles, mode;

    if( !CheckConditionFlag(cpu, instr.mul.cond) )
        return 0;

    cycles = 0;

    GetStatusRegisterMode(cpu, CPSR, &mode);
   
    Rd = instr.mul.Rd;
    Rm = instr.mul.Rm;
    Rs = instr.mul.Rs;
    Rn = instr.mul.Rn;

    /* PC branching not allowed */
    if(Rd == PC || Rm == PC || Rs == PC|| Rn == PC){
        ASSERT(!"Unpredictable use of multiplication.\n \
                PC is not allowed\n");
        RaiseException(cpu, ARM_Exception_Unpredictable);
        return 0;
    }

    /* Operand restrictions */
    if(Rd == Rm || Rd == Rn || Rm == Rn){
        ASSERT(!"Unpredictable use of multiplication.\n \
                Rd, Rm and Rn must differ.\n");
        RaiseException(cpu, ARM_Exception_Unpredictable);
        return 0;
    }

    RdPtr =  cpu->reg[mode][Rd]; /* low */
    RnPtr =  cpu->reg[mode][Rn]; /* high */
    RmVal = *cpu->reg[mode][Rm];
    RsVal = *cpu->reg[mode][Rs];

    result64 = (int64_t)RmVal * (int64_t)RsVal;
    *RdPtr = (uint64_t)result64 & 0xFFFFFFFF;
    *RnPtr = (uint64_t)result64 >> 32ULL;

    if(instr.mul.S){
        cpu->cpsr.f.N = (signed)*RnPtr < 0;
        cpu->cpsr.f.Z = !(*RdPtr || *RnPtr);
    }
    
    return cycles;
}

static int handler_smlal(ARM_CPU* cpu, ARM_Memory* mem, ARMV4_Instruction instr)
{
    uint32_t Rd, Rm, Rn, Rs, *RdPtr, *RnPtr, RmVal, RsVal;
    int64_t result64;
    uint64_t accum64;
    int cycles, mode;

    if( !CheckConditionFlag(cpu, instr.mul.cond) )
        return 0;

    cycles = 0;

    GetStatusRegisterMode(cpu, CPSR, &mode);
   
    Rd = instr.mul.Rd;
    Rm = instr.mul.Rm;
    Rs = instr.mul.Rs;
    Rn = instr.mul.Rn;

    /* PC branching not allowed */
    if(Rd == PC || Rm == PC || Rs == PC|| Rn == PC){
        ASSERT(!"Unpredictable use of multiplication.\n \
                PC is not allowed\n");
        RaiseException(cpu, ARM_Exception_Unpredictable);
        return 0;
    }

    /* Operand restrictions */
    if(Rd == Rm || Rd == Rn || Rm == Rn){
        ASSERT(!"Unpredictable use of multiplication.\n \
                Rd, Rm and Rn must differ.\n");
        RaiseException(cpu, ARM_Exception_Unpredictable);
        return 0;
    }

    RdPtr =  cpu->reg[mode][Rd]; /* low */
    RnPtr =  cpu->reg[mode][Rn]; /* high */
    RmVal = *cpu->reg[mode][Rm];
    RsVal = *cpu->reg[mode][Rs];

    accum64 = ((uint64_t)*RnPtr << 32ULL) | *RdPtr;
    result64 = (int64_t)RmVal * (int64_t)RsVal + (int64_t)accum64;
    *RdPtr = (uint64_t)result64 & ~0xFFFFFFFF;
    *RnPtr = (uint64_t)result64 >> 32ULL;

    if(instr.mul.S){
        cpu->cpsr.f.N = (signed)*RnPtr < 0;
        cpu->cpsr.f.Z = !(*RdPtr || *RnPtr);
    }
    
    return cycles;
}

static int handler_umull(ARM_CPU* cpu, ARM_Memory* mem, ARMV4_Instruction instr)
{
    uint32_t Rd, Rm, Rn, Rs, *RdPtr, *RnPtr, RmVal, RsVal;
    uint64_t result64;    
    int cycles, mode;

    if( !CheckConditionFlag(cpu, instr.mul.cond) )
        return 0;

    cycles = 0;

    GetStatusRegisterMode(cpu, CPSR, &mode);
   
    Rd = instr.mul.Rd;
    Rm = instr.mul.Rm;
    Rs = instr.mul.Rs;
    Rn = instr.mul.Rn;

    /* PC branching not allowed */
    if(Rd == PC || Rm == PC || Rs == PC|| Rn == PC){
        ASSERT(!"Unpredictable use of multiplication.\n \
                PC is not allowed\n");
        RaiseException(cpu, ARM_Exception_Unpredictable);
        return 0;
    }

    /* Operand restrictions */
    if(Rd == Rm || Rd == Rn || Rm == Rn){
        ASSERT(!"Unpredictable use of multiplication.\n \
                Rd, Rm and Rn must differ.\n");
        RaiseException(cpu, ARM_Exception_Unpredictable);
        return 0;
    }

    RdPtr =  cpu->reg[mode][Rd]; /* low */
    RnPtr =  cpu->reg[mode][Rn]; /* high */
    RmVal = *cpu->reg[mode][Rm];
    RsVal = *cpu->reg[mode][Rs];

    result64 = (uint64_t)RmVal * RsVal;
    *RdPtr = result64 & 0xFFFFFFFF;
    *RnPtr = result64 >> 32ULL;

    if(instr.mul.S){
        cpu->cpsr.f.N = (signed)*RnPtr < 0;
        cpu->cpsr.f.Z = !(*RdPtr || *RnPtr);
    }
    
    return cycles;
}

static int handler_umlal(ARM_CPU* cpu, ARM_Memory* mem, ARMV4_Instruction instr)
{
    uint32_t Rd, Rm, Rn, Rs, *RdPtr, *RnPtr, RmVal, RsVal;
    uint64_t result64, accum64;
    int cycles, mode;

    if( !CheckConditionFlag(cpu, instr.mul.cond) )
        return 0;

    cycles = 0;

    GetStatusRegisterMode(cpu, CPSR, &mode);
   
    Rd = instr.mul.Rd;
    Rm = instr.mul.Rm;
    Rs = instr.mul.Rs;
    Rn = instr.mul.Rn;

    /* PC branching not allowed */
    if(Rd == PC || Rm == PC || Rs == PC|| Rn == PC){
        ASSERT(!"Unpredictable use of multiplication.\n \
                PC is not allowed\n");
        RaiseException(cpu, ARM_Exception_Unpredictable);
        return 0;
    }

    /* Operand restrictions */
    if(Rd == Rm || Rd == Rn || Rm == Rn){
        ASSERT(!"Unpredictable use of multiplication.\n \
                Rd, Rm and Rn must differ.\n");
        RaiseException(cpu, ARM_Exception_Unpredictable);
        return 0;
    }

    RdPtr =  cpu->reg[mode][Rd]; /* low */
    RnPtr =  cpu->reg[mode][Rn]; /* high */
    RmVal = *cpu->reg[mode][Rm];
    RsVal = *cpu->reg[mode][Rs];

    accum64 = ((uint64_t)*RnPtr << 32ULL) | *RdPtr;
    result64 = (uint64_t)RmVal * RsVal + accum64;
    *RdPtr = result64 & 0xFFFFFFFF;
    *RnPtr = result64 >> 32ULL;

    if(instr.mul.S){
        cpu->cpsr.f.N = (signed)*RnPtr < 0;
        cpu->cpsr.f.Z = !(*RdPtr || *RnPtr);
    }
    
    return cycles;
}


/*
    Remember to follow the ARM9 base restored Data Abort model here!
    This is documented in ARMARM revision A, page A2-18, as well as in
    the ARM9TDMI specification (ARM920T or ARM940T)
*/
/* LDR, STR, LDRT, STRT, LDRB, STRB, LDRBT, STRBT */
static void loadstore_accessmemory(ARM_CPU* cpu, ARM_Memory* mem, 
    uint32_t address, uint32_t* Rd, int L, int B)
{
    if(L){
        if(B)
            *Rd = ReadMemory8(cpu, mem, address);
        else
            *Rd = ReadMemory32(cpu, mem, address);
    }
    else {
        if(B)
            WriteMemory8(cpu, mem, address, *Rd);
        else
            WriteMemory32(cpu, mem, address, *Rd);
    }
    return;
}

static int handler_loadstore(ARM_CPU* cpu, ARM_Memory* mem, ARMV4_Instruction instr)
{
    int type;
    int cond;
    int cycles;
    int mode;
    int B, L, U;
    
    uint32_t *dest, *base, index, Rd, Rn;

    cycles = 0;    
    type = (instr.ls_io.P<<1)|instr.ls_io.W;
    cond = CheckConditionFlag(cpu, instr.ls_io.cond);

    /*  ARM_LoadStore_Offset = 0x2 = (P=1 && W=0), which means no writeback.
        With no writeback, the condition works on the instruction as a whole.
        With writeback, the condition affects the writeback only.
    */
    if(type == ARM_LoadStore_Offset && !cond)
        return cycles;

    AddressingMode2(cpu, instr, &index);

    if(GetException(cpu, ARM_Exception_Unpredictable))
        return 0;
    
    GetStatusRegisterMode(cpu, CPSR, &mode);

    B = instr.ls_io.B;
    L = instr.ls_io.L;
    U = instr.ls_io.U;
    Rn = instr.ls_io.Rn;
    Rd = instr.ls_io.Rd;
    base = cpu->reg[mode][Rn];
    dest = cpu->reg[mode][Rd]; /* destination for LDR, source for STR */

    switch(type)
    {
        case ARM_LoadStore_PostIndexed:
            loadstore_accessmemory(cpu, mem, *base, dest, L, B);
            if(GetException(cpu, ARM_Exception_Data_Abort))
                break; /* Restored data abort model. Don't do writebacks */
            if(cond){
                if(U)            
                    *base += index;
                else
                    *base -= index;
            }
        break;

        case ARM_LoadStore_PostIndexed_T:
            /*  Temprarily changed CPSR here, to perform STRT, STRBT, LDRT or
                LDRBT in user mode */
            cpu->cpsr.f.mode = (unsigned)((1<<4) | ARM_CPU_MODE_USR);
            loadstore_accessmemory(cpu, mem, *base, dest, L, B);
            cpu->cpsr.f.mode = (unsigned)((1<<4) | mode);
            if(GetException(cpu, ARM_Exception_Data_Abort))
                break; /* Restored data abort model. Don't do writebacks */
            if(cond){ /* condition code controls the writeback */
                if(U)            
                    *base += index;
                else
                    *base -= index;
            }
        break;

        case ARM_LoadStore_Offset:
            if(U){
                if(Rn == PC){
                    loadstore_accessmemory(cpu, mem, *base + 8 + index, dest, L, B);
                }
                else {
                    loadstore_accessmemory(cpu, mem, *base + index, dest, L, B);
                }
            }
            else {
                if(Rn == PC){
                    loadstore_accessmemory(cpu, mem, *base + 8 - index, dest, L, B);
                }
                else {
                    loadstore_accessmemory(cpu, mem, *base - index, dest, L, B);
                }
            }
            /* no exception checking here, as offsets don't do writebacks */
        break;

        case ARM_LoadStore_PreIndexed:
        if(U){
            loadstore_accessmemory(cpu, mem, *base + index, dest, L, B);
            if(GetException(cpu, ARM_Exception_Data_Abort))
                break; /* Restored data abort model. Don't do writebacks */
            if(cond)
                *base += index;
        }
        else {
            loadstore_accessmemory(cpu, mem, *base - index, dest, L, B);
            if(GetException(cpu, ARM_Exception_Data_Abort))
                break; /* Restored data abort model. Don't do writebacks */
            if(cond)
                *base -= index;
        }
        break;
    }

    if(Rd == PC)
        FlushPipeline(cpu); /* branch */

    return cycles;
}

static void loadstoreextra_accessmemory(ARM_CPU* cpu, ARM_Memory* mem, 
    uint32_t address, uint32_t* Rd, int L, int H, int S)
{
    if(L){
        if(H){ /* halfword */
            *Rd = ReadMemory16(cpu, mem, address);
            if(S && (*Rd & (1UL<<15UL))){ /* sign extend signed words */
                *Rd |= 0xFFFF0000;
            }
        }
        else { /* byte with this instruction are always signed extended */
            *Rd = ReadMemory8(cpu, mem, address);
            /* sign extend here */
            if(*Rd & (1UL<<15UL)){ /* sign extend signed words */
                *Rd |= 0xFFFFFF00;
            }
        }
    }
    else {
        /*  
            Encodings for store signed byte/halfword and
            unsigned byte are a part of the unused instruction extension space,
            and is undefined. ARM uses STRB or STRH instead, since storing 
            doesn't require sign extending. The ARMV4_ParseInstrucion should already
            have caught this, hence the assert below.
        */
        ASSERT(!S && H);
        WriteMemory16(cpu, mem, address, *Rd); /* unsigned halfword only */
    }
    return;
}

/* LDRS, LDRSH, LDRSB and STRH */
int handler_loadstoreextra(ARM_CPU* cpu, ARM_Memory* mem, ARMV4_Instruction instr)
{
    int type;
    int cond;
    int cycles;
    int mode;
    int H, L, U, S;
    
    uint32_t *dest, *base, index, Rd, Rn;

    cycles = 0;
    type = (instr.lsh_io.P<<1)|instr.lsh_io.W;
    cond = CheckConditionFlag(cpu, instr.lsh_io.cond);

    /*  ARM_LoadStore_Offset = 0x2 = (P=1 && W=0), which means no writeback.
        With no writeback, the condition works on the instruction as a whole.
        With writeback, the condition affects the writeback only.
    */
    if(type == ARM_LoadStore_Offset && !cond)
        return cycles;

    AddressingMode3(cpu, instr, &index);

    if(GetException(cpu, ARM_Exception_Unpredictable))
        return 0;

    GetStatusRegisterMode(cpu, CPSR, &mode);

    H = instr.lsh_io.H;
    L = instr.lsh_io.L;
    U = instr.lsh_io.U;
    S = instr.lsh_io.S;
    Rn = instr.lsh_io.Rn;
    Rd = instr.lsh_io.Rd;

    base = cpu->reg[mode][Rn];
    dest = cpu->reg[mode][Rd]; /* destination for LDR, source for STR */

    switch(type)
    {
    ARM_LoadStore_PostIndexed:
        loadstoreextra_accessmemory(cpu, mem, *base, dest, L, H, S);
        if(GetException(cpu, ARM_Exception_Data_Abort))
            break;
        if(cond){
            if(U)
                *base += index;
            else
                *base -= index;
        }
        break;
    ARM_LoadStore_PostIndexed_T:
        /* Address Mode 3 does not have a translation mode (P=0 && W=1) */
        RaiseException(cpu, ARM_Exception_Unpredictable);
        ASSERT(!"Addressing mode 3 has no translation support!\n");
        break;
    ARM_LoadStore_Offset:
        if(U){
            if(Rn == PC){
                loadstoreextra_accessmemory(cpu, mem, *base + 8 + index, dest, L, H, S);
            }
            else {
                loadstoreextra_accessmemory(cpu, mem, *base + index, dest, L, H, S);            
            }
        }
        else {
            if(Rn == PC){
                loadstoreextra_accessmemory(cpu, mem, *base + 8 - index, dest, L, H, S);
            }
            else {
                loadstoreextra_accessmemory(cpu, mem, *base - index, dest, L, H, S);
            }
        }
        break;
    ARM_LoadStore_PreIndexed:
        if(U){
            loadstoreextra_accessmemory(cpu, mem, *base + index, dest, L, H, S);
            if(GetException(cpu, ARM_Exception_Data_Abort))
                break;
            if(cond)
                *base += index;
        }
        else {
            loadstoreextra_accessmemory(cpu, mem, *base - index, dest, L, H, S);
            if(GetException(cpu, ARM_Exception_Data_Abort))
                break;
            if(cond)
                *base -= index;
        }
        break;
    }

    if(Rd == PC)
        FlushPipeline(cpu); /* branch */

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

    const instr_handler mulptr[8] = {
        handler_mul,    NULL,
        handler_mla,    NULL,
        handler_smull, handler_umull,
        handler_smlal, handler_umlal
    };

    int index;

    switch(type)
    {
        case ARMV4_TypeUndefined:
            return 0;
        case ARMV4_TypeUnpredictable:
            return 0;
        case ARMV4_TypeDataProcessing:
            index = (instr.dp_is.opcode1<<1) | instr.dp_is.S;
            return datapr[index](cpu, mem, instr);
        case ARMV4_TypeMultiplication:
            index = (instr.mul.islong << 2) | (instr.mul.A << 1) | instr.mul.U;
            return mulptr[index](cpu, mem, instr);
        case ARMV4_TypeLoadStoreSingle:
            return handler_loadstore(cpu, mem, instr);
        case ARMV4_TypeLoadStoreExtra:
            return handler_loadstoreextra(cpu, mem, instr);
        default:
            ASSERT(!"Instruction not yet implemented.\n");
    }

    return 0;
}

