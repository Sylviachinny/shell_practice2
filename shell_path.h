#ifndef _SHELL_PATH_H_
#define _SHELL_PATH_H_

#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

#include "strtok.h"

typedef struct directory
{
	char *path;
	struct directory *link;
} directory_n;
directory_n *add_at_beg(directory_n **headptr, const char *path);
directory_n *dir_at_the_end(directory_n **dir_head, const char *path);
void free_dir(directory_n **head_ptr);
directory_n *path_to_list(directory_n **tail_ptr,
		const char *path, char delim);
directory_n *path_wrapper(const char *path, char delim);

#endif /*SHELL_PATH_H*/
