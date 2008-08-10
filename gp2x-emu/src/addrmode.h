#ifndef ADDRMODE_H_
#define ADDRMODE_H_

#include "opcodes.h"

typedef unsigned char imm8_t;
typedef unsigned int imm32_t;
typedef unsigned char offset8_t;
typedef unsigned int offset12_t;

/* 32-bit immediate */
imm32_t AddrMode1_0(instr_t instr);
/* immediate shift, no shift or rotate right with extend*/
imm32_t int AddrMode1_1(instr_t instr);
/* register shift */
imm32_t int AddrMode1_2(instr_t instr);

#endif

