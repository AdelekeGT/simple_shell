#include "shell.h"

/**
 * exit_builtin - function for exit
 * @sh_data: data from shell
 * Return: 1
*/
int exit_builtin(Shell_pack *sh_data)
{
	unsigned int sh_stat;
	int stat_is_digit, _length, number;

	if (sh_data->sh_arguments[1] != NULL)
	{
		sh_stat = makeshift_atoi(sh_data->sh_arguments[1]);
		stat_is_digit = makeshift_isdigit(sh_data->sh_arguments[1]);
		_length = makeshift_strlen(sh_data->sh_arguments[1]);
		number = sh_stat > INT_MAX;

		if (!stat_is_digit || _length >= 11 || number)
		{
			sh_data->sh_status = 2;
			return (-1);
		}
		sh_data->sh_status = sh_stat;
	}
	return (1);
}

/**
 * setenv_builtin - function for executing setenv
 * @sh_data: data from shell
 *
 * Return: 0 on success
*/
int setenv_builtin(Shell_pack *sh_data)
{
	if (makeshift_setenv(sh_data) != 0)
	{
		perror("setenv failure");
		return (-1);
	}

	return (0);
}

/**
 * unsetenv_builtin - function for executing setenv
 * @sh_data: data from shell
 *
 * Return: 0 on success
*/
int unsetenv_builtin(Shell_pack *sh_data)
{
	if (makeshift_unsetenv(sh_data) != 0)
	{
		perror("unsetenv failure");
		return (-1);
	}

	return (0);
}

/**
 * env_builtin - function for printintg environment
 * @sh_data: data from shell
 *
 * Return: 0 on success
*/
int env_builtin(Shell_pack *sh_data)
{
	int idx;

	if (sh_data->sh_environ == NULL)
		return (-1);

	idx = 0;
	while (sh_data->sh_environ[idx] != NULL)
	{
		makeshift_printf(sh_data->sh_environ[idx]);
		makeshift_printf("\n");
		idx++;
	}

	return (0);
}
