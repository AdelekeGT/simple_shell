#include "shell.h"

/**
 * makeshift_printf - custom printf for me
 * @the_string: string/message to be printed
*/
void makeshift_printf(const char *the_string)
{
	write(STDOUT_FILENO, the_string, makeshift_strlen(the_string));
}
