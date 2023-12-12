#include "shell.h"

/**
 * validate_command - checks a command to see if its file exists
 * in the PATH directories
 * @command: command typed in
 *
 * Return: pointer to directory containing command, NULL otherwise
*/
char *validate_command(const char *command)
{
	char **tok_paths;
	DIR *folder_ptr;
	struct dirent *dir_entry;
	int j = 0, cmd_len;

	if (command == NULL)
		return (NULL);

	tok_paths = do_tokenize_PATH();

	if (tok_paths == NULL)
		return (NULL);
	cmd_len = makeshift_strlen(command);
	while (tok_paths[j] != NULL)
	{
		folder_ptr = opendir(tok_paths[j]);
		if (folder_ptr == NULL)
		{
			write(STDERR_FILENO, "opendir failure\n", 15);
			free(tok_paths);
			return (NULL);
		}

		dir_entry = readdir(folder_ptr);
		while (dir_entry != NULL)
		{
			if (makeshift_strncmp(dir_entry->d_name, command, cmd_len) == 0)
			{
				closedir(folder_ptr);
				return (tok_paths[j]);
			}
			dir_entry = readdir(folder_ptr);
		}
		closedir(folder_ptr);
		j++;
	}
	free(tok_paths);
	return (NULL);
}
