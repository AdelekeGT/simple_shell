#include "shell.h"

/**
 * check_for_builtins - checks for certain builtin commands
 * cd, exit, setenv, unsetenv
 * @sh_data: user input from getline; sh_data.sh_input
 *
 * Return: _value
*/
int check_for_builtins(Shell_pack *sh_data)
{
	int iterator, length, _value;
	Builtin_execs builtin_array[] = {
		{"exit", exit_builtin}, {"setenv", setenv_builtin},
		{"unsetenv", unsetenv_builtin},
		{"env", env_builtin}, {NULL, NULL}
	};

	if (sh_data->sh_arguments[0] == NULL)
		return (-1);

	length = makeshift_strlen(sh_data->sh_arguments[0]);

	/*
	* check if the first tokenized string from
	* input matches any of the builtin executables in the exec array
	*/
	for (iterator = 0; builtin_array[iterator].command != NULL; iterator++)
	{
		if (makeshift_strncmp(builtin_array[iterator].command,
		sh_data->sh_arguments[0], length) == 0)
		{
			_value = builtin_array[iterator].builtin_func(sh_data);
			break;
		}
	}

	return (_value);
}
