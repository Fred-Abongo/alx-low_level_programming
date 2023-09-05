#include <elf.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * main - Displays the information contained in the
 *        ELF header at the start of an ELF file.
 * @argc: The number of arguments supplied to the program.
 * @argv: An array of pointers to the arguments.
 *
 * Return: 0 on success.
 *
 * Description: If the file is not an ELF File or
 *              the function fails - exit code 98.
 */
int main(int __attribute__((__unused__)) argc, char *argv[])
{
    int o, r;
    Elf64_Ehdr *header;

    o = open(argv[1], O_RDONLY);
    if (o == -1)
    {
        dprintf(STDERR_FILENO, "Error: Can't read file %s\n", argv[1]);
        exit(98);
    }

    header = malloc(sizeof(Elf64_Ehdr));
    if (header == NULL)
    {
        close(o);
        dprintf(STDERR_FILENO, "Error: Can't read file %s\n", argv[1]);
        exit(98);
    }

    r = read(o, header, sizeof(Elf64_Ehdr));
    if (r == -1)
    {
        free(header);
        close(o);
        dprintf(STDERR_FILENO, "Error: `%s`: No such file\n", argv[1]);
        exit(98);
    }

    if (header->e_ident[0] != 0x7f || header->e_ident[1] != 'E' || header->e_ident[2] != 'L' || header->e_ident[3] != 'F')
    {
        dprintf(STDERR_FILENO, "Error: Not an ELF file\n");
        exit(98);
    }

    printf("ELF Header:\n");
    printf("	Magic:   ");
    for (int index = 0; index < EI_NIDENT; index++)
    {
        printf("%02x", header->e_ident[index]);
        if (index == EI_NIDENT - 1)
            printf("\n");
        else
            printf(" ");
    }

    printf("	Class:                             ");
    switch (header->e_ident[EI_CLASS])
    {
    case ELFCLASSNONE:
        printf("none\n");
        break;
    case ELFCLASS32:
        printf("ELF32\n");
        break;
    case ELFCLASS64:
        printf("ELF64\n");
        break;
    default:
        printf("<unknown: %x>\n", header->e_ident[EI_CLASS]);
    }

    printf("	Data:                              ");
    switch (header->e_ident[EI_DATA])
    {
    case ELFDATANONE:
        printf("none\n");
        break;
    case ELFDATA2LSB:
        printf("2's complement, little endian\n");
        break;
    case ELFDATA2MSB:
        printf("2's complement, big endian\n");
        break;
    default:
        printf("<unknown: %x>\n", header->e_ident[EI_DATA]);
    }

    printf("	Version:                           %d", header->e_ident[EI_VERSION]);
    switch (header->e_ident[EI_VERSION])
    {
    case EV_CURRENT:
        printf(" (current)\n");
        break;
    default:
        printf("\n");
        break;
    }

    printf("	OS/ABI:                            ");
    switch (header->e_ident[EI_OSABI])
    {
    case ELFOSABI_NONE:
        printf("UNIX - System V\n");
        break;
    case ELFOSABI_HPUX:
        printf("UNIX - HP-UX\n");
        break;
    case ELFOSABI_NETBSD:
        printf("UNIX - NetBSD\n");
        break;
    case ELFOSABI_LINUX:
        printf("UNIX - Linux\n");
        break;
    case ELFOSABI_SOLARIS:
        printf("UNIX - Solaris\n");
        break;
    case ELFOSABI_IRIX:
        printf("UNIX - IRIX\n");
        break;
    case ELFOSABI_FREEBSD:
        printf("UNIX - FreeBSD\n");
        break;
    case ELFOSABI_TRU64:
        printf("UNIX - TRU64\n");
        break;
    case ELFOSABI_ARM:
        printf("ARM\n");
        break;
    case ELFOSABI_STANDALONE:
        printf("Standalone App\n");
        break;
    default:
        printf("<unknown: %x>\n", header->e_ident[EI_OSABI]);
    }

    printf("	ABI Version:                       %d\n", header->e_ident[EI_ABIVERSION]);

    if (header->e_ident[EI_DATA] == ELFDATA2MSB)
        header->e_type >>= 8;

    printf("	Type:                              ");
    switch (header->e_type)
    {
    case ET_NONE:
        printf("NONE (None)\n");
        break;
    case ET_REL:
        printf("REL (Relocatable file)\n");
        break;
    case ET_EXEC:
        printf("EXEC (Executable file)\n");
        break;
    case ET_DYN:
        printf("DYN (Shared object file)\n");
        break;
    case ET_CORE:
        printf("CORE (Core file)\n");
        break;
    default:
        printf("<unknown: %x>\n", header->e_type);
    }

    if (header->e_ident[EI_DATA] == ELFDATA2MSB)
    {
        header->e_entry = ((header->e_entry << 8) & 0xFF00FF00) |
                          ((header->e_entry >> 8) & 0xFF00FF);
        header->e_entry = (header->e_entry << 16) | (header->e_entry >> 16);
    }

    if (header->e_ident[EI_CLASS] == ELFCLASS32)
        printf("	Entry point address:               %#x\n", (unsigned int)header->e_entry);
    else
        printf("	Entry point address:               %#lx\n", header->e_entry);

    free(header);
    close(o);
    return (0);
}
