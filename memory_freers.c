#include "shell.h"

/**
 * ptr_freer - pointer freer
 * @the_ptr: pointer to address for freeing
 *
 * Return: 1 on success
 */
int ptr_freer(void **the_ptr)
{
	if (the_ptr && *the_ptr)
	{
		free(*the_ptr);
		*the_ptr = NULL;
		return (1);
	}

	return (0);
}

/**
 * _free_str_array - function frees array of strings
 * @the_arr: array of strings
 */
void _free_str_array(char **the_arr)
{
	char **result = the_arr;
	int j;

	if (the_arr == NULL)
		return;

	j = 0;
	while (the_arr[j] != NULL)
	{
		free(the_arr[j]);
		j++;
	}

	free(result);
}
