#ifndef _STRTOK_H_
#define _STRTOK_H_

#include "main.h"

typedef struct strtok
{
	char **tokens;
	const char *store_tok;
	quote_state state;
} strtok_t;

size_t tok_counter(const char *s);
char **my_token(const char *tok);
void release_mem(char ***str);
#endif /*_STRTOK_H_*/
