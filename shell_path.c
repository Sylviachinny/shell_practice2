#include "shellcmd.h"
#include "strtok.h"
#include "secondpath.h"

/**
 * handle_path - function to handle path and process it
 * @path_info: path_info to struct
 * @path_dir: path directory
 * Return: path name or NULL if not find.
 */
char *handle_path(store_info_t *path_info, directory_n *path_dir)
{
	char *pathname_se, *cmd;
	struct stat st;

	cmd = *path_info->tokens;

	while (path_dir)
	{
		if (*path_dir->path == '\0')
			pathname_se = str_concat(NULL, "/", path_info->cwd_s, cmd);
		else
			pathname_se = str_concat(NULL, "/", path_dir->path, cmd);
		if (stat(pathname_se, &st) == 0)
		{
			if ((st.st_mode & S_IFMT) != S_IFDIR)
				return (pathname_se);
		}
		free(pathname_se);
		path_dir = path_dir->link;
	}
	return (NULL);
}
