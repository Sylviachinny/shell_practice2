#include "shell_builtins.h"
#include "dictionary.h"

/**
 * _env - Print the current environment variables.
 *  @shell_info: Pointer to the shell's information structure
 *
 *  Return: EXIT_SUCCESS if successful, otherwise an error code
 */
int _env(store_info_t *shell_info)
{
	shell_dict_s *env;

	shell_info->status = EXIT_SUCCESS;

	for (env = shell_info->env; env != NULL; env = env->link)
	{
		if (env->key)
			write(STDOUT_FILENO, env->key, _strlen(env->key));
		write(STDOUT_FILENO, "=", 2);
		if (env->value)
			write(STDOUT_FILENO, env->value, _strlen(env->value));
		write(STDOUT_FILENO, "\n", 1);
	}
	return (shell_info->status);
}

/**
 * _exec - Execute a command with arguments and environment variables
 * @shell_info: Pointer to the shell's information struct
 *
 * Return: The exit status of the executed command
 */
int _exec(store_info_t *shell_info)
{
	char *execute, **args, **environment;
	int index;

	environment = NULL;
	args = shell_info->tokens + 1;
	shell_info->status = EXIT_SUCCESS;
	if (*args == NULL)
		return (shell_info->status);
	shell_info->tokens = args;
	args = duplicateStringArray(args);

	index = _strchr(*args, '/');
	if (index == -1)
	{
		free_dir(&shell_info->path);
		shell_info->path = path_wrapper(get_value(shell_info->env, "PATH"), ':');
		execute = handle_path(shell_info, shell_info->path);
	}
	else
		execute = _strdup(*args);
	shell_info->tokens -= 1;
	if (access(execute, X_OK) == 0)
	{
		environment = build_env_array(shell_info->env);
		release_store_information(shell_info);
		execve(execute, args, environment);
		handle_error(*shell_info->argv, shell_info->line_read, "not found",
				*shell_info->tokens, *args, NULL);
		free_all(1, execute);
		release_mem(&args);
		release_mem(&environment);
		exit(127);
	}
	handle_error(*shell_info->argv, shell_info->line_read, "Permission denied",
			*shell_info->tokens, *args, NULL);
	free_all(1, execute);
	release_mem(&args);
	release_mem(&environment);
	exit(126);
}

/**
 * _exit_s - Exit the shell with a specified status code
 * @shell_info: Pointer to the shell's information structure
 *
 * Description: This function exits the shell with the specified status code
 * If a numeric argument is provided, it is used as the exit status code
 * If the argument is not numeric, an error message is displayed, and the
 * exit status code is set to 2.
 */
int _exit_s(store_info_t *shell_info)
{
	char **argument = shell_info->tokens + 1;

	if (*argument)
	{
		if (is_numeric(*argument) && my_atoi(*argument) <= INT_MAX)
			shell_info->status = my_atoi(*argument);
		else
		{
			handle_error(*shell_info->argv, shell_info->line_read, *argument,
					shell_info->tokens, "Invalid number", NULL);
			shell_info->status = 2;

			return (shell_info->status);
		}
	}
	if (shell_info->file)
		close(shell_info->fileno);
	exit(release_store_information(shell_info));
}

/**
 * _setenv - Set or modify an environment variable
 * @shell_info: Pointer to the shell's information struct
 *
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE on failure
 */
int _setenv(store_info_t *shell_info)
{
	shell_dict_s *key;
	char **argument = shell_info->tokens + 1;
	char *value;

	if (argument[0] != NULL)
	{
		if (argument[1] != NULL)
		{
			if (argument[2])
			{
				write(STDERR_FILENO, "Too many argument", 18);
				return (shell_info->status = EXIT_FAILURE);
			}
			value = argument[1];
		}
		else
			value = "";
		key = get_node(shell_info->env, argument[0]);
		if (key != NULL)
		{
			free_all(1, key->value);
			key->value = _strdup(value);
		}
		else
			add_dict_to_the_end(&shell_info->env, argument[0], value);
		shell_info->status = EXIT_SUCCESS;
	}
	return (shell_info->status);
}

/**
 * _unsetenv - Unset one or more environment variables
 * @shell_info: Pointer to the shell's information struct
 *
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE on failure
 */
int _unsetenv(store_info_t *shell_info)
{
	char **argument = shell_info->tokens + 1;

	if (*argument)
	{
		while (*argument)
			delete_nodes(&shell_info->env, *argument++);
		shell_info->status = EXIT_SUCCESS;
	}
	else
	{
		write(STDERR_FILENO, "Too many argument", 18);
		shell_info->status = EXIT_FAILURE;
	}
	return (shell_info->status);
}
