#include "shell.h"

/**
 * makeshift_strcat - custom strcat function
 * @destination: original string to which another will be added
 * @source: the string to added to the destination
 *
 * Return: pointer to the modified destination
 */
char *makeshift_strcat(char *destination, const char *source)
{
	int i;
	int j;

	for (i = 0; destination[i] != '\0'; i++)
		;

	for (j = 0; source[j] != '\0'; j++)
	{
		destination[i] = source[j];
		i++;
	}

	destination[i] = '\0';
	return (destination);
}
