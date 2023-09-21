#include "dictionary.h"
#include "main.h"

/**
 * build_env_array - Build an environment variable array from a linked list
 * @ptr: Pointer to the linked list of environmental variables
 *
 * Return: Adynamically allocated array of environmental variable strings
 * (in the format "KEY=VALUE") terminated with a NULL pointer, or
 * NULL if memory allocation fails or if the linked list is empty
 */
char **build_env_array(shell_dict_s *ptr)
{
	char **env;
	size_t length = 0;
	shell_dict_s *temp = ptr;

	/*loop through the list to get length*/
	while (temp)
	{
		temp = temp->link;
		++length;
	}

	env = malloc(sizeof(char *) * (length + 1));
	if (!env)
		return (NULL);
	for (length = 0; ptr; ptr = ptr->link)
		env[length++] = str_concat(NULL, "=", ptr->key, ptr->value);
	env[length] = NULL;

	return (env);
}

shell_dict_s *build_dict_from_env(shell_dict_s **head_ptr, char **env)
{
	shell_dict_s *new_node, *prev, *tail;
	ssize_t len = 0;
	char *env_str = NULL;

	prev = NULL;
	tail = *head_ptr;

	while (*env)
	{
		env_str = _strdup(*env);
		if (env_str == NULL)
			return (NULL);
		len = _strchr(*env, '=');
		if (len == -1)
		{
			free_all(1, env_str);
			return (NULL);
		}

		env_str[len] = '\0';
		new_node = add_dict_to_the_end(head_ptr, env_str, env_str + len + 1);
		free_all(1, env_str);

		if (tail)
			prev->link = new_node;
		else
			*head_ptr = new_node;
		prev = new_node;
		env++;
	}
	return (*head_ptr);
}

shell_dict_s *build_dict_from_env_caller(char **env)
{
	shell_dict_s *head = NULL;

	if (!(env && *env))
		return (NULL);

	if (!build_dict_from_env(&head, env))
		free_dictionary(&head);
	return (head);
}
