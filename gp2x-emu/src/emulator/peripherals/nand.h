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

#ifndef NAND_H_INCLUDED
#define NAND_H_INCLUDED
#include <stdio.h>
#include <stdint.h>

typedef struct ARM_NAND
{
    FILE* file;
    int isopen;
} ARM_NAND;

/* number of 32-bit words loaded by NAND Boot Sequence with DMA0 */
#define NAND_BOOT_LOAD_SIZE 128

int InitNAND(ARM_NAND* nand, const char* filepath);
/*  Read the first 512 bytes from NAND during INIT and write them
    to the instr_boot buffer. */
int OnInitNAND(ARM_NAND* nand, uint32_t* instr_boot);
void DestroyNAND(ARM_NAND* nand);
#endif
