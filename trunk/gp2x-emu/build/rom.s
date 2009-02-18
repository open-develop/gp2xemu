@@ All exceptions except Reset runs in an infinite loop
@@ The NAND controller is suppose to load the first 512 bytes from NAND
@@ and to memory during a Reset, so assume that length for now.
.arm
.section .text
.global _start
_start:
mov pc, #0x20 @@ Reset.                 0x00
sub pc, pc, #0x8 @@ Undefined           0x04
sub pc, pc, #0x8 @@ Software interrupt  0x08
sub pc, pc, #0x8 @@ Prefetch abort      0x0C
sub pc, pc, #0x8 @@ Data Abort          0x10
sub pc, pc, #0x8 @@ 0x14 is unused      0x14
sub pc, pc, #0x8 @@ IRQ                 0x18
sub pc, pc, #0x8 @@ FIQ                 0x1C
mov r0, #1 @@ 0x20
mov r1, #2
add r2, r0, r1
mov r2, r2, LSL#3
sub pc, pc, #0x8

