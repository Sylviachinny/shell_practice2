#include "shellcmd.h"
#include "strtok.h"
#include "main.h"

/**
 * _strcpy - copies the string pointed by src to dest
 * @dest: destination string
 * @src: source string
 * Return: pointer to dest
 */
char *_strcpy(char *dest, const char *src)
{
	int e;

	for (e = 0; src[e] != '\0'; e++)
		dest[e] = src[e];
	dest[e] = src[e];
	return (dest);
}

/**
 * _strlen - returns the length of string
 * @s: string to be measured
 * Return: length of the string
 */
size_t _strlen(const char *s)
{
	int len;

	for (len = 0; s[len] != '\0'; len++)
		;
	return (len);
}

/**
 * _isquote - check for quote character
 * @c: character to be checked
 * Return: true if it is a character or
 * false if it is not
 */
bool _isquote(int c)
{
	return (c == '\'' || c == '"' || c == '\\');
}

/**
 * quote_proc - character processor function
 * @c: character to process
 *
 * Return: the state of character base on the processor
 */
quote_state quote_proc(char c)
{
	if (_isspace(c))
		return (QUOTE_NONE);
	else if (c == '"')
		return (QUOTE_DOUBLE);
	else if (c == '\'')
		return (QUOTE_SINGLE);
	else if (c == '\\')
		return (QUOTE_ESCAPE);
	else
		return (QUOTE_WORD);
}

