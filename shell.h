#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <stdbool.h>

#define OGA_DELIMS " \t\r\n\a"

extern char **environ;


/**
 * struct node_lt - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct node_lt
{
	struct node_lt *next;
	char *str;
	int num;
} sh_list;

/**
 *struct data_pack - Uniform struct
 *@sh_input: input string from GETLINE
 *@sh_arguments: an array of strings generated from sh_input
 *@sh_path: a string sh_path for the current command
 *@arg_cnt_cmd_line: the argument count from getline
 *@sh_count: the error count
 *@sh_err_no: the error code for exit()s
 *@sh_line_no: counts line of input
 *@sh_fname: name of file passed at command line
 *@sh_env: copy of environ in a linked list
 *@sh_environ: linked list of environment variables
 *@modified_env: counter for change in environment if it happens
 *@sh_status: return status of last process echo$?
 *@sh_cmd: ointer to command
 *@sh_cmd_type: ||, &&, ;
 *@readfd: read from file
 *@sh_h_count: the history line number count
 */
typedef struct data_pack
{
	int sh_err_no;
	int arg_cnt_cmd_line;
	int modified_env;
	int sh_status;
	int sh_cmd_type;
	int readfd;
	int sh_h_count;
	int sh_line_no;
	unsigned int sh_count;
	char *sh_fname;
	char *sh_path;
	char *sh_input;
	sh_list *sh_env;
	char **sh_arguments;
	char **sh_environ;
	char **sh_cmd;
} Shell_pack;

/**
 * struct builtin_execs - struct for built-in commands
 * @command: name of built-in command
 * @builtin_func: function corresponding to the built-in command
*/
typedef struct builtin_execs
{
	char *command;
	int (*builtin_func)(Shell_pack *sh_data);
} Builtin_execs;


/* _check_for_builtins.c */
int _check_for_builtins(Shell_pack *sh_data);


/* A_built_builtins.c */
int built_env(Shell_pack *sh_data);
int built_exit(Shell_pack *sh_data);
char *built_getenv(Shell_pack *sh_data, const char *env_var);


/* annoying_nodes_A.c */
size_t print_list_str(const sh_list *pointer);
char **get_strings_from_list(sh_list *n_head);
int remove_node_4_index(sh_list **n_head, unsigned int index);
void do_free_list(sh_list **the_head);
size_t length_of_list(const sh_list *n_h);


/* annoying_nodes_B.c */
size_t print_list(const sh_list *n_h);
sh_list *put_node(sh_list **n_head, const char *str, int num);
sh_list *put_node_4_end(sh_list **n_head, const char *str, int num);
ssize_t get_node_index(sh_list *n_head, sh_list *n_node);
sh_list *commencement_of_node(sh_list *n_node, char *prefix, char chr);


/* B_built_builtins.c */
int do_load_envs(Shell_pack *sh_data);
int built_setenv(Shell_pack *sh_data);
int _helper_setenv(Shell_pack *sh_data, char *env_var, char *env_value);
int built_unsetenv(Shell_pack *sh_data);
int _helper_unsetenv(Shell_pack *sh_data, char *env_var);


/* do_copy_environ.c */
char **do_copy_environ(Shell_pack *sh_data);


/* do_free_allocs_0_n_1.c */
void _do_free_allocs0(Shell_pack *sh_data);
void _do_free_allocs1(Shell_pack *sh_data);


/* do_get_sigint.c */
void do_get_sigint(int signal);


/* do_handle_errors.c */
int do_handle_errors(Shell_pack *sh_data, int return_val);
void err_for_environ(Shell_pack *sh_data);
void err_for_not_found(Shell_pack *sh_data);
void err_for_exit(Shell_pack *sh_data);
void err_permission(Shell_pack *sh_data);


/* err_write.c */
void err_write(const char *the_string);


/* get_input_family.c */
ssize_t loving_input_buffer(Shell_pack *sh_data, char **the_buffer,
size_t *len);
void remove_comments(char *);
ssize_t do_accept_input(Shell_pack *sh_data);
void cmd_link_check(Shell_pack *sh_data, char *the_buffer,
size_t *cur_p, size_t start, size_t l_length);
int is_link_char(Shell_pack *sh_data, char *the_buffer, size_t *cur_p);


/* gimme_clean_slate.c */
void gimme_clean_slate(Shell_pack *sh_data);


/* initialize_struct.c */
void initialize_struct(Shell_pack *sh_data, char **av);


/* the string functions.c */
char **makeshift_strtow(char *the_str, char *the_delim);
char *makeshift_strdup(const char *string);
void *makeshift_memset(void *n_ptr, int value, size_t n_num);
char *makeshift_strcpy(char *destination, char *source);
char *makeshift_strcat(char *destination, const char *source);
int makeshift_strlen(const char *string);
int makeshift_strcmp(char *string_a, char *string_b);
int makeshift_strncmp(const char *string_a, const char *string_b,
size_t n_char);
void makeshift_printf(const char *the_string);
int makeshift_strlen(const char *string);
int makeshift_atoi(char *string);
char *makeshift_itoa(int integer);


/* memory_freers.c */
int ptr_freer(void **the_ptr);
void _free_str_array(char **the_arr);


/* other_functions.c */
int _cmd_is_valid(Shell_pack *sh_data, char *sh_path);
char *copy_copy(char *the_str, int beginning, int conclude);
char *validate_PATH(Shell_pack *sh_data, char *the_str, char *command);
char *starts_with(const char *basket, const char *item);
int delimiter_confirm(char the_char, char *the_delim);


/* run_shell.c */
int run_shell(Shell_pack *, char **);
void validate_cmd(Shell_pack *sh_data);

/* _do_fork_exec.c */
void _do_fork_exec(Shell_pack *sh_data);

#endif /* SHELL_H */
