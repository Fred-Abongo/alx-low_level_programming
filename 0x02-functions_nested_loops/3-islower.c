#include "main.h"

/**
 * _islower - Checks if a character is lowercase.
 * @c: The character to be checked.
 *
 * Description: This function checks if the input character 'c' is a
 *              lowercase letter.
 *
 * Return: 1 if 'c' is a lowercase letter, otherwise 0.
 */
int _islower(int c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	else
		return (0);
}
