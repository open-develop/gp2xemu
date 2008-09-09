#ifndef _ARMArit_h_
#define _ARMArit_h_
#include <x86.h>


void leftShiftImm(x86GPReg);
void rightShiftImm(x86GPReg );
void leftShiftReg(x86GPReg );
void rightShiftReg(x86GPReg );
void aritShiftImm(x86GPReg );
void aritShiftReg(x86GPReg );
void rightRotImm(x86GPReg );
void rightRotReg(x86GPReg );

void recADCi(void);
void recADCs(void);
void recADDi(void);
void recADDs(void);
void recANDi(void);
void recANDs(void);
void recSUBi(void);
void recSUBs(void);
void recEORi(void);
void recEORs(void);
void recORRi(void);
void recORRs(void);
void recRSBi(void);
void recRSBs(void);
void recRSCi(void);
void recRSCs(void);
void recSBCi(void);
void recSBCs(void);
void recCLZ(void);
void recBICi(void);
void recBICs(void);
void recMOVi(void);
void recMOVs(void);
void recMRCi(void);
void recMRCs(void);
void recMVNi(void);
void recMVNs(void);


u32 matchCondition(u32 );




#endif 
