#include "shellcmd.h"
#include "strtok.h"
#include "main.h"

/**
 * quote_factory - function pointer string processor helper
 * @state: state
 *
 * Return: state with associated c
 */
quote_state_fp quote_factory(quote_state state)
{
	switch (state)
	{
		case QUOTE_NONE:
			return (quote_none);
		case QUOTE_DOUBLE:
			return (quote_double);
		case QUOTE_SINGLE:
			return (quote_single);
		case QUOTE_ESCAPE:
			return (quote_escape);
		case QUOTE_WORD:
			return (quote_word);
	}
	return (NULL);
}

/**
 * quote_str_len - get the length of state
 * @str: string
 * @state: state
 *
 * Return: length
 */
size_t quote_str_len(const char *str, quote_state state)
{
	return (quote_factory(state)(str, NULL));
}

/**
 * process_usr_input - process user input
 * @line_input: line input parameter
 * @fd: file descriptor
 * Return: state
 */
quote_state process_usr_input(char **line_input, int fd)
{
	char *line = *line_input = my_getline(fd);
	static quote_state state = QUOTE_NONE;
	size_t index = 0;

	while (line)
	{
		switch (state & (QUOTE_DOUBLE | QUOTE_SINGLE))
		{
			case QUOTE_DOUBLE:
			case QUOTE_SINGLE:
				do {
					index += quote_str_len(line + index, state);
					if (line[index] == '\0')
						continue;
					if (state & (QUOTE_DOUBLE | QUOTE_SINGLE))
						index += 1;
					/*fall-through*/
					default:
					state = quote_proc(line[index]);
					if (state & (QUOTE_DOUBLE | QUOTE_SINGLE | QUOTE_ESCAPE))
						index += 1;
				} while (line[index]);
		}
	}
	return (state);
}

command_lst *cmd_btree(const char * const *not_modifed __attribute__((unused)))
{
	return (NULL);
}

/**
 * update_the_cmd - process and update a linked list of commands from a string.
 * @cmd: The input string containing multiple commands
 * separated by a delimiter.
 *
 * Return: A pointer to the head of the linked list
 * containing processed commands
 * NULL if the input string is empty or if memory allocation fails
 */
command_lst *_update_the_cmd(const char *cmd)
{
	command_lst *head = NULL;
	size_t count;
	char *split;

	split = _strdup(cmd);
	if (!split)
		return (NULL);
	count = cmd_to_split(split);

	if (_update_cmd(&head, split, count))
	{
		free_command_lst(&head);
		return (NULL);
	}
	free_all(1, split);

	return (head);
}
