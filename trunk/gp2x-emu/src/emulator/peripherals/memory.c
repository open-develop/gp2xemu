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

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "memory.h"
#include "../cpu/cpu.h"
#include "../assert.h"

int InitMemory(ARM_NAND* nand, ARM_Memory* mem, unsigned int len)
{
    if(!mem || len < NAND_BOOT_LOAD_SIZE*4){
        ASSERT(!"mem pointer is zero, or len is of illegal size");
        return -1;
    }
    /* align to four */
    len = (len + 3) / 4;
    mem->mem = malloc( len * 4);
    memset(mem->mem, 0x0BADF00D, len * 4);
    mem->length = len * 4;
    if(!mem->mem){
        ASSERT(!"Allocation failure.");
        return -1;
    }

    OnInitNAND(nand, (uint32_t*)mem->mem);
    return len*4;
}

void DestroyMemory(ARM_Memory* mem)
{
    ASSERT(mem != NULL);

    if(mem->mem){
        free(mem->mem);
        mem->mem = NULL;
    }
    return;
}

void ReInitializeMemory(ARM_Memory* mem)
{
    ASSERT(mem != NULL);
    memset(mem->mem, 0x0BADF00D, mem->length);
}

/* TODO: Check memory access regions, writeback and cache here */
uint32_t FetchInstruction32(ARM_CPU* cpu, const ARM_Memory* mem)
{
    const void* src;
    uint32_t pc;
    ASSERT(cpu && mem);
    pc = *GetProgramCounter(cpu);
    src = mem->mem;
    pc &= ~0x3;
    if(pc >= mem->length){
        RaiseException(cpu, ARM_Exception_Prefetch_Abort);
        return ~0UL;
    }
    return ((const uint32_t*)src)[pc>>2];
}

uint16_t FetchInstruction16(ARM_CPU* cpu, const ARM_Memory* mem)
{
    const void* src;
    uint32_t pc;
    ASSERT(cpu && mem);
    pc = *GetProgramCounter(cpu);
    src = mem->mem;
    pc &= ~0x1;
    if(pc >= mem->length){
        RaiseException(cpu, ARM_Exception_Prefetch_Abort);
        return 0xFFFF;
    }
    return ((const uint16_t*)src)[pc>>1];
}

uint32_t FetchMemory32(ARM_CPU* cpu, const ARM_Memory* mem, uint32_t address)
{
    const void* src = mem->mem;
    address &= ~0x3;
    if(address >= mem->length){
        RaiseException(cpu, ARM_Exception_Data_Abort);
        return -1;
    }
    return ((const uint32_t*)src)[address>>2];
}

uint16_t FetchMemory16(ARM_CPU* cpu, const ARM_Memory* mem, uint32_t address)
{
    const void* src = mem->mem;
    address &= ~0x1;
    if(address >= mem->length){
        RaiseException(cpu, ARM_Exception_Data_Abort);
        return -1;
    }
    return ((const uint16_t*)mem)[address>>1];
}

uint8_t FetchMemory8(ARM_CPU* cpu, const ARM_Memory* mem, uint32_t address)
{
    const void* src = mem->mem;
    if(address >= mem->length){
        RaiseException(cpu, ARM_Exception_Data_Abort);
        return -1;
    }
    return ((const uint8_t*)mem)[address];
}

