#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "emulator/disasm_arm.h"
#include "emulator/cpu/cpu.h"
#include "emulator/instrset_armv4.h"

void PrintInstruction(int type, uint32_t address);

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
#if 0
        scanf("%s", cmd);
        if(strcmp(cmd, "next") && strcmp(cmd, "n"))
            break;
        memset(cmd, '\0', sizeof(char) * 10);
#endif
        if(!cpu.cpubusywait){
            pc = GetProgramCounter(&cpu);
            instr_arm = FetchInstruction32(&cpu, &mem);
            type = ARMV4_ParseInstruction((ARM_Word)instr_arm);
            cpu.cpubusywait  = ARMV4_ExecuteInstruction(&cpu, &mem, (ARMV4_Instruction)instr_arm, type);
            exp = HandleException(&cpu); //undefined, interrupt, SWI, data abort, etc
            PrintInstruction(type, *pc);
            if(exp == ARM_Exception_Unpredictable){
                printf("Unpredictable behaviour at address %lu!\n",*pc);
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

void PrintInstruction(int type, uint32_t address)
{
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
    return;
}
