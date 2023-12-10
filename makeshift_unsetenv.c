#include "shell.h"

/**
 * makeshift_unsetenv - custom unsetenv function
 * it deletes an environmental variable
 * @sh_data: data from shell
 *
 * Return: 0 on success
*/
int makeshift_unsetenv(Shell_pack *sh_data)
{
	char **create_new_environ;
	char *full_env_var, *env_var;
	int p, q, r = -1, length;

	if (sh_data->sh_arguments[1] == NULL)
	{
		do_handle_errors(sh_data, -1);
		return (0);
	}

	length = makeshift_strlen(sh_data->sh_arguments[1]);

	for (p = 0; sh_data->sh_environ[p]; p++)
	{
		full_env_var = makeshift_strdup(sh_data->sh_environ[p]);
		env_var = makeshift_strtok(full_env_var, "=");
		if (makeshift_strncmp(env_var, sh_data->sh_arguments[1], length) == 0)
			r = p;
		free(full_env_var);
	}

	if (r == -1)
	{
		do_handle_errors(sh_data, -1);
		return (0);
	}

	create_new_environ = malloc(sizeof(char *) * (p));
	for (p = q = 0; sh_data->sh_environ[p]; p++)
	{
		if (p != r)
		{
			create_new_environ[q] = sh_data->sh_environ[p];
			q++;
		}
	}
	create_new_environ[q] = NULL;

	free(sh_data->sh_environ[r]);
	free(sh_data->sh_environ);
	sh_data->sh_environ = create_new_environ;

	return (0);
}

/**
 * test_makeshift_unsetenv - custom unsetenv function
 * it deletes an environmental variable
 * @sh_data: data from shell
 *
 * Return: 0 on success
*/
int test_makeshift_unsetenv(Shell_pack *sh_data)
{
	int j, k, _len = 0;

	if (sh_data->sh_arguments[1] == NULL || *sh_data->sh_arguments[1] == '\0' ||
	makeshift_strchr(sh_data->sh_arguments[1], '=') == NULL)
	{
		write(STDERR_FILENO, "unsetenv error", sizeof("unsetenv error") - 1);
		return (-1);
	}

	/* find length of variable name*/
	while (sh_data->sh_arguments[1][_len] != '\0')
		_len++;

	/* comapre variable name passed in to the variable name in the */
	/* current iteration of the environment variables*/
	for (j = 0; sh_data->sh_environ[j] != NULL; j++)
	{
		if (makeshift_strncmp(sh_data->sh_environ[j], sh_data->sh_arguments[1], _len)
		== 0 && sh_data->sh_environ[j][_len] == '=')
		{
			/* if a match has been found*/
			free(sh_data->sh_environ[j]);
			/* shift subsequent variables to fill the gap*/
			for (k = j; sh_data->sh_environ[k] != NULL; k++)
				sh_data->sh_environ[k] = sh_data->sh_environ[k + 1];

			break;
		}
	}

	return (0);
}
