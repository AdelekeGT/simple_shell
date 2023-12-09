#include "shell.h"

/**
 * fuse_commands - concatenates the command that has been
 * checked by the validate_command function
 * @command: command brought in from validate_command
 * Return: concatenated command
*/
char *fuse_commands(const char *command)
{
	char *full_command;
	int validated_command;

	if (command == NULL)
		return (NULL);

	/*check first if the command exists in /bin directory*/
	validated_command = validate_command(command);
	if (validated_command == 0)
	{
		/*
		* if command exists in /bin,
		* then concatenate the command with the path /bin/
		*/
		full_command = makeshift_strcat(command);
		return (full_command);
	}

	return (NULL);
}
