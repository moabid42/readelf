#ifndef	ELF_UTILS_H
# define	ELF_UTILS_H

#include "elf.h"
#include "elf_parser.h"
#include "elf_macros.h"

char* add_ELF; // addr of the content of the ELF
char* SHSTRTAB; // addr of the section header string table
char* STRTAB; // addr of the string table
char* DYNSTR; //addr of the dynamic string table

// General_utils
void usage(char* prog);
void fatal(char* msg);
int check_magic(unsigned char* ident);
void space(int count);

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

#endif