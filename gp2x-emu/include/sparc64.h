#ifndef _SPARC64_H_
#define _SPARC64_H_

#define v9CODE code_ptr

#define OP0	0x00000000U
#define OP1	0x40000000U
#define OP2	0x80000000U
#define OP3	0xc0000000U


#define RS2_OFF		0
#define IMM_OFF		13
#define RS1_OFF		14
#define OPC_OFF		19
#define RD_OFF		25
#define COND_OFF	25
#define ANNUL_OFF	29

#define OP0i	0x00001000U
#define OP1i	0x40001000U
#define OP2i	0x80001000U
#define OP3i	0xc0001000U

#define SET_CC(x)	(x|(cc<<5))

#define WRITE_INST(x)	do{\
				(*v9CODE)=x;\
				v9CODE++;\
			}while(1);

#define OPCODE0(opc,rd,rs1,rs2) WRITE_INST(((u32)(OP0|((rd&0x1f)<<RD_OFF)|(((opc)&0x1f)<<OPC_OFF)|((rs1&0x1f)<<RS1_OFF)|((rs2&0x31)<<RS2_OFF))))
#define OPCODE1(opc,rd,rs1,rs2) WRITE_INST(((u32)(OP1|((rd&0x1f)<<RD_OFF)|(((opc)&0x1f)<<OPC_OFF)|((rs1&0x1f)<<RS1_OFF)|((rs2&0x1f)<<RS2_OFF))))
#define OPCODE2(opc,rd,rs1,rs2) WRITE_INST(((u32)(OP2|((rd&0x1f)<<RD_OFF)|(((opc)&0x1f)<<OPC_OFF)|((rs1&0x1f)<<RS1_OFF)|((rs2&0x1f)<<RS2_OFF))))
#define OPCODE3(opc,rd,rs1,rs2) WRITE_INST(((u32)(OP3|((rd&0x1f)<<RD_OFF)|(((opc)&0x1f)<<OPC_OFF)|((rs1&0x1f)<<RS1_OFF)|((rs2&0x1f)<<RS2_OFF))))

#define OPCODE0i(opc,rd,rs1,imm) WRITE_INST(((u32)(OP0i|((rd&0x1f)<<RD_OFF)|(((opc)&0x1f)<<OPC_OFF)|((rs1&0x1f)<<RS1_OFF)|((imm&0x1fff)<<RS2_OFF))))
#define OPCODE1i(opc,rd,rs1,imm) WRITE_INST(((u32)(OP0i|((rd&0x1f)<<RD_OFF)|(((opc)&0x1f)<<OPC_OFF)|((rs1&0x1f)<<RS1_OFF)|((imm&0x1fff)<<RS2_OFF))WR))
#define OPCODE2i(opc,rd,rs1,imm) WRITE_INST(((u32)(OP0i|((rd&0x1f)<<RD_OFF)|(((opc)&0x1f)<<OPC_OFF)|((rs1&0x1f)<<RS1_OFF)|((imm&0x1fff)<<RS2_OFF))))
#define OPCODE3i(opc,rd,rs1,imm) WRITE_INST(((u32)(OP0i|((rd&0x1f)<<RD_OFF)|(((opc)&0x1f)<<OPC_OFF)|((rs1&0x1f)<<RS1_OFF)|((imm&0x1fff)<<RS2_OFF))))

u32 *code_ptr;

typedef enum {
	r0 = 0,
	r1,
	r2,
	r3,
	r4,
	r5,
	r6,
	r7,
	r8,
	r9,
	r10,
	r11,
	r12,
	r13,
	r14,
	r15,
	r16,
	r17,
	r18,
	r19,
	r20,
	r21,
	r22,
	r23,
	r24,
	r25,
	r26,
	r27,
	r28,
	r29,
	r30,
	r31
}v9GPReg;


typedef enum {
	g0 = r0,
	g1,
	g2,
	g3,
	g4,
	g5,
	g6,
	g7
}v9GlobReg;

typedef enum {
	o0 = r8,
	o1,
	o2,
	o3,
	o4,
	o5,
	o6,
	o7
}v9OutReg;

typedef enum {
	l0 = r16,
	l1,
	l2,
	l3,
	l4,
	l5,
	l6,
	l7
}v9LocReg;

typedef enum {
	i0 = r24,
	i1,
	i2,
	i3,
	i4,
	i5,
	i6,
	i7
}v9InReg;

enum {
	ICC=4,
	XCC=6
};

/* mapping from ARM to SPARC-Regs */

#define R0	l0	
#define R1	l1
#define R2	l2
#define R3	l3
#define R4	l4
#define R5	l5
#define R6	l6
#define R7	l7
#define R8	i0
#define R9	i1
#define R10	i2
#define R11	i3
#define R12	i4
#define R13	i5
#define R14	i6
#define R15	i7

typedef enum conditionCode {
	BN,
	BE,
	BLE,
	BL,
	BLEU,
	BCS,
	BNEG,
	BVS,
	BA,
	BNE,
	BG,
	BGE,
	BGU,
	BCC,
	BPOS,
	BVC
}condition_t;

union {
	v9GPReg reg;
	s32 imm;
}cont;

void ADD(v9GPReg dst, v9GPReg src1, v9GPReg src2, int cc);
void ADDI(v9GPReg dst, v9GPReg src1, s32 imm, int cc);
/*void ADDC(v9GPReg dst, v9GPReg src1, v9GPReg src2, int cc);*/
void ADDCI(v9GPReg dst, v9GPReg src1, s32 imm, int cc);


#endif
