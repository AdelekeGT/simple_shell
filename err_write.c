#include "shell.h"

/**
 * err_write - custom printf for writing errors
 * @the_string: string/message to be printed
*/
void err_write(const char *the_string)
{
	write(STDERR_FILENO, the_string, makeshift_strlen(the_string));
}
