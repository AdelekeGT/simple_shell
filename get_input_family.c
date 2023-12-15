#include "shell.h"

/**
 * loving_input_buffer - gets and stores chained commands
 * @sh_data: Struct structure for shell information
 * @the_buffer: buffer address
 * @l_length: length variable
 *
 * Return: number of bytes read
 */
ssize_t loving_input_buffer(Shell_pack *sh_data, char **the_buffer,
size_t *l_length)
{
	ssize_t _bytes_read = 0;
	size_t figure = 0;

	if (!*l_length)
	{
		free(*the_buffer);

		*the_buffer = NULL;

		signal(SIGINT, do_get_sigint);

		_bytes_read = getline(the_buffer, &figure, stdin);

		if (_bytes_read > 0)
		{
			if ((*the_buffer)[_bytes_read - 1] == '\n')
			{
				(*the_buffer)[_bytes_read - 1] = '\0'; /* this removes newline */
				_bytes_read = _bytes_read - 1;
			}

			sh_data->sh_line_no = 1;

			remove_comments(*the_buffer);

			{
				*l_length = _bytes_read;
				sh_data->sh_cmd = the_buffer;
			}
		}
	}

	return (_bytes_read);
}

/**
 * remove_comments - function replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 *
 * Return: Always 0;
 */
void remove_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}

/**
 * do_accept_input - gets input from command line
 * using getline, and removing the new line character
 * @sh_data: Struct structure for shell information
 *
 * Return: number of bytes read
 */
ssize_t do_accept_input(Shell_pack *sh_data)
{
	static char *the_buffer;
	static size_t e, f, l_length;
	ssize_t _read = 0;
	char **temp_buff, *temp;

	temp_buff = &(sh_data->sh_input);

	_read = loving_input_buffer(sh_data, &the_buffer, &l_length);

	if (_read == -1) /* EOF */
		return (-1);

	if (l_length != 0)
	{
		f = e;
		temp = the_buffer + e;

		cmd_link_check(sh_data, the_buffer, &f, e, l_length);

		while (f < l_length)
		{
			if (is_link_char(sh_data, the_buffer, &f))
				break;
			f++;
		}
		e = f + 1;

		if (e >= l_length)
		{
			e = l_length = 0;
			sh_data->sh_cmd_type = 0;
		}
		*temp_buff = temp;

		return (makeshift_strlen(temp));
	}

	*temp_buff = the_buffer;

	return (_read);
}

/**
 * cmd_link_check - checks if chain should be continued
 * based on previous status
 * @sh_data: Struct structure for shell information
 * @the_buffer: character buffer
 * @cur_p: current position address
 * @start: starting position in character buffer
 * @l_length: length of the_buffer
 *
 * Return: Void
 */
void cmd_link_check(Shell_pack *sh_data, char *the_buffer,
size_t *cur_p, size_t start, size_t l_length)
{
	size_t fig;

	fig = *cur_p;

	if (sh_data->sh_cmd_type == 2)
	{
		if (sh_data->sh_status)
		{
			the_buffer[start] = 0;
			fig = l_length;
		}
	}

	if (sh_data->sh_cmd_type == 1)
	{
		if (!sh_data->sh_status)
		{
			the_buffer[start] = 0;
			fig = l_length;
		}
	}

	*cur_p = fig;
}

/**
 * is_link_char - checks if character in buffer is a link delimeter
 * @sh_data: the parameter struct
 * @the_buffer: the char buffer
 * @cur_p: address of current position in the_buffer
 *
 * Return: 1 if chain is seen; 0 otherwise
 */
int is_link_char(Shell_pack *sh_data, char *the_buffer, size_t *cur_p)
{
	size_t j;

	j = *cur_p;

	if (the_buffer[j] == '|' && the_buffer[j + 1] == '|')
	{
		the_buffer[j] = 0;
		j++;
		sh_data->sh_cmd_type = 1;
	}

	else if (the_buffer[j] == '&' && the_buffer[j + 1] == '&')
	{
		the_buffer[j] = 0;
		j++;
		sh_data->sh_cmd_type = 2;
	}

	else if (the_buffer[j] == ';')
	{
		the_buffer[j] = 0;
		sh_data->sh_cmd_type = 3;
	}
	else
		return (0);

	*cur_p = j;

	return (1);
}
