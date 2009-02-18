/*
Copyright (c) 2009,
Mads Andreas Elvheim

Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files, to deal in the software without
restriction, including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the software, and to permit persons to whom the
software is furnished to do so, subject to the following
conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.
*/

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
mov r0, #0xff000000 @@ 0x20
add r0, r0, #0xff0000
add r0, r0, #0xff00
add r0, r0, #0xff
mov r1, #0x3
mov r2, #0x10
mov r3, #0x23
adds r4, r0, r1
adc r5, r2, r3
sub pc, pc, #0x8

