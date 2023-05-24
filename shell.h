#ifndef shell_h
#define shell_h

#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#define CMD_CHAIN 3
#define CMD_AND 2
#define CMD_OR 1
#define CMD_NORM 0
#define BUF_FLUSH -1
#define WRITE_BUF_SIZE 1024
#define READ_BUF_SIZE 1024
#define USE_STRTOK 0
#define USE_GETLINE 0
#define HIST_MAX 4096
#define HIST_FILE ".simple_shell_history"
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

extern char **environ;

/**
 * struct liststr -> a list
 * @num: number
 * @str: string of characters
 * @next: pointer to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct builtin -> handles builtin functions
 * @type: builtin commands
 * @func: function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

/**
 * struct passinfo -> maintains argument format
 * @arg: arguments passed
 * @path: full path for command
 * @argv: array of arguments passed
 * @fname: filename
 * @environ: environment
 * @argc: number of arguments passed
 * @err_num: errno
 * @linecount_flag: line count
 * @line_count: errno count
 * @env_changed: checks for change in env
 * @status: return status
 * @env: list
 * @history: previous node
 * @alias: next node
 *
 * @histcount: history count
 * @cmd_buf: command buffer
 * @cmd_buf_type: or or and
 * @readfd: file descriptor from input
 */
typedef struct passinfo
{
	char *arg;
	char *path;
	char **argv;
	char *fname;
	char **environ;
	int argc;
	int err_num;
	int linecount_flag;
	unsigned int line_count;
	int env_changed;
	int status;
	list_t *env;
	list_t *history;
	list_t *alias;

	int histcount;
	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

void find_cmd(info_t *);
void fork_cmd(info_t *);
int hsh(info_t *, char **);
int find_builtin(info_t *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);
int is_cmd(info_t *, char *);
int loophsh(char **);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);
void _eputs(char *);
int _eputchar(char);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);
int _strlen(char *);
int _strcmp(char *, char *);
void _puts(char *);
int _putchar(char);
char *_strcpy(char *, char *);
char *_strdup(const char *);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);
char *_strncpy(char *, char *, int);
char **strtow2(char *, char);
char **strtow(char *, char *);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);
char *_memset(char *, char, unsigned int);
int bfree(void **);
int _isalpha(int);
int _atoi(char *);
int interactive(info_t *);
int is_delim(char, char *);
char *convert_number(long int, int, int);
void remove_comments(char *);
void print_error(info_t *, char *);
int print_d(int, int);
int _erratoi(char *);
int _mycd(info_t *);
int _myhelp(info_t *);
int _myexit(info_t *);
int _myalias(info_t *);
int _myhistory(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);
ssize_t get_input(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);
void clear_info(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);
char *get_history_file(info_t *info);
int write_history(info_t *info);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);

#endif
