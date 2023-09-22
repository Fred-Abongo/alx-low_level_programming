#include "main.h"

/**
 * print_alphabet_x10 - Prints the lowercase alphabet 10 times, each followed by a newline.
 *
 * Description: This function prints the lowercase alphabet from 'a' to 'z' ten times,
 * with each set of alphabets followed by a newline character.
 */
void print_alphabet_x10(void)
{
	char ch;
	int i;

	i = 0;

	while (i < 10)
	{
		ch = 'a';
		while (ch <= 'z')
		{
			_putchar(ch);
			ch++;
		}
		_putchar('\n');
		i++;
	}
}
