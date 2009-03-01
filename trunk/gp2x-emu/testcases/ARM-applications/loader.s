.arm
.section .text
.global start
start:
B entrypoint @@mov pc, #0x20
sub pc, pc, #0x8 @@ Undefined           0x04
sub pc, pc, #0x8 @@ Software interrupt  0x08
sub pc, pc, #0x8 @@ Prefetch abort      0x0C
sub pc, pc, #0x8 @@ Data Abort          0x10
sub pc, pc, #0x8 @@ 0x14 is unused      0x14
sub pc, pc, #0x8 @@ IRQ                 0x18
sub pc, pc, #0x8 @@ FIQ                 0x1C

