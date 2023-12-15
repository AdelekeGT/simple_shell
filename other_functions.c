#include "shell.h"

/**
 * _cmd_is_valid - determines if a file is an executable command
 * @sh_data: Struct structure for shell information
 * @path: file path
 *
 * Return: 1 if true, 0 otherwise
 */
int _cmd_is_valid(Shell_pack *sh_data, char *path)
{
	struct stat st;

	(void)sh_data;
	if (path == NULL || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}

	return (0);
}

/**
 * copy_copy - makes duplicates of characters
 * @the_str: PATH string
 * @beginning: index to start
 * @conclude: index to stop
 *
 * Return: pointer to brand new buffer
 */
char *copy_copy(char *the_str, int beginning, int conclude)
{
	int _ind = 0, _in = 0;
	static char the_buffer[1024];

	for (_in = 0, _ind = beginning; _ind < conclude; _ind++)
	{
		if (the_str[_ind] != ':')
			the_buffer[_in++] = the_str[_ind];

	}

	the_buffer[_in] = 0;

	return (the_buffer);
}

/**
 * validate_PATH - validates a path in PATH
 * @sh_data: the sh_data struct
 * @the_str: the PATH string
 * @command: the command to find
 *
 * Return: full path of command if found or NULL
 */
char *validate_PATH(Shell_pack *sh_data, char *the_str, char *command)
{
	int _ind = 0, position_now = 0;
	char *_PATH;

	if (the_str == NULL)
		return (NULL);

	if ((makeshift_strlen(command) >= 3) && starts_with(command, "./"))
	{
		if (_cmd_is_valid(sh_data, command))
			return (command);
	}

	while (true)
	{
		if (the_str[_ind] == 0 || the_str[_ind] == ':')
		{
			_PATH = copy_copy(the_str, position_now, _ind);

			if (!*_PATH)
				makeshift_strcat(_PATH, command);
			else
			{
				makeshift_strcat(_PATH, "/");
				makeshift_strcat(_PATH, command);
			}

			if (_cmd_is_valid(sh_data, _PATH))
				return (_PATH);

			if (the_str[_ind] == 0)
				break;

			position_now = _ind;
		}
		_ind++;
	}

	return (NULL);
}

/**
 * starts_with - checks if item starts with basket
 * @basket: string to search
 * @item: the substring to find
 *
 * Return: address of next char of basket or NULL
 */
char *starts_with(const char *basket, const char *item)
{
	int iterator;

	iterator = 0;
	while (item[iterator] != '\0')
	{
		if (item[iterator] != basket[iterator] || basket[iterator] == '\0')
			return (NULL);

		iterator++;
	}

	return ((char *)basket);
}


/**
 * delimiter_confirm - checks if character is a delimeter
 * @the_char: character
 * @the_delim: the delimeter string
 * Return: 1 if true, 0 if false
 */
int delimiter_confirm(char the_char, char *the_delim)
{
	int iterator;

	iterator = 0;
	while (the_delim[iterator] != '\0')
	{
		if (the_delim[iterator] == the_char)
			return (1);

		iterator++;
	}

	return (0);
}
