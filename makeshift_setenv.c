#include "shell.h"

/**
 * _makeshift_realloc_setenv - custom realloc for setenv
 * @the_old_block: old block of memory to be resized
 * @_o_size: old size of allocated memory block
 * @_n_size: concatenated size of memory to be allocated
 *
 * Return: pointer to newly allocated memory block
 */
char **makeshift_realloc_setenv(char **the_old_block, unsigned int _o_size,
unsigned int _n_size)
{
	char **new_block;
	unsigned int i;

	if (the_old_block == NULL)
		return (malloc(sizeof(char *) * _n_size));

	if (_n_size == _o_size)
		return (the_old_block);

	new_block = malloc(sizeof(char *) * _n_size);
	if (new_block == NULL)
		return (NULL);

	for (i = 0; i < _o_size; i++)
		new_block[i] = the_old_block[i];

	free(the_old_block);

	return (new_block);
}
/**
 * data_copy_setenv - copy data
 * @env_var: variable name
 * @env_val: variable value
 *
 * Return: pointer to full environment variable
 */
char *data_copy_setenv(char *env_var, char *env_val)
{
	char *concatenated;
	int len_env_var, len_env_val, total_len;

	len_env_var = makeshift_strlen(env_var);
	len_env_val = makeshift_strlen(env_val);
	total_len = len_env_var + len_env_val + 2;
	concatenated = malloc(sizeof(char) * (total_len));
	makeshift_strcpy(concatenated, env_var);
	_makeshift_strcat(concatenated, "=");
	_makeshift_strcat(concatenated, env_val);
	_makeshift_strcat(concatenated, "\0");

	return (concatenated);
}


/**
 * makeshift_setenv - custom setenv function
 * @sh_data: data from the shel
 *
 * Return: 0 on success; -1 otherwise
 */
int makeshift_setenv(Shell_pack *sh_data)
{
	int i, len;
	char *full_var, *env_var;

	if (sh_data->sh_arguments[1] == NULL || sh_data->sh_arguments[2] == NULL)
	{
		do_handle_errors(sh_data, -1);
		return (0);
	}

	len = makeshift_strlen(sh_data->sh_arguments[1]);

	for (i = 0; sh_data->sh_environ[i]; i++)
	{
		full_var = makeshift_strdup(sh_data->sh_environ[i]);
		env_var = makeshift_strtok(full_var, "=");
		if (makeshift_strncmp(env_var, sh_data->sh_arguments[1], len) == 0)
		{
			free(sh_data->sh_environ[i]);
			sh_data->sh_environ[i] =
			data_copy_setenv(env_var, sh_data->sh_arguments[2]);
			free(full_var);
			return (0);
		}
		free(full_var);
	}

	sh_data->sh_environ =
	makeshift_realloc_setenv(sh_data->sh_environ, i, sizeof(char *) * (i + 2));
	sh_data->sh_environ[i] =
	data_copy_setenv(sh_data->sh_arguments[1], sh_data->sh_arguments[2]);
	sh_data->sh_environ[i + 1] = NULL;

	return (0);
}

/**
 * test_makeshift_setenv - custom setenv function
 * @sh_data: data from the shel
 *
 * Return: 0 on success; -1 otherwise
 */
int test_makeshift_setenv(Shell_pack *sh_data)
{
	int i, len;
	char *env_var;

	if (sh_data->sh_arguments[1] == NULL || sh_data->sh_arguments[2] == NULL)
		return (-1);

	len = makeshift_strlen(sh_data->sh_arguments[1]);

	for (i = 0; sh_data->sh_environ[i]; i++)
	{
		env_var = makeshift_strtok(sh_data->sh_environ[i], "=");
		if (makeshift_strncmp(env_var, sh_data->sh_arguments[1], len) == 0)
		{
			free(sh_data->sh_environ[i]);  /*Free the old entry*/
			sh_data->sh_environ[i] =
			data_copy_setenv(env_var, sh_data->sh_arguments[2]);
			return (0);
		}
	}

	/* If not found, append a new entry */
	sh_data->sh_environ =
		makeshift_realloc_setenv(sh_data->sh_environ, i, sizeof(char *) * (i + 2));
	sh_data->sh_environ[i] =
	data_copy_setenv(sh_data->sh_arguments[1], sh_data->sh_arguments[2]);
	sh_data->sh_environ[i + 1] = NULL;

	return (0);
}
