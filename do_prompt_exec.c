#include "shell.h"

/**
 * do_split - tokenize input if certain delimiters exist
 * @delim_args: pointer to input that will be split
 * @input: input from shell
 *
 * Return: 0 on success
*/
int do_split(char *delim_args[], char *input)
{
	int i;

	if (input == NULL)
		return (-2);

	i = 0;

	delim_args[i] = makeshift_strtok(input, OGA_DELIMITERS);
	while (delim_args[i] != NULL)
		delim_args[++i] = makeshift_strtok(NULL, OGA_DELIMITERS);

	return (0);
}

/**
 * do_prompt_exec - executes command typed in prompt
 * @input: input received from user
 * @sh_data: information from shell pack; argument needed
 *
 * Return: 0 on success
*/
int do_prompt_exec(char *input, Shell_pack *sh_data)
{
	char *exec_args[30] = {NULL}, *delim_args[10] = {NULL}, *full_command;
	const char *the_delims = " ";
	int i, j, k = 0, command_exists, builtin_return_val, path_validation;

	if (do_split(delim_args, input) != 0)
		return (-2);
	for (j = 0; delim_args[j] != NULL; j++)
	{
		k = 0;
		exec_args[k] = makeshift_strtok(delim_args[j], the_delims);
		while (exec_args[k] != NULL)
			exec_args[++k] = makeshift_strtok(NULL, the_delims);
		for (i = 0; exec_args[i] != NULL; i++)
			sh_data->sh_arguments[i] = makeshift_strdup(exec_args[i]);
		sh_data->sh_arguments[i] = NULL;
		builtin_return_val = check_for_builtins(sh_data);
		if (builtin_return_val == 1 || builtin_return_val == 0)
		{
			free(input);
			free(full_command);
			return (builtin_return_val);
		}

		/*If a direct command e.g ls, is passed, validate it*/
		command_exists = validate_command(exec_args[0]);
		full_command = fuse_commands(exec_args[0]);
		if ((command_exists == 0) && (full_command != NULL))
			exec_args[0] = full_command;

		/*If a path e.g /bin/ls, validate the path first*/
		path_validation = validate_path(exec_args[0]);
		if (path_validation == 0)
			do_fork_exec(input, exec_args, sh_data);

		if (path_validation != 0 && command_exists != 0)
			do_handle_errors(sh_data, 127);
	}
	free(input);
	free(full_command);
	return (0);
}
