#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <errno.h>
#include <fcntl.h>
#include <syslog.h>
#include <unistd.h>
#include <stdbool.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "limits.h"

#include "myquote.h"
#include "dictionary.h"
#include "shell_path.h"

/**STRING PROTOTYPES**/
char *_strcat(char *dest, const char *src);
ssize_t _memchr(const void *s, int c, size_t n);
int _strcmp(const char *s1, const char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);
bool _isspace(int c);
char *_strdup(const char *str);
char *_strstr(const char *haystack, const char *needle);
void *_memcpy(void *dest, const void *src, size_t n);
void *_realloc(void *buffer, size_t old_size, size_t new_size);
size_t _strlen(const char *s);
char *_strcpy(char *dest, const char *src);
bool _isquote(int c);
void *_memdup(const void *str, size_t n);
ssize_t find_char_in_str(const char *str, char ch, size_t size);
ssize_t _strchr(const char *s, int c);
char **duplicateStringArray(char **array);
bool _isdigit(int c);
bool is_numeric(const char *str);
unsigned int my_atoi(char *str);
void handle_ctrl_c(int sig __attribute__((unused)));
extern char **environ;

/**SHELL ERROR**/
void printerror(char **av, int count, char **arg);
int write_error_stderr(int error);
void handle_error(const char *av, size_t linenum, const char *error_m, ...);

/**SHELL HELPER**/
void free_all(const unsigned int n, ...);

/**
 * store_info - store shell information
 * @argv: argument
 * @argc: argument counter
 * @interactive: shell interactive
 * @fileno: fileno
 * @file: file
 * @error: error
 * @status: status
 */
typedef struct store_info
{
	int interactive;
	int argc;
	int status;
	int error;
	int fileno;
	char **argv;
	char *file;
	char *line;
	char **tokens;
	size_t line_read;
	pid_t p_pid;
	char *cwd_s;
	char *execute;
	shell_dict_s *env;
	directory_n *path;
	command_lst *cmd;
} store_info_t;

store_info_t *init_prmpt(char **av, int ac);
bool read_usr_input(store_info_t *input_info);
int release_store_information(store_info_t *store_info);
int executeShellCommand(store_info_t *shell_info);
int exec_init(store_info_t *shell_info);

/******STRING******/
char *str_concat(size_t *len, const char *delim,
		const char *prev, const char *next);

/******COMMAND TO SPLIT FUNCTION*****/

typedef struct error
{
	char *buf;
	size_t len;
	char *linenum_error;
	const char *str_ret;
} error_s;
char *convert_str(size_t n);

/**
 * struct atoi - Represents state information for converting
 * strings to integers
 * @num: The accumulated integer value
 * @curr_digit: The current digit being processed
 * @iterator: The iterator
 * This structure is used for tracking the state of
 * string-to-integer conversion
 * It stores the accumulated integer value (num) and the current digit being
 * processed (curr_digit)
 */
typedef struct atoi
{
	unsigned int num;
	unsigned int curr_digit;
	size_t iterator;
} atoi_t;
#endif /*MAIN_H*/
