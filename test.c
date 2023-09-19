#include <stdio.h>
#include <string.h>

typedef struct builtins
{
	const char *name;
	const char *help;
	const char *dsc;
} builtins_t;

const builtins_t *get_builtins(const char *name)
{
	static builtins_t alias_builtin = {"alias", __alias, ALIAS_HELP, ALIAS_DESC};
	static builtins_t cd_builtin = {"cd", __cd, CD_HELP, CD_DESC};
	static builtins_t env_builtin = {"env", __env, ENV_HELP, ENV_DESC};
	static builtins_t exec_builtin = {"exec", __exec, EXEC_HELP, EXEC_DESC};
	static builtins_t exit_builtin = {"exit", __exit, EXIT_HELP, EXIT_DESC};
	static builtins_t help_builtin = {"help", __help, HELP_HELP, HELP_DESC};
	static builtins_t setenv_builtin = {"setenv",
		__setenv, SETENV_HELP, SETENV_DESC};
	static builtins_t unsetenv_builtin = {"unsetenv",
		__unsetenv, UNSETENV_HELP, UNSETENV_DESC};

	static builtins_t *builtins[] = {
		&alias_builtin,
		&cd_builtin,
		&env_builtin,
		&exit_builtin,
		&help_builtin,
		&setenv_builtin,
		&unsetenv_builtin,
		NULL
	};

	const builtins_t *builtin = NULL;
	const builtins_t **temp = NULL;

	for (temp = (const builtins_t **)builtins; (*temp)->name; temp += 1)
	{
		builtin = *temp;
		if (strcmp(name, builtin->name) == 0)
		{
			return (builtin);
		}
	}
	return (NULL);
}
int main()
{
	const char *command = "env";
	const builtins_t *built = get_builtins(command);

	if (built != NULL)
	{
		printf("Found built-in command:\n");
		printf("Name: %s\n", built->name);
	}
	else
	{
		printf("builtin-in command '%s' not found.\n", command);
	}
}
