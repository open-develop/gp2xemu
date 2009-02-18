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

Elf32_Ehdr* Elf32_ReadHeader(FILE* f)
{
    Elf32_Ehdr* header;
    int i;
    if( !(header = malloc(sizeof(Elf32_Ehdr))) )
        return NULL;
    rewind(f);
    i = fread(header, sizeof(Elf32_Ehdr), 1, f);
    if( !i || ferror(f) || feof(f) )
        return NULL;
    return header;
}

void Elf32_FreeHeader(Elf32_Ehdr* header)
{
    if(header)
        free(header);
    return;
}

int Elf32_PrintHeader(Elf32_Ehdr* header)
{
   if(!header)
       return -1;
    printf("Elf header magic: %c%c%c%c\n",header->e_ident[0], header->e_ident[1],
            header->e_ident[2], header->e_ident[3]);

    printf("Elf class: ");
    switch(header->e_ident[4])
    {
        case ELFCLASSNONE:
            printf("ELFCLASSNONE\n");
            break;
        case ELFCLASS32:
            printf("ELFCLASS32\n");
            break;
        case ELFCLASS64:
            printf("ELFCLASS64\n");
            break;
        default:
            printf("INVALID\n");
        break;
    }
    printf("Endianess: ");
    switch(header->e_ident[5])
    {
        case ELFDATANONE:
            printf("ELFDATANONE\n");
            break;
        case ELFDATA2LSB:
            printf("Two's complement, little-endian.\n");
            break;
        case ELFDATA2MSB:
            printf("Two's complement, big-endian.\n");
            break;
        default:
            printf("INVALID\n");
            break;
    }
    printf("Version: ");
    switch(header->e_ident[6])
    {
        case EV_NONE:
            printf("EV_NONE\n");
            break;
        case EV_CURRENT:
            printf("EV_CURRENT\n");
            break;
        default:
            printf("INVALID\n");
            break;
    }
    printf("ABI target: ");
    switch(header->e_ident[7])
    {
        case ELFOSABI_NONE:
            printf("NONE\n");
            break;
        case ELFOSABI_LINUX:
            printf("Linux ABI\n");
            break;
        case ELFOSABI_SOLARIS:
            printf("Solaris ABI\n");
            break;
        case ELFOSABI_FREEBSD:
            printf("FreeBSD ABI\n");
            break;
        case ELFOSABI_ARM:
            printf("ARM EABI\n");
            break;
        case ELFOSABI_STANDALONE:
            printf("Stand-alone (embedded) ABI\n");
            break;
        default:
            printf("INVALID\n");
            break;
    }
    printf("ABI version: %d\n",header->e_ident[8]);
	printf("This ELF file is ");
	switch(header->e_type)
	{
		case ET_NONE:
			printf("an unknown type\n");
			break;
		case ET_REL:
			printf("a relocatable file\n");
			break;
		case ET_EXEC:
			printf("an executable\n");
			break;
		case ET_DYN:
			printf("a shared object\n");
			break;
		case ET_CORE:
			printf("a core file\n");
			break;
		default:
			printf("INVALID\n");
			break;
	}
	printf("Architecture: ");
	switch(header->e_machine)
	{
		case EM_NONE:
			printf("NONE\n");
			break;
		case EM_SPARC:
			printf("SPARC\n");
			break;
		case EM_386:
			printf("386\n");
			break;
		case EM_68K:
			printf("68K\n");
			break;
		case EM_MIPS:
			printf("MIPS\n");
			break;
		case EM_ARM:
			printf("ARM\n");
			break;
		case EM_X86_64:
			printf("IA-64\n");
			break;
		default:
			printf("INVALID\n");
			break;
	}
	printf("File version: ");
	switch(header->e_version)
	{
		case EV_NONE:
			printf("Invalid version\n");
			break;
		case EV_CURRENT:
			printf("Current version\n");
			break;
		default:
			printf("INVALID");
			break;
	}
	printf("Entrypoint VA: %X\n",header->e_entry);
	printf("Program header file offset: %X\n", header->e_phoff);
	printf("Section header file offset: %X\n", header->e_shoff);
	printf("CPU specific flags: %X\n", header->e_flags);
	printf("Program header entry size: %d\n", header->e_phentsize);
	printf("Program header count: %d\n", header->e_phnum);
	printf("Section header entry size: %d\n", header->e_shentsize);
	printf("Section header count: %d\n", header->e_shnum);
	printf("String table section header index: %d\n", header->e_shstrndx);
	return 0;
}
