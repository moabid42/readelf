#include "elf.h"
#include "elf_parser.h"
#include "elf_macros.h"
#include "elf_utils.h"

//////////////
char* elf_get_magic_letter(struct elf_file *elf) {
	return ((char *)elf->ident + 1);
}

int	elf_get_magic_number(struct elf_file *elf) {
	return (elf->ident[0]);
}


//////////////
bool	elf_file_magic_check(struct elf_file *elf) {
	char* 			magic_letter = elf_get_magic_letter(elf);
	unsigned char	magic_number = elf_get_magic_number(elf);
	int				check = strncmp(magic_letter, "ELF", 3);
	
	return (magic_number == 0x7f && check == 0) ? 1 : 0;
}