#include "elf.h"
#include "elf_parser.h"
#include "elf_macros.h"
#include "elf_utils.h"

/*
 * This fucntion returns the corresponding data encoding
 * string of the variable data
 */
char* get_hdata(unsigned char data){
    switch(data){
        case ELFDATA2_LSB:
            return "Two's complement, little-endian";
        case ELFDATA2_MSB:
            return "Two's complement, big-endian";
  
        default :
            return "Unknown data format";
    }
}

/*
 * This function returns the corresponding version string 
 * of the variable version
 */
char* get_hversion(unsigned char version){
    switch(version){
        case 1:
            return "Current version";
        default :
            return "Invalid version";
    }
}

/*
 * This function returns the corresponding os and abi
 * string of the variable osabi
 */
char* get_hosabi(unsigned char osabi){
    switch(osabi){
        case ELFOSABI_SYSV:
            return "UNIX System V ABI";
        case ELFOSABI_HPUX:
            return "HP-UX ABI";
        case ELFOSABI_NETBSD:
            return "NETBSD ABI";
        case ELFOSABI_LINUX:
            return "Linux ABI";
        case ELFOSABI_SOLARIS:
            return "Solaris ABI";
        case ELFOSABI_IRIX:
            return "IRIX ABI";   
        case ELFOSABI_FREEBSD:
            return "FreeBSD ABI";
        case ELFOSABI_TRU64:
            return "TRU64 UNIX ABI";
        case ELFOSABI_ARM:
            return "ARM architecture ABI";
        case ELFOSABI_STANDALONE:
            return "Stand-alone (embedded) ABI";
  
        default :
            return "Unknown";
    }
}

/*
 * This function returns the corresponding elf file
 * type string of the variable type
 */
char* get_htype(unsigned short type){
    switch(type){
        case ET_REL:
            return "Relocatable";
        case ET_EXEC:
            return "Executable";
        case ET_DYN:
            return "Shared object";
        case ET_CORE:
            return "Core";
        default:
            return "Unknown";
    }
}

/*
 * This function returns the corresponding machine
 * string of the variable machine
 */
char* get_hmachine(unsigned short machine){
    switch(machine){
        case EM_M32:
            return "AT&T WE 32100";
        case EM_SPARC:
            return "Sun Microsystems SPARC";
        case EM_386:
            return "Intel 80386";
        case EM_68K:
            return "Motorola 68000";
        case EM_88K:
            return "Motorola 88000";
        case EM_860:
            return "Intel 80860";
        case EM_MIPS:
            return "MIPS RS3000 (big-endian only)";
        case EM_PARISC:
            return "HP/PA";
        case EM_SPARC32PLUS:
            return "SPARC with enhanced instruction set";
        case EM_PPC:
            return "PowerPC";
        case EM_PPC64:
            return "PowerPC 64-bit";
        case EM_S390:
            return "IBM S/390";
        case EM_ARM:
            return "Advanced RISC Machines";
        case EM_SH:
            return "Renesas SuperH";
        case EM_SPARCV9:
            return "SPARC v9 64-bit";
        case EM_IA_64:
            return "Intel Itanium";
        case EM_X86_64:
            return "AMD x86-64";
        case EM_VAX:
            return "DEC Vax";
        
        default:
            return "Unknown";
    }
}

/*
 * This function returns the corresponding program header
 * type string of the variable type
 */ 
char* get_phtype(unsigned int type){
    switch(type){
        case PT_NULL:
            return "NULL";
        case PT_LOAD:
            return "LOAD";
        case PT_DYNAMIC:
            return "DYNAMIC";
        case PT_INTERP:
            return "INTERP";
        case PT_NOTE:
            return "NOTE";
        case PT_SHLIB:
            return "SHLIB";
        case PT_PHDR:
            return "PHDR";
        case PT_TLS:
            return "TLS";
        case PT_LOPROC:
            return "LOPROC";
        case PT_HIPROC:
            return "HIPROC";
        case PT_GNU_STACK:
            return "GNU_STACK";
        default:
            return "UNKNWON";
    }
}

/*
 * This function returns the corresponding program header
 * flags string of the variable flags
 */
char* get_phflags(unsigned int flags){
    char* perm = malloc(4);
    perm[3] = '\0';
    
    if(flags & PF_R)
        perm[0] = 'r';
    else
        perm[0] = '-';
        
    if(flags & PF_W)
        perm[1] = 'w';
    else
        perm[1] = '-';
    
    if(flags & PF_X)
        perm[2] = 'x';
    else
        perm[2] = '-';
        
    return perm;
}

/*
 * This function returns the corresponding section header
 * type string of the variable type
 */
char* get_shtype(unsigned int type){
    switch(type){
        case SHT_NULL:
            return "NULL";
        case SHT_PROGBITS:
            return "PROGBITS";
        case SHT_SYMTAB:
            return "SYMTAB";
        case SHT_STRTAB:
            return "STRTAB";
        case SHT_RELA:
            return "RELA";
        case SHT_HASH:
            return "HASH";
        case SHT_DYNAMIC:
            return "DYNAMIC";
        case SHT_NOTE:
            return "NOTE";
        case SHT_NOBITS:
            return "NOBITS";
        case SHT_REL:
            return "REL";
        case SHT_SHLIB:
            return "SHLIB";
        case SHT_DYNSYM:
            return "DYNSYM";
        case SHT_LOPROC:
            return "LOPROC";
        case SHT_HIPROC:
            return "HIPROC";
        case SHT_LOUSER:
            return "LOUSER";
        case SHT_HIUSER:
            return "HIUSER";
        
        default:
            return "UNKNOWN";
    }
}

/*
 * This function returns the corresponding program header
 * flags string of the variable flags
 */
char* get_shflags(unsigned int flags){
    char* perm = malloc(4);
    perm[3] = '\0';
    
    if(flags & SHF_ALLOC)
        perm[0] = 'A';
    else
        perm[0] = ' ';
        
    if(flags & SHF_WRITE)
        perm[1] = 'W';
    else
        perm[1] = ' ';
    
    if(flags & SHF_EXECINSTR)
        perm[2] = 'X';
    else
        perm[2] = ' ';
        
    return perm;    
}
