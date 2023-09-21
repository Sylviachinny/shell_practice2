#include "main.h"

void handle_ctrl_c(int sig __attribute__((unused)))
{
	write(1, "\nshell$ ", 9);
	signal(SIGINT, handle_ctrl_c);
}

int main(int ac, char **av)
{
	store_info_t *shell_info;

	shell_info = init_prmpt(av, ac);

	signal(SIGINT, handle_ctrl_c);

	while (read_usr_input(shell_info))
	{
		while ((shell_info->tokens = remove_cmd(&(shell_info->cmd))))
		{
			executeShellCommand(shell_info);
			release_mem(&(shell_info->tokens));
		}
	       free_all(1, shell_info->line);
	       shell_info->line = NULL;
	}
	if (shell_info->interactive)
		write(STDOUT_FILENO, "\n", 2);
	if (shell_info->file)
		close(shell_info->fileno);
	exit(release_store_information(shell_info));
}
