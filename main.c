#include "shell.h"

/**
 * main - starting point of the program
 * @ac: number of arguments passed to ./hsh
 * @av: argument vector
 *
 * Return: 0 on success of initialization
 */
int main(int ac, char **av)
{
	Shell_pack sh_data[] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, NULL,
	NULL, NULL, NULL, NULL, NULL, NULL}};
	(void)ac;

	do_load_envs(sh_data);

	run_shell(sh_data, av);

	return (EXIT_SUCCESS);
}
