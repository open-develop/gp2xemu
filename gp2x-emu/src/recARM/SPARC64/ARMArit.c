#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arm_emu.h>
#include <ARMsparc64.h>
#include <ARMArit.h>
#include <sparc64.h>
/*#warning "S-flag still has to be added"
 */



/* table to get the right value to shift the operand 
 * only even values are allowed and we use the shift field in
 * the instruction as index for the table 
 */

const u32 shift_table[16]={0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30};
const u32 flagsTable[]={0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xa,0xb,0xc,0xd,0xe,0xf};


void (*shiftDispatch[])(v9GPReg ) = {
leftShiftImm, leftShiftReg, rightShiftImm, rightShiftReg,
aritShiftImm, aritShiftReg, rightRotImm, rightRotReg,
};

void leftShiftImm(v9GPReg reg){
}


void rightShiftImm(v9GPReg reg){
}

void leftShiftReg(v9GPReg reg){
}

void rightShiftReg(v9GPReg reg){
}

void aritShiftImm(v9GPReg reg){
}

void aritShiftReg(v9GPReg reg){
}

void rightRotImm(v9GPReg reg){
}

void rightRotReg(v9GPReg reg){
}




void recADDi(void){

}

void recADDs(void){
	
}



void recADCi(void){
	
}


void recADCs(void){

}


void recANDi(void){

}


void recANDs(void){

}




void recSUBi(void){

}


void recSUBs(void){

}


	


void recEORi(void){

}


void recEORs(void){

}

		
void recORRi(void){

}

void recORRs(void){

}


void recRSBi(void){

}

void recRSBs(void){

}


void recRSCi(void){

}

void recRSCs(void){

}


void recSBCi(void){


}

void recSBCs(void){

}


void recCLZ(void){
}

void recBICi(void){

}


void recBICs(void){

}

void recMOVi(void){

}


void recMOVs(void){

}




void recMVNi(void){
	
}

void recMVNs(void){

}
