#ifndef _SHELL_BUILTINS_H_
#define _SHELL_BUILTINS_H_

#include "limits.h"
#include "secondpath.h"
#include "main.h"

typedef int (*builtin_handler)(store_info_t *);

typedef struct built_in
{
	const char *name;
	builtin_handler built_f;
	const char *help;
	const char *dsc;
} builtin_t;

int _cd(store_info_t *shell_info);
int _exit_s(store_info_t *shell_info);
int _env(store_info_t *shell_info);
int _exec(store_info_t *shell_info);
int _setenv(store_info_t *shell_info);
int _unsetenv(store_info_t *shell_info);

const builtin_t *get_builtins(const char *name);
#endif /*_SHELL_BUILTINS_H*/
