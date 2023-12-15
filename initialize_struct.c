#include "shell.h"

/**
 * initialize_struct - Does initialization of Shell_pack struct
 * @sh_data: & of struct
 * @av: pointer to argument strings
 */
void initialize_struct(Shell_pack *sh_data, char **av)
{
	int init = 0;

	sh_data->sh_fname = av[0];
	if (sh_data->sh_input)
	{
		sh_data->sh_arguments = makeshift_strtow(sh_data->sh_input, OGA_DELIMS);
		if (!sh_data->sh_arguments)
		{

			sh_data->sh_arguments = malloc(sizeof(char *) * 2);
			if (sh_data->sh_arguments)
			{
				sh_data->sh_arguments[0] = makeshift_strdup(sh_data->sh_input);
				sh_data->sh_arguments[1] = NULL;
			}
		}
		for (init = 0; sh_data->sh_arguments && sh_data->sh_arguments[init]; init++)
			;
		sh_data->arg_cnt_cmd_line = init;
	}
}
