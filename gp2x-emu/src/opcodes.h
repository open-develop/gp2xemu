#ifndef OPCODES_H_
#define OPCODES_H_
#include "opcodelist.h"

#define ARITHMETIC_S_FLAG_MASK (1<<20)

typedef unsigned int instr_t;
typedef int (*opcode_callback_t)(unsigned int, instr_t);

typedef struct opcode_mask_t
{
   unsigned long sbo;
   unsigned long sbz;
   const char* name;
   opcode_callback_t callback;
} opcode_mask_t;
#endif
