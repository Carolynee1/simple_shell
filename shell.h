#ifndef __SHELL_H__
#define __SHELL_H__

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/*for read/write buffers */
#define READ_BUF_SIZE 2048
#define WRITE_BUF_SIZE 2048
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE ".my_simple_shell-history"
#define HIST_MAX   4096\

extern char **environ;

/**
 * struct liststr -singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
}
list_t;

/**
 * struct passinfo - contains pseudo-arguments to pass into a function.
 * @arg: a string generated from getline containing arguments
 * @agrv: an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: The argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @line_count_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ
 * @history: the history node
 * @env_changed: on if environ was changed
 * @status: the return status of the last executed command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&,;
 * @readfd: the fd from which to read line input 
 * @histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int line_count_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;
char **cmd_buf;/*pointer to cmd: chain buffer for memmory management*/
	int cmd_buf_type; /* CMD_type ||, &&, */
	int readfd;
	int hiscount;
}info_t;
#define INFO_INIT \{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL,\ 0, 0, 0}

/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
}builtin_table;

/* Caro&Josh_shloop.c */ 
/*These function declaration are part of the shloop.c file, they are related to the main loop and execution of commands in the shell */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/* Caro&Josh_parser.c */
/* These functions are relating to the parsing and handling commands within the shell */
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/* loophsh.c */
/* this function is likely the entry point or the main function for the shell program */
int loophsh(char **);

/* Caro&Josh_errors.c */
/*They likely provide error handling and printing functions. */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* Caro&Josh_string.c */
/*They likely provide various string manipulation functions */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* Caro&Josh_string1.c */
/* they likely provide additional string manipulation functions.*/
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* Caro&josh_exits.c */
/* they provide functions related th string operations and manipulation,*/
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* Caro&Josh_tokenizer.c */
/* this is relating to the string tokenization */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* Caro&Josh_realloc.c 
 * this is for memory management and reallocation */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* Caro&Josh_memory.c
 * This for memory deallocation */
int bfree(void **);

/* Caro&Josh_atoi.c 
 * this is for string manipulations and conversion.*/
int interactive(info_t *);
int is_delim(char, char *);
int _isaplha(int);
int _atoi(char *);

/* Caro&Josha_errors1.c
 * this is also for error handling and string manipulation.*/
int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* Caro&Josh_builtin.c
 * this is for the built-in shell commands.*/
int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);

/* Caro&Josh_builtin1.c
 * these are additional functions for the built-in shell commands*/
int _myhistory(info_t *);
int _myalias(info_t *);

/* Caro&Josh_getline.c
 * this handles reading user input from the command line*/
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/* Caro&Josh_getinfo.c
 * this involves managing and manipulating the 'info_t' structure, which stores information about the shell.*/
void init_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/* Caro&Josh_environ.c
 * It handles environment related operations and built-in commands
 * related to environment variables*/
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);

/* Caro&Josh_getenv.c
 * this provides additional funcions for managing environment variables*/
char **get_environ(info_t *);
int _unset_env_var(info_t *, char *);
int _set_env_var(info_t *, char *, char *);

/* Caro&Josh_history.c
 * this handles the history feature of the shell,
 * and allows storing and retrieving previously executed commands*/
char *get_history_fil(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int line_count);
int renumber_history(info_t *info);

/* Caro&Josh_lists.c
 * This provides function for manipulating linked lists.*/
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* Caro&Josh_lists1.c
 * this provides additional functions for manipulating linked lists*/
size_t List_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *,list_t *);

/* Caro&Josh_vars.c
 * This is for handling variable substitution and string replacement.*/
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

#endif
