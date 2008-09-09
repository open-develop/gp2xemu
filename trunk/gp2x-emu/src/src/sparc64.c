#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <arm_emu.h>
#include <sparc64.h> 






__inline void ADD(v9GPReg dst,v9GPReg src1, v9GPReg src2, int cc){
	OPCODE2(SET_CC(0),dst,src1,src2)
}

__inline void ADDI(v9GPReg dst, v9GPReg src1, s32 imm, int cc){
	OPCODE2i(SET_CC(0),dst,src1,imm)
}

__inline void ADDC(v9GPReg dst, v9GPReg src1, s32 imm, int cc){
	OPCODE2(SET_CC(8),dst,src1,imm);
}

__inline void ADDCI(v9GPReg dst, v9GPReg src1, s32 imm , int cc){
	OPCODE2i(SET_CC(8),dst,src1,imm);
}

__inline void BIcc(condition_t cc, s32 disp, int annul){

	u32 i=((cc<<COND_OFF)|(2<<22)|((annul&1)<<ANNUL_OFF) | (disp&0x3fffff)) ;
	WRITE_INST(i);
}

__inline void BPcc(condition_t cc, s32 disp, int annul, int cc10){
	u32 i = ((cc<<COND_OFF) | (2<<22)|((annul&1)<<ANNUL_OFF) | (disp&0x7ffff) | (1<<19)|(cc10<<20));
	WRITE_INST(i);
}

__inline void CALL(s32 disp){
	WRITE_INST(OP1|(disp&0x3fffffff));
}

__inline void CSASA(v9GPReg rd, v9GPReg rs1, v9GPReg rs2){
	u32 i = (OP3 | (0x3c<<OPC_OFF)|(rd<<RD_OFF) | (rs1<<RS1_OFF) |(rs2<<RS2_OFF));
	WRITE_INST(i);
}

__inline void CSASAi(v9GPReg rd, v9GPReg rs1, v9GPReg rs2, s32 imm){
	u32 i = (OP3i | (0x3c<<OPC_OFF) | (rd<<RD_OFF) | ((imm&0xff)<<5)| (rs1<<RS1_OFF)| (rs2<<RS2_OFF));
	WRITE_INST(i);

}

__inline void CSASXA(v9GPReg rd, v9GPReg rs1, v9GPReg rs2){
	u32 i = (OP3  | ( 0x3e<<OPC_OFF) | (rd<<RD_OFF)| (rs1<<RS1_OFF) | (rs2<<RS2_OFF));
	WRITE_INST(i);
}

__inline void CSASXAi(v9GPReg rd, v9GPReg rs1, v9GPReg rs2, s32 imm){
	u32 i = (OP3i | (0x3e<<OPC_OFF) | (rd<RD_OFF) | ((imm&0xff)<<5) |  (rs1<<RS1_OFF) | (rs2<<RS2_OFF));
	WRITE_INST(i);
}

__inline void UDIV(v9GPReg rd, v9GPReg rs1, v9GPReg rs2, int cc){
	OPCODE2(SET_CC(0xe),rd,rs1,rs2);
}

__inline void UDIVi(v9GPReg rd, v9GPReg rs1, s32 imm, int cc){
	OPCODE2i(SET_CC(0xe),rd,rs1,imm);
}


__inline void SDIV(v9GPReg rd, v9GPReg rs1, v9GPReg rs2, int cc){
	OPCODE2(SET_CC(0xf),rd,rs1,rs2);
}

__inline void SDIVi(v9GPReg rd, v9GPReg rs1, s32 imm, int cc){
	OPCODE2i(SET_CC(0xf),rd,rs1,imm);
}

__inline void DONE(void){
	u32 i = (OP2 | (0<<25) | (0x2e<<19));
	WRITE_INST(i);
}

__inline void ENTRY(void){
	u32 i = (OP2 | (1<<25) |( 0x2e<<19));
	WRITE_INST(i);
}

__inline void FLUSH(v9GPReg rs1, v9GPReg rs2){
	OPCODE2(0x3b,0,rs1,rs2);
}

__inline void FLUSHi(v9GPReg rs1, s32 imm){
	OPCODE2i(0x3b,0,rs1,imm);
}

__inline void FLUSHW(void){
	OPCODE2(0x2b,0,0,0);
}

__inline void ILLTRAP(void){
	OPCODE0(0,0,0,0);
}

__inline void JUMPL(v9GPReg rd, v9GPReg rs1, v9GPReg rs2){
	OPCODE2(0x38,rd,rs1,rs2);
}

__inline void JUMPLi(v9GPReg rd, v9GPReg rs1, s32 imm){
	OPCODE2i(0x38,rd,rs1,imm);
}

__inline void LDSB(v9GPReg rd, v9GPReg rs1, v9GPReg rs2){
	OPCODE3(0x09,rd,rs1,rs2);
}

__inline void LDSBi(v9GPReg rd, v9GPReg rs1, s32 imm){
	OPCODE3i(0x09,rd,rs1,imm);
}

__inline void LDSH(v9GPReg rd, v9GPReg rs1, v9GPReg rs2){
	OPCODE3(0xa,rd,rs1,rs2);
}

__inline void LDSHi(v9GPReg rd, v9GPReg rs1, s32 imm){
	OPCODE3i(0xa,rd,rs1,imm);
}


__inline void LDSW(v9GPReg rd, v9GPReg rs1, v9GPReg rs2){
	OPCODE3(0x08,rd,rs1,rs2);
}

__inline void LDSWi(v9GPReg rd, v9GPReg rs1, s32 imm){
	OPCODE3i(0x08,rd,rs1,imm);
}

__inline void LDUB(v9GPReg rd, v9GPReg rs1, v9GPReg rs2){
	OPCODE3(0x01,rd,rs1,rs2);
}

__inline void LDUBi(v9GPReg rd, v9GPReg rs1, s32 imm){
	OPCODE3i(0x01,rd,rs1,imm);
}

__inline void LDUH(v9GPReg rd, v9GPReg rs1, v9GPReg rs2){
	OPCODE3(0x02,rd,rs1,rs2);
}

__inline void LDUHi(v9GPReg rd, v9GPReg rs1, s32 imm){
	OPCODE3i(0x03,rd,rs1,imm);
}

__inline void LDUW(v9GPReg rd, v9GPReg rs1, v9GPReg rs2){
	OPCODE3(0x00,rd,rs1,rs2);
}

__inline void LDUWi(v9GPReg rd, v9GPReg rs1, s32 imm){
	OPCODE3i(0x00,rd,rs1,imm);
}

__inline void LDX(v9GPReg rd, v9GPReg rs1, v9GPReg rs2){
	OPCODE3(0x0b,rd,rs1,rs2);
}

__inline void LDXi(v9GPReg rd, v9GPReg rs1, s32 imm){
	OPCODE3i(0x0b,rd,rs1,imm);
}

__inline void LDSTUB(v9GPReg rd, v9GPReg rs1, v9GPReg rs2){
	OPCODE3(0x0d,rd,rs1,rs2);
}

__inline void LDSTUBi(v9GPReg rd, v9GPReg rs1, s32 imm){
	OPCODE3i(0x0d,rd,rs1,imm);
}

__inline void AND(v9GPReg rd, v9GPReg rs1, v9GPReg rs2, int cc){
	OPCODE2(SET_CC(0x01),rd,rs1,rs2);
}

__inline void ANDi(v9GPReg rd, v9GPReg rs1, s32 imm, int cc){
	OPCODE2i(SET_CC(0x01),rd,rs1,imm);
}

__inline void ANDN(v9GPReg rd, v9GPReg rs1, v9GPReg rs2, int cc){
	OPCODE2(SET_CC(0x05),rd,rs1,rs2);
}

__inline void ANDNi(v9GPReg rd, v9GPReg rs1, s32 imm, int cc){
	OPCODE2i(SET_CC(0x05),rd,rs1,imm);
}

__inline void OR(v9GPReg rd, v9GPReg rs1, v9GPReg rs2, int cc){
	OPCODE2(SET_CC(0x02),rd,rs1,rs2);
}

__inline void ORi(v9GPReg rd, v9GPReg rs1, s32 imm, int cc){
	OPCODE2i(SET_CC(0x02), rd, rs1, imm);
}

__inline void ORN(v9GPReg rd, v9GPReg rs1, v9GPReg rs2, int cc){
	OPCODE2(SET_CC(0x06),rd,rs1,rs2);
}

__inline void ORNi(v9GPReg rd, v9GPReg rs1, s32 imm, int cc){
	OPCODE2i(SET_CC(0x06),rd,rs1,imm);
}

__inline void XOR(v9GPReg rd, v9GPReg rs1, v9GPReg rs2, int cc){
	OPCODE2(SET_CC(0x03),rd,rs1,rs2);
}

__inline void XORi(v9GPReg rd, v9GPReg rs1, s32 imm, int cc){
	OPCODE2i(SET_CC(0x03),rd,rs1,imm);
}

__inline void XNOR(v9GPReg rd, v9GPReg rs1, v9GPReg rs2, int cc){
	OPCODE2(SET_CC(0x07),rd,rs1,rs2);
}

__inline void XNORi(v9GPReg rd, v9GPReg rs1, s32 imm, int cc){
	OPCODE2(SET_CC(0x07),rd,rs1,imm);
}

