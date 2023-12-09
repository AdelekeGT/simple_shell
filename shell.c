#include "shell.h"

/**
 * main - main function that executes shell
 * @argc: number of arguments
 * @argv: pointer to array of pointers to string arguments
 *
 * Return: status
*/
int main(int argc, char **argv)
{
	Shell_pack sh_data;
	(void)argc;

	signal(SIGINT, do_get_sigint);
	do_set_data(&sh_data, argv);
	run_shell(&sh_data);

	if (sh_data.sh_status < 0)
	{
		do_free_allocs(&sh_data);
		return (127);
	}

	do_free_allocs(&sh_data);

	return (sh_data.sh_status);
}
