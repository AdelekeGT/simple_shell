#include "shell.h"

/**
 * _do_fork_exec - execute fork() system call
 * @sh_data: Struct structure for shell information
 */
void _do_fork_exec(Shell_pack *sh_data)
{
	pid_t the_pid;

	the_pid = fork();

	if (the_pid < 0)
	{

		perror("Error:");
		return;
	}

	if (the_pid == 0)
	{
		if (execve(sh_data->sh_path, sh_data->sh_arguments,
		do_copy_environ(sh_data)) == -1)
		{
			_do_free_allocs1(sh_data);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(sh_data->sh_status));
		if (WIFEXITED(sh_data->sh_status))
		{
			sh_data->sh_status = WEXITSTATUS(sh_data->sh_status);
			if (sh_data->sh_status == 126)
				do_handle_errors(sh_data, 126);
		}
	}
}
