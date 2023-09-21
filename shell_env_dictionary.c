#include "dictionary.h"
#include "main.h"

/**
 * add_dict_to_the_end - Add a new node with key and
 * value to the end of a linked list
 * @headptr: A pointer to the head of the linked list.
 * @key: The key to be added to the new node.
 * @value: The value associated with the key.
 *
 * Return: A pointer to the newly created node, or NULL on failure
 */
shell_dict_s *add_dict_to_the_end(shell_dict_s **headptr,
		const char *key, const char *value)
{
	shell_dict_s *new_node, *ptr;

	if (!headptr)
		return (NULL);
	new_node = malloc(sizeof(shell_dict_s));
	if (!new_node)
		return (NULL);
	new_node->key = _strdup(key);
	new_node->value = _strdup(value);
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

/**
 * get_value - Retrieve the value associated with a key in a linked list
 * @head: The head of the linked list.
 * @key: The key to search for.
 *
 * Return: The value associated with the key, or NULL if not found.
 */
char *get_value(shell_dict_s *head, const char *key)
{
	if (key == NULL)
		return (NULL);
	while (head)
	{
		if (_strcmp(head->key, key) == 0)
			return (head->value);
		head = head->link;
	}
	return (NULL);
}

/**
 * get_node - Retrieve a node with a specific key in a linked list.
 * @head: The head of the linked list.
 * @key: They key to search for.
 *
 * Return: A poinyter to the node with the specified key, or NULL if not found.
 */
shell_dict_s *get_node(shell_dict_s *head, const char *key)
{
	if (head == NULL)
		return (NULL);
	while (head)
	{
		if (_strcmp(head->key, key) == 0)
			return (head);
		head = head->link;
	}
}

/**
 * delete_nodes - delete nodes with a specific key from a linked list
 * @headptr: A pointer to the head of the linked list
 * @key: The key to search for and delete.
 *
 * Return: A pointer to the updated head of the linked list.
 */
shell_dict_s *delete_nodes(shell_dict_s **headptr, const char key)
{
	shell_dict_s *temp, *current, *prev;

	prev = NULL;

	if (!(headptr && *headptr))
		return (NULL);
	current = *headptr;

	while (current)
	{
		if (_strcmp(current->key, key) == 0)
		{
			if (prev)
				prev->link = cuurent->link;
			*headptr = current->link;
			temp = current;
			current = current->link;
			free_all(3, temp->key, temp->value, temp);
		}
		else
		{
			prev = current->link;
			current = current->link;
		}
	}
	return (*headptr);
}

/**
 * free_dictionary - Free all memory associated with a linked list
 * @headptr: A pointer to the head of the linked list.
 */
void free_dictionary(shell_dict_s **headptr)
{
	if (*headptr == NULL)
		return;
	free_dictionary(&((*headptr)->link));
	free_all(3, (*headptr)->key, (*headptr)->value, *headptr);
	*headptr = NULL;
}
