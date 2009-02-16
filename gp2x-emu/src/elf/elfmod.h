
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
