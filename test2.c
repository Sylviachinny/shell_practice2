#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/*Replace with the actual definitions of env_t and shell_dict_s*/
/*and the required functions if not already defined*/
typedef struct env{
	char *key;
	char *val;
	struct env_t *next;
} env_t;

env_t *_env_to_dict(env_t **tailptr, char **env);
/*senior programmer's version*/
env_t *add_dict_node_end(env_t **headptr, const char *key, const char *val)
{
	env_t *new;

	if (!headptr)
		return (NULL);
	if (*headptr)
		return (add_dict_node_end(&((*headptr)->next), key, val));

	new = malloc(sizeof(env_t));
	if (!new)
		return (NULL);

	new->key = strdup(key);
	new->val = strdup(val);
	new->next = NULL;

	*headptr = new;
	return (new);
}

void free_dict(env_t *headptr)
{
	if (!headptr)
		return;

	free_dict(headptr->next);
	free(headptr->key);
	free(headptr->val);
	free(headptr);
}

env_t *env_to_dict(char **env)
{
	env_t *head = NULL;

	if (!_env_to dict(&head, env))
		free_dict(head);
	return (head);
}

env_t *_env_to_dict(env_t **tailptr, char **env)
{
	env_t *tail;
	char *env_str;
	ssize_t key_len;

	if (!env)
		return (*tailptr);

	env_str = strdup(*env);
	if (!env_str)
		return (NULL);

	key_len = strchr(*env, '=');
	if (key_len == -1)
		return (NULL);

	env_str[key_len] = '\0';
	tail = add_dict_node_end(tailptr, env_str, env_str + key_len + 1);
	free(env_str);

	return (_env_to_dict(&tail, env + 1));
}

typedef struct shell_dict_s{
	char *key;
	char *value;
	struct shell_dict_s *link;
} shell_dict_s;

shell_dict_s *add_dict_to_the_end(shell_dict_s **headptr, const char key, const char *value)
{
	shell_dict_s *new_node, *ptr;

	if (!headptr)
		return (NULL);
	new_node = malloc(sizeof(shell_dict_s));
	if (!new_node)
		return (NULL);
	new_node->key = strdup(key);
	new_node->value = strdup(value);
	new_node->link = NULL;

	if (*headptr == NULL)
		*headptr = new_node;
	else
	{
		ptr = *headptr;
		while (ptr->link != NULL)
			ptr = ptr->link;
		ptr->link = new_node;
	}
	return (new_node);
}
void free_dictionary(env_t *headptr)
{
	if (!headptr)
		return;

	free_dict(headptr->next);
	free(headptr->key);
	free(headptr->val);
	free(headptr);
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
		env_str = strdup(*env);
		if (env_str == NULL)
			return (NULL);
		len = strchr(*env, '=');
		if (len == -1)
		{
			free(env_str);
			return (NULL);
		}

		env_str[len] = '\0';
		new_node = add_dict_to_the_end(head_ptr, env_str, env_str + len + 1);
		free(env_str);

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
	shell_dict_s *head;
	if (!(env && *env))
		return (NULL);

	if (!build_dict_from_env(&head, env))
		free_dictionary(head);
	return (head);
}

int main(void)
{
	/*Test environment variable (replace with actual values)*/
	char *test_env[] = {
		"VAR1=Value1",
		"VAR2=Value2",
		"VAR3=Value3",
		NULL /*End of environment variables*/
	}

	/* Test Senior programmer's version*/
	env_t *senior_result = env_to_dict(test_env);

	/*Test your version*/
	shell_dict_s *your_result = build_dict_from_env_caller(test_env);

	/*Print and check the results (replace with appropriate printing)*/
	printf("Senior Programmer's Version Result:\n");
	/*Print senior_result here (format according to env_t structure)*/

	printf("\nYour Version Result:\n");
	/*Print your_result here (format according to shell_dict_s structure)*/

	/*Free memory if needed*/
	free_dict(&senior_result);
	/*Free your_result if needed*/

	return 0;
}
