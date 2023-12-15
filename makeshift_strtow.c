#include "shell.h"

/**
 * **makeshift_strtow - breaks or splits string into tokens
 * @the_str: input from getline
 * @the_delim: the delimeter string
 *
 * Return: pointer to array of strings containing all tokens
 */

char **makeshift_strtow(char *the_str, char *the_delim)
{
	int p, q, r, s, words_number = 0;
	char **all_token;

	if (the_str == NULL || the_str[0] == 0)
		return (NULL);

	if (the_delim == NULL)
		the_delim = " ";
	for (p = 0; the_str[p] != '\0'; p++)
	{
		if (!delimiter_confirm(the_str[p], the_delim) &&
		(delimiter_confirm(the_str[p + 1], the_delim) || !the_str[p + 1]))
			words_number++;
	}
	if (words_number == 0)
		return (NULL);
	all_token = malloc((1 + words_number) * sizeof(char *));
	if (all_token == NULL)
		return (NULL);
	for (p = 0, q = 0; q < words_number; q++)
	{
		while (delimiter_confirm(the_str[p], the_delim))
			p++;
		r = 0;
		while (!delimiter_confirm(the_str[p + r], the_delim) && the_str[p + r])
			r++;
		all_token[q] = malloc((r + 1) * sizeof(char));
		if (all_token[q] == NULL)
		{
			for (r = 0; r < q; r++)
				free(all_token[r]);
			free(all_token);
			return (NULL);
		}
		for (s = 0; s < r; s++)
			all_token[q][s] = the_str[p++];
		all_token[q][s] = 0;
	}
	all_token[q] = NULL;
	return (all_token);
}

