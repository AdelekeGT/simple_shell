#include "shell.h"

/**
 * run_shell - function runs shell
 * @sh_data: data from shell
*/
void run_shell(Shell_pack *sh_data)
{
	char *the_input;
	int prompt_return_value;

	while (true)
	{
		/*check if file is connected to terminal for taking input*/
		if (isatty(STDIN_FILENO))
			makeshift_printf("$ ");

		the_input = do_accept_input();

		if (the_input == NULL)
		{
			free(the_input);
			continue;
		}
		sh_data->sh_input = the_input;

		/*execute the prompt; here lies fork() and execve()*/
		/* here also lies validation of commmand from user input*/
		/* here also lies checking if input is builtin command*/
		prompt_return_value = do_prompt_exec(the_input, sh_data);
		if (prompt_return_value == 1)
			break;

		if (prompt_return_value == 0)
			sh_data->sh_status = 0;
	}

}
