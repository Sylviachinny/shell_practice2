#include "shellcmd.h"
#include "strtok.h"
#include "main.h"

/**
 * _strdup - duplicates a string
 * @str: string to duplicate
 * Return: pointer to the new string
 */
char *_strdup(const char *str)
{
	char *new_str = NULL;
	int i, len;

	if (str == NULL)
		return (NULL);
	len = _strlen(str);
	new_str = malloc(sizeof(char) * (len + 1));

	if (new_str == NULL)
		return (NULL);

	for (i = 0; str[i] != '\0'; i++)
		new_str[i] = str[i];
	new_str[i] = '\0';

	return (new_str);
}

/**
 * _strstr - locates a substring
 * @haystack: string to search
 * @needle: substring to search for
 * Return: pointer to the beginning of the located substring
 */
char *_strstr(const char *haystack, const char *needle)
{
	int i, j, k;

	for (i = 0; haystack[i] != '\0'; i++)
	{
		for (j = 0, k = i; needle[j] != '\0'; j++, k++)
		{
			if (needle[j] != haystack[k] || haystack[k] == '\0')
				break;
		}

		if (needle[j] == '\0')
			return ((char *)haystack + i);
	}
	return (NULL);
}

/**
 * _memcpy - memory copy function
 * @dest: destination
 * @src: source
 * @n: size
 * Return: void
 */
void *_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char *destination = dest;
	const unsigned char *source = src;
	size_t iterator;

	if (dest && src)
	{
		for (iterator = 0; iterator < n; iterator++)
		{
			*destination++ = *source++;
		}
		return (dest);
	}
	return (NULL);
}

/**
 * _realloc - reallocates buffer
 * @buffer: pointer to buffer
 * @old_size: old size
 * @new_size: new size
 * Return: new memory
 */
void *_realloc(void *buffer, size_t old_size, size_t new_size)
{
	void *new_buff = NULL;

	if (buffer)
	{
		if (new_size)
		{
			new_buff = malloc(new_size);
			if (new_buff)
			{
				_memcpy(new_buff, buffer, new_size > old_size ? new_size : old_size);
				free_all(1, buffer);
			}
		}
		else
		{
			free_all(1, buffer);
		}
	}
	return (new_buff);
}

/**
 * _memdup - memory duplicate
 * @str: string to duplicate
 * @n: size of string to duplicate
 *
 * Return: Pointer to the calling function if successful
 * or NULL is not
 */
void *_memdup(const void *str, size_t n)
{
	void *duplicate;
	unsigned char *dup;
	const unsigned char *src;
	size_t iterator;

	duplicate = malloc(n);

	if (duplicate == NULL)
		return (NULL);
	dup = duplicate;
	src = str;

	for (iterator = 0; iterator < n; iterator++)
	{
		*dup++ = *src++;
	}
	return (duplicate);
}
