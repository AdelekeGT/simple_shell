#include "shell.h"

/**
 * built_env - prints the current environment
 * @sh_data: Struct structure for shell information
 * Return: 0 all the time
 */
int built_env(Shell_pack *sh_data)
{
	print_list_str(sh_data->sh_env);

	return (0);
}

/**
 * built_exit - function for exit
 * @sh_data: data from shell
 *
 * Return: -3
*/
int built_exit(Shell_pack *sh_data)
{
	int sh_stat;

	if (sh_data->sh_arguments[1] != NULL)
	{
		sh_stat = makeshift_atoi(sh_data->sh_arguments[1]);

		if (sh_stat == -1)
		{
			sh_data->sh_status = 2;
			do_handle_errors(sh_data, 5);
			return (1);
		}

		sh_data->sh_err_no = makeshift_atoi(sh_data->sh_arguments[1]);
		return (-3);
	}

	sh_data->sh_err_no = -1;

	return (-3);
}

/**
 * built_getenv - extracts an environmental variable and prints it
 * @sh_data: Struct structure for shell information
 * @env_var: variable name
 *
 * Return: the string containing variable name and value with '='
 */
char *built_getenv(Shell_pack *sh_data, const char *env_var)
{
	char *pointer;
	sh_list *n_node;

	n_node = sh_data->sh_env;

	while (n_node != NULL)
	{
		pointer = starts_with(n_node->str, env_var);

		if (pointer && *pointer)
			return (pointer);

		n_node = n_node->next;
	}

	return (NULL);
}
