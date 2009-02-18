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

#ifndef MEMORY_H_INCLUDED
#define MEMORY_H_INCLUDED
/* need uint32_t */
#include <stdint.h>
#include "../cpu/cpu.h"
#include "nand.h"

/* TODO:
 * Implement the MMU and MPU interfaces.
 * No support for access regions, memory translation, cache and write buffers for now
 */

 #define ARM_MEMORY_SIZE 0x10000

/* TODO: Add an indirection here, so we can map hardware registers */
typedef struct ARM_Memory
{
    uint8_t *mem;
    unsigned int length;
} ARM_Memory;

/* len must be a multiple of four */
int InitMemory(ARM_NAND* nand, ARM_Memory* mem, unsigned int len);
void DestroyMemory(ARM_Memory* mem);
void ReInitializeMemory(ARM_Memory* mem);

uint32_t FetchInstruction32(ARM_CPU* cpu, const ARM_Memory* mem);
uint16_t FetchInstruction16(ARM_CPU* cpu, const ARM_Memory* mem);

uint32_t FetchMemory32(ARM_CPU* cpu, const ARM_Memory* mem, uint32_t address);
uint16_t FetchMemory16(ARM_CPU* cpu, const ARM_Memory* mem, uint32_t address);
uint8_t   FetchMemory8(ARM_CPU* cpu, const ARM_Memory* mem, uint32_t address);
#endif

