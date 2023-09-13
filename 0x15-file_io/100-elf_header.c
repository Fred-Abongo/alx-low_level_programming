#include <elf.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void check_elf(unsigned char *e_ident);
void print_elf_info(Elf64_Ehdr *header);
void close_elf(int elf);

/**
 * check_elf - Checks if the file is an ELF file.
 * @e_ident: Pointer to an array containing the ELF magic numbers.
 *
 * Description: If the file is not an ELF file, exit with code 98.
 */
void check_elf(unsigned char *e_ident)
{
	int index;

	for (index = 0; index < 4; index++)
	{
		if (e_ident[index] != 127 &&
			e_ident[index] != 'E' &&
			e_ident[index] != 'L' &&
			e_ident[index] != 'F')
		{
			dprintf(STDERR_FILENO, "Error: Not an ELF file\n");
			exit(98);
		}
	}
}

/**
 * print_elf_info - Prints various information from the ELF header.
 * @header: Pointer to an ELF header structure.
 */
void print_elf_info(Elf64_Ehdr *header)
{
	int index; /* Declare index here */

	printf("ELF Header:\n");
	printf(" Magic: ");
	for (index = 0; index < EI_NIDENT; index++)
	{
		printf("%02x", header->e_ident[index]);

		if (index == EI_NIDENT - 1)
			printf("\n");
		else
			printf(" ");
	}

	printf(" Class: ");
	/* Print class information here... */

	printf(" Data: ");
	/* Print data information here... */

	printf(" Version: ");
	/* Print version information here... */

	printf(" OS/ABI: ");
	/* Print OS/ABI information here... */

	printf(" ABI Version: %d\n", header->e_ident[EI_ABIVERSION]);

	printf(" Type: ");
	/* Print type information here... */

	printf(" Entry point address: ");
	/* Print entry point information here... */
}

/**
 * close_elf - Closes the ELF file.
 * @elf: The file descriptor of an ELF file.
 *
 * Description: If the file cannot be closed, exit with code 98.
 */
void close_elf(int elf)
{
	if (close(elf) == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", elf);
		exit(98);
	}
}

/**
 * main - Displays information contained in the
 * ELF header at the start of an ELF file.
 * @argc: Number of arguments supplied to the program.
 * @argv: Array of pointers to the arguments.
 *
 * Return: 0 on success.
 *
 * Description: If the file is not an ELF File or
 * the function fails, exit with code 98.
 */
int main(int __attribute__((__unused__)) argc, char *argv[])
{
	Elf64_Ehdr *header;
	int o, r;

	o = open(argv[1], O_RDONLY);
	if (o == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't read file %s\n", argv[1]);
		exit(98);
	}
	header = malloc(sizeof(Elf64_Ehdr));
	if (header == NULL)
	{
		close_elf(o);
		dprintf(STDERR_FILENO, "Error: Can't read file %s\n", argv[1]);
		exit(98);
	}
	r = read(o, header, sizeof(Elf64_Ehdr));
	if (r == -1)
	{
		free(header);
		close_elf(o);
		dprintf(STDERR_FILENO, "Error: `%s`: No such file\n", argv[1]);
		exit(98);
	}

	check_elf(header->e_ident);
	print_elf_info(header);

	free(header);
	close_elf(o);
	return (0);
}
