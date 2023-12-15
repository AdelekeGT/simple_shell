#include "shell.h"

/**
 * _do_free_allocs0 - frees Shell_pack struct fields
 * @sh_data: struct address
 */
void _do_free_allocs0(Shell_pack *sh_data)
{
	int g = 0;

	_free_str_array(sh_data->sh_arguments);

	sh_data->sh_arguments = NULL;
	sh_data->sh_path = NULL;

	if (g)
	{
		if (!sh_data->sh_cmd)
			free(sh_data->sh_input);

		if (sh_data->sh_env)
			do_free_list(&(sh_data->sh_env));

		_free_str_array(sh_data->sh_environ);
			sh_data->sh_environ = NULL;

		ptr_freer((void **)sh_data->sh_cmd);

		if (sh_data->readfd > 2)
			close(sh_data->readfd);

	}
}

/**
 * _do_free_allocs1 - frees Shell_pack struct fields
 * @sh_data: struct address
 */
void _do_free_allocs1(Shell_pack *sh_data)
{
	int g = 1;

	_free_str_array(sh_data->sh_arguments);

	sh_data->sh_arguments = NULL;
	sh_data->sh_path = NULL;

	if (g)
	{
		if (!sh_data->sh_cmd)
			free(sh_data->sh_input);

		if (sh_data->sh_env)
			do_free_list(&(sh_data->sh_env));

		_free_str_array(sh_data->sh_environ);
			sh_data->sh_environ = NULL;

		ptr_freer((void **)sh_data->sh_cmd);

		if (sh_data->readfd > 2)
			close(sh_data->readfd);

	}
}
