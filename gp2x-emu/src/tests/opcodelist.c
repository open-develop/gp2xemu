#include <stdio.h>
#include "../opcodelist.h"
#include "../opcodes.h"

#define OPDEC(name, num) {name##num##_SBO, name##num##_SBZ, #name##num , NULL}

opcode_mask_t lut[] = {
	OPDEC(ADC,0),
	OPDEC(ADC,1),
	OPDEC(ADC,2)
};

int main(void)
{
	int i;
	for(i=0;i<sizeof(lut) / sizeof(opcode_mask_t); ++i)
		printf("%s\n",lut[i].name);
	return 0;
}