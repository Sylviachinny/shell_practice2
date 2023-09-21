#include "shellcmd.h"
#include "shell_builtins.h"
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
	char *errorno;

	my_info.argv = av;
	my_info.argc = ac;
	my_info.fileno = STDIN_FILENO;

	if (ac > 1)
	{
		my_info.file = av[1];
		my_info.fileno = open(my_info.file, O_RDONLY);

		if (my_info.fileno == -1)
		{
			errorno = str_concat(NULL, " ", "can't open", my_info.file);
			handle_error(*av, my_info.line_read, errorno, NULL);
			free_all(1, errorno);
			my_info.status = 127;
			exit(release_store_information(&my_info));
		}
	}
	my_info.interactive = isatty(my_info.fileno);
	my_info.p_pid = getpid();
	my_info.cwd_s = getcwd(NULL, 0);
	my_info.env = build_dict_from_env_caller(environ);

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
		write(STDIN_FILENO, "shell$: ", 7);
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

/**
 * exec_init - Execute a shell command in a child process
 * @shell_info: Pointer to the shell information struct
 *
 * This function forks a child process to execute a shell command and waits for
 * the child process to complete. it handles errors and cleanup
 *
 * Return: The exit status of the child process
 */
int exec_init(store_info_t *shell_info)
{
	char **argv, *exec, **environment;
	pid_t child_pid = fork();

	if (child_pid == -1)
	{
		handle_error(*shell_info->argv, shell_info->line_read,
				"can't fork process", NULL);
		shell_info->status = 2;
	}
	else if (child_pid == 0)
	{
		exec = shell_info->execute;
		argv = shell_info->tokens;
		environment = build_env_array(shell_info->env);

		shell_info->execute = NULL;
		shell_info->tokens = NULL;
		release_store_information(shell_info);

		execve(exec, argv, environment);
		perror(*argv);

		if (shell_info->file)
			close(shell_info->fileno);
		free_all(1, exec);
		release_mem(&argv);
		release_mem(&environment);
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(&shell_info->status);
		shell_info->status = WEXITSTATUS(shell_info->status);
	}
	free_all(1, shell_info->env);
	shell_info->env = NULL;
	return (shell_info->status);
}

/**
 * executeShellCommand - Execute a shell command
 * @shell_info: Pointer to the shell information struct
 *
 * This function checks if the command is a built-in shell command and executes
 * it if it is. If not, it attempts to execute an external command, handling
 * errors and permissions. it returns the exit status of the command execution
 *
 * Return: the exit status of the executed command
 */
int executeShellCommand(store_info_t *shell_info)
{
	const builtin_t *builtin = get_builtins(*shell_info->tokens);

	if (builtin)
		return (builtin->built_f(shell_info));
	if (_strchr(*shell_info->tokens, '/') == -1)
	{
		free_dir(&shell_info->path);
		shell_info->path = path_wrapper(get_value(shell_info->env, "PATH"), ':');
		shell_info->execute = handle_path(shell_info, shell_info->path);
	}
	else
		shell_info->execute = _strdup(*shell_info->tokens);
	if (shell_info->execute && access(shell_info->execute, X_OK) == 0)
		return (exec_init(shell_info));
	if (shell_info->execute)
	{
		handle_error(*shell_info->argv, shell_info->line_read,
				"Permissioned denied", *shell_info->tokens, NULL);
		shell_info->status = 126;
	}
	else
	{
		handle_error(*shell_info->argv, shell_info->line_read, "Not found",
				*shell_info->tokens, NULL);
		shell_info->status = 127;
	}

	return (shell_info->status);
}
