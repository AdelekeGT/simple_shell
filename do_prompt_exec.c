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
	char *exec_args[100000] = {NULL}, *full_cmd = NULL, *is_cmd = NULL;
	int i, k, bltin_ret_val, path_validation, len;

	k = 0;
	exec_args[k] = strtok(input, OGA_DELIMS);
	while (exec_args[k] != NULL)
		exec_args[++k] = strtok(NULL, OGA_DELIMS);
	for (i = 0; exec_args[i] != NULL; i++)
		sh_data->sh_arguments[i] = makeshift_strdup(exec_args[i]);
	sh_data->sh_arguments[i] = NULL;
	bltin_ret_val = check_for_builtins(sh_data);
	if (bltin_ret_val == 1 || bltin_ret_val == 0 || bltin_ret_val == -1)
	{
		free_args(sh_data);
		free(input);
		return (bltin_ret_val);
	}
	is_cmd = validate_command(exec_args[0]); /*If direct command, validate it*/
	if (is_cmd != NULL)
	{
		len = makeshift_strlen(is_cmd) + makeshift_strlen(exec_args[0]) + 1;
		full_cmd = malloc((len + 1) * sizeof(char));
		copy_to_fullCMD(full_cmd, "/bin", exec_args[0]);
		if (full_cmd != NULL)
			exec_args[0] = full_cmd;
	}

	/*If a path e.g /bin/ls, validate the path first*/
	path_validation = validate_path(exec_args[0]);
	if (path_validation != 0 && !is_cmd)
	{
		do_handle_errors(sh_data, 127);
		return (127);
	}
	do_fork_exec(input, exec_args, sh_data);

	free_args(sh_data);
	free_prompt_exec(is_cmd, input, full_cmd);
	return (0);
}

/**
 * copy_to_fullCMD - copy path and command to full_cmd
 * @full_cmd: memory allocated to hold concatenated path and command
 * @path: path from is_cmd
 * @command: exec_args[0]
*/
void copy_to_fullCMD(char *full_cmd, char *path, char *command)
{
	if (full_cmd == NULL)
	{
		free(path);
		write(STDERR_FILENO, ": memory alloc error\n", 20);
		return;
	}
	makeshift_strcpy(full_cmd, path);
	_makeshift_strcat(full_cmd, "/");
	_makeshift_strcat(full_cmd, command);
	_makeshift_strcat(full_cmd, "\0");
}

/**
 * free_prompt_exec - free is_cmd, input and full_cmd
 * @is_cmd: is_cmd
 * @input: input
 * @full_cmd: full command; path and command
*/
void free_prompt_exec(char *is_cmd, char *input, char *full_cmd)
{
	free(is_cmd);
	free(input);
	free(full_cmd);
}

/**
 * free_args - free is_cmd, input and full_cmd
 * @sh_data: data
*/
void free_args(Shell_pack *sh_data)
{
	int i = 0;

	for (i = 0; sh_data->sh_arguments[i]; i++)
		free(sh_data->sh_arguments[i]);
	free(sh_data->sh_arguments);
}

