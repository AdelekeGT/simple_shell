#include "shell.h"

/**
 * makeshift_strcat - concatenates /bin/ and any valid command passed in
 * @command: command to be added to /bin/
 * Return: pointer to new string
*/
char *makeshift_strcat(const char *command)
{
	char *path = "/bin/";
	char *concat_string;
	int _len = 0, _m, _n;

	if (command == NULL)
		return (NULL);

	while (command[_len])
		_len++;

	concat_string = malloc((_len + 6) * sizeof(char));
	if (!concat_string)
		return (NULL);

	_m = 0;
	while (path[_m] != '\0')
	{
		concat_string[_m] = path[_m];
		_m++;
	}

	_n = 0;
	while (command[_n] != '\0')
	{
		concat_string[_m] = command[_n];
		_m++;
		_n++;
	}
	concat_string[_m] = '\0';

	return (concat_string);
}
