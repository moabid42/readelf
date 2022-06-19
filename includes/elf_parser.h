#ifndef ELF_PARSER
#define ELF_PARSER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include "elf_macros.h"
#include "elf.h"

struct	elf_file {
	int 			fd;
	unsigned char	ident[EI_NIDENT];
};

enum	elf_version {
	ELF_VERSION_32 = 1,
	ELF_VERSION_64 = 2
};


///////////////////////////////
//      Program Header       //
///////////////////////////////

typedef struct {
    Word       p_type;
    Elf32_Off  p_offset;
    Elf32_Addr p_vaddr;
    Elf32_Addr p_paddr;
    Word       p_filesz;
    Word       p_memsz;
    Word       p_flags;
    Word       p_align;
} Elf32_Phdr;

typedef struct {
    Word       p_type;
    Word       p_flags;
    Elf64_Off  p_offset;
    Elf64_Addr p_vaddr;
    Elf64_Addr p_paddr;
    uint64_t   p_filesz;
    uint64_t   p_memsz;
    uint64_t   p_align;
} Elf64_Phdr;

///////////////////////////////
//    Section Header table   //
///////////////////////////////

typedef struct {
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
} Elf32_Shdr;

typedef struct {
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
} Elf64_Shdr;

///////////////////////////////
// Strings and symblos table //
///////////////////////////////

typedef struct {
    Word          st_name;
    Elf32_Addr    st_value;
    Word          st_size;
    unsigned char st_info;
    unsigned char st_other;
    HalfWord      st_shndx;
} Elf32_Sym;

typedef struct {
    Word          st_name;
    unsigned char st_info;
    unsigned char st_other;
    HalfWord      st_shndx;
    Elf64_Addr    st_value;
    uint64_t      st_size;
} Elf64_Sym;

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

//Basic functions
void usage(char* prog);
void fatal(char* msg);
int check_magic(unsigned char* ident);
void space(int count);

//main functions
void	version_parser(unsigned char ident[], int elf);
void	magical_parser(int elf);
int	    open_file(int elf, char *file);
void    version_parsing(unsigned char ident[], int elf, int bytes);

/*
 * Getters
 */

//ELF header
char* get_hdata(unsigned char data);
char* get_hversion(unsigned char version);
char* get_hosabi(unsigned char osabi);
char* get_htype(unsigned short type);
char* get_hmachine(unsigned short machine);

//Program header
char* get_phtype(unsigned int type);
char* get_phflags(unsigned int flags);

//Section header
char* get_shtype(unsigned int type);
char* get_shflags(unsigned int flags);

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
void print_esymtbl32(Elf32_Shdr* shdr, char* name);
void print_ephdr32(Elf32_Phdr* phdr);
void print_eshdr32(Elf32_Shdr* shdr, int index);
void print_esym32(Elf32_Sym* sym, int index, char* name);


//Elf64 functions
void parse_elf64(struct elf_header_64 hdr, struct elf_file *elf);
void print_ehdr64(struct elf_header_64 hdr);
void print_ephtbl64(struct elf_header_64 hdr);
void print_eshtbl64(struct elf_header_64 hdr);
void print_esymtbl64(Elf64_Shdr* shdr, char* name);
void print_ephdr64(Elf64_Phdr* phdr);
void print_eshdr64(Elf64_Shdr* shdr, int index);
void print_esym64(Elf64_Sym* sym, int index, char* name);



#endif
