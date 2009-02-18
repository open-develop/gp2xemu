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

