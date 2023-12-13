#include "shell.h"

/**
 * do_free_allocs - frees memories allocated using malloc
 * @sh_data: shell pack datatype
*/
void do_free_allocs(Shell_pack *sh_data)
{
	unsigned int idx;

	for (idx = 0; sh_data->sh_environ[idx] != NULL; idx++)
		free(sh_data->sh_environ[idx]);

	free(sh_data->sh_environ);

	for (idx = 0; idx < 10 && sh_data->sh_arguments[idx] != NULL; idx++)
		free(sh_data->sh_arguments[idx]);

	free(sh_data->sh_arguments);

	free(sh_data->sh_pid);
}

/**
 * do_set_data - sets shell data
 * @sh_data: shell pack datatype
 * @argv: pointer to array of pointers to argument strings
 *
 * Return: 0 on success; -1 otherwise
*/
int do_set_data(Shell_pack *sh_data, char **argv)
{
	unsigned int _i, _j;

	sh_data->sh_argv = argv;
	sh_data->sh_input = NULL;
	sh_data->sh_status = 0;
	sh_data->sh_count = 1;

	_i = 0;
	while (environ[_i] != NULL)
		_i++;

	sh_data->sh_environ = malloc(sizeof(char *) * (_i + 1));
	sh_data->sh_arguments = malloc(sizeof(char *) * 10);

	if (sh_data->sh_environ == NULL || sh_data->sh_arguments == NULL)
		return (-1);

	for (_i = 0; environ[_i] != NULL; _i++)
	{
		sh_data->sh_environ[_i] = makeshift_strdup(environ[_i]);
		if (sh_data->sh_environ[_i] == NULL)
		{
			for (_j = 0; _j < _i; _j++)
				free(sh_data->sh_environ[_j]);
			free(sh_data->sh_environ);
			free(sh_data->sh_arguments);
			return (-1);
		}
	}

	sh_data->sh_environ[_i] = NULL;

	_i = 0;
	while (_i < 10)
		sh_data->sh_arguments[_i++] = NULL;

	sh_data->sh_pid = makeshift_itoa(getpid());

	return (0);
}
