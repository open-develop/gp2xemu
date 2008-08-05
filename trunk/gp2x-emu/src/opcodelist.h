#ifndef OPCODELIST_H_
#define OPCODELIST_H_

/*! TODO:
 *     We should be able to differ between UNPREDICTABLE and UNDEFINED
 *     instruction space. I bet the C library soft-float emulation
 *     depends on the "undefined" exception.
*/

#define INSTR_UNDEFINED0_SBO 0x000000D0
#define INSTR_UNDEFINED0_SBZ 0x0E100020
#define INSTR_UNDEFINED1_SBO 0x000000F0
#define INSTR_UNDEFINED1_SBZ 0x0E100000
#define INSTR_UNDEFINED2_SBO 0x06000010
#define INSTR_UNDEFINED2_SBZ 0x08000000

#define INSTR_UNPREDICTABLE0_SBO 0x08600000
#define INSTR_UNPREDICTABLE0_SBZ 0x06100000
#define INSTR_UNPREDICTABLE1_SBO 0x08700000
#define INSTR_UNPREDICTABLE1_SBZ 0x06000000

#define ADC0_SBO		0x02A00000
#define ADC0_SBZ		0x0D400000
#define ADC1_SBO		0x00A00000
#define ADC1_SBZ		0x0F400010
#define ADC2_SBO		0x00A00010
#define ADC2_SBZ		0x0F400080

#define ADD0_SBO		0x02800000
#define ADD0_SBZ		0x0D600000
#define ADD1_SBO		0x00800000
#define ADD1_SBZ		0x0F600010
#define ADD2_SBO		0x00800010
#define ADD2_SBZ		0x0F600080

#define AND0_SBO		0x02000000
#define AND0_SBZ		0x0DE00000
#define AND1_SBO		0x00000000
#define AND1_SBZ		0x0FE00010
#define AND2_SBO		0x00000010
#define AND2_SBZ		0x0FE00080

#define BIC0_SBO		0x03C00000
#define BIC0_SBZ		0x0C200000
#define BIC1_SBO		0x01C00000
#define BIC1_SBZ		0x0E200010
#define BIC2_SBO		0x01C00010
#define BIC2_SBZ		0x0E200080

#define B0_SBO			0x0A000000
#define B0_SBZ			0x05000000

#define BL0_SBO			0x0B000000
#define BL0_SBZ			0x04000000

#define BX0_SBO			0x012FFF10
#define BX0_SBZ			0x0ED000E0

#define CDP0_SBO		0x0E000000
#define CDP0_SBZ		0x01000010

#define CMN0_SBO		0x03700000
#define CMN0_SBZ		0x0C80F000
#define CMN1_SBO		0x01700000
#define CMN1_SBZ		0x0E80F010
#define CMN2_SBO		0x01700010
#define CMN2_SBZ		0x0E80F080

#define CMP0_SBO		0x03500000
#define CMP0_SBZ		0x0CA0F000
#define CMP1_SBO		0x01500000
#define CMP1_SBZ		0x0EA0F010
#define CMP2_SBO		0x01500010
#define CMP2_SBZ		0x0EA0F080

#define EOR0_SBO		0x02200000
#define EOR0_SBZ		0x0DC00000
#define EOR1_SBO		0x00200000
#define EOR1_SBZ		0x0FC00010
#define EOR2_SBO		0x00200010
#define EOR2_SBZ		0x0FC00080

#define LDC0_SBO		0x0C100000
#define LDC0_SBZ		0x02000000

#define LDM0_SBO		0x08500000
#define LDM0_SBZ		0x06208000
#define LDM1_SBO		0x08100000
#define LDM1_SBZ		0x06400000
#define LDM2_SBO		0x08508000
#define LDM2_SBZ		0x06000000

#define LDR0_SBO		0x04100000
#define LDR0_SBZ		0x0A400000
#define LDR1_SBO		0x06100000
#define LDR1_SBZ		0x08400010
#define LDR2_SBO		0x04500000
#define LDR2_SBZ		0x0A000000
#define LDR3_SBO		0x06500000
#define LDR3_SBZ		0x08000010
#define LDR4_SBO		0x04700000
#define LDR4_SBZ		0x0B000000
#define LDR5_SBO		0x06700000
#define LDR5_SBZ		0x09000010
#define LDR6_SBO		0x001000B0
#define LDR6_SBZ		0x0E000040
#define LDR7_SBO		0x001000D0
#define LDR7_SBZ		0x0E000020
#define LDR8_SBO		0x001000F0 /* addr mode */
#define LDR8_SBZ		0x0E000000 /* addr mode */
#define LDR9_SBO		0x04300000 /* addr mode */
#define LDR9_SBZ		0x0B400000
#define LDR10_SBO		0x06300000
#define LDR10_SBZ		0x09400010

#define MCR0_SBO		0x0E000010
#define MCR0_SBZ		0x01100000

#define MLA0_SBO		0x00200090
#define MLA0_SBZ		0x0FC00060

#define MOV0_SBO		0x03A00000
#define MOV0_SBZ		0x0C4F0000
#define MOV1_SBO		0x01A00000
#define MOV1_SBZ		0x0E4F0010
#define MOV2_SBO		0x01A00010
#define MOV2_SBZ		0x0E4F0080

#define MRC0_SBO		0x0E100010
#define MRC0_SBZ		0x01000000

#define MRS0_SBO		0x010F0000
#define MRS0_SBZ		0x0EF00FFF
#define MRS1_SBO		0x014F0000
#define MRS1_SBZ		0x0EB00FFF

/* NOTE the SBZ flag here,
   in addition to the 0 bit which  is a part of the opcode */
#define MSR0_SBO		0x0120F000
#define MSR0_SBZ		0x0ED00FF0
#define MSR1_SBO		0x0320F000
#define MSR1_SBZ		0x0CD00000
#define MSR2_SBO		0x0160F000
#define MSR2_SBZ		0x0E900FF0
#define MSR3_SBO		0x0360F000
#define MSR3_SBZ		0x0C900000

#define MUL0_SBO		0x00000090
#define MUL0_SBZ		0x0FE0F060

#define MVN0_SBO		0x03E00000
#define MVN0_SBZ		0x0C0F0000
#define MVN1_SBO		0x01E00000
#define MVN1_SBZ		0x0E0F0010
#define MVN2_SBO		0x01E00010
#define MVN2_SBZ		0x0E0F0080

#define ORR0_SBO		0x03800000
#define ORR0_SBZ		0x0C600000
#define ORR1_SBO		0x01800000
#define ORR1_SBZ		0x0E600010
#define ORR2_SBO		0x01800010
#define ORR2_SBZ		0x0E600080

#define RSB0_SBO		0x02600000
#define RSB0_SBZ		0x0D800000
#define RSB1_SBO		0x00600000
#define RSB1_SBZ		0x0F800010
#define RSB2_SBO		0x00600010
#define RSB2_SBZ		0x0F800080

#define RSC0_SBO		0x02E00000
#define RSC0_SBZ		0x0D000000
#define RSC1_SBO		0x00E00000
#define RSC1_SBZ		0x0F000010
#define RSC2_SBO		0x00E00010
#define RSC2_SBZ		0x0F000080

#define SBC0_SBO		0x02C00000
#define SBC0_SBZ		0x0D200000
#define SBC1_SBO		0x00C00000
#define SBC1_SBZ		0x0F200010
#define SBC2_SBO		0x00C00010
#define SBC2_SBZ		0x0F200080

#define SMLAL0_SBO		0x00E00090
#define SMLAL0_SBZ		0x0F000060

#define SMULL0_SBO		0x00C00090
#define SMULL0_SBZ		0x0F200060

#define STC0_SBO		0x0C000000
#define STC0_SBZ		0x02100000

#define STM0_SBO		0x08400000
#define STM0_SBZ		0x06308000
#define STM1_SBO		0x08000000
#define STM1_SBZ		0x06500000
#define STM2_SBO		0x08408000
#define STM2_SBZ		0x06100000

#define STR0_SBO		0x04000000
#define STR0_SBZ		0x0A500000
#define STR1_SBO		0x06000000
#define STR1_SBZ		0x08500010
#define STR2_SBO		0x04400000
#define STR2_SBZ		0x0A100000
#define STR3_SBO		0x06400000
#define STR3_SBZ		0x08100010
#define STR4_SBO		0x04600000
#define STR4_SBZ		0x0B100000
#define STR5_SBO		0x06600000
#define STR5_SBZ		0x09100010
#define STR6_SBO		0x000000B0
#define STR6_SBZ		0x0E100040
#define STR7_SBO		0x04200000
#define STR7_SBZ		0x0B500000
#define STR8_SBO		0x06200000
#define STR8_SBZ		0x09500010

#define SUB0_SBO		0x02400000
#define SUB0_SBZ		0x0DA00000
#define SUB1_SBO		0x00400000
#define SUB1_SBZ		0x0FA00010
#define SUB2_SBO		0x00400010
#define SUB2_SBZ		0x0FA00080

#define SWI0_SBO		0x0F000000
#define SWI0_SBZ		0x00000000

#define SWP0_SBO		0x01000090
#define SWP0_SBZ		0x0EF00F60
#define SWP1_SBO		0x01400090
#define SWP1_SBZ		0x0EB00F60

#define TEQ0_SBO		0x03300000
#define TEQ0_SBZ		0x0CC0F000
#define TEQ1_SBO		0x01300000
#define TEQ1_SBZ		0x0EC0F010
#define TEQ2_SBO		0x01300010
#define TEQ2_SBZ		0x0EC0F080

#define TST0_SBO		0x03100000
#define TST0_SBZ		0x0CE0F000
#define TST1_SBO		0x01100000
#define TST1_SBZ		0x0EE0F010
#define TST2_SBO		0x01100010
#define TST2_SBZ		0x0EE0F080

#define UMLAL0_SBO		0x00A00090
#define UMLAL0_SBZ		0x0F300060

#define UMULL0_SBO		0x00800090
#define UMULL0_SBZ		0x0F600060
#endif
