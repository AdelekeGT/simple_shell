#include "shell.h"

/**
 * do_load_envs - loads envs into linked list
 * @sh_data: Struct structure for shell information
 *
 * Return: 0
 */
int do_load_envs(Shell_pack *sh_data)
{
	sh_list *n_node = NULL;
	size_t i_i;

	for (i_i = 0; environ[i_i]; i_i++)
	{
		put_node_4_end(&n_node, environ[i_i], 0);
	}

	sh_data->sh_env = n_node;

	return (0);
}

/**
 * built_setenv - Sets a new environmental variable,
 * or modify an existing one
 * @sh_data: Struct structure for shell information
 *
 *  Return: 0
 */
int built_setenv(Shell_pack *sh_data)
{
	int helper_ret;

	if (sh_data->arg_cnt_cmd_line != 3)
	{
		err_write("Usage: setenv VARIABLE VALUE\n");
		return (0);
	}

	helper_ret = _helper_setenv(sh_data, sh_data->sh_arguments[1],
	sh_data->sh_arguments[2]);
	if (helper_ret == -1)
	{
		do_handle_errors(sh_data, -1);
		return (0);
	}

	return (0);
}

/**
 * _helper_setenv - Creates a new environment variable,
 *             or modify an existing one
 * @sh_data: Struct structure for shell information
 * @env_var: the string sh_env env_var property
 * @env_value: the string sh_env env_var env_value
 *  Return: Always 0; -1 otherwise
 */
int _helper_setenv(Shell_pack *sh_data, char *env_var, char *env_value)
{
	char *the_buffer = NULL, *_ptr;
	sh_list *n_node;
	int var_len, val_len;

	if (env_var == NULL || env_value == NULL)
		return (-1);

	var_len = makeshift_strlen(env_var);
	val_len = makeshift_strlen(env_value);

	the_buffer = malloc(var_len +
	 val_len + 2);

	if (the_buffer == NULL)
		return (-1);

	makeshift_strcpy(the_buffer, env_var);
	makeshift_strcat(the_buffer, "=");
	makeshift_strcat(the_buffer, env_value);
	n_node = sh_data->sh_env;

	while (n_node)
	{
		_ptr = starts_with(n_node->str, env_var);
		if (_ptr && *_ptr == '=')
		{
			free(n_node->str);
			n_node->str = the_buffer;
			sh_data->modified_env = 1;
			return (0);
		}
		n_node = n_node->next;
	}

	put_node_4_end(&(sh_data->sh_env), the_buffer, 0);
	free(the_buffer);

	sh_data->modified_env = 1;

	return (0);
}

/**
 * built_unsetenv - Remove an environment variable
 * @sh_data: Struct structure for shell information
 *
 *  Return: 0
 */
int built_unsetenv(Shell_pack *sh_data)
{
	int i_i, ret;

	if (sh_data->arg_cnt_cmd_line == 1)
	{
		err_write("Usage: unsetenv VARIABLE\n");
		return (1);
	}

	for (i_i = 1; i_i <= sh_data->arg_cnt_cmd_line; i_i++)
		ret = _helper_unsetenv(sh_data, sh_data->sh_arguments[i_i]);

	(void)ret;

	return (0);
}

/**
 * _helper_unsetenv - Remove an environment variable
 * @sh_data: Struct structure for shell information
 * @env_var: environmental variable name to be removed
 *
 *  Return: 1 on delete, 0 otherwise
 */
int _helper_unsetenv(Shell_pack *sh_data, char *env_var)
{
	sh_list *n_node = sh_data->sh_env;
	size_t _idx = 0;
	char *_ptr;

	if (!n_node || env_var == NULL)
		return (0);

	while (n_node)
	{
		_ptr = starts_with(n_node->str, env_var);
		if (_ptr && *_ptr == '=')
		{
			sh_data->modified_env = remove_node_4_index(&(sh_data->sh_env), _idx);
			_idx = 0;
			n_node = sh_data->sh_env;
			continue;
		}

		n_node = n_node->next;
		_idx++;
	}

	return (sh_data->modified_env);
}
