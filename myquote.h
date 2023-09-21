#ifndef _MYQUOTE_H_
#define _MYQUOTE_H_

#include <stdio.h>
#include <unistd.h>
/**QUOTE STRING PROCESS**/

/**
 * enum quote - Represents quoting states for text processing
 * @QUOTE_NONE: No quoting state.
 * @QUOTE_DOUBLE: Inside a double-quoted section
 * @QUOTE_SINGLE: Inside a single-quoted section
 * @QUOTE_ESCAPE: Following an escape character
 */
typedef enum quote
{
	QUOTE_NONE = 0x0,
	QUOTE_WORD = 0x1,
	QUOTE_DOUBLE = 0x2,
	QUOTE_SINGLE = 0x4,
	QUOTE_ESCAPE = 0x8
} quote_state;

typedef size_t (*quote_state_fp)(const char *, quote_state *);
quote_state_fp quote_factory(quote_state str);
quote_state quote_proc(char c);

size_t quote_double(const char *str, quote_state *state);
size_t quote_single(const char *str, quote_state *state);
size_t quote_escape(const char str, quote_state *state);
size_t quote_none(const char *str, quote_state *state);
size_t quote_word(const char *str, quote_state *state);
size_t quote_str_len(const char *str, quote_state state);
quote_state process_usr_input(char **line_input, int fd);
#endif
