#include "shell.h"

/**
 * _check_for_builtins - function looks for builtin commands
 * @sh_data: Struct structure for shell information
 *
 * Return: -1 if builtin func not found,
 *			-3 if builtin func signals exit()
 *			1 if builtin func found but not successful,
 *			0 if builtin func successfully executed,
 */
int _check_for_builtins(Shell_pack *sh_data)
{
	int iterator, length, _value = -1;
	Builtin_execs builtin_array[] = {
		{"env", built_env},
		{"exit", built_exit},
		{"setenv", built_setenv},
		{"unsetenv", built_unsetenv},
		{NULL, NULL}
	};

	if (sh_data->sh_arguments[0] == NULL)
		return (-1);

	length = makeshift_strlen(sh_data->sh_arguments[0]);
	(void)length;
	/*
	* check if the first tokenized string from
	* input matches any of the builtin executables in the exec array
	*/

	for (iterator = 0; builtin_array[iterator].command != NULL; iterator++)
	{
		if (makeshift_strcmp(sh_data->sh_arguments[0],
		builtin_array[iterator].command) == 0)
		{
			sh_data->sh_count++;
			_value = builtin_array[iterator].builtin_func(sh_data);
			break;
		}
	}

	return (_value);
}


