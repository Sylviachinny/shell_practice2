#ifndef _DICTIONARY_H_
#define _DICTIONARY_H_

#include <stdio.h>
#include <unistd.h>
#include "shellcmd.h"

/*Build an environment dictionary*/
typedef struct shell_dict
{
	char *key;
	char *value;
	struct shell_dict *link;
} shell_dict_s;

shell_dict_s *add_dict_to_the_end(shell_dict_s **headptr,
		const char *key, const char *value);
char *get_value(shell_dict_s *head, const char *key);
shell_dict_s *get_node(shell_dict_s *head, const char *key);
shell_dict_s *delete_nodes(shell_dict_s **headptr, const char *key);
void free_dictionary(shell_dict_s **headptr);
char **build_env_array(shell_dict_s *ptr);
shell_dict_s *build_dict_from_env(shell_dict_s **head_ptr, char **env);
shell_dict_s *build_dict_from_env_caller(char **env);
#endif /*DICTIONARY*/
