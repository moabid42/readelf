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

// ELF version
enum	elf_version {
	ELF_VERSION_32 = 1,
	ELF_VERSION_64 = 2
};


//EI_DATA(endieness)
enum endieness {
	ELFDATA2_LSB = 1,
	ELFDATA2_MSB = 2
};


//EI_OSABI

enum OS_ABI {
	ELFOSABI_SYSV    =   0,
	ELFOSABI_HPUX    =   1,
	ELFOSABI_NETBSD  =   2,
	ELFOSABI_LINUX   =   3,
	ELFOSABI_SOLARIS =   6,
	ELFOSABI_IRIX    =   8,
	ELFOSABI_FREEBSD =   9,
	ELFOSABI_TRU64   =   10,
	ELFOSABI_ARM     =   97,
	ELFOSABI_STANDALONE = 255

};

//EI_TYPE
enum EI_type {
	ET_NONE = 0,
	ET_REL  = 1,
	ET_EXEC = 2,
	ET_DYN  = 3,
	ET_CORE = 4
};

//E_MACHINE
enum	e_machine {
	EM_NONE     	= 0,
	EM_M32      	= 1,
	EM_SPARC    	= 2,
	EM_386      	= 3,
	EM_68K      	= 4,
	EM_88K      	= 5,
	EM_860      	= 6,
	EM_MIPS     	= 8,
	EM_PARISC   	= 15,
	EM_SPARC32PLUS	= 18,
	EM_PPC 	    	= 20,
	EM_PPC64     	= 21,
	EM_S390     	= 22,
	EM_ARM	     	= 40,
	EM_SH	     	= 42,
	EM_SPARCV9    	= 43,
	EM_IA_64     	= 50,
	EM_X86_64     	= 62,
	EM_VAX	     	= 75
};

//PT_TYPE
enum	pt_type {
	PT_NULL         = 0,
	PT_LOAD         = 1,
	PT_DYNAMIC      = 2,
	PT_INTERP       = 3,
	PT_NOTE         = 4,
	PT_SHLIB        = 5,
	PT_PHDR         = 6,
	PT_TLS          = 7,
	PT_LOPROC       = 0x70000000,
	PT_HIPROC       = 0x7fffffff,
	PT_GNU_STACK    = 0x6474e551
};

//P_FLAGS
enum p_flags {
	PF_X    = (1 << 0), // An executable segment
	PF_W    = (1 << 1), // A writable segment
	PF_R    = (1 << 2) // A readable segment
};

//SH_TYPE
enum	sh_type {
	SHT_NULL     = 0,
	SHT_PROGBITS = 1,
	SHT_SYMTAB   = 2,
	SHT_STRTAB   = 3,
	SHT_RELA     = 4,
	SHT_HASH     = 5,
	SHT_DYNAMIC  = 6,
	SHT_NOTE     = 7,
	SHT_NOBITS   = 8,
	SHT_REL      = 9,
	SHT_SHLIB    = 10,
	SHT_DYNSYM   = 11,
	SHT_LOPROC   = 0x70000000,
	SHT_HIPROC   = 0x7fffffff,
	SHT_LOUSER   = 0x80000000,
	SHT_HIUSER   = 0x8fffffff
};

//SH_FLAGS
enum sh_flags {
	SHF_WRITE      = 0x1,
	SHF_ALLOC      = 0x2,
	SHF_EXECINSTR  = 0x4,
	SHF_MASKPROC   = 0xF0000000
};
//ST_INFO
enum	stt_info {
	STT_NOTYPE       =  0,
	STT_OBJECT       =  1,
	STT_FUNC         =  2,
	STT_SECTION      =  3,
	STT_FILE         =  4,
	STT_LOPROC       =  13,
	STT_HIPROC       =  15
};

enum	stb_info {
	STB_LOCAL     	=  0,
	STB_GLOBAL    	=  1,
	STB_WEAK      	=  2,
	STB_LOPROC    	=  13,
	STB_HIPROC    	=  15
};


//Symbol visibility specification encoded in the st_other field.
enum	svt {
STV_DEFAULT     = 0,                /* Default symbol visibility rules */
STV_INTERNAL    = 1,                /* Processor specific hidden class */
STV_HIDDEN      = 2,                /* Sym unavailable in other modules */
STV_PROTECTED   = 3                /* Not preemptible, not exported */
};

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

#       define Elf64_Addr  uint64_t
#       define Elf64_Off   uint64_t
#       define Elf32_Addr  uint64_t
#       define Elf32_Off   uint64_t

#endif