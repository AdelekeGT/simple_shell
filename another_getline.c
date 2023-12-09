#include "shell.h"
#define BUFFER_SIZE 512

/**
 * another_getline - custom getline function that accepts user input
 * Return: pointer to string read in
*/
char *another_getline()
{
	static char the_buffer[BUFFER_SIZE];
	static size_t _index, _read_bytes;
	size_t _ind = 0;
	char *ext_input;

	_index = 0;
	_read_bytes = 0;
	ext_input = (char *)malloc(BUFFER_SIZE);
	if (ext_input == NULL)
		return (NULL);

	while (1)
	{
		if (_index >= _read_bytes)
		{
			_index = 0;
			_read_bytes = read(STDIN_FILENO, the_buffer, BUFFER_SIZE);
			if (_read_bytes <= 0)
			{
				if (_ind == 0)
				{
					free(ext_input);
					return (NULL); /* No input read */
				}
			}
		}

		/* Do a copy of characters from the buffer to the line */
		while (_index < _read_bytes && the_buffer[_index] != '\n')
			ext_input[_ind++] = the_buffer[_index++];

		if (_index < _read_bytes && the_buffer[_index] == '\n')
		{
			ext_input[_ind++] = the_buffer[_index++];
			break; /* if it finds end of line */
		}
	}

	ext_input[_ind] = '\0';
	return (ext_input);
}
