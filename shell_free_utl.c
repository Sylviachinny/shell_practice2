#include "main.h"

int release_store_information(store_info_t *store_info)
{
	free_all(3, store_info->line, store_info->cwd_s, store_info->execute);
	store_info->line = my_getline(-1);
	release_mem(&store_info->tokens);
	store_info->cwd_s = NULL;
	store_info->execute = NULL;
	free_dictionary(&store_info->env);
	free_dir(&store_info->path);
	free_command_lst(&store_info->cmd);
	return (store_info->status);
}
