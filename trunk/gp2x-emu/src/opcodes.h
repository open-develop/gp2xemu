#ifndef OPCODES_H_
#define OPCODES_H_

#include "opcodelist.h"
#include "cpu.h"

#define ARITHMETIC_S_FLAG_MASK (1<<20)

typedef unsigned long instr_t;
typedef int (*opcode_callback_t)(instr_t, cpu_t*);

typedef struct opcode_mask_t
{
   unsigned long sbo;
   unsigned long sbz;
   const char* name;
   opcode_callback_t callback;
} opcode_mask_t;

extern opcode_mask_t opcode_lut[];
#endif
