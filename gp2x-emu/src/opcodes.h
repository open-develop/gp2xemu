#ifndef OPCODES_H_
#define OPCODES_H_
#include "opcodelist.h"

typedef unsigned int opcode_t;
typedef int (*opcode_callback_t)(unsigned int, opcode_t);

typedef struct opcode_mask_t
{
   unsigned long sbo;
   unsigned long sbz;
   const char* name;
   opcode_callback_t callback;
};
#endif
