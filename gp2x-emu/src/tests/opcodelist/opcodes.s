@@ Arithmetic, logical and comparsion instructions with
@@ barrel shifter (Adress Mode 1 according to ARM ARM) are first listed
@@
ADC r0, r1, #255
ADC r0, r1, r2
ADC r0, r1, r2, LSL #31
ADC r0, r1, r2, LSR #32
ADC r0, r1, r2, ASR #32
ADC r0, r1, r2, ROR #31
ADC r0, r1, r2, RRX
ADC r0, r1, r2, LSL r3
ADC r0, r1, r2, LSR r3
ADC r0, r1, r2, ASR r3
ADC r0, r1, r2, ROR r3

@@
ADD r0, r1, #255
ADD r0, r1, r2
ADD r0, r1, r2, LSL #31
ADD r0, r1, r2, LSR #32
ADD r0, r1, r2, ASR #32
ADD r0, r1, r2, ROR #31
ADD r0, r1, r2, RRX
ADD r0, r1, r2, LSL r3
ADD r0, r1, r2, LSR r3
ADD r0, r1, r2, ASR r3
ADD r0, r1, r2, ROR r3
@@
AND r0, r1, #255
AND r0, r1, r2
AND r0, r1, r2, LSL #31
AND r0, r1, r2, LSR #32
AND r0, r1, r2, ASR #32
AND r0, r1, r2, ROR #31
AND r0, r1, r2, RRX
AND r0, r1, r2, LSL r3
AND r0, r1, r2, LSR r3
AND r0, r1, r2, ASR r3
AND r0, r1, r2, ROR r3
@@
BIC r0, r1, #255
BIC r0, r1, r2
BIC r0, r1, r2, LSL #31
BIC r0, r1, r2, LSR #32
BIC r0, r1, r2, ASR #32
BIC r0, r1, r2, ROR #31
BIC r0, r1, r2, RRX
BIC r0, r1, r2, LSL r3
BIC r0, r1, r2, LSR r3
BIC r0, r1, r2, ASR r3
BIC r0, r1, r2, ROR r3
@@
CMN r0, #255
CMN r0, r1
CMN r0, r1, LSL #31
CMN r0, r1, LSR #32
CMN r0, r1, ASR #32
CMN r0, r1, ROR #31
CMN r0, r1, RRX
CMN r0, r1, LSL r3
CMN r0, r1, LSR r3
CMN r0, r1, ASR r3
CMN r0, r1, ROR r3
@@
CMP r0, #255
CMP r0, r1
CMP r0, r1, LSL #31
CMP r0, r1, LSR #32
CMP r0, r1, ASR #32
CMP r0, r1, ROR #31
CMP r0, r1, RRX
CMP r0, r1, LSL r3
CMP r0, r1, LSR r3
CMP r0, r1, ASR r3
CMP r0, r1, ROR r3
@@
EOR r0, r1, #255
EOR r0, r1, r2
EOR r0, r1, r2, LSL #31
EOR r0, r1, r2, LSR #32
EOR r0, r1, r2, ASR #32
EOR r0, r1, r2, ROR #31
EOR r0, r1, r2, RRX
EOR r0, r1, r2, LSL r3
EOR r0, r1, r2, LSR r3
EOR r0, r1, r2, ASR r3
EOR r0, r1, r2, ROR r3
@@
MOV r0, #255
MOV r0, r1
MOV r0, r1, LSL #31
MOV r0, r1, LSR #32
MOV r0, r1, ASR #32
MOV r0, r1, ROR #31
MOV r0, r1, RRX
MOV r0, r1, LSL r3
MOV r0, r1, LSR r3
MOV r0, r1, ASR r3
MOV r0, r1, ROR r3
@@
MVN r0, #255
MVN r0, r1
MVN r0, r1, LSL #31
MVN r0, r1, LSR #32
MVN r0, r1, ASR #32
MVN r0, r1, ROR #31
MVN r0, r1, RRX
MVN r0, r1, LSL r3
MVN r0, r1, LSR r3
MVN r0, r1, ASR r3
MVN r0, r1, ROR r3
@@
ORR r0, r1, #255
ORR r0, r1, r2
ORR r0, r1, r2, LSL #31
ORR r0, r1, r2, LSR #32
ORR r0, r1, r2, ASR #32
ORR r0, r1, r2, ROR #31
ORR r0, r1, r2, RRX
ORR r0, r1, r2, LSL r3
ORR r0, r1, r2, LSR r3
ORR r0, r1, r2, ASR r3
ORR r0, r1, r2, ROR r3
@@
RSB r0, r1, #255
RSB r0, r1, r2
RSB r0, r1, r2, LSL #31
RSB r0, r1, r2, LSR #32
RSB r0, r1, r2, ASR #32
RSB r0, r1, r2, ROR #31
RSB r0, r1, r2, RRX
RSB r0, r1, r2, LSL r3
RSB r0, r1, r2, LSR r3
RSB r0, r1, r2, ASR r3
RSB r0, r1, r2, ROR r3
@@
RSC r0, r1, #255
RSC r0, r1, r2
RSC r0, r1, r2, LSL #31
RSC r0, r1, r2, LSR #32
RSC r0, r1, r2, ASR #32
RSC r0, r1, r2, ROR #31
RSC r0, r1, r2, RRX
RSC r0, r1, r2, LSL r3
RSC r0, r1, r2, LSR r3
RSC r0, r1, r2, ASR r3
RSC r0, r1, r2, ROR r3
@@
SBC r0, r1, #255
SBC r0, r1, r2
SBC r0, r1, r2, LSL #31
SBC r0, r1, r2, LSR #32
SBC r0, r1, r2, ASR #32
SBC r0, r1, r2, ROR #31
SBC r0, r1, r2, RRX
SBC r0, r1, r2, LSL r3
SBC r0, r1, r2, LSR r3
SBC r0, r1, r2, ASR r3
SBC r0, r1, r2, ROR r3
@@
SUB r0, r1, #255
SUB r0, r1, r2
SUB r0, r1, r2, LSL #31
SUB r0, r1, r2, LSR #32
SUB r0, r1, r2, ASR #32
SUB r0, r1, r2, ROR #31
SUB r0, r1, r2, RRX
SUB r0, r1, r2, LSL r3
SUB r0, r1, r2, LSR r3
SUB r0, r1, r2, ASR r3
SUB r0, r1, r2, ROR r3
@@
TEQ r0, #255
TEQ r0, r1
TEQ r0, r1, LSL #31
TEQ r0, r1, LSR #32
TEQ r0, r1, ASR #32
TEQ r0, r1, ROR #31
TEQ r0, r1, RRX
TEQ r0, r1, LSL r3
TEQ r0, r1, LSR r3
TEQ r0, r1, ASR r3
TEQ r0, r1, ROR r3
@@
TST r0, #255
TST r0, r1
TST r0, r1, LSL #31
TST r0, r1, LSR #32
TST r0, r1, ASR #32
TST r0, r1, ROR #31
TST r0, r1, RRX
TST r0, r1, LSL r3
TST r0, r1, LSR r3
TST r0, r1, ASR r3
TST r0, r1, ROR r3

@@ Branches
B  0x00123454
BL 0x00123454
BX r0

@@ PSR instructions
MRS r0, cpsr
MRS r0, spsr
MSR cpsr_c, #1020
MSR cpsr_cxsf, r0
MSR spsr_c, #1020
MSR spsr_cxsf, r0

@@ Multiplication instructions
MUL r0, r1, r2
SMLAL r0, r1, r2, r3
SMULL r0, r1, r2, r3
UMLAL r0, r1, r2, r3
UMULL r0, r1, r2, r3

@@ Co-processor instructions. CDP, LDC and STC are not used by the CP15 coprocessor.
CDP p15, 10, cr1, cr2, cr3, 4
LDC p15, c0, [r0, #64]
LDC p15, c0, [r0, #64]!
LDC p15, c0, [r0], #64
LDC p15, c0, [r0], {127}
LDCL p15, c0, [r0, #64]
LDCL p15, c0, [r0, #64]!
LDCL p15, c0, [r0], #64
LDCL p15, c0, [r0], {127}
MCR p15, 0, r0, c1, c2, 4
@@ Memory-related instructions
