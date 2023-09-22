#include "main.h"

/**
 * print_alphabet - Prints the lowercase alphabet from 'a' to 'z'.
 *
 * Description: This function prints all the lowercase letters of the
 * alphabet in ascending order, followed by a newline character.
 */
void print_alphabet(void)
{
	char letter;

	for (letter = 'a'; letter <= 'z'; letter++)
		_putchar(letter);

	_putchar('\n');
}
