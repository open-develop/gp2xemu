#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "emulator/disasm_arm.h"
#include "emulator/cpu/cpu.h"
#include "emulator/instrset_armv4.h"

int main(int argc, const char* argv[])
{
    ARM_CPU cpu;
    ARM_Memory mem;
    uint32_t *pc;
    ARM_Word instr;
    int type;

    ResetCPU(&cpu);
    InitMemory(&mem, 0x1000);
    //LoadBinary(&mem "foo.bin", 0x0);

    while(1)
    {
        if(!cpu.cpubusywait){
            pc = GetProgramCounter(&cpu);
            instr.word = FetchInstruction32(&cpu, &mem);
            type = ARMV4_ParseInstruction(instr);
            cpu.cpubusywait  = ARMV4_ExecuteInstruction(&cpu, &mem, (ARMV4_Instruction)instr.word, type);
            if( HandleException(&cpu) ) //undefined, interrupt, SWI, data abort, etc
                continue;
            if(!cpu.shouldflush)
                *pc += 4;
        }
        else
            --cpu.cpubusywait;
    }
    return 0;
}
