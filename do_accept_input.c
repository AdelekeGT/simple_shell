#include "shell.h"

/**
 * do_accept_input - function accepts input
 *
 * Return: the user input
*/
char *do_accept_input(void)
{
	size_t n = 0;
	char *the_input = NULL;
	ssize_t input_line;
	int length = 0;

	/*input_line = getline(&the_input, &n, stdin);*/
	the_input = another_getline();
	(void)n;
	(void)input_line;

	if (the_input == NULL)
	{
		if (feof(stdin))
		{
			makeshift_printf("\n");
			free(the_input);
		} else
		{
			makeshift_printf("\n");
			free(the_input);
			exit(EXIT_FAILURE);
		}
	}
	/*
	*if ONLY an 'enter key' is pressed which is represented by '\n',
	we need to tell the program to just print a new line and do nothing
	*/
	if (*the_input == '\n')
	{
		free(the_input);
		return (NULL);
	}

	while (the_input[length])
		length++;

	/*we need to remove the new line from our string*/
	the_input[length - 1] = '\0';

	return (the_input);
}
