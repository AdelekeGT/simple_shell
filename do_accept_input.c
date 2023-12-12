#include "shell.h"

/**
 * do_accept_input - function accepts input
 * @get_ret: return value of getline
 *
 * Return: the user input
*/
char *do_accept_input(ssize_t *get_ret)
{
	size_t n = 0;
	char *the_input = NULL;

	/*input_line = getline(&the_input, &n, stdin);*/
	*get_ret = getline(&the_input, &n, stdin);

	return (the_input);
}
