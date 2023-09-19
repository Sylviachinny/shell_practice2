#ifndef _SHELL_BUILTINS_H_
#define _SHELL_BUILTINS_H_

#include "main.h"

typedef struct built_in
{
	const char *name;
	const char *help;
	const char *dsc;
} builtin_t;

int _cd(store_info_t *shell_info);
int _exit(store_info_t *shell_info);
int _env(store_info_t *shell_info);
int _exec(store_info_t *shell_info);
int _setenv(store_info_t *shell_info);
int _unsetenv(store_info_t *shell_info);
#endif /*_SHELL_BUILTINS_H*/
