#include "elf.h"
#include "elf_parser.h"
#include "elf_macros.h"
#include "elf_utils.h"

int main(int argc, char* argv[]) {
	struct elf_file	elf;

	if (argc > 2 || argc == 1)
		usage(argv[0]);
	if (elf_file_create(&elf, argv[1])) {
		if (elf_file_magic_check(&elf)) {
			if (elf_file_version_64(&elf))
				elf_file_64_parse(&elf);
			else
				elf_file_32_parse(&elf);
		}
		elf_file_destroy(&elf);
	}
	return (0);
}
