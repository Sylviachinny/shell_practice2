#include "shell_builtins.h"

/**
 * get_builtins - Retrieve a specific builtin by name
 * @name: The name of the builtin to retrieve
 *
 * Return: A pointer to the requested builtin, or NULL if not found
 */
const builtin_t *get_builtins(const char *name)
{
	const builtin_t *builtin = NULL;
	const builtin_t **temp = NULL;

	/*static builtin_t alias_builtin = {"alias", __alias};*/
	/*static builtin_t cd_builtin = {"cd, __cd, CD_HELP, CD_DESC"};*/
	static builtin_t env_builtin = {"env", _env};
	static builtin_t exec_builtin = {"exec", _exec};
	static builtin_t exit_builtin = {"exit", _exit_s};
	/*static builtin_t help_builtin = {"help", __help, HELP_HELP, HELP_DESC};*/
	static builtin_t setenv_builtin = {"setenv", _setenv};
	static builtin_t unsetenv_builtin = {"unsetenv", _unsetenv};

	static builtin_t *builtins[] = {
		/*&alias_builtin,*/
		/*&cd_builtin,*/
		&env_builtin,
		&exit_builtin,
		/*&help_builtin,*/
		&setenv_builtin,
		&unsetenv_builtin,
		NULL
	};

	for (temp = (const builtin_t **)builtins; (*temp)->name; temp += 1)
	{
		builtin = *temp;
		if (_strcmp(name, builtin->name) == 0)
		{
			return (builtin);
		}
	}
	return (NULL);
}
