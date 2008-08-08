#include <stdlib.h>
#include <stdio.h>
#include "../../opcodelist.h"
#include "../../opcodes.h"

#define OPDEC(name, num) {name ## num ## _SBO, name##num##_SBZ, #name #num , NULL}

opcode_mask_t lut[] = {
	OPDEC(ADC,0),
	OPDEC(ADC,1),
	OPDEC(ADC,2),

	OPDEC(ADD,0),
	OPDEC(ADD,1),
	OPDEC(ADD,2),

	OPDEC(AND,0),
	OPDEC(AND,1),
	OPDEC(AND,2),

	OPDEC(BIC,0),
	OPDEC(BIC,1),
	OPDEC(BIC,2),

	OPDEC(B,0),
	OPDEC(BL,0),
	OPDEC(BX,0),

	OPDEC(CDP,0),

	OPDEC(CMN,0),
	OPDEC(CMN,1),
	OPDEC(CMN,2),

	OPDEC(CMP,0),
	OPDEC(CMP,1),
	OPDEC(CMP,2),

	OPDEC(EOR,0),
	OPDEC(EOR,1),
	OPDEC(EOR,2),

	OPDEC(LDC,0),

	OPDEC(LDM,0),
	OPDEC(LDM,1),
	OPDEC(LDM,2),

	OPDEC(LDR,0),
	OPDEC(LDR,1),
	OPDEC(LDR,2),
	OPDEC(LDR,3),
	OPDEC(LDR,4),
	OPDEC(LDR,5),
	OPDEC(LDR,6),
	OPDEC(LDR,7),
	OPDEC(LDR,8),
	OPDEC(LDR,9),
	OPDEC(LDR,10),

	OPDEC(MCR,0),

	OPDEC(MLA,0),

	OPDEC(MOV,0),
	OPDEC(MOV,1),
	OPDEC(MOV,2),

	OPDEC(MRC,0),

	OPDEC(MRS,0),
	OPDEC(MRS,1),

	OPDEC(MSR,0),
	OPDEC(MSR,1),
	OPDEC(MSR,2),
	OPDEC(MSR,3),

	OPDEC(MUL,0),

	OPDEC(MVN,0),
	OPDEC(MVN,1),
	OPDEC(MVN,2),

	OPDEC(ORR,0),
	OPDEC(ORR,1),
	OPDEC(ORR,2),

	OPDEC(RSB,0),
	OPDEC(RSB,1),
	OPDEC(RSB,2),

	OPDEC(RSC,0),
	OPDEC(RSC,1),
	OPDEC(RSC,2),

	OPDEC(SBC,0),
	OPDEC(SBC,1),
	OPDEC(SBC,2),

	OPDEC(SMLAL,0),
	OPDEC(SMULL,0),

	OPDEC(STC,0),

	OPDEC(STM,0),
	OPDEC(STM,1),
	OPDEC(STM,2),

    OPDEC(STR,0),
	OPDEC(STR,1),
	OPDEC(STR,2),
	OPDEC(STR,3),
	OPDEC(STR,4),
	OPDEC(STR,5),
	OPDEC(STR,6),
	OPDEC(STR,7),
	OPDEC(STR,8),

	OPDEC(SUB,0),
	OPDEC(SUB,1),
	OPDEC(SUB,2),

	OPDEC(SWI,0),

    OPDEC(SWP,0),
	OPDEC(SWP,1),

    OPDEC(TEQ,0),
	OPDEC(TEQ,1),
	OPDEC(TEQ,2),

	OPDEC(TST,0),
	OPDEC(TST,1),
	OPDEC(TST,2),

	OPDEC(UMLAL,0),
	OPDEC(UMULL,0)
};

#define IN 0
#define OUT 1

int main(void)
{
	int i,j,len,match;
	FILE *fp[2];
	instr_t *testdata;

	fp[IN] = fopen("opcode.bin", "rb");
	if(!fp[IN]){
        printf("Couldn't open test file opcodes.bin\n");
        return -1;
	}
	fseek(fp[IN], 0, SEEK_END);
	len = ftell(fp[IN]);
	rewind(fp[IN]);
	len /= 4;
	if(!len){
	    printf("Test file was empty.\n");
	    return -1;
	}

	testdata = malloc( sizeof(instr_t) * len);
	if(!testdata){
        printf("Out of memory.\n");
        return -1;
	}
	fread(testdata, sizeof(instr_t), len, fp[IN]);
	fclose(fp[IN]);

	fp[OUT] = fopen("opcodes.txt","w");
	if(!fp[OUT]){
        printf("Couldn't open file for writing.\n");
        return -1;
	}

	for(j=0;j<len;++j){
	    match = 0;
        for(i=0;i<sizeof(lut) / sizeof(opcode_mask_t); ++i){
            if( ((testdata[j]&lut[i].sbo) == lut[i].sbo) &&
                    (((~testdata[j])&lut[i].sbz) == lut[i].sbz) ){
                fprintf(fp[OUT], "%#8.8lX %s\n", j, lut[i].name);
                //printf("SBO: %#8.8lX\n", lut[i].sbo);
                //printf("SBO: %#8.8lX\n", lut[i].sbz);
                match = 1;
            }
        }
        if(!match){
            fprintf(fp[OUT], "%#8.8lX %s\n", j, "UNDEF/UNPRED");
        }
	}
	fclose(fp[OUT]);
	return 0;
}
