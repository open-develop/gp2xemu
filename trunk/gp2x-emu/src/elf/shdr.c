#include "elfmod.h"

Elf32_Shdr* Elf32_ReadSectionHeader(FILE* f, Elf32_Ehdr* ehdr)
{
    Elf32_Shdr* shdr;
    int ret;
    ASSERT(sizeof(Elf32_Shdr) == ehdr->e_shentsize);

    if(!ehdr->e_shnum)
        return NULL;

    shdr = malloc( sizeof(Elf32_Shdr) * ehdr->e_shnum );
    if(!shdr)
        return NULL;
    fseek(f, ehdr->e_shoff, SEEK_SET);
    ret = fread(shdr, sizeof(Elf32_Shdr), ehdr->e_shnum, f);
    if(ret != ehdr->e_shnum){
        #ifdef DEBUG
        printf("Warning. ELF Header inconsistent with actual number of section headers.\n");
        #endif
        free(shdr);
        return NULL;
    }
    return shdr;
}

void Elf32_FreeSectionHeader(Elf32_Shdr* shdr)
{
    if(shdr)
        free(shdr);
    return;
}

int Elf32_PrintSectionHeader(Elf32_Shdr* shdr, const char* str)
{

    const char* s = &str[shdr->sh_name];
    if(*s)
        printf("Name: %s\n",s);
    else
        printf("Name: \\0\n");

    printf("Type: ");
    switch(shdr->sh_type)
    {
        case SHT_NULL:
            printf("SHT_NULL\n");
            break;
        case SHT_PROGBITS:
            printf("SHT_PROGBITS\n");
            break;
        case SHT_SYMTAB:
            printf("SHT_SYMTAB\n");
            break;
        case SHT_STRTAB:
            printf("SHT_STRTAB\n");
            break;
        case SHT_RELA:
            printf("SHT_RELA\n");
            break;
        case SHT_HASH:
            printf("SHT_HASH\n");
            break;
        case SHT_DYNAMIC:
            printf("SHT_DYNAMIC\n");
            break;
        case SHT_NOTE:
            printf("SHT_NOTE\n");
            break;
        case SHT_NOBITS:
            printf("SHT_NOBITS\n");
            break;
        case SHT_REL:
            printf("SHT_REL\n");
            break;
        case SHT_SHLIB:
            printf("SHT_SHLIB\n");
            break;
        case SHT_DYNSYM:
            printf("SHT_DYNSYM\n");
            break;
        /*
        case SHT_LOPROC:
            break;
        case SHT_HIPROC:
            break;
        case SHT_LOUSER:
            break;
        case SHT_HIUSER:
            break;
        */
        default:
            printf("INVALID\n");
            break;
    }
    printf("Flags: ");
    if(shdr->sh_flags & SHF_WRITE)
        printf("SHF_WRITE, ");
    if(shdr->sh_flags & SHF_ALLOC)
        printf("SHF_ALLOC, ");
    if(shdr->sh_flags & SHF_EXECINSTR)
        printf("SHF_EXECINSTR");
    printf("\n");
    printf("Address: %X\n", shdr->sh_addr);
    printf("Offset: %X\n", shdr->sh_offset);
    printf("Size: %d\n", shdr->sh_size);
    printf("Link section header index: %d\n", shdr->sh_link);
    /* printf("Info: %d\n", shdr->sh_info); */
    printf("Address alignment: %X\n", shdr->sh_addralign);
    printf("Fixed size for entries (zero means no): %d\n", shdr->sh_entsize);
    return 0;
}



