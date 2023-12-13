#include "shell.h"

/**
 * makeshift_getenv - gets the value of an environment variable
 * @env_var: environment variable name
 * @env: the environment from sh_data->sh_environ
 * Return: pointer to the needed variable
*/
char *makeshift_getenv(char *env_var, char ***env)
{
	int j, _len = 0;

	if (env_var == NULL || *env_var == '\0')
		return (NULL);

	while (env_var[_len] != '\0')
		_len++;

	for (j = 0; *env[j] != NULL; j++)
	{
		if (makeshift_strncmp(*env[j], env_var, _len) == 0 && *env[j][_len] == '=')
			return (*env[j] + _len + 1);
	}

	return (NULL);
}
