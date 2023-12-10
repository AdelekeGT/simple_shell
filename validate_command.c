#include "shell.h"

/**
 * validate_command - checks a command to see if its file exists
 * in the /bin/ directory
 * @command: command typed in
 * Return: 0 if command exists, -1 otherwise
*/
int validate_command(const char *command)
{
	char **tok_paths;
	DIR *folder_ptr;
	struct dirent *dir_entry;
	int j = 0;

	if (command == NULL)
		return (-1);

	tok_paths = do_tokenize_PATH();

	if (tok_paths == NULL)
		return (-1);

	while (tok_paths[j] != NULL)
	{
		folder_ptr = opendir(tok_paths[j]);
		if (folder_ptr == NULL)
		{
			free(tok_paths);
			return (-1);
		}

		dir_entry = readdir(folder_ptr);
		while (dir_entry != NULL)
		{
			if (makeshift_strncmp(dir_entry->d_name, command,
			makeshift_strlen(command)) == 0)
			{
				closedir(folder_ptr);
				free(tok_paths);
				return (0);
			}
			dir_entry = readdir(folder_ptr);
		}
		closedir(folder_ptr);
		j++;
	}
	free(tok_paths);
	return (-1);
}
