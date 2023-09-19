#include "strtok.h"

/**
 * tok_counter - function to get the length of string in
 * a quote character
 * @s: string to evaluate
 * Return: length
 */
size_t tok_counter(const char *s)
{
	size_t s_count;
	quote_state state;

	for (s_count = 0; *(s += quote_str_len(s, QUOTE_NONE)); ++s_count)
	{
		while (*s && (state = quote_proc(*s)) != QUOTE_ESCAPE)
		{
			if (state & (QUOTE_DOUBLE | QUOTE_SINGLE | QUOTE_ESCAPE))
				s += quote_str_len(s + 1, state) + 1;
			else
				s += quote_str_len(s, state);

			if (*s && (state & (QUOTE_DOUBLE | QUOTE_SINGLE)))
				++s;
		}
	}
	return (s_count);
}

/**
 * my_token - strtok function
 * @tok: the array of string to split
 * Return: tokens
 */
char **my_token(const char *tok)
{
	strtok_t tokenize;
	size_t tok_count;

	if (tok == NULL)
		return (NULL);

	tokenize.tokens = malloc(sizeof(char *) * (tok_counter(tok) + 1));
	if (!tokenize.tokens)
		return (NULL);
	for (tok_count = 0; *(tok += quote_str_len(tok, QUOTE_NONE)); ++tok_count)
	{
		tokenize.store_tok = tok;
		while (*tok && (tokenize.state = quote_proc(*tok)) != QUOTE_NONE)
		{
			if (tokenize.state & (QUOTE_DOUBLE | QUOTE_SINGLE | QUOTE_ESCAPE))
				tok += quote_str_len(tok + 1, tokenize.state) + 1;
			else
				tok += quote_str_len(tok, tokenize.state);
			if (*tok && (tokenize.state & (QUOTE_DOUBLE | QUOTE_SINGLE)))
				++tok;
		}
		tokenize.tokens[tok_count] = _memdup(tokenize.store_tok,
				tok - tokenize.store_tok + 1);
		if (tokenize.tokens[tok_count] == NULL)
		{
			release_mem(&tokenize.tokens);
			return (NULL);
		}
		tokenize.tokens[tok_count][tok - tokenize.store_tok] = '\0';
	}
	tokenize.tokens[tok_count] = NULL;
	return (tokenize.tokens);
}

/**
 * release_mem - release memory after used
 * @str: str
 */
void release_mem(char ***str)
{
	char **tok_r;

	if (str == NULL)
		return;
	tok_r = *str;

	if (tok_r == NULL)
		return;
	while (*tok_r)
		free_all(1, *tok_r++);
	free_all(1, *str);

	*str = NULL;
}
