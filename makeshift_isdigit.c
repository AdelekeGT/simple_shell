#include "shell.h"

/**
 * makeshift_isdigit - custom is_digit function
 * @the_char: the character to be checked
 *
 * Return: 1 on success; 0 otherwise
 */
int makeshift_isdigit(const char *the_char)
{
	unsigned int _idx;

	for (_idx = 0; the_char[_idx]; _idx++)
	{
		if (the_char[_idx] < 48 || the_char[_idx] > 57)
			return (0);
	}
	return (1);
}
