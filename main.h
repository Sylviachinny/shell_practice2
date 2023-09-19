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


/**STRING PROTOTYPES**/
char *_strcat(char *dest, const char *src);
ssize_t _memchr(const void *s, int c, size_t n);
int _strcmp(char *s1, char *s2);
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

/**SHELL ERROR**/
void printerror(char **av, int count, char **arg);
int write_error_stderr(int error);

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
	char **argv;
	int argc;
	int interactive;
	int fileno;
	char *file;
	size_t line_read;
	char *line;
	int error;
	int status;
} store_info_t;

/**QUOTE STRING PROCESS**/

/**
 * enum quote - represents quoting states for text processing.
 * @QUOTE_NONE: No quoting state.
 * @QUOTE_DOUBLE: Inside a double-quoted section.
 * @QUOTE_SINGLE: Inside a single-quoted section.
 * @QUOTE_ESCAPE: Following an escape character.
 */
typedef enum quote
{
	QUOTE_NONE   = 0X0,
	QUOTE_WORD   = 0X1,
	QUOTE_DOUBLE = 0X2,
	QUOTE_SINGLE = 0X4,
	QUOTE_ESCAPE = 0X8
} quote_state;

typedef size_t (*quote_state_fp)(const char *, quote_state *);
quote_state_fp quote_factory(quote_state str);
quote_state quote_proc(char c);

size_t quote_double(const char *str, quote_state *state);
size_t quote_single(const char *str, quote_state *state);
size_t quote_escape(const char *str, quote_state *state);
size_t quote_none(const char *str, quote_state *state);
size_t quote_word(const char *str, quote_state *state);
size_t quote_str_len(const char *str, quote_state state);
store_info_t *init_prmpt(char **av, int ac);
bool read_usr_input(store_info_t *input_info);
quote_state process_usr_input(char **line_input, int fd);

/******STRING******/
char *str_concat(size_t *len, const char *delim,
		const char *prev, const char *next);

/******COMMAND TO SPLIT FUNCTION*****/
/**
 * struct cmd - Structure to represent command processing information
 * @cmd_count: The count of tokens found in the command string
 * @quote_len: The length of the current quoted section.
 * @delim_indx: The index of the delimiter within a quoted section
 * @state: The current quote_state for parsing the command string.
 */
typedef struct cmd
{
	size_t cmd_count;
	size_t quote_len;
	ssize_t delim_indx;
	quote_state state;
} cmd_t;
size_t cmd_to_split(char *cmd);

typedef struct command
{
	char **tokens;
	struct command *link;
	struct cmd_btree *b_tree;

} command_lst;

command_lst *at_the_end(command_lst **head, const char *cmd);
void free_command_lst(command_lst **head);
command_lst *del_cmd_at_pos(command_lst **head, size_t pos);
char **remove_cmd(command_lst **head);
command_lst *_update_cmd(command_lst **ptr, char *split, size_t count);
command_lst *_update_the_cmd(const char *cmd);

typedef struct cmd_btree
{
	struct cmd_btree *success;
	struct cmd_btree *failure;
	const char * const *ntmodified;
} cmd_btree_lst;
void free_command_btree(cmd_btree_lst **headptr);

typedef struct error
{
	char *buf;
	size_t len;
	char *linenum_error;
	const char *str_ret;
} error_s;
#endif /*MAIN_H*/
