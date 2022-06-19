#ifndef	ELF_H
# define ELF_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include "elf_parser.h"
#include "elf_macros.h"

void	elf_header_64_read(struct elf_header_64 *ehdr64, struct elf_file *elf);
void	elf_header_32_read(struct elf_header_32 *ehdr32, struct elf_file *elf);
void	elf_header_init_64(struct elf_header_64 *ehdr64, struct elf_file *elf);
void	elf_header_init_32(struct elf_header_32 *ehdr32, struct elf_file *elf);
void	elf_file_64_parse(struct elf_file *elf);
void	elf_file_32_parse(struct elf_file *elf);
int		elf_file_check_version(struct elf_file *elf);
bool	elf_file_version_64(struct elf_file *elf);

int		elf_file_get_fd(struct elf_file *elf, char* file);
void	elf_file_read_buffer(struct elf_file *elf);
bool	elf_file_create(struct elf_file *elf, char *file);
void	elf_file_destroy(struct elf_file *elf);
char* 	elf_get_magic_letter(struct elf_file *elf);
int		elf_get_magic_number(struct elf_file *elf);

bool	elf_file_magic_check(struct elf_file *elf);


#endif