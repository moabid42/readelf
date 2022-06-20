#ifndef ELF_PARSER
#define ELF_PARSER

#include "elf.h"
#include "elf_macros.h"
#include "elf_utils.h"

struct	elf_file {
	int 			fd;
	unsigned char	ident[EI_NIDENT];
};

///////////////////////////////
//      Program Header       //
///////////////////////////////

struct elf_pheader_32 {
    Word       p_type;
    Elf32_Off  p_offset;
    Elf32_Addr p_vaddr;
    Elf32_Addr p_paddr;
    Word       p_filesz;
    Word       p_memsz;
    Word       p_flags;
    Word       p_align;
};

struct elf_pheader_64 {
    Word       p_type;
    Word       p_flags;
    Elf64_Off  p_offset;
    Elf64_Addr p_vaddr;
    Elf64_Addr p_paddr;
    uint64_t   p_filesz;
    uint64_t   p_memsz;
    uint64_t   p_align;
};

///////////////////////////////
//    Section Header table   //
///////////////////////////////

struct elf_sheader_32 {
    Word       sh_name;
    Word       sh_type;
    Word       sh_flags;
    Elf32_Addr sh_addr; //if exist it means the first byte which should reside
    Elf32_Off  sh_offset;
    Word       sh_size;
    Word       sh_link;
    Word       sh_info;
    Word       sh_addralign;
    Word       sh_entsize;
};

struct elf_sheader_64 {
    Word       sh_name;
    Word       sh_type;
    uint64_t   sh_flags;
    Elf64_Addr sh_addr;
    Elf64_Off  sh_offset;
    uint64_t   sh_size;
    Word       sh_link;
    Word       sh_info;
    uint64_t   sh_addralign;
    uint64_t   sh_entsize;
};

///////////////////////////////
// Strings and symblos table //
///////////////////////////////

struct elf_sym_table_32 {
    Word          st_name;
    Elf32_Addr    st_value;
    Word          st_size;
    unsigned char st_info;
    unsigned char st_other;
    HalfWord      st_shndx;
};

struct elf_sym_table_64 {
    Word          st_name;
    unsigned char st_info;
    unsigned char st_other;
    HalfWord      st_shndx;
    Elf64_Addr    st_value;
    uint64_t      st_size;
};

///////////////////////////////
//        Elf Header         //
///////////////////////////////

struct elf_header_64{
    unsigned char   e_ident[EI_NIDENT];
    HalfWord        e_type;
    HalfWord        e_machine;
    Word            e_version;
    Elf64_Addr      e_entry; //entry address for executable
    Elf64_Off       e_phoff; //program header offset
	Elf64_Off       e_shoff; //section headers offset
	Word			e_flags; //flags for all file(heavily architecture and OS depent)
	HalfWord		e_ehsize;
	HalfWord		e_phentsize;
	HalfWord		e_phnum;
	HalfWord		e_shentsize;
	HalfWord		e_shnum;
	HalfWord		e_shstrndx;
};

struct elf_header_32{
    unsigned char   e_ident[EI_NIDENT];
    HalfWord        e_type;
    HalfWord        e_machine;
    Word            e_version;
    Elf32_Addr      e_entry; //entry address for executable
    Elf32_Off       e_phoff; //program header offset
	Elf32_Off       e_shoff; //section headers offset
	Word			e_flags; //flags for all file(heavily architecture and OS depent)
	HalfWord		e_ehsize;
	HalfWord		e_phentsize;
	HalfWord		e_phnum;
	HalfWord		e_shentsize;
	HalfWord		e_shnum;
	HalfWord		e_shstrndx;
};

/*
 * Getters
 */

//Symbol table
char* get_symtype32(unsigned char info);
char* get_symtype64(unsigned char info);
char* get_symbind32(unsigned char info);
char* get_symbind64(unsigned char info);
char* get_symvis32(unsigned char other);
char* get_symvis64(unsigned char other);

//Elf32 functions
void parse_elf32(struct elf_header_32 hdr, struct elf_file *elf);
void print_ehdr32(struct elf_header_32 hdr);
void print_ephtbl32(struct elf_header_32 hdr);
void print_eshtbl32(struct elf_header_32 hdr);
void print_esymtbl32(struct elf_sheader_32* shdr, char* name);
void print_ephdr32(struct elf_pheader_32* phdr);
void print_eshdr32(struct elf_sheader_32* shdr, int index);
void print_esym32(struct elf_sym_table_32* sym, int index, char* name);


//Elf64 functions
void parse_elf64(struct elf_header_64 hdr, struct elf_file *elf);
void print_ehdr64(struct elf_header_64 hdr);
void print_ephtbl64(struct elf_header_64 hdr);
void print_eshtbl64(struct elf_header_64 hdr);
void print_esymtbl64(struct elf_sheader_64* shdr, char* name);
void print_ephdr64(struct elf_pheader_64* phdr);
void print_eshdr64(struct elf_sheader_64* shdr, int index);
void print_esym64(struct elf_sym_table_64* sym, int index, char* name);



#endif
