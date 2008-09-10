#include <stdio.h>
#include <stdlib.h>
#include <arm_emu.h>
#include <ARMsparc64.h>
#include <ARMArit.h>
#include <ARMLoadStore.h>
#include <MMU.h>
#include <sparc64.h>




static void loadMultRegs(u32 addr, u32 regNum){



	int counter=0;

	while(counter<16){

		if(CINST&(1<<counter)){
			if(counter == 15){
				fprintf(stderr,"loadMultRegs(): warning r15 overwritten\n");
			}
			GPR(counter).sVal=readMemU32(addr);	
			addr+=4;
		}
		counter++;
	}


	if( _W_ ){
		GPR(regNum).uVal=addr;
	}
}


static void storeMultRegs(u32 addr, u32 regNum){

	int counter=0;

	while(counter<16){
		
		if(CINST&(1<<counter)){
			writeMemU32(addr,GPR(counter).uVal);
			addr+=4;
		}
		counter++;
	}

	if( _W_ ){
		GPR(regNum).uVal=addr;
	}
}

void recLDM1(void){

	CHECK_CONDITION(0);
#ifdef _DEBUG_ 
	if( _Rn_ == 15){
		fprintf(stderr,"recLDM1(): _Rn_ == 15\n");
	}
#endif
}



void recLDM2(void){

	CHECK_CONDITION(0);
#ifdef _DEBUG_ 
	if( _Rn_ == 15 ){
		fprintf(stderr,"recLDM2(): _Rn_ == 15\n");
	}
#endif 
}


void recLDM3(void){

}


void recLDR(void){

}


void recLDRB(void){

}


void recLDRBT(void){

}


void recLDRH(void){

}


void recLDRSB(void){

}


void recLDRSH(void){

}