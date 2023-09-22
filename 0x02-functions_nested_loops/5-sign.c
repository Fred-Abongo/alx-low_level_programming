#include "main.h"

/**
 * print_sign - Prints the sign of an integer.
 * @n: The integer to check.
 *
 * Description: This function checks the sign of the input integer 'n' and
 * prints the appropriate sign character and returns the corresponding value.
 *
 * Return:
 *  1 and prints '+' if 'n' is greater than zero.
 *  0 and prints '0' if 'n' is zero.
 * -1 and prints '-' if 'n' is less than zero.
 */
int print_sign(int n)
{
	if (n > 0)
	{
		_putchar('+');
		return (1);
	}
	else if (n == 0)
	{
		_putchar('0');
		return (0);
	}
	else if (n < 0)
	{
		_putchar('-');
	}
	return (-1);
}
