#include "shell.h"

/**
 * do_comments_check - check if '#' for comments
 * exist in the input got from command line
 * @the_input: input from command line
 *
 * Return: the input
*/
char *do_comments_check(char *the_input)
{
	int it, input_len = 0;

	while (the_input[input_len])
		input_len++;

	for (it = 0; the_input[it] != '\0'; it++)
	{
		if (the_input[it] == '#')
		{
			if (it == 0)
			{
				free(the_input);
				return (NULL);
			}

			if (the_input[it - 1] == ' ' || the_input[it - 1] == '\t' ||
			the_input[it - 1] == ';')
			{
				the_input = makeshift_realloc(the_input, (it + 1));
				the_input[it] = '\0';
			}
		}
	}
	return (the_input);
}

