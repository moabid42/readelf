#include "elf.h"
#include "elf_parser.h"
#include "elf_macros.h"
#include "elf_utils.h"

struct elf_sheader_32* SYMTAB32; // the symbol table for ELF32
struct elf_sheader_32* DYNSYM32; // the dynamic symbol table for ELF32
char* add_ELF; // addr of the content of the ELF
char* SHSTRTAB; // addr of the section header string table
char* STRTAB; // addr of the string table
char* DYNSTR; //addr of the dynamic string table


/*
 * This function returns the corresponding symbol table
 * index type string of the variable info
 * for a 32 bits ELF
 */
char* get_symtype32(unsigned char info){
    switch(ELF32_ST_TYPE(info)){
        case STT_NOTYPE:
            return "NOTYPE";
        case STT_OBJECT:
            return "OBJECT";
        case STT_FUNC:
            return "FUNCTION";
        case STT_SECTION:
            return "SECTION";
        case STT_FILE:
            return "FILE";
        case STT_LOPROC:
            return "LOPROC";
        case STT_HIPROC:
            return "HIPROC";
            
        default:
            return "UNKNOWN";        
    }
}

/*
 * This function returns the corresponding symbol table
 * index binding string of the variable info
 * for a 32 bits ELF
 */
char* get_symbind32(unsigned char info){
    switch(ELF32_ST_BIND(info)){
        case STB_LOCAL:
            return "LOCAL";
        case STB_GLOBAL:
            return "GLOBAL";
        case STB_WEAK:
            return "WEAK";
        case STB_LOPROC:
            return "LOPROC";
        case STB_HIPROC:
            return "HIPROC";
            
        default :
            return "UNKNOWN";
    }
}

/*
 * This function returns the corresponding symbol table
 * index visibilty string of the variable other
 * for a 32 bits ELF
 */
char* get_symvis32(unsigned char other){
    switch(ELF32_ST_VISIBILITY(other)){
        case STV_DEFAULT:
            return "DEFAULT";
        case STV_INTERNAL:
            return "INTERNAL";
        case STV_HIDDEN:
            return "HIDDEN";
        case STV_PROTECTED:
            return "PROTECTED";
            
        default :
            return "UNKNOWN";
    }
}

/*
 * This function prints all inforamtion contained
 * on an Elf32 header
 */
void print_ehdr32(struct elf_header_32 hdr){
    puts("");
    puts("===============ELF32 header===============");
    puts("");
    printf("Magic number : "); 
    for(int i=0; i < 4; i++)
        printf("0x%02x ", hdr.e_ident[i]);
    puts("");
    printf("Data : %s (0x%x)\n", get_hdata(hdr.e_ident[5]), hdr.e_ident[5]);
    printf("Version : %s (0x%x)\n", get_hversion(hdr.e_ident[6]), hdr.e_ident[6]);
    printf("OS&ABI : %s (0x%x)\n", get_hosabi(hdr.e_ident[7]), hdr.e_ident[7]);
    printf("ABI version : 0x%x\n", hdr.e_ident[8]);
    printf("Type : %s (0x%x)\n", get_htype(hdr.e_type), hdr.e_type);
    printf("Machine : %s (0x%x)\n", get_hmachine(hdr.e_machine), hdr.e_machine);
    printf("Version : 0x%x\n", hdr.e_version);
    printf("Entry point : 0x%lx\n", hdr.e_entry);
    printf("Program header offset : 0x%lx\n", hdr.e_phoff);
    printf("Section header offset : 0x%lx\n", hdr.e_shoff);
    printf("Flags : 0x%x\n", hdr.e_flags);
    printf("ELF header size : %d bytes\n", hdr.e_ehsize);
    printf("Program header entry size : %d bytes\n", hdr.e_phentsize);
    printf("Program header entry count : %d\n", hdr.e_phnum);
    printf("Section header entry size : %d bytes\n", hdr.e_shentsize);
    printf("Section header entry count : %d\n", hdr.e_shnum);
    printf("Section header string index : %d\n", hdr.e_shstrndx);
    puts("");
    puts("===================EOH===================");
}

/*
 * This is the main function that will map the  
 * ELF32 into memory, parse it and print each  
 * component of it
 */
void parse_elf32(struct elf_header_32 hdr, struct elf_file *elf) {
    
    struct stat elf_stat;
    
    if(fstat(elf->fd, &elf_stat) < 0)
        fatal("[-] Can't get the file size");
    add_ELF = mmap(NULL, elf_stat.st_size, PROT_READ, MAP_PRIVATE, elf->fd, 0);
    if(add_ELF == MAP_FAILED)
        fatal("[-] Can't allocate memory for the file");
    
    print_ehdr32(hdr);
    
    if(hdr.e_phoff)
        print_ephtbl32(hdr);
    if(hdr.e_shoff)
        print_eshtbl32(hdr);
    
    print_esymtbl32(SYMTAB32, ".symtab");
    print_esymtbl32(DYNSYM32, ".dynsym");
}

/*
 * This function prints all information contained
 * on an Elf32 program header table
 */
void print_ephtbl32(struct elf_header_32 hdr){
    //Get the program header table
    struct elf_pheader_32* phdr = (struct elf_pheader_32*) &add_ELF[hdr.e_phoff];
    
    puts("");
    puts("==========================================Program header table==========================================");
    printf("offset in file : 0x%lx\n", hdr.e_phoff);
    printf("Number of entry : %d\n", hdr.e_phnum);
    puts("");
    //title of the table
    printf("Type");
    space(10);
    printf("Offset");
    space(5);
    printf("File size");
    space(2);
    printf("Mem size");
    space(3);
    printf("Virt addr");
    space(2);
    printf("Phys addr");
    space(2);
    printf("Align");
    space(6);
    printf("Flags\n");
    
    //print each phdr
    for(int i=0; i < hdr.e_phnum; i++){
        print_ephdr32(&phdr[i]);
    }
    
    puts("");
    puts("===================================================EOPHT===================================================");
    puts("");
    
}

/*
 * This function prints all information contained
 * on Elf32 section header table
 */
void print_eshtbl32(struct elf_header_32 hdr){
    //Get the section header table
    struct elf_sheader_32* shdr = (struct elf_sheader_32*) &add_ELF[hdr.e_shoff];
    
    puts("");
    puts("===========================================Section header table===========================================");
    printf("offset in file : 0x%lx\n", hdr.e_shoff);
    printf("Number of entry : %d\n", hdr.e_shnum);
    puts("");
    //title of the table
    space(6);
    printf("Name");
    space(16);
    printf("Type");
    space(10);
    printf("Address");
    space(4);
    printf("Offset");
    space(5);
    printf("Size");
    space(7);
    printf("Entry Size");
    space(1);
    printf("Align");
    space(6);
    printf("Flags  ");
    printf("Link   ");
    printf("Info\n");
    
    //Get the section header string table
    SHSTRTAB = &add_ELF[shdr[hdr.e_shstrndx].sh_offset];
    
    //print each shdr
    for(int i=0; i < hdr.e_shnum; i++){
        print_eshdr32(&shdr[i], i);
    }
    
    puts("");
    puts("===================================================EOSHT===================================================");
    puts("");
    
}

/*
 * This function prints all information contained
 * on an Elf32 symbol table
 */
void print_esymtbl32(struct elf_sheader_32* shdr, char* name){
    
    if(!shdr){
        puts("");
        printf("[*] There is no %s section\n", name);
        return ;
    }

    //Get the symbol table
    struct elf_sym_table_32* sym = (struct elf_sym_table_32*) &add_ELF[shdr->sh_offset];
    
    puts("");
    printf("==========================================%s table===========================================\n", name);
    printf("offset in file : 0x%lx\n", shdr->sh_offset);
    printf("Number of entry : %d\n", shdr->sh_size / shdr->sh_entsize);
    puts("");
    //title of the table
    space(6);
    printf("Value");
    space(6);
    printf("Size ");   
    printf("Type");
    space(5);
    printf("Bind");
    space(3);
    printf("Visibility ");
    printf("Index ");
    printf("Name");
    puts("");
    
    //print each shdr
    for(uint64_t i=0; i < shdr->sh_size / shdr->sh_entsize; i++){
        print_esym32(&sym[i], i, name);
    }
    
    puts("");
    puts("===============================================EOST===============================================");
    puts("");
    
}

/*
 * This function prints a 32 bits program header
 */
void print_ephdr32(struct elf_pheader_32* phdr){
    int printed;
    puts("");
    printed = printf("%s", get_phtype(phdr->p_type));
    space(14 - printed);
    printf("0x%08lx ", phdr->p_offset);
    printf("0x%08x ", phdr->p_filesz);
    printf("0x%08x ", phdr->p_memsz);
    printf("0x%08lx ", phdr->p_vaddr);
    printf("0x%08lx ", phdr->p_paddr);
    printf("0x%08x ", phdr->p_align);
    printf("%s", get_phflags(phdr->p_flags));
    puts("");
}

/*
 * This function prints a 32 bits section header
 */
void print_eshdr32(struct elf_sheader_32* shdr, int index){
    int printed;
    puts("");
    printf("[%03d] ", index);
    printed = printf("%s", &SHSTRTAB[shdr->sh_name]);
    space(20 - printed);
    printed = printf("%s", get_shtype(shdr->sh_type));
    space(14 - printed);
    printf("0x%08lx ", shdr->sh_addr);
    printf("0x%08lx ", shdr->sh_offset);
    printf("0x%08x ", shdr->sh_size);
    printf("0x%08x ", shdr->sh_entsize);
    printf("0x%08x ", shdr->sh_addralign);
    printf(" %s    ", get_shflags(shdr->sh_flags));
    printed = printf("0x%x ", shdr->sh_link);
    space(7 - printed);
    printf("0x%x ", shdr->sh_info);
    puts("");
    
    if(!strcmp(".symtab", &SHSTRTAB[shdr->sh_name]))
        SYMTAB32 = shdr;
    else if(!strcmp(".dynsym", &SHSTRTAB[shdr->sh_name]))
        DYNSYM32 = shdr;
    else if(!strcmp(".strtab", &SHSTRTAB[shdr->sh_name]))
        STRTAB = &add_ELF[shdr->sh_offset];
    else if(!strcmp(".dynstr", &SHSTRTAB[shdr->sh_name]))
        DYNSTR = &add_ELF[shdr->sh_offset];
            
}

void print_esym32(struct elf_sym_table_32* sym, int index, char* name){
    
    //set the apropriate string table
    char* strtab;
    if(!strcmp(".dynsym", name))
        strtab = DYNSTR;
    else
        strtab = STRTAB;
        
    int printed;
    puts("");
    printf("[%03d] ", index);
    printf("0x%08lx ", sym->st_value);
    printed = printf("%4d ", sym->st_size);
    printed = printf("%s", get_symtype64(sym->st_info));
    space(9 - printed);
    printed = printf("%s", get_symbind64(sym->st_info));
    space(7 - printed);
    printed = printf("%s", get_symvis64(sym->st_other));
    space(10 - printed);
    printed = printf("%6d ", sym->st_shndx);
    printf("%s", &strtab[sym->st_name]);    
    puts("");
   
}
