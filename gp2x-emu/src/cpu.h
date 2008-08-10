#ifndef CPU_H_
#define CPU_H_

#include "registers.h"
#include "opcodes.h"

typedef struct cpu_t
{
    int type; /* is this the 920 or 940? MCR and MRC must know */
    /* normal registers */
    regs_t r;
    /* system control coprocessor CP15 */
};

    reg_t ReadRegister0(instr_t);
    reg_t ReadRegister1(instr_t);
    reg_t ReadRegister2(instr_t;
    reg_t ReadRegister3(instr_t;
    reg_t ReadRegister4(instr_t;
#endif

