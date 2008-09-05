#ifndef CPU_H_
#define CPU_H_

#include "registers.h"
/*#include "opcodes.h"*/

typedef unsigned long instr_t; /* needed because of circular dependancy with opcodes.h */

typedef struct cpu_t
{
    int type; /* is this the 920 or 940? MCR and MRC must know */
    int active; /* True if the CPU is enabled, and false if it is RESET */
    /* normal registers */
    regs_t r;
    /* system control coprocessor CP15 */
    void (*mcr_callback)(instr_t instr, cpu_t* cpu);
    void (*mrc_callback)(instr_t instr, cpu_t* cpu);
};

#endif
