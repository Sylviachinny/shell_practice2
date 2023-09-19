#ifndef _SHELL_PATH_H_
#define _SHELL_PATH_H_

#include <sys/stat.h>
#include "main.h"
#include "strtok.h"

typedef struct directory
{
	char *path;
	struct directory *link;
} directory_n;
directory_n *add_at_beg(directory_n **headptr, const char *path);
directory_n *dir_at_the_end(directory_n **dir_head, const char *path);
void free_dir(directory_n **head_ptr);

typedef struct helper
{
	const char *path;
	char delim;
} path_helper;

directory_n *path_to_list(directory_n **tail_ptr, path_helper help);
directory_n *path_wrapper(path_helper help);

typedef struct path_handler
{
	char **tokens;
	char *cwd_s;
} path_handler_s;

#endif /*SHELL_PATH_H*/
