#include "elf.h"
#include "elf_parser.h"
#include "elf_macros.h"
#include "elf_utils.h"

void usage(char* prog){
    printf("[*] Usage: %s <elf_file>\n", prog);
    exit(EXIT_FAILURE);
}

void fatal(char* msg){
    puts(msg);
    exit(EXIT_FAILURE);
}

int check_magic(unsigned char* ident){
    int check = strncmp((char *)ident + 1, "ELF", 3);
    return (ident[0] == 0x7f && check == 0)? 1 : 0;
}

void space(int count){
    for(int i=0; i < count; i++)
        printf(" ");
}
