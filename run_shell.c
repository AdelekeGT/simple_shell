#include "shell.h"

/**
 * run_shell - this is loop that starts the shell
 * @sh_data: Struct structure for shell information
 * @av: argument list passed to ./hsh
 *
 * Return: 0 on success of execution
 */
int run_shell(Shell_pack *sh_data, char **av)
{
	ssize_t get = 0;
	int bltin_return_val = 0;

	while (get != -1 && bltin_return_val != -3)
	{
		gimme_clean_slate(sh_data);

		if (isatty(STDIN_FILENO))
			makeshift_printf("Jupiter$$ ");

		get = do_accept_input(sh_data);
		if (get != -1)
		{
			initialize_struct(sh_data, av);
			bltin_return_val = _check_for_builtins(sh_data);
			if (bltin_return_val == -1)
				validate_cmd(sh_data);
		}

		else if (isatty(STDIN_FILENO))
			makeshift_printf("\n");

		_do_free_allocs0(sh_data);
	}

	_do_free_allocs1(sh_data);

	if (!(isatty(STDIN_FILENO)) && sh_data->sh_status)
		exit(sh_data->sh_status);

	if (bltin_return_val == -3)
	{
		if (sh_data->sh_err_no == -1)
			exit(sh_data->sh_status);
		exit(sh_data->sh_err_no);
	}

	return (bltin_return_val);
}



/**
 * validate_cmd - checks if command exists in the PATH
 * @sh_data: Struct pack for shell information
 *
 * Return: void
 */
void validate_cmd(Shell_pack *sh_data)
{
	char *path = NULL;
	int i, k;

	sh_data->sh_path = sh_data->sh_arguments[0];

	if (sh_data->sh_line_no == 1)
	{
		sh_data->sh_count++;
		sh_data->sh_line_no = 0;
	}

	for (i = 0, k = 0; sh_data->sh_input[i]; i++)
		if (!delimiter_confirm(sh_data->sh_input[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = validate_PATH(sh_data, built_getenv(sh_data, "PATH="),
	sh_data->sh_arguments[0]);

	if (path != NULL)
	{
		sh_data->sh_path = path;
		_do_fork_exec(sh_data);
	}
	else
	{
		if ((isatty(STDIN_FILENO) || built_getenv(sh_data, "PATH=")
			|| sh_data->sh_arguments[0][0] == '/') &&
			_cmd_is_valid(sh_data, sh_data->sh_arguments[0]))
			_do_fork_exec(sh_data);
		else if (*(sh_data->sh_input) != '\n')
		{
			sh_data->sh_status = 127;
			do_handle_errors(sh_data, 127);
		}
	}
}
