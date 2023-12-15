#include "shell.h"

/**
 * makeshift_strdup - custom strdup function
 * @string: string to be duplicated
 *
 * Return: pointer to duplicate
 * malloc has to be used to allocate memory for duplicate
*/
char *makeshift_strdup(const char *string)
{
	char *dup_string;
	size_t length, _i = 0;

	if (string == NULL)
		return (NULL);

	length = makeshift_strlen(string);

	dup_string = malloc((length + 1) * sizeof(char));

	if (dup_string == NULL)
		return (NULL);

	while (string[_i] != '\0')
	{
		dup_string[_i] = string[_i];
		_i++;
	}

	dup_string[_i] = '\0';

	return (dup_string);

}
