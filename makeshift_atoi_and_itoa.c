#include "shell.h"

/**
 * makeshift_atoi - custom atoi function
 * @string: string to be converted
 *
 * Return: int convert
 */

int makeshift_atoi(char *string)
{
	unsigned int _idx = 0;
	unsigned int sign = 1;
	unsigned int _result = 0;

	if (string == NULL)
		return (0);

	while (string[_idx] != '\0')
	{
		if (string[_idx] == '-')
		{
			sign *= -1;
		}
		else if (string[_idx] >= '0' && string[_idx] <= '9')
		{
			while (string[_idx] >= '0' && string[_idx] <= '9')
			{
				_result = _result * 10 + (string[_idx] - '0');
				_idx++;
			}
			return (_result * sign);
		}
		_idx++;
	}
	return (0);
}

/**
 * makeshift_itoa - custom itoa function
 * @integer: integer to be converted to string
 *
 * Return: string convert
 */
char *makeshift_itoa(int integer)
{
	char *int_buffer, temp;
	int base = 10, i = 0, is_negative = 0, remainder, start, end;

	int_buffer = malloc(20 * sizeof(char));
	if (int_buffer == NULL)
		return (NULL);
	/* Handle 0 explicitly, otherwise empty string is returned */
	if (integer == 0)
	{
		int_buffer[i++] = '0';
		int_buffer[i] = '\0';
		return (int_buffer);
	}
	/* Handle negative numbers for non-decimal bases */
	if (integer < 0 && base != 10)
	{
		is_negative = 1;
		integer = -integer;
	}
	while (integer != 0) /* Process individual digits */
	{
		remainder = integer % base;
		int_buffer[i++] = (remainder > 9) ? (remainder - 10) + 'a' : remainder + '0';
		integer = integer / base;
	}
	if (is_negative && base != 10) /* Add negative sign for non-decimal bases */
		int_buffer[i++] = '-';
	int_buffer[i] = '\0';
	/* Reverse the string */
	start = 0;
	end = i - 1;
	while (start < end)
	{
		temp = int_buffer[start];
		int_buffer[start] = int_buffer[end];
		int_buffer[end] = temp;
		start++;
		end--;
	}
	return (int_buffer);
}
