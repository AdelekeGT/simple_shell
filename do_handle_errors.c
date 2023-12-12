#include "shell.h"

/**
 * do_handle_errors - function handles errors separately
 * @sh_data: data pack from shell
 * @return_val: return value of the functions that get triggered
 * the return values will determine what error messages will be printed
 *
 * Return: return value
 */
int do_handle_errors(Shell_pack *sh_data, int return_val)
{
	if (return_val == -1)
		err_for_environ(sh_data);
	else if (return_val == 127)
		err_for_not_found(sh_data);
	else if (return_val == 5)
	{
		if (makeshift_strncmp("exit", sh_data->sh_arguments[0], 4) == 0)
			err_for_exit(sh_data);
	}

	sh_data->sh_status = return_val;
	return (return_val);
}

/**
 * err_for_environ - error message to be displayed when
 * error occurs in executing the env functions
 * @sh_data: data from Shell_pack
 */
void err_for_environ(Shell_pack *sh_data)
{
	int _len;
	char *full_error_msg, *count_str, *e_msg;

	count_str = makeshift_itoa(sh_data->sh_count);
	e_msg = ": Add/remove environment variable failure\n";

	_len = makeshift_strlen(sh_data->sh_argv[0]) + makeshift_strlen(count_str)
	+ makeshift_strlen(sh_data->sh_arguments[0]) + makeshift_strlen(e_msg) + 4;

	full_error_msg = malloc(sizeof(char) * (_len + 1));
	if (full_error_msg == NULL)
	{
		free(full_error_msg);
		free(count_str);
		return;
	}

	makeshift_strcpy(full_error_msg, sh_data->sh_argv[0]);
	_makeshift_strcat(full_error_msg, ": ");
	_makeshift_strcat(full_error_msg, count_str);
	_makeshift_strcat(full_error_msg, ": ");
	_makeshift_strcat(full_error_msg, sh_data->sh_arguments[0]);
	_makeshift_strcat(full_error_msg, e_msg);
	_makeshift_strcat(full_error_msg, "\0");
	free(count_str);

	if (full_error_msg)
	{
		write(STDERR_FILENO, full_error_msg, _len);
		free(full_error_msg);
	}
}

/**
 * err_for_not_found - displays error message for command not found
 * @sh_data: Data from Shell_pack
 */
void err_for_not_found(Shell_pack *sh_data)
{
	int _len;
	char *full_error_msg, *e_msg, *count_str;

	count_str = makeshift_itoa(sh_data->sh_count);
	e_msg = ": not found\n";
	_len = makeshift_strlen(sh_data->sh_argv[0]) + makeshift_strlen(count_str) +
	makeshift_strlen(sh_data->sh_arguments[0]) + makeshift_strlen(e_msg) + 4;

	full_error_msg = malloc(sizeof(char) * (_len + 1));
	if (full_error_msg == NULL)
	{
		free(full_error_msg);
		free(count_str);
		return;
	}

	makeshift_strcpy(full_error_msg, sh_data->sh_argv[0]);
	_makeshift_strcat(full_error_msg, ": ");
	_makeshift_strcat(full_error_msg, count_str);
	_makeshift_strcat(full_error_msg, ": ");
	_makeshift_strcat(full_error_msg, sh_data->sh_arguments[0]);
	_makeshift_strcat(full_error_msg, e_msg);
	_makeshift_strcat(full_error_msg, "\0");
	free(count_str);

	if (full_error_msg)
	{
		write(STDERR_FILENO, full_error_msg, _len);
		free(full_error_msg);
	}
	sh_data->sh_status = 127;
}

/**
 * err_for_exit - displays error message for when exit is entered
 * @sh_data: data from Shell_pack
 */
void err_for_exit(Shell_pack *sh_data)
{
	int _len;
	char *full_error_msg, *count_str, *e_msg;

	count_str = makeshift_itoa(sh_data->sh_count);
	e_msg = ": Illegal number: ";

	_len = makeshift_strlen(sh_data->sh_argv[0]) + makeshift_strlen(count_str) +
	makeshift_strlen(sh_data->sh_arguments[0]) + makeshift_strlen(e_msg) +
	makeshift_strlen(sh_data->sh_arguments[1]) + 5;

	full_error_msg = malloc(sizeof(char) * (_len + 1));
	if (full_error_msg == 0)
	{
		free(count_str);
		return;
	}

	makeshift_strcpy(full_error_msg, sh_data->sh_argv[0]);
	_makeshift_strcat(full_error_msg, ": ");
	_makeshift_strcat(full_error_msg, count_str);
	_makeshift_strcat(full_error_msg, ": ");
	_makeshift_strcat(full_error_msg, sh_data->sh_arguments[0]);
	_makeshift_strcat(full_error_msg, e_msg);
	_makeshift_strcat(full_error_msg, sh_data->sh_arguments[1]);
	_makeshift_strcat(full_error_msg, "\n\0");
	free(count_str);

	if (full_error_msg)
	{
		write(STDERR_FILENO, full_error_msg, _len);
		free(full_error_msg);
	}
}
