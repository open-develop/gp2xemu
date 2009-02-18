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

#include "elfmod.h"

Elf32_Phdr* Elf32_ReadProgramHeader(FILE* f, Elf32_Ehdr* ehdr)
{
    Elf32_Phdr* phdr;
    int ret;
    ASSERT(sizeof(Elf32_Phdr) == ehdr->e_phentsize);

    if(!ehdr->e_phnum)
        return NULL;

    phdr = malloc( sizeof(Elf32_Phdr) * ehdr->e_phnum );
    if(!phdr)
        return NULL;
    fseek(f, ehdr->e_phoff, SEEK_SET);
    ret = fread(phdr, sizeof(Elf32_Phdr), ehdr->e_phnum, f);
    if(ret != ehdr->e_phnum){
        #ifdef DEBUG
        printf("Warning. ELF Header inconsistent with actual number of program headers.\n");
        #endif
        free(phdr);
        return NULL;
    }
    return phdr;
}

void Elf32_FreeProgramHeader(Elf32_Phdr* phdr)
{
    if(phdr)
        free(phdr);
    return;
}

int Elf32_PrintProgramHeader(Elf32_Phdr* phdr)
{
    if(!phdr)
        return -1;
    printf("Segment type: ");
    switch(phdr->p_type)
    {
        case PT_NULL:
            printf("PT_NULL\n");
            break;
        case PT_LOAD:
            printf("PT_LOAD\n");
            break;
        case PT_DYNAMIC:
            printf("PT_DYNAMIC\n");
            break;
        case PT_INTERP:
            printf("PT_INTERP\n");
            break;
        case PT_NOTE:
            printf("PT_NOTE\n");
            break;
        case PT_SHLIB:
            printf("PT_SHLIB\n");
            break;
        case PT_PHDR:
            printf("PT_PHDR\n");
            break;
        default:
            printf("INVALID OR UNKNOWN\n");
            break;
    }
    printf("File offset: %X\n", phdr->p_offset);
    printf("Virtual address: %X\n", phdr->p_vaddr);
    printf("Physical address: %X\n", phdr->p_paddr);
    printf("File size: %d\n", phdr->p_filesz);
    printf("Memory size: %d\n", phdr->p_memsz);
    printf("Flags: ");
    if(phdr->p_flags & PF_X)
        printf("X");
    else
        printf(" ");
    if(phdr->p_flags & PF_R)
        printf("R");
    else
        printf(" ");
    if(phdr->p_flags & PF_W)
        printf("W");
    else
        printf(" ");
    printf("\n");
    printf("Segment alignment (in bytes): %d\n", phdr->p_align);
    return 0;
}
