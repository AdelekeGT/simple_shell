#include "shell.h"

/**
 * makeshift_strlen - custom strlen function
 * @string: string whose length is to be counted
 *
 * Return: length of string
*/
int makeshift_strlen(const char *string)
{
	int counter_of_length = 0;

	if (string == NULL)
		return (0);

	while (*string != '\0')
	{
		string++;
		counter_of_length++;
	}

	return (counter_of_length);
}
