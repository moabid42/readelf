#ifndef ELF_MACROS_H
# define ELF_MACROS_H

#include "elf_parser.h"
#include "elf.h"

#define TRUE    1
#define FALSE   0

#define EI_NIDENT   16

//version
#define VERSION_I   4

typedef uint16_t    HalfWord;
typedef uint32_t	Word    ;

//EI_CLASS
#define ELFCLASS32  1
#define ELFCLASS64  2

//EI_DATA(endieness)
#define ELFDATA2_LSB 1
#define ELFDATA2_MSB 2

//EI_OSABI
#define ELFOSABI_SYSV       0
#define ELFOSABI_HPUX       1
#define ELFOSABI_NETBSD     2
#define ELFOSABI_LINUX      3
#define ELFOSABI_SOLARIS    6
#define ELFOSABI_IRIX       8
#define ELFOSABI_FREEBSD    9
#define ELFOSABI_TRU64      10
#define ELFOSABI_ARM        97
#define ELFOSABI_STANDALONE 255

//EI_TYPE
#define ET_NONE 0
#define ET_REL  1
#define ET_EXEC 2
#define ET_DYN  3
#define ET_CORE 4

//E_MACHINE
#define EM_NONE     	0
#define EM_M32      	1
#define EM_SPARC    	2
#define EM_386      	3
#define EM_68K      	4
#define EM_88K      	5
#define EM_860      	6
#define EM_MIPS     	8
#define EM_PARISC   	15
#define EM_SPARC32PLUS	18
#define EM_PPC 	    	20
#define EM_PPC64     	21
#define EM_S390     	22
#define EM_ARM	     	40
#define EM_SH	     	42
#define EM_SPARCV9    	43
#define EM_IA_64     	50
#define EM_X86_64     	62
#define EM_VAX	     	75

//PT_TYPE
#define	PT_NULL         0
#define	PT_LOAD         1
#define PT_DYNAMIC      2
#define PT_INTERP       3
#define PT_NOTE         4
#define PT_SHLIB        5
#define PT_PHDR         6
#define PT_TLS          7
#define PT_LOPROC       0x70000000
#define PT_HIPROC       0x7fffffff
#define PT_GNU_STACK    0x6474e551

//P_FLAGS
#define PF_X    (1 << 0) // An executable segment
#define PF_W    (1 << 1) // A writable segment
#define PF_R    (1 << 2) // A readable segment


//SH_TYPE
#define SHT_NULL    0
#define SHT_PROGBITS 1
#define SHT_SYMTAB  2
#define SHT_STRTAB  3
#define SHT_RELA    4
#define SHT_HASH    5
#define SHT_DYNAMIC 6
#define SHT_NOTE    7
#define SHT_NOBITS  8
#define SHT_REL     9
#define SHT_SHLIB   10
#define SHT_DYNSYM  11
#define SHT_LOPROC  0x70000000
#define SHT_HIPROC  0x7fffffff
#define SHT_LOUSER  0x80000000
#define SHT_HIUSER  0x8fffffff

//SH_FLAGS
#define SHF_WRITE       0x1
#define SHF_ALLOC       0x2
#define SHF_EXECINSTR   0x4
#define SHF_MASKPROC    0xF0000000

//ST_INFO
#define STT_NOTYPE         0
#define STT_OBJECT         1
#define STT_FUNC           2
#define STT_SECTION        3
#define STT_FILE           4
#define STT_LOPROC         13
#define STT_HIPROC         15

#define STB_LOCAL           0
#define STB_GLOBAL          1
#define STB_WEAK            2
#define STB_LOPROC          13
#define STB_HIPROC          15


//Symbol visibility specification encoded in the st_other field.
#define STV_DEFAULT     0                /* Default symbol visibility rules */
#define STV_INTERNAL    1                /* Processor specific hidden class */
#define STV_HIDDEN      2                /* Sym unavailable in other modules */
#define STV_PROTECTED   3                /* Not preemptible, not exported */


/* How to extract and insert information held in the st_other field.  */
#define ELF32_ST_VISIBILITY(a)        ((a) & 0x03)
/* For ELF64 the definitions are the same.  */
#define ELF64_ST_VISIBILITY(a)        ELF32_ST_VISIBILITY(a)

/* How to extract and insert information held in the st_info field.  */
#define ELF32_ST_BIND(val)                (((unsigned char) (val)) >> 4)
#define ELF32_ST_TYPE(val)                ((val) & 0xf)

/* Both Elf32_Sym and Elf64_Sym use the same one-byte st_info field.  */
#define ELF64_ST_BIND(val)                ELF32_ST_BIND (val)
#define ELF64_ST_TYPE(val)                ELF32_ST_TYPE (val)

// #ifdef __linux__
// #  define SYSTEM_TARGET LINUX
#       define Elf64_Addr  uint64_t
#       define Elf64_Off   uint64_t
#       define Elf32_Addr  uint64_t
#       define Elf32_Off   uint64_t
// #endif

#endif