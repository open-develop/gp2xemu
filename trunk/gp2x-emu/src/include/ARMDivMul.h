#ifndef _ARMDivMul_h_
#define _ARMDivMul_h_
#include <arm_emu.h>


void recMUL(void);
void recMLA(void);
void recSMULL(void);
void recSMLAL(void);
void recUMULL(void);
void recUMLAL(void);
u32 matchCondition(u32 );

#endif
