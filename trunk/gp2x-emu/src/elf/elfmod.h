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

#ifndef ELFMOD_H
#define ELFMOD_H

#include <elf.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef DEBUG
#include <assert.h>
#define ASSERT(x) assert(x)
#else
#define ASSERT(x)
#endif

typedef struct Elf32_File
{
    Elf32_Ehdr header;
    Elf32_Phdr *phdr;
    Elf32_Shdr *shdr;
} Elf32_File;

Elf32_Ehdr* Elf32_ReadHeader(FILE*);
Elf32_Phdr* Elf32_ReadProgramHeader(FILE*, Elf32_Ehdr*);
Elf32_Shdr* Elf32_ReadSectionHeader(FILE*, Elf32_Ehdr*);

void Elf32_FreeHeader(Elf32_Ehdr*);
void Elf32_FreeProgramHeader(Elf32_Phdr*);
void Elf32_FreeSectionHeader(Elf32_Shdr*);

int Elf32_PrintHeader(Elf32_Ehdr*);
int Elf32_PrintProgramHeader(Elf32_Phdr*);
int Elf32_PrintSectionHeader(Elf32_Shdr*, const char*);

#endif
