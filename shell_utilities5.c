#include "shellcmd.h"
#include "strtok.h"
#include "main.h"

/**
 * duplicateStringArray - Duplicate a string array
 *
 * @array: The original string array to duplicate
 *
 * Return: A new dynamically allocated array containing duplicated strings,
 * or NULL on failure
 */
char **duplicateStringArray(char **array)
{
	char **arr_dup = NULL;
	size_t length = 0, iterator;

	if (!array || !*array)
		return (NULL);
	while (array[length++])
		;
	arr_dup = malloc(sizeof(*arr_dup) * length);
	if (arr_dup == NULL)
		return (NULL);
	length = 0;
	while (array[length])
	{
		arr_dup[length] = _strdup(array[length]);
		if (arr_dup[length] == NULL)
		{
			for (iterator = 0; iterator < length; iterator++)
			{
				free_all(1, arr_dup[iterator]);
			}
			free_all(1, arr_dup);
			return (NULL);
		}
		length++;
	}
	return (arr_dup);
}

/**
 * _isdigit - check if a character is a digit
 * @c: The character to check
 *
 * Return: Returns true (1) if the character is a digit (0-9),
 * or false (0) otherwise.
 */
bool _isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

/**
 * is_numeric - check if a string consists of numeric digits
 * @str: The input string to check
 *
 * Return: Returns true (1) if the entire string consists of numeric digits
 * or false (0) otherwise
 */
bool is_numeric(const char *str)
{
	if (str)
	{
		while (*str)
		{
			if (!_isdigit(*str++))
				return (false);
		}
		return (true);
	}
	return (false);
}

/**
 * my_atoi - convert a string to an unsigned integer.
 * @str: The input string to convert
 *
 * Return: Returns the converted unsigned integer value from the string
 * if the string contains non-numeric characters or the value exceeds UINT_MAX,
 * it returns UINT_MAX
 */
unsigned int my_atoi(char *str)
{
	atoi_t atou;

	atou.num = 0;

	size_t len = _strlen(str);

	for (atou.iterator = 0; atou. iterator < len; atou.iterator++)
	{
		if (UINT_MAX / 10 < atou.num)
			return (UINT_MAX);
		atou.num *= 10;
		atou.curr_digit = str[atou.iterator] - '0';
		if (UINT_MAX - atou.curr_digit < atou.num)
			return (UINT_MAX);
		atou.num += atou.curr_digit;
	}
	return (atou.num);
}

/**
 * is_double_quote_escape - checks if a character is a special
 * escape character within double quotes
 * @c: The character to check
 * @return: 1 if the character is a double quote, dollar sign,
 * or backlash; 0 otherwise
 */
int is_double_quote_escape(char c)
{
	return (c == '"' || c == '$' || c == '\\');
}
