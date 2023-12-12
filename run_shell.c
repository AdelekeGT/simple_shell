#include "shell.h"

/**
 * run_shell - function runs shell
 * @sh_data: data from shell
*/
void run_shell(Shell_pack *sh_data)
{
	char *the_input;
	int prompt_return_value, h = 12;
	ssize_t get_ret;

	while (h == 12)
	{
		if (isatty(STDIN_FILENO))
			makeshift_printf("$ ");
		the_input = do_accept_input(&get_ret);
		if (get_ret != -1)
		{
			if (*the_input == '\n')
			{
				free(the_input);
				continue;
			}
			the_input = do_comments_check(the_input);
			if (the_input == NULL)
				continue;
			if (check_for_wrong_input_char(sh_data, the_input) == 8)
			{
				sh_data->sh_status = 2;
				free(the_input);
				continue;
			}
			sh_data->sh_input = the_input;
			prompt_return_value = do_prompt_exec(the_input, sh_data);
			if (prompt_return_value == 1)
				break;
			sh_data->sh_count += 1;
			sh_data->sh_status = prompt_return_value;
		} else
		{
			h = 0;
			free(the_input);
		}
	}
}
