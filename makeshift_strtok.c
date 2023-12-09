#include "shell.h"

/**
 * makeshift_cmpchr - compares character
 * @the_str: the array of strings
 * @the_delim: ever-abiding delimiter
 *
 * Return: 0 on success; 1 otherwise
*/
int makeshift_cmpchr(char *the_str, const char *the_delim)
{
	unsigned int l, u, p;

	for (l = 0, p = 0; the_str[l]; l++)
	{
		for (u = 0; the_delim[u]; u++)
		{
			if (the_str[l] == the_delim[u])
			{
				p++;
				break;
			}
		}
	}

	if (l == p)
		return (1);
	return (0);
}

/**
 * makeshift_strtok - custom string tokenization function
 * @the_str: the string to be tokenized
 * @the_delim: delimiter to break string into tokens
 *
 * Return: pointer to tokenized/isolated string
*/
char *makeshift_strtok(char *the_str, const char *the_delim)
{
	static char *segmented, *end_token;
	char *start_token;
	unsigned int _i, condition;

	if (the_str != NULL)
	{
		if (makeshift_cmpchr(the_str, the_delim))
			return (NULL);
		segmented = the_str;
		_i = makeshift_strlen(the_str);
		end_token = &the_str[_i];
	}
	start_token = segmented;
	if (start_token == end_token)
		return (NULL);

	for (condition = 0; *segmented; segmented++)
	{
		if (segmented != start_token)
			if (*segmented && *(segmented - 1) == '\0')
				break;

		for (_i = 0; the_delim[_i]; _i++)
		{
			if (*segmented == the_delim[_i])
			{
				*segmented = '\0';
				if (segmented == start_token)
					start_token++;
				break;
			}
		}
		if (condition == 0 && *segmented)
			condition = 1;
	}

	if (condition == 0)
		return (NULL);

	return (start_token);
}
