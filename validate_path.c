#include "shell.h"

/**
 * validate_path - if path is passed in, function checks if path is valid
 * then goes on to check the command after it if it is valid
 * @path_n_cmd: path passed in
 * Return: 0 if path is valid; -1 otherwise
*/
int validate_path(char *path_n_cmd)
{
	char *path = "/bin/";
	char *cmd_left;
	int _ind = 0, _i = 0;
	int command_is_valid;

	cmd_left = malloc(30 * sizeof(char));
	if (cmd_left == NULL)
		return (-1);

	while (path[_ind] != '\0')
	{
		if (path[_ind] != path_n_cmd[_ind])
		{
			free(cmd_left);
			return (-1);
		}
		_ind++;
	}

	while (path_n_cmd[_ind] != '\0')
	{
		cmd_left[_i] = path_n_cmd[_ind];
		_i++;
		_ind++;
	}
	cmd_left[_i] = '\0';

	/*Now check if command left is valid*/
	command_is_valid = validate_command(cmd_left);
	if (command_is_valid != 0)
	{
		free(cmd_left);
		return (-1);
	}

	free(cmd_left);
	return (0);
}
