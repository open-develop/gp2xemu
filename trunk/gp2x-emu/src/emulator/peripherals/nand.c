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

#include "nand.h"
#include "../assert.h"

int InitNAND(ARM_NAND* nand, const char* filepath)
{
    if(!nand || !filepath){
        ASSERT(!"nand or filepath pointers are NULL");    
        return -1;
    }
    nand->isopen = 0;
    nand->file = fopen(filepath, "rw");
    
    if(!nand->file){
        ASSERT(!"nand->file is NULL after fopen");        
        return -1;
    }
    nand->isopen = 1;
    return 0;
}

/* Called by InitMemory in emulator/peripherals/memory.c */
int OnInitNAND(ARM_NAND* nand, uint32_t* instr_boot)
{
    int wordsread;
    long len;
    
    if(!nand || !instr_boot){
        ASSERT(!"nand or instr_boot pointers are NULL");
        return -1;
    }
    fseek(nand->file, 0, SEEK_END);
    len = ftell(nand->file);
    rewind(nand->file);
    wordsread = fread(instr_boot, sizeof(uint32_t), len / 4, nand->file);
#if 0    
    if(wordsread != NAND_BOOT_LOAD_SIZE){
        ASSERT(!"Couldn't read the whole bootloader");
        return -1;
    }
#endif
    return 0;    
}

void DestroyNAND(ARM_NAND* nand)
{
    fclose(nand->file);
    return;
}
