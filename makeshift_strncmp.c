#include "shell.h"

/**
 * makeshift_strncmp - compares two strings
 * @string_a: first string to be compared
 * @string_b: second string to be compared
 * @n_char: number of characters to be compared
 *
 * Return: 0 if strings are the same
 * if not, returns < 0 or > 0
*/
int makeshift_strncmp(const char *string_a,
const char *string_b, size_t n_char)
{
	size_t _g;

	if (string_a == NULL || string_b == NULL)
		return (-1);

	for (_g = 0; _g < n_char; _g++)
	{
		if (string_a[_g] != string_b[_g])
			return ((unsigned char)(string_a[_g]) - (unsigned char)(string_b[_g]));
			/*above condition, both chars are not equal*/
		else if (string_a[_g] == '\0')
			return (0);
			/*above condition, both strings are equal up to first n_char chars*/
	}
	return (0);
}
