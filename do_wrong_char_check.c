#include "shell.h"

/**
 * check_for_wrong_input_char - checks for characters not allowed
 * @sh_data: data from Shell_pack
 * @the_input: input from command line
 *
 * Return: 0 on success; 1 otherwise
 */
int check_for_wrong_input_char(Shell_pack *sh_data, char *the_input)
{
	int ch_start = 0, ch_first = 0, _ind = 0;

	ch_first = check_1st_char(the_input, &ch_start);
	if (ch_first == -1)
	{
		err_for_wrong_input_char(sh_data, the_input, 0, ch_start);
		return (8);
	}

	_ind = check_some_chars(the_input + ch_start, 0, *(the_input + ch_start));
	if (_ind != 0)
	{
		err_for_wrong_input_char(sh_data, the_input, 1, ch_start + _ind);
		return (8);
	}

	return (0);
}

/**
 * check_1st_char - checks the first character in the input passed in
 * @the_input: input from command line
 * @_ind: index
 *
 * Return: 0 on success; -1 otherwise
 */
int check_1st_char(char *the_input, int *_ind)
{
	for (*_ind = 0; the_input[*_ind]; *_ind += 1)
	{
		if (the_input[*_ind] == ' ' || the_input[*_ind] == '\t')
			continue;

		if (the_input[*_ind] == ';' || the_input[*_ind] == '|' ||
		the_input[*_ind] == '&')
			return (-1);

		break;
	}

	return (0);
}

/**
 * check_some_chars - checks for some chars; space, \t
 * @the_input: input from user
 * @_ind: index
 * @end_char: last character at that point
 *
 * Return: recursively return the check_some_chars function
 */
int check_some_chars(char *the_input, int _ind, char end_char)
{
	int count, _c;

	count = 0;
	if (*the_input == '\0')
		return (0);

	if (*the_input == ' ' || *the_input == '\t')
		return (check_some_chars(the_input + 1, _ind + 1, end_char));

	if (*the_input == ';')
		if (end_char == '|' || end_char == '&' || end_char == ';')
			return (_ind);
	if (*the_input == '|')
	{
		if (end_char == ';' || end_char == '&')
			return (_ind);

		if (end_char == '|')
		{
			_c = 0;
			count = char_over_and_over(the_input, _c);
			if (count == 0 || count > 1)
				return (_ind);
		}
	}
	if (*the_input == '&')
	{
		if (end_char == ';' || end_char == '|')
			return (_ind);

		if (end_char == '&')
		{
			_c = 0;
			count = char_over_and_over(the_input, _c);
			if (count == 0 || count > 1)
				return (_ind);
		}
	}

	return (check_some_chars(the_input + 1, _ind + 1, *the_input));
}

/**
 * char_over_and_over - checks for characters repeated in the the_input
 * @the_input: input passed in through command line
 * @_c: integer count
 *
 * Return: _c
 */
int char_over_and_over(char *the_input, int _c)
{
	if (*(the_input - 1) == *the_input)
		return (char_over_and_over(the_input - 1, _c + 1));

	return (_c);
}

/**
 * err_for_wrong_input_char - prints error message
 * @sh_data: data from Shell_pack
 * @the_input: input from command line
 * @_ind: index
 * @val: some boolean value for evaluation
 */
void err_for_wrong_input_char(Shell_pack *sh_data, char *the_input,
int val, int _ind)
{
	char *a_msg, *b_msg, *c_msg, *full_error_msg, *err_count;
	int _len;

	if (the_input[_ind] == ';')
	{
		if (val == 0)
			a_msg = (the_input[_ind + 1] == ';' ? ";;" : ";");
		else
			a_msg = (the_input[_ind - 1] == ';' ? ";;" : ";");
	}
	if (the_input[_ind] == '|')
		a_msg = (the_input[_ind + 1] == '|' ? "||" : "|");

	if (the_input[_ind] == '&')
		a_msg = (the_input[_ind + 1] == '&' ? "&&" : "&");

	b_msg = ": Syntax error: \"";
	c_msg = "\"unexpected\n";
	err_count = makeshift_itoa(sh_data->sh_count);
	_len = makeshift_strlen(sh_data->sh_arguments[0]) +
	makeshift_strlen(err_count) + makeshift_strlen(a_msg) +
	makeshift_strlen(b_msg) + makeshift_strlen(c_msg) + 2;

	full_error_msg = malloc(sizeof(char) * (_len + 1));
	if (full_error_msg == NULL)
	{
		free(err_count);
		return;
	}
	makeshift_strcpy(full_error_msg, sh_data->sh_arguments[0]);
	_makeshift_strcat(full_error_msg, ": ");
	_makeshift_strcat(full_error_msg, err_count);
	_makeshift_strcat(full_error_msg, b_msg);
	_makeshift_strcat(full_error_msg, a_msg);
	_makeshift_strcat(full_error_msg, c_msg);
	_makeshift_strcat(full_error_msg, "\0");

	write(STDERR_FILENO, full_error_msg, _len);
	free(full_error_msg);
	free(err_count);
}
