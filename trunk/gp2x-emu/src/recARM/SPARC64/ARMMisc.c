#include <stdio.h>
#include <stdlib.h>
#include <arm_emu.h>
#include <ARMsparc64.h>
#include <ARMArit.h>
#include <ARMMisc.h>
#include <sparc64.h>


void recNULL(void){

	/* should write nop's? 
	 */
	printf("ARMMisc.c: recNULL() fixme\n");
}



void recSWI(void){

}


void recSWP(void){

}


void recSWPB(void){


	fprintf(stderr,"ARMMisc: recSWPB()\n");
}

void recTEQi(void){

}


void recTEQs(void){

}


void recTSTi(void){


}

void recTSTs(void){


}

void recCDP(void){
	printf("fixme: recCDP()\ncoprocessor\n");
	return ;
}


void recCMPi(void){
	
}


void recCMPs(void){

}


void recCMNi(void){

}



void recCMNs(void){

}

