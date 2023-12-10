#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <signal.h>
#include <limits.h>

#define THE_BUFFER_SIZE 1024
#define TOKEN_SPACE 128
#define OGA_DELIMITERS "\t\r\n\a"

/* environment accessed from global variable environ */
extern char **environ;

/**
 * struct data_pack - data for child process
 * @sh_argv: arguments
 * @sh_input: input to be taken from command line
 * @sh_arguments: args
 * @sh_environ: environment variables
 * @sh_pid: pid of child process
 * @sh_status: status of process
 * @sh_count: counting number of processes intialized
*/
typedef struct data_pack
{
	char **sh_argv;
	char *sh_input;
	char **sh_arguments;
	char **sh_environ;
	char *sh_pid;
	int sh_status;
	int sh_count;
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

/* FUNCTIONS*/
void run_shell(Shell_pack *sh_data);

void makeshift_printf(const char *the_string);
int makeshift_strncmp(const char *string_a,
const char *string_b, size_t n_char);
char *makeshift_strcat(const char *command);
char *_makeshift_strcat(char *destination, const char *source);
char *makeshift_strchr(char *the_str, char the_char);
int makeshift_strlen(const char *string);
char *makeshift_strcpy(char *destination, char *source);
char *makeshift_strdup(char *string);
int makeshift_atoi(char *string);
char *makeshift_itoa(int integer);
int makeshift_cmpchr(char *the_str, const char *the_delim);
char *makeshift_strtok(char *the_str, const char *the_delim);
int makeshift_isdigit(const char *the_char);
void do_get_sigint(int integer);

int validate_command(const char *command);
char *fuse_commands(const char *command);
void copy_commands(char *full_command, const char *command, char *found_path);
int validate_path(char *path_n_cmd);
char **do_tokenize_PATH(void);
int do_split(char *delim_args[], char *input);

char *do_accept_input(void);
int check_for_env(char *command, char **argv, char **env);
int do_prompt_exec(char *input, Shell_pack *sh_data);
void do_fork_exec(char *input, char **exec_args, Shell_pack *sh_data);
void do_free_allocs(Shell_pack *sh_data);
int do_set_data(Shell_pack *sh_data, char **argv);

/* functions for custom getline*/
int allocate_buffer(char **buffer, size_t size);
ssize_t makeshift_getline(char **user_input, size_t *num, FILE *file_desc);
char *another_getline();

/* the environment family*/
int makeshift_unsetenv(Shell_pack *sh_data);
char *makeshift_getenv(char *env_var, char ***env);
int makeshift_setenv(Shell_pack *sh_data);
char **makeshift_realloc_setenv(char **old_block, unsigned int _o_size,
unsigned int _n_size);
char *data_copy_setenv(char *env_var, char *env_val);

/* function for checking for builtin commands*/
int check_for_builtins(Shell_pack *sh_data);

/* the builtins*/
int exit_builtin(Shell_pack *sh_data);
int env_builtin(Shell_pack *sh_data);
int cd_builtin(Shell_pack *sh_data);
int echo_builtin(Shell_pack *sh_data);

/* Error functions*/
int do_handle_errors(Shell_pack *sh_data, int return_val);
void err_for_environ(Shell_pack *sh_data);
void err_for_not_found(Shell_pack *sh_data);
void err_for_exit(Shell_pack *sh_data);

#endif /* SHELL_H */
