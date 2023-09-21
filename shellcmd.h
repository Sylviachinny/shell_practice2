#ifndef _SHELLCMD_H_
#define _SHELLCMD_H_

#include <unistd.h>
#include "myquote.h"
#include "getline.h"
#include "strtok.h"

/**
 * struct cmd - structure to represent command processing information.
 * @cmd_count: The count of tokens found in the command string.
 * @quote_len: The length of the current quoted section.
 * @delim_indx: The index of the delimiter wiyhin a quoted section
 * @state: The current quote_state for parsing the command string.
 */
typedef struct cmd
{
	size_t cmd_count;
	size_t quote_len;
	ssize_t delim_indx;
	quote_state state;
} cmd_t;
size_t cmd_to_split(char *cmd);

typedef struct command
{
	char **tokens;
	struct command *link;
	struct cmd_btree *b_tree;

} command_lst;

command_lst *at_the_end(command_lst **head, const char *cmd);
void free_command_lst(command_lst **head);
command_lst *del_cmd_at_pos(command_lst **head, size_t pos);
char **remove_cmd(command_lst **head);
command_lst *_update_cmd(command_lst **ptr, char *split, size_t count);
command_lst *_update_the_cmd(const char *cmd);

typedef struct cmd_btree
{
	struct cmd_btree *success;
	struct cmd_btree *failure;
	const char * const *ntmodified;
} cmd_btree_lst;
void free_command_btree(cmd_btree_lst **headptr);

#endif /*_SHELLCMD_H*/
