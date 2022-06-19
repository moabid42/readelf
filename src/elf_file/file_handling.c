#include "../../includes/elf.h"
#include "../../includes/elf_parser.h"
#include "../../includes/elf_macros.h"

//////////////
void	elf_header_64_read(struct elf_header_64 *ehdr64, struct elf_file *elf) {
	int bytes = read(elf->fd, (char*)ehdr64 + EI_NIDENT, sizeof(struct elf_header_64) - EI_NIDENT);
    if(!bytes) 
        fatal("[-] Unexpected EOF while parsing Elf32_header");
}

void	elf_header_32_read(struct elf_header_32 *ehdr32, struct elf_file *elf) {
	int bytes = read(elf->fd, (char*)ehdr32 + EI_NIDENT, sizeof(struct elf_header_32) - EI_NIDENT);
    if(!bytes)
        fatal("[-] Unexpected EOF while parsing Elf32_header");
}


/////////////
void	elf_header_init_64(struct elf_header_64 *ehdr64, struct elf_file *elf) {
	memcpy(ehdr64->e_ident, elf->ident, EI_NIDENT);
	elf_header_64_read(ehdr64, elf);
}

void	elf_header_init_32(struct elf_header_32 *ehdr32, struct elf_file *elf) {
	memcpy(ehdr32->e_ident, elf->ident, EI_NIDENT);
	elf_header_32_read(ehdr32, elf);
}