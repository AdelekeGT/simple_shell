#include "shell.h"

/**
 * makeshift_strcpy - custom strcpy function
 * @destination: the destination string that receives
 * @source: the source string that is copied into destination
 *
 * Return: pointer to the modified destination
 */
char *makeshift_strcpy(char *destination, char *source)
{
	size_t _ind;

	for (_ind = 0; source[_ind] != '\0'; _ind++)
	{
		destination[_ind] = source[_ind];
	}
	destination[_ind] = '\0';

	return (destination);
}
