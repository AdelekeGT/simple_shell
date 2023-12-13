#include "shell.h"

/**
 * makeshift_strchr - locates a character in a string and
 * returns a pointer to it
 * @the_str: string to be checked
 * @the_char: character to be located
 * Return: pointer to the character
*/
char *makeshift_strchr(char *the_str, char the_char)
{
	int _i;

	if (the_str == NULL)
		return (NULL);

	for (_i = 0; the_str[_i] >= '\0'; _i++)
	{
		if (the_str[_i] == the_char)
		{
			return (the_str + _i);
		}
	}
	return ((char *)0);
}
