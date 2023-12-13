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

	do_free_allocs(&sh_data);

	if (sh_data.sh_status < 0)
		return (255);

	return (sh_data.sh_status);
}
