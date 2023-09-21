#include "shellcmd.h"
#include "main.h"

/**
 * at_the_end - Add a new command node at the end of the list
 * @the_end: A pointer to a pointer to the last node in the list
 * @cmd: The command string to associate with the new node
 *
 * Return: If memory allocation fails or @the_end is NULL, return NULL
 * otherwise, return a pointer to the newly created node
 */
command_lst *at_the_end(command_lst **the_end, const char *cmd)
{
	command_lst *new_node, *temp;

	if (!the_end)
		return (NULL);
	new_node = malloc(sizeof(command_lst));
	if (!new_node)
		return (NULL);
	new_node->link = NULL;
	new_node->b_tree = NULL;

	new_node->tokens = my_token(cmd);
	if (!new_node->tokens)
	{
		free_all(1, new_node);
		return (NULL);
	}
	if (!*the_end)
	{
		*the_end = new_node;
		return (new_node);
	}
	else
	{
		temp = *the_end;
		while (temp->link != NULL)
			temp = temp->link;
		temp->link = new_node;
	}
	return (new_node);
}

/**
 * free_command_lst - frees memory allocated for a linked list of command_lst
 * @head: A pointer to the head of the linked list
 *
 * This function iterates through the linked list starting from the head node,
 * frees memory associated with each node, and updates the head pointer to NULL
 */
void free_command_lst(command_lst **head)
{
	command_lst *next_node;

	while (head && *head != NULL)
	{
		next_node = (*head)->link;
		free_command_btree(&((*head)->b_tree));
		release_mem(&((*head)->tokens));
		free_all(1, *head);
		*head = next_node;
	}
	*head = NULL;
}

/**
 * free_command_btree - Frees memory allocated for a binary tree
 * of cmd_btree_lst
 * @headptr: A pointer to the root of the binary tree
 *
 * This function recursively traverses the binary tree
 * starting from the root node, frees memory associated
 * with each node, and updates the root pointer to NULL
 */
void free_command_btree(cmd_btree_lst **headptr)
{
	if (headptr && *headptr)
	{
		free_command_btree(&((*headptr)->success));
		free_command_btree(&((*headptr)->failure));
		(*headptr)->ntmodified = NULL;
		(*headptr) = NULL;
	}
}

/**
 * del_cmd_at_pos - Deletes a node at a specified position in a linked list
 * @head: Pointer to the pointer to the head of the linked list
 * @pos: The position of the node to be deleted (0-based index)
 *
 * This function deletes the node at the specified position in the linked list
 * and performs necessary memory cleanup.
 *
 * Return: Pointer to the deleted node if successful, NULL otherwise
 */
command_lst *del_cmd_at_pos(command_lst **head, size_t pos)
{
	command_lst *current = *head;
	command_lst *previous = *head;

	size_t index_es;

	if (head == NULL || *head == NULL)
		return (NULL);

	if (pos == 0)
	{
		current = (*head)->link;
		free_command_btree(&(current->b_tree));
		release_mem(&(current->tokens));
		free_all(1, current);
		(*head)->link = NULL;
		*head = (*head)->link;
		return (current);
	}
	else
	{
		for (index_es = 0; index_es < pos - 1; index_es++)
		{
			if (previous->link == NULL)
				return (NULL);
			previous = previous->link;
		}
		current = previous->link;
	}
	current = previous->link;
	previous->link = current->link;
	free_command_btree(&(current->b_tree));
	release_mem(&(current->tokens));
	free_all(1, current);
	return (current);

return (NULL);
}

/**
 * remove_cmd - Removes the first node from a linked list
 * and retrieves its tokens
 * @head: A pointer to the pointer to the head of the linked list
 *
 * This function removes the first node from the linked list pointed to
 * by 'head' and retrieves the token associated with that node.
 * It also performs memory cleanup for the removed node
 *
 * Return: a pointer to the tokens if sucessful,
 * NULL if the list is empty or 'head' is NULL.
 */
char **remove_cmd(command_lst **head)
{
	command_lst *next_node;
	char **retrieve_tok;

	if (!(head && *head))
		return (NULL);

	retrieve_tok = (*head)->tokens;
	next_node = (*head)->link;
	free_command_btree(&((*head)->b_tree));
	free_all(1, *head);

	*head = next_node;
	return (retrieve_tok);
}
