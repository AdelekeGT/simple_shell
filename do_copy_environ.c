#include "shell.h"

/**
 * do_copy_environ - creates a copy of environ and returns
 * an array of strings containing them
 * @sh_data: Struct structure for shell information
 *
 * Return: 0
 */
char **do_copy_environ(Shell_pack *sh_data)
{
	if (!sh_data->sh_environ || sh_data->modified_env)
	{
		sh_data->sh_environ = get_strings_from_list(sh_data->sh_env);

		sh_data->modified_env = 0;
	}

	return (sh_data->sh_environ);
}
