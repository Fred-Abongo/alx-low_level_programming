#include "main.h"

/**
 * _isalpha - Checks for an alphabetic character.
 * @c: The character to be checked.
 *
 * Description: This function checks whether the input character 'c' is an
 * alphabetic character (a letter), whether lowercase or uppercase.
 *
 * Return: 1 if 'c' is a letter, 0 otherwise.
 */
int _isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}
