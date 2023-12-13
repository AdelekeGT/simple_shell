#include "shell.h"

/**
 * do_get_sigint - controls CntrlC
 * @signal: signal
*/
void do_get_sigint(int signal)
{
	(void)signal;
	makeshift_printf("\n^-^ ");
}
