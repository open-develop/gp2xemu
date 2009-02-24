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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "emulator/disasm_arm.h"
#include "emulator/cpu/cpu.h"
#include "emulator/instrset_armv4.h"

void PrintInstruction(ARM_CPU* cpu, int type, uint32_t address);

int main(int argc, const char* argv[])
{
    ARM_CPU cpu;
    ARM_NAND nand;
    ARM_Memory mem;
    ARM_Exception exp;
    uint32_t *pc;
    uint32_t instr_arm;
    uint16_t instr_thumb;
    int type;
    char cmd[10];
    
    if(argc != 2){
        printf("Usage: %s <foo.rom>\n", argv[0]);
        return 0;
    }
    
    memset(cmd, '\0', sizeof(char) * 10);
    ResetCPU(&cpu);
    InitNAND(&nand, argv[1]);
    InitMemory(&nand, &mem, 0x10000);
    
    printf("-All good so far.. starting.\n");

    while(1)
    {
#if 1
        scanf("%s", cmd);
        if(strcmp(cmd, "next") && strcmp(cmd, "n"))
            break;
        memset(cmd, '\0', sizeof(char) * 10);
#endif
        if(!cpu.cpubusywait){
            pc = GetProgramCounter(&cpu);
            instr_arm = ReadInstruction32(&cpu, &mem);
            type = ARMV4_ParseInstruction((ARM_Word)instr_arm);
            cpu.cpubusywait  = ARMV4_ExecuteInstruction(&cpu, &mem, (ARMV4_Instruction)instr_arm, type);
            exp = HandleException(&cpu); /*undefined, interrupt, SWI, data abort, etc */
            PrintInstruction(&cpu, type, *pc);
            if(exp == ARM_Exception_Unpredictable){
                printf("Unpredictable behaviour at address %u!\n",*pc);
                break;
            }
            if(!cpu.shouldflush)
                *pc += 4; /* cpu->cpsr.f.thumb ? 2 : 4; */
            else
                cpu.shouldflush = 0;
        }
        else
            --cpu.cpubusywait;
    }
    return 0;
}

void PrintInstruction(ARM_CPU* cpu, int type, uint32_t address)
{
    int i,j, regid, mode;
    printf("%X ",address);
    switch(type)
    {
        case ARMV4_TypeUndefined:
            printf("Undefined\n");
        break;
        case ARMV4_TypeUnpredictable:
            printf("Unpredictable\n");
        break;
        case ARMV4_TypeDataProcessing:
            printf("Data processing\n");
        break;
        case ARMV4_TypeMultiplication:
            printf("Multiplication\n");
        break;
        case ARMV4_TypeAtomicSwap:
            printf("SWP(B)\n");
        break;
        case ARMV4_TypeLoadStoreExtra:
            printf("Load/Store halfword\n");
        break;
        case ARMV4_TypeStatusRegister:
            printf("MSR/MRS\n");
        break;
        case ARMV4_TypeLoadStoreSingle:
            printf("LDR/STR\n");
        break;
        case ARMV4_TypeLoadStoreMultiple:
            printf("LDM/STM\n");
        break;
        case ARMV4_TypeBranch:
            printf("B/BL/BX\n");
        break;
        case ARMV4_TypeLoadStoreCoprocessor:
            printf("LDC/STC\n");
        break;
        case ARMV4_TypeDataProcessingCoprocessor:
            printf("CDP\n");
        break;
        case ARMV4_TypeRegisterTransferCoprocessor:
            printf("MCR/MRC\n");
        break;
        case ARMV4_TypeSoftwareInterrupt:
            printf("SWI\n");
        break;
    }
    GetStatusRegisterMode(cpu, CPSR, &mode);
    printf("Registers: \n");
    for(j=0; j<4;++j){
        for(i=0; i<4;++i){
            regid = i+j*4;
            if(regid < SP)
                printf("r%d %X ",regid, *cpu->reg[mode][regid]);
            else if(regid == SP)
                printf("sp %X ", *cpu->reg[mode][regid]);
            else if(regid == LR)
                printf("lr %X ", *cpu->reg[mode][regid]);
            else if(regid == PC)
                printf("pc %X ", *cpu->reg[mode][regid]);
        }
        printf("\n");
    }
    return;
}

