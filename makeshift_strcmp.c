#include "shell.h"

/**
 * makeshift_strcmp - custom strcmp function
 * @string_a: first strang
 * @string_b: second strang
 *
 * Return: 0 if strings are equal
 */
int makeshift_strcmp(char *string_a, char *string_b)
{
	while (*string_a && *string_b)
	{
		if (*string_a != *string_b)
			return (*string_a - *string_b);

		string_a++;
		string_b++;
	}

	if (*string_a == *string_b)
		return (0);

	else
		return (*string_a < *string_b ? -1 : 1);
}
