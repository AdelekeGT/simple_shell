#include "shell.h"

/**
 * gimme_clean_slate - Does the initialization of sh_data struct
 * @sh_data: & of struct
 */
void gimme_clean_slate(Shell_pack *sh_data)
{
	sh_data->sh_input = NULL;

	sh_data->sh_arguments = NULL;

	sh_data->sh_path = NULL;

	sh_data->arg_cnt_cmd_line = 0;
}
