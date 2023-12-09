#include "shell.h"

/**
 * do_tokenize_PATH - tokenize PATH from environ
 *
 * Return: pointer to array of tokenized strings
*/
char **do_tokenize_PATH(void)
{
	char *path_env, **tok_paths = malloc(218 * sizeof(char *));
	const char *delim = ":";
	int i = 0, j = 0, k = 0, len = 5;

	if (tok_paths == NULL)
		return (NULL);
	while (environ[i] != NULL)
	{
		if (makeshift_strncmp("PATH", environ[i], 4) == 0)
		{
			path_env = malloc(((makeshift_strlen(environ[i]) - len) + 1)
			* sizeof(char));

			if (path_env == NULL)
			{
				free(tok_paths);
				return (NULL);
			}
			while (environ[i][len] != '\0')
				path_env[j++] = environ[i][len++];
			path_env[j] = '\0';
			break;
		}
		i++;
	}
	tok_paths[k] = makeshift_strdup(makeshift_strtok(path_env, delim));
	if (tok_paths[k] == NULL)
	{
		free(path_env);
		free(tok_paths);
		return (NULL);
	}
	while (tok_paths[k] != NULL && i < 217)
	{
		tok_paths[++k] = makeshift_strdup(makeshift_strtok(NULL, delim));
		if (tok_paths[k] == NULL)
			break;
	}
	free(path_env);
	return (tok_paths);
}
