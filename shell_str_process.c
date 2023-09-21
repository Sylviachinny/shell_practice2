#include "shellcmd.h"
#include "strtok.h"
#include "main.h"

/**
 * quote_double - function to process double quote in a string
 * @str: string to process
 * @state: state of the string
 * Return: the length of the state
 */
size_t quote_double(const char *str, quote_state *state)
{
	size_t length = 0;

	while (*str && *str != '"')
		++str, ++length;
	if (state && *str)
		*state = quote_proc(*(str + 1));
	return (length);
}

/**
 * quote_single - function to process single quote in a string
 * @str: string to process
 * @state: state of the string
 * Return: the length of the state
 */
size_t quote_single(const char *str, quote_state *state)
{
	size_t length = 0;

	while (*str && *str != '\'')
		++str, ++length;
	if (state && *str)
		*state = quote_proc(*(str + 1));
	return (length);
}

/**
 * quote_escape - function to process escape character in a string
 * @str: string to process
 * @state: state of the string
 * Return: the length of the state
 */
size_t quote_escape(const char *str, quote_state *state)
{
	if (*str)
	{
		if (state && *(++str))
			*state = quote_proc(*str);
		return (1);
	}
	return (0);
}

/**
 * quote_none - function to process none character in a string
 * @str: string to process
 * @state: state of trhe string
 * Return: the length of the state
 */
size_t quote_none(const char *str, quote_state *state)
{
	size_t length = 0;

	while (_isspace(*str) != 0)
		++str, ++length;
	if (state && *str)
		*state = quote_proc(*str);
	return (length);
}

/**
 * quote_word - function to process word in a string
 * @str: string to process
 * @state: state of the string
 * Return: the length of the state
 */
size_t quote_word(const char *str, quote_state *state)
{
	size_t length = 0;

	while (*str && !_isquote(*str) && !_isspace(*str))
		++str, ++length;
	if (state && *str)
		*state = quote_proc(*str);
	return (length);
}
