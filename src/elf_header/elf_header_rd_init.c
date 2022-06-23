#include "elf.h"
#include "elf_parser.h"
#include "elf_macros.h"
#include "elf_utils.h"

//////////////
void	elf_file_64_parse(struct elf_file *elf) {
	struct elf_header_64 ehdr64;

	elf_header_init_64(&ehdr64, elf);
	parse_elf64(ehdr64, elf);
}

void	elf_file_32_parse(struct elf_file *elf) {
	struct elf_header_32 ehdr32;

	elf_header_init_32(&ehdr32, elf);
	parse_elf32(ehdr32, elf);
}


//////////////
int	elf_file_check_version(struct elf_file *elf) {
	return (elf->ident[4]);
}

bool	elf_file_version_64(struct elf_file *elf) {
	int	version = elf_file_check_version(elf);
	if (version == ELF_VERSION_64)
		return (true);
	else if (version == ELF_VERSION_32)
		return (false);
	else
		fatal("[-] ELF version not recognized");
	return (false);
}

//////////////
int	elf_file_get_fd(struct elf_file *elf, char* file){
	int fd = open(file, O_RDONLY);
	return (fd);
}

void	elf_file_read_buffer(struct elf_file *elf) {
	int		bytes = read(elf->fd, elf->ident, EI_NIDENT);

	if (!bytes)
		fatal("[-] Unexpected EOF while parsing e_ident");
}


//////////////
bool	elf_file_create(struct elf_file *elf, char *file){
	
	elf->fd = elf_file_get_fd(elf, file);
	elf_file_read_buffer(elf);
	return (true);
}

void	elf_file_destroy(struct elf_file *elf) {
	close(elf->fd);
}