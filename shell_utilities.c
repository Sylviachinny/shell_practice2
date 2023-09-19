#include "main.h"

/**
 * _strcat - concatenates two strings
 * @dest_a: destination string
 * @src: source string
 * Return: pointer to the resulting string destination
 */
char *_strcat(char *dest_a, const char *src)
{
	int e, length = _strlen(dest_a);

	for (e = 0; src[e] != '\0'; e++)
		dest_a[length + e] = src[e];
	dest_a[length + e] = src[e];
	return (dest_a);
}

/**
 * _memchr - memory character
 * @s: character to array of string to search
 * @c: character to search
 * @n: size of array of string
 * Return: pointer to the first occurrence
 * of the found character
 */
ssize_t _memchr(const void *s, int c, size_t n)
{
	unsigned char *str = (unsigned char *)s;
	size_t iterator;

	if (str)
	{
		for (iterator = 0; iterator < n; iterator++)
		{
	if (str[iterator] == (unsigned char)c)
	{
		return (iterator);
	}
		}
	}
	return (-1);
}

/**
 * _strcmp - function that compare two strings
 * @s1: the first string to compare
 * @s2: The second string to compare
 * Return: s1 - s2
 */
int _strcmp(char *s1, char *s2)
{
	int e;

	for (e = 0; s1[e] && s2[e]; e++)
	{
		if (s1[e] != s2[e])
		{
			return (s1[e] - s2[e]);
		}
	}
	return (s1[e] - s2[e]);
}

/**
 * _strncmp - compare two strings
 * @s1_es: first string
 * @s2_es: second string
 * @n: number of bytes to be compared
 * Return: difference between the two strings
 */
int _strncmp(const char *s1_es, const char *s2_es, size_t n)
{
	while (n > 0)
	{
		if (*s1_es == '\0' && *s2_es == '\0')
		{
			return (0);
		}
		else if (*s1_es == *s2_es)
		{
			s1_es++;
			s2_es++;
			n--;
		}
		else
		{
			return (*s1_es - *s2_es);
		}
	}
	return (0);
}

/**
 * _isspace - checks for white space characters
 * @c: character to be checked
 * Return: 1 if c is a white-space character, 0 otherwise
 */
bool _isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' ||
			c == '\v' || c == '\f' || c == '\r');
}
