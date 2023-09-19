#include "main.h"

/**
 * free_all - frees all memory
 * @n: number of arguments
 * Return: void
 */
void free_all(const unsigned int n, ...)
{
	va_list args;
	unsigned int i;
	char *ptr;

	va_start(args, n);
	for (i = 0; i < n; i++)
	{
		ptr = va_arg(args, char *);
		free(ptr);
	}
	va_end(args);
}

/**
 * init_prmpt - initialize the shell prompt
 * @av: argument vector
 * @ac: argument counter
 * Return: pointer to the calling function
 */
store_info_t *init_prmpt(char **av, int ac)
{
	static store_info_t my_info;

	my_info.argv = av;
	my_info.argc = ac;
	my_info.fileno = STDIN_FILENO;

	if (ac > 1)
	{
		my_info.file = av[1];
		my_info.fileno = open(my_info.file, O_RDONLY);

		if (my_info.fileno == -1)
		{
			/*printerror(av, my_info.error, ac);*/
			my_info.status = 127;
		}
	}
	my_info.interactive = isatty(my_info.fileno);

	return (&my_info);
}

/**
 * read_usr_input - Read user input and process it
 * @input_info: a pointer to a structure containing information about the input
 *
 * Return: a dynamically allocated string containing the user's input;
 * or NULL if there was an error or if the user entered no input
 */
bool read_usr_input(store_info_t *input_info)
{
	char *temp = NULL, *line = NULL;

	if (input_info->interactive)
		write(STDIN_FILENO, "shell$: ", 9);
	input_info->line_read += 1;

	while (process_usr_input(&input_info->line, input_info->fileno) &
			(QUOTE_DOUBLE | QUOTE_SINGLE | QUOTE_ESCAPE))
	{
		temp = line;
		line = str_concat(NULL, "", temp, input_info->line);
		free_all(2, temp, input_info->line);
		if (input_info->interactive)
			write(STDIN_FILENO, "shell$: ", 9);
		input_info->line_read += 1;
	}

	if (line)
	{
		temp = input_info->line;
		input_info->line = str_concat(NULL, "", line, temp);
		free_all(2, temp, line);
	}
	return (input_info->line);
}
