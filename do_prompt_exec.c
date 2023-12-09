#include "shell.h"

/**
 * do_prompt_exec - executes command typed in prompt
 * @input: input received from user
 * @sh_data: information from shell pack; argument needed
 *
 * Return: 0 on success
*/
int do_prompt_exec(char *input, Shell_pack *sh_data)
{
	char *exec_args[30], *full_command;
	const char *the_delim = " ";
	int i = 0, iterator = 0, command_exists, builtin_return_val, path_validation;

	exec_args[iterator] = makeshift_strtok(input, the_delim);
	while (exec_args[iterator] != NULL)
		exec_args[++iterator] = makeshift_strtok(NULL, the_delim);
	while (exec_args[i] != NULL)
	{
		sh_data->sh_arguments[i] = makeshift_strdup(exec_args[i]);
		i++;
	}
	sh_data->sh_arguments[i] = NULL;

	builtin_return_val = check_for_builtins(sh_data);
	if (builtin_return_val == 1 || builtin_return_val == 0)
		return (builtin_return_val);

	/*If a direct command e.g ls, is passed, validate it*/
	command_exists = validate_command(exec_args[0]);
	full_command = fuse_commands(exec_args[0]);
	if ((command_exists == 0) && (full_command != NULL))
		exec_args[0] = full_command;

	/*If a path e.g /bin/ls, validate the path first*/
	/*Then validate the command after it - validate_command function*/
	path_validation = validate_path(exec_args[0]);

	if (path_validation == 0)
		do_fork_exec(input, exec_args, sh_data);
	if (path_validation != 0 && command_exists != 0)
	{
		makeshift_printf(sh_data->sh_argv[0]);
		makeshift_printf(": No such file or directory\n");
	}
	free(input);
	free(full_command);
	return (0);
}
