#ifndef _ARMSPARC64_H_
#define _ARMSPARC64_H_

#include <arm920t.h>
#include <sparc64.h>

u32 *code_ptr;

#define CHECK_CONDITION(slot) 

void leftShiftImm(v9GPReg );
void rightShiftImm(v9GPReg  );
void leftShiftReg(v9GPReg  );
void rightShiftReg(v9GPReg  );
void aritShiftImm(v9GPReg  );
void aritShiftReg(v9GPReg  );
void rightRotImm(v9GPReg  );
void rightRotReg(v9GPReg  );

#endif
