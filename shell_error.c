#include "main.h"
#include <string.h>

/**
 * printerror - prints error message
 * @av: name of the program
 * @count: number of commands entered
 * @arg: command entered
 * Return: void
 */
void printerror(char **av, int count, char **arg)
{
	write(STDERR_FILENO, av[0], _strlen(av[0]));
	write(STDERR_FILENO, ": ", 2);
	write_error_stderr(count);
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, arg[0], _strlen(arg[0]));
	write(STDERR_FILENO, ": not found\n", 12);
}

/**
 * write_error_stderr - writes an error to stderr
 * @error: error to write
 * Return: number of characters written
 */
int write_error_stderr(int error)
{
	int temp, char_count = 0;
	unsigned int num;

	if (error < 0)
	{
		error = -error;
		write(2, "-", 1);
		char_count++;
	}

	num = error;
	while (num / 10)
	{
		char_count += write_error_stderr(num / 10);
	}

	temp = (num % 10) + '0';
	write(2, &temp, 1);
	char_count++;

	return (char_count);
}

static void cnv_to_helper(char **buff, size_t m)
{
	if (m > 9) /*base case*/
		cnv_to_helper(buff, m / 10);
	**buff = '0' + m % 10;
	*buff += 1;
	**buff = '\0';
}

char *convert_str(size_t n)
{
	error_s error;

	error.len = 1;

	error.buf = NULL;
	size_t temp = n;

	while (temp /= 10)
		error.len++;
	error.buf = malloc(sizeof(error_s) * (error.len + 1));
	if (error.buf == NULL)
		return (NULL);
	cnv_to_helper(&error.buf, n);
	return (error.buf - error.len);
}

void handle_error(const char *av, size_t linenum, const char *error_m, ...)
{
	error_s err;

	err.linenum_error = convert_str(linenum);

	err.str_ret = NULL;
	va_list arg;

	if (av)
		write(STDERR_FILENO, av, strlen(av));
	write(STDERR_FILENO, ": ", 3);
	if (err.linenum_error)
		write(STDERR_FILENO, err.linenum_error, strlen(err.linenum_error));
	write(STDERR_FILENO, ": ", 3);
	va_start(arg, error_m);
	while ((err.str_ret = va_arg(arg, char *)))
	{
		write(STDERR_FILENO, err.str_ret, strlen(err.str_ret));
		write(STDERR_FILENO, ": ", 3);
	}
	va_end(arg);

	if (error_m)
		write(STDERR_FILENO, error_m, strlen(error_m));
	write(STDERR_FILENO, ": ", 3);

	free(err.linenum_error);
}
