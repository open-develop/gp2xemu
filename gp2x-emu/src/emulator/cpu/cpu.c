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

#include <string.h>
#include "cpu.h"
#include "../assert.h"

static void ResetPSR(ARM_CPU* cpu)
{
    /*  Our ARM_CPU_MODE_ defines are four bits, while the *real*
        mode flag in PSR is 5 bits. We omit the most significant bit, because
        it is always 1 anyway. Using four bits makes the array used for banking
        smaller. We OR in 1<<4 here, to add the missing implied bit so it
        reflects the *real* mode flag.
        This must always be done when assigning the PSR mode flag.
    */

    ASSERT(cpu);

    memset(&cpu->spsr, 0, sizeof(ARM_StatusRegister) * 16);
    memset(&cpu->cpsr, 0, sizeof(ARM_StatusRegister));

    /* This is the state during a RESET */
    cpu->cpsr.f.mode = (1<<4) | ARM_CPU_MODE_SVC;
    cpu->cpsr.f.thumb = 0;
    cpu->cpsr.f.fiq = 1;
    cpu->cpsr.f.irq = 1;
    cpu->cpsr.f.V = 0; /* undefined values for the flags during RESET */
    cpu->cpsr.f.C = 0;
    cpu->cpsr.f.Z = 0;
    cpu->cpsr.f.N = 0;
    return;
}

static void ResetRegisters(ARM_CPU* cpu)
{
    /* initialize the pointer indirection required by the register banking */
    int i;

    ASSERT(cpu);

    for(i=0;i<16;++i)
        memset(&cpu->reg[i], 0, sizeof(uint32_t*) * 16);
    memset(cpu->regval, 0, sizeof(uint32_t) * 31);

    /* all modes share registers r0 - r7 */
    for(i=0;i<8;++i){
        cpu->reg[ARM_CPU_MODE_USR][i] = &cpu->regval[i];
        cpu->reg[ARM_CPU_MODE_SYS][i] = &cpu->regval[i];
        cpu->reg[ARM_CPU_MODE_FIQ][i] = &cpu->regval[i];
        cpu->reg[ARM_CPU_MODE_IRQ][i] = &cpu->regval[i];
        cpu->reg[ARM_CPU_MODE_SVC][i] = &cpu->regval[i];
        cpu->reg[ARM_CPU_MODE_ABT][i] = &cpu->regval[i];
        cpu->reg[ARM_CPU_MODE_UND][i] = &cpu->regval[i];
    }

    /* all modes share PC */
    cpu->reg[ARM_CPU_MODE_USR][PC] = &cpu->regval[PC];
    cpu->reg[ARM_CPU_MODE_SYS][PC] = &cpu->regval[PC];
    cpu->reg[ARM_CPU_MODE_FIQ][PC] = &cpu->regval[PC];
    cpu->reg[ARM_CPU_MODE_IRQ][PC] = &cpu->regval[PC];
    cpu->reg[ARM_CPU_MODE_SVC][PC] = &cpu->regval[PC];
    cpu->reg[ARM_CPU_MODE_ABT][PC] = &cpu->regval[PC];
    cpu->reg[ARM_CPU_MODE_UND][PC] = &cpu->regval[PC];

    /* all modes except FIQ share registers r8 - r12 */
    for(i=8;i<13;++i){
        cpu->reg[ARM_CPU_MODE_USR][i] = &cpu->regval[i];
        cpu->reg[ARM_CPU_MODE_IRQ][i] = &cpu->regval[i];
        cpu->reg[ARM_CPU_MODE_SVC][i] = &cpu->regval[i];
        cpu->reg[ARM_CPU_MODE_ABT][i] = &cpu->regval[i];
        cpu->reg[ARM_CPU_MODE_UND][i] = &cpu->regval[i];
        cpu->reg[ARM_CPU_MODE_SYS][i] = &cpu->regval[i];
    }

    /* User and System are not privileged */
    cpu->reg[ARM_CPU_MODE_USR][SP] = &cpu->regval[SP];
    cpu->reg[ARM_CPU_MODE_USR][LR] = &cpu->regval[LR];
    cpu->reg[ARM_CPU_MODE_SYS][SP] = &cpu->regval[SP];
    cpu->reg[ARM_CPU_MODE_SYS][LR] = &cpu->regval[LR];

    /* banked stack and link registers */
    cpu->reg[ARM_CPU_MODE_FIQ][SP] = &cpu->regval[16];
    cpu->reg[ARM_CPU_MODE_FIQ][LR] = &cpu->regval[17];
    cpu->reg[ARM_CPU_MODE_IRQ][SP] = &cpu->regval[18];
    cpu->reg[ARM_CPU_MODE_IRQ][LR] = &cpu->regval[19];
    cpu->reg[ARM_CPU_MODE_SVC][SP] = &cpu->regval[20];
    cpu->reg[ARM_CPU_MODE_SVC][LR] = &cpu->regval[21];
    cpu->reg[ARM_CPU_MODE_ABT][SP] = &cpu->regval[22];
    cpu->reg[ARM_CPU_MODE_ABT][LR] = &cpu->regval[23];
    cpu->reg[ARM_CPU_MODE_UND][SP] = &cpu->regval[24];
    cpu->reg[ARM_CPU_MODE_UND][LR] = &cpu->regval[25];

    /* FIQ has banked r8 - r12 registers */
    for(i=0;i<6;++i){
        cpu->reg[ARM_CPU_MODE_FIQ][i+8] = &cpu->regval[i + 26];
    }

    return;
}

void ResetCPU(ARM_CPU* cpu)
{
    ASSERT(cpu);
    ResetRegisters(cpu);
    ResetPSR(cpu);
    cpu->exception = ARM_Exception_None;
    cpu->cpubusywait = 0;
    cpu->shouldflush = 0;
    return;
}

void GetStatusRegisterMode(ARM_CPU* cpu, int which, int* result)
{
    /*  'which' is the PSR to query:
        0 = CPSR, 1 = SPSR
        Note that we remove the most significant bit from the PSR mode,
        to reflect the four-bit ARM_CPU_MODE_ defines.
    */
    ASSERT( cpu && result );

    if(!cpu || !result)
        return;
    if(which == CPSR){
        *result = cpu->cpsr.f.mode & 0xF;
    } else if(which == SPSR){
        /*  TODO: Add assert for NULL pointer */
        *result = cpu->spsr[cpu->cpsr.f.mode & 0xF].f.mode & 0xF;
    }
    return;
}

uint32_t* GetProgramCounter(ARM_CPU* cpu)
{
    int mode;

    ASSERT(cpu);
    if(!cpu)
        return NULL;
    return (cpu->reg[0][PC]);
}

void RaiseException(ARM_CPU* cpu, ARM_Exception which)
{
    ASSERT(cpu);
    cpu->exception |= which;
    return;
}

void ClearException(ARM_CPU* cpu, ARM_Exception which)
{
    ASSERT(cpu);
    cpu->exception &= ~which;
    return;
}

/* 1 on exception. Does this make sense? Other functions return -1 on "error" */
int GetException(ARM_CPU* cpu, ARM_Exception which)
{
    ASSERT(cpu);
    if(cpu->exception & which)
        return 1;
    return 0;
}

ARM_Exception HandleException(ARM_CPU* cpu)
{
    ASSERT( cpu != NULL );

    /*  Note:, PC is not banked, so the CPU_MODE does not matter for the index.
        For example, cpu->reg[ARM_CPU_MODE_UND][PC],
        cpu->reg[ARM_CPU_MODE_FIQ][PC] or cpu->reg[ARM_CPU_MODE_USR][PC] would
        all point to the same register. We just pass [0] in the code below to
        avoid confusion.
    */
    /* TODO: Implement proper priorities */
    if(!cpu->exception)
        return ARM_Exception_None;
    else if(cpu->exception & ARM_Exception_Unpredictable){
        return ARM_Exception_Unpredictable;
    }
    else if(cpu->exception & ARM_Exception_Reset){
        ResetCPU(cpu);
        /* ResetMemory(mem); */
        /* LoadBinary(&mem "foo.bin", EXCEPTION_VECTOR_TABLE_RESET); */
        FlushPipeline(cpu);
        ClearException(cpu, ARM_Exception_Reset);
        return ARM_Exception_Reset;
    }
    else if(cpu->exception & ARM_Exception_Undefined){
        cpu->spsr[ARM_CPU_MODE_UND] = cpu->cpsr;
        cpu->cpsr.f.mode = (1<<4) | ARM_CPU_MODE_UND;
        cpu->cpsr.f.thumb = 0; /* run in ARM state */
        cpu->cpsr.f.irq = 1; /* disable interrupts (but leave FIQ alone) */
        *(cpu->reg[ARM_CPU_MODE_UND][LR]) = *(cpu->reg[0][PC]) + 8;
        *(cpu->reg[0][PC]) = EXCEPTION_VECTOR_TABLE_UND;
        FlushPipeline(cpu);
        ClearException(cpu, ARM_Exception_Undefined);
        return ARM_Exception_Undefined;
    }
    else if(cpu->exception & ARM_Exception_Software_Interrupt){
        cpu->spsr[ARM_CPU_MODE_SVC] = cpu->cpsr;
        cpu->cpsr.f.mode = (1<<4) | ARM_CPU_MODE_UND;
        cpu->cpsr.f.thumb = 0;
        cpu->cpsr.f.irq = 1;
        *(cpu->reg[ARM_CPU_MODE_SVC][LR]) = *(cpu->reg[0][PC]) + 8;
        *(cpu->reg[0][PC]) = EXCEPTION_VECTOR_TABLE_SWI;
        FlushPipeline(cpu);
        ClearException(cpu, ARM_Exception_Software_Interrupt);
        return ARM_Exception_Software_Interrupt;
    }
    else if(cpu->exception & ARM_Exception_Prefetch_Abort){
        cpu->spsr[ARM_CPU_MODE_ABT] = cpu->cpsr;
        cpu->cpsr.f.mode = (1<<4) | ARM_CPU_MODE_UND;
        cpu->cpsr.f.thumb = 0;
        cpu->cpsr.f.irq = 1;
        *(cpu->reg[ARM_CPU_MODE_ABT][LR]) = *(cpu->reg[0][PC]) + 8;
        *(cpu->reg[0][PC]) = EXCEPTION_VECTOR_TABLE_IABT;
        FlushPipeline(cpu);
        ClearException(cpu, ARM_Exception_Prefetch_Abort);
        return ARM_Exception_Prefetch_Abort;
    }
    else if(cpu->exception & ARM_Exception_Data_Abort){
        cpu->spsr[ARM_CPU_MODE_ABT] = cpu->cpsr;
        cpu->cpsr.f.mode = (1<<4) | ARM_CPU_MODE_UND;
        cpu->cpsr.f.thumb = 0;
        cpu->cpsr.f.irq = 1;
        *(cpu->reg[ARM_CPU_MODE_ABT][LR]) = *(cpu->reg[0][PC]) + 8;
        *(cpu->reg[0][PC]) = EXCEPTION_VECTOR_TABLE_DABT;
        FlushPipeline(cpu);
        ClearException(cpu, ARM_Exception_Data_Abort);
        return ARM_Exception_Data_Abort;
    }
    else if(cpu->exception & ARM_Exception_Interrupt){
        cpu->spsr[ARM_CPU_MODE_IRQ] = cpu->cpsr;
        cpu->cpsr.f.mode = (1<<4) | ARM_CPU_MODE_UND;
        cpu->cpsr.f.thumb = 0;
        cpu->cpsr.f.irq = 1;
        *(cpu->reg[ARM_CPU_MODE_IRQ][LR]) = *(cpu->reg[0][PC]) + 8;
        *(cpu->reg[0][PC]) = EXCEPTION_VECTOR_TABLE_IRQ;
        FlushPipeline(cpu);
        ClearException(cpu, ARM_Exception_Interrupt);
        return ARM_Exception_Interrupt;
    }
    else if(cpu->exception & ARM_Exception_Fast_Interrupt){
        cpu->spsr[ARM_CPU_MODE_FIQ] = cpu->cpsr;
        cpu->cpsr.f.mode = (1<<4) | ARM_CPU_MODE_UND;
        cpu->cpsr.f.thumb = 0;
        cpu->cpsr.f.irq = 1;
        cpu->cpsr.f.fiq = 1; /* disable FIQ for FIQ exceptions */
        *(cpu->reg[ARM_CPU_MODE_FIQ][LR]) = *(cpu->reg[0][PC]) + 8;
        *(cpu->reg[0][PC]) = EXCEPTION_VECTOR_TABLE_FIQ;
        FlushPipeline(cpu);
        ClearException(cpu, ARM_Exception_Fast_Interrupt);
        return ARM_Exception_Fast_Interrupt;
    }
    else
        ASSERT(!"Invalid exception enum");
    return ARM_Exception_None;
}

void FlushPipeline(ARM_CPU* cpu)
{
    cpu->shouldflush = 1;
    return;
}

