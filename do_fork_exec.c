#include "shell.h"

/**
 * do_fork_exec - calls the fork system call
 * @input: input from command line
 * @exec_args: validated arguments
 * @sh_data: shell data
*/
void do_fork_exec(char *input, char **exec_args, Shell_pack *sh_data)
{
	pid_t the_pid;
	int execve_status, wait_status;

	the_pid = fork();
	if (the_pid < 0)
	{
		free(input);
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (the_pid == 0)
	{
		execve_status = execve(exec_args[0], exec_args, NULL);

		if (execve_status == -1)
		{
			write(STDERR_FILENO, "./hsh : 1: ", 11);
			write(STDERR_FILENO, sh_data->sh_argv[0],
			makeshift_strlen(sh_data->sh_argv[0]));
			write(STDERR_FILENO, ": not found\n", 12);
			sh_data->sh_status = 127;
			exit(2);
		}
	}
	else
	{
		wait(&wait_status);
	}
}
