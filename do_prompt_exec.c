#include "shell.h"

/**
 * do_split - tokenize input if certain delimiters exist
 * @delim_args: pointer to input that will be split
 * @input: input from shell
*/
void do_split(char *delim_args[], char *input)
{
	int i;

	if (input == NULL)
		return;

	i = 0;

	delim_args[i] = makeshift_strtok(input, OGA_DELIMITERS);
	while (delim_args[i] != NULL)
		delim_args[++i] = makeshift_strtok(NULL, OGA_DELIMITERS);

}

/**
 * do_print_prompt_exec_error - print error
 * @input: input from command line
*/
void do_print_prompt_exec_error(char *input)
{
	makeshift_printf(": 1: ");
	makeshift_printf(input);
	makeshift_printf(": not found\n");
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
	char *exec_args[30], *delim_args[10], *full_command;
	const char *the_delims = " ";
	int i = 0, j = 0, k = 0, command_exists, builtin_return_val, path_validation;

	do_split(delim_args, input);
	while (delim_args[j] != NULL)
	{
		exec_args[k] = makeshift_strtok(delim_args[j], the_delims);
		while (exec_args[k] != NULL)
			exec_args[++k] = makeshift_strtok(NULL, the_delims);
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
		path_validation = validate_path(exec_args[0]);
		if (path_validation == 0)
			do_fork_exec(input, exec_args, sh_data);
		if (path_validation != 0 && command_exists != 0)
		{
			makeshift_printf(sh_data->sh_argv[0]);
			do_print_prompt_exec_error(input);
		}
		j++;
	}
	free(input);
	free(full_command);
	return (0);
}
