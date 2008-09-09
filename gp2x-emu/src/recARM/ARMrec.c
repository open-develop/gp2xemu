#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arm_emu.h>
#include <arm920t.h>
#include <x86.h>
#include <ARMrec.h>
#include <ARMArit.h>
#include <ARMDivMul.h>
#include <ARMLoadStore.h>
#include <ARMMisc.h>
#include <ARMJump.h>




static void (*recFUNC[8][32])(void);
static void (*recSPECIAL1[1][32])(void);
static void (*recSPECIAL2[1][32])(void);
static void (*recSPECIAL3[1][32])(void);
static void (*recSPECIAL4[1][32])(void);


void recompile(u32 *buf, size_t size){

	size_t ndx=0;

	printf("buf: %u\n",((u32)buf)&0x3);
	if(!(((u32)buf)&0x3)){
		while(ndx < size){
			printf("value: %#x\n",buf[ndx]);
			recompileInstruction(buf[ndx]);
			ndx++;
			getchar();
		}
	}
	else printf("error: buffer doesn't start on a 4 byte boundary\n");
}

void recompileInstruction(u32 inst){


	u32 ndx=0,ndx2=0;


	ndx=(inst>>25)&0x7;
	switch(ndx){
	case 0:
		ndx2=(inst>>21)&0xf;

		if(((inst>>7)&1) & ((inst>>4)&1)){
			const u32 spe=(inst>>4)&0xf;
			ndx2=(inst>>20)&0x1f;
			/* we have a special instruction */
			switch(spe){
				case 9:recSPECIAL1[ndx][ndx2]();
					break;
				case 11:
				       recSPECIAL2[ndx][ndx2]();
					break;
				case 13:
				       recSPECIAL3[ndx][ndx2]();
					break;
				case 15:
				       recSPECIAL4[ndx][ndx2]();
					break;
			}
		}
		else recFUNC[ndx][ndx2]();
		break;
	case 1:
		ndx2=(inst>>21)&0xf;
		recFUNC[ndx][ndx2]();
		break;
	case 2:
		ndx2=(inst>>20)&0x1f;
		recFUNC[ndx][ndx2]();
		break;
	case 3:
		ndx2=(inst>>20)&0x1f;
		recFUNC[ndx][ndx2]();
		break;

	case 4:
		ndx2=(inst>>20)&0x1f;
		recFUNC[ndx][ndx2]();
		break;
	case 5:
		ndx2=(inst>>20)&0x1f;
		if(_COND_ == ALWAYS){
			
		}
		recFUNC[ndx][ndx2]();
		break;

	case 6:
		break;

	case 7:
		ndx2=(inst>>20)&0x1f;
		recFUNC[ndx][ndx2]();
		break;

	}
}


static void (*recFUNC[8][32])(void) = {

	{
		recANDs,recEORs,recSUBs,recRSBs,recADDs,recADCs,recSBCs,recRSCs,

		recTSTs,recTEQs,recCMPs,recCMNs,recORRs,recMOVs,recBICs,recMVNs,

		recNULL,recNULL,recNULL,recNULL,recNULL,recNULL,recNULL,recNULL,

		recNULL,recNULL,recNULL,recNULL,recNULL,recNULL,recNULL,recNULL,

	},
	{

		recANDi,recEORi,recSUBi,recRSBi,recADDi,recADCi,recSBCi,recRSCi,

		recTSTi,recTEQi,recCMPi,recCMNi,recORRi,recMOVi,recBICi,recMVNi,

		recNULL,recNULL,recNULL,recNULL,recNULL,recNULL,recNULL,recNULL,

		recNULL,recNULL,recNULL,recNULL,recNULL,recNULL,recNULL,recNULL,
	},
	{
		recSTRi  ,recLDRi  ,recSTRi  ,recLDRi  ,recSTRBi,recLDRBi,recSTRBi,recLDRBi,
		 
		recSTRiu ,recLDRiu ,recSTRiu ,recLDRiu ,recSTRBiu,recLDRBiu,recSTRBiu,recLDRBiu,

		recSTRip ,recLDRip ,recSTRip ,recLDRip ,recSTRBip,recLDRBip,recSTRBip,recLDRBip,

		recSTRiup,recLDRiup,recSTRiup,recLDRiup,recSTRBiup,recLDRBiup,recSTRBiup,recLDRBiup,
	},

	{
		recSTR  ,recLDR  ,recSTR  ,recLDR  ,recSTRB,recLDRB,recSTRB,recLDRB,
		 
		recSTRu ,recLDRu ,recSTRu ,recLDRu ,recSTRBu,recLDRBu,recSTRBu,recLDRBu,

		recSTRp ,recLDRp ,recSTRp ,recLDRp ,recSTRBp,recLDRBp,recSTRBp,recLDRBp,

		recSTRup,recLDRup,recSTRup,recLDRup,recSTRBup,recLDRBup,recSTRBup,recLDRBup,
	},
	{
		recNULL,recNULL,recNULL,recNULL,recNULL,recNULL,recNULL,recNULL,
		recNULL,recNULL,recNULL,recNULL,recNULL,recNULL,recNULL,recNULL,
		recNULL,recNULL,recNULL,recNULL,recNULL,recNULL,recNULL,recNULL,
		recNULL,recNULL,recNULL,recNULL,recNULL,recNULL,recNULL,recNULL,
	},
	{
		recB,recB,recB,recB,recB,recB,recB,recB,

		recB,recB,recB,recB,recB,recB,recB,recB,

		recBL,recBL,recBL,recBL,recBL,recBL,recBL,recBL,

		recBL,recBL,recBL,recBL,recBL,recBL,recBL,recBL,
	},
	{
		recNULL,recNULL,recNULL,recNULL,recNULL,recNULL,recNULL,recNULL,
		recNULL,recNULL,recNULL,recNULL,recNULL,recNULL,recNULL,recNULL,
		recNULL,recNULL,recNULL,recNULL,recNULL,recNULL,recNULL,recNULL,
		recNULL,recNULL,recNULL,recNULL,recNULL,recNULL,recNULL,recNULL,
	},
	{
		recSWI,recSWI,recSWI,recSWI,recSWI,recSWI,recSWI,recSWI,

		recSWI,recSWI,recSWI,recSWI,recSWI,recSWI,recSWI,recSWI,
	},
};


static void (*recSPECIAL1[1][32])(void)={

	{
		recMUL  ,recMUL  ,recMUL ,recMUL ,recNULL,recNULL,recNULL,recNULL,
		recMLA  ,recMLA  ,recMLA ,recMLA ,recMLA ,recMLA ,recMLA ,recMLA,
		recSWP  ,recNULL ,recNULL,recNULL,recSWPB,recNULL,recNULL,recNULL,
		recNULL ,recNULL ,recNULL,recNULL,recNULL,recNULL,recNULL,recNULL,
	}
};


static void (*recSPECIAL2[1][32])(void)={

	{
		recSTRH  ,recLDRH  ,recSTRH  ,recLDRH  ,recSTRHi ,recLDRHi  ,recSTRHi  ,recLDRHi,
		recSTRHu ,recLDRHu ,recSTRHu ,recLDRHu ,recSTRHiu,recLDRHiu ,recSTRHiu ,recLDRHiu,
		recSTRHp ,recLDRHp ,recSTRHp ,recLDRHp ,recSTRHip,recLDRHip ,recSTRHip ,recLDRHip,
		recSTRHup,recLDRHup,recSTRup ,recLDRHup,recSTRiup,recLDRHiup,recSTRHiup,recLDRHiup
	},
};

static void (*recSPECIAL3[1][32])(void)={

	{
		recNULL,recLDRSB  ,recNULL,recLDRSB  ,recNULL,recLDRSBi  ,recNULL,recLDRSBi,
		recNULL,recLDRSBu ,recNULL,recLDRSBu ,recNULL,recLDRSBiu ,recNULL,recLDRSBiu,
		recNULL,recLDRSBp ,recNULL,recLDRSBp ,recNULL,recLDRSBip ,recNULL,recLDRSBip,
		recNULL,recLDRSBup,recNULL,recLDRSBup,recNULL,recLDRSBiup,recNULL,recLDRSBiup,
	},
};

static void (*recSPECIAL4[1][32])(void)={

	{
		recNULL,recLDRSH  ,recNULL,recLDRSH  ,recNULL,recLDRSHi  ,recNULL,recLDRSHi,
		recNULL,recLDRSHu ,recNULL,recLDRSHu ,recNULL,recLDRSHiu ,recNULL,recLDRSHiu,
		recNULL,recLDRSHp ,recNULL,recLDRSHp ,recNULL,recLDRSHip ,recNULL,recLDRSHip,
		recNULL,recLDRSHup,recNULL,recLDRSHup,recNULL,recLDRSHiup,recNULL,recLDRSHiup,
	},
};
