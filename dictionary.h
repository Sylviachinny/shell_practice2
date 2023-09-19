#ifndef _DICTIONARY_H_
#define _DICTIONARY_H_

#include <stdio.h>
#include <unistd.h>
#include "main.h"
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
#endif /*DICTIONARY*/
