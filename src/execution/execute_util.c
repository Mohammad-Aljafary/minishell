#include <minishell.h>

void	handle_pipe_or_exit(t_all *all)
{
	perror("pipe");
	ft_free_split(all->heredoc);
	clear_all(all);
	exit(EXIT_FAILURE);
}

void	find_file(t_token *cmd, t_token *list, int *i)
{
	while (list != cmd)
	{
		if (list->type == HERE_DOC)
			*i += 1;
		list = list->next;
	}
}

void	wait_status(t_all *wait_statuss)
{
	int		status;
	pid_t	pid;

	while (wait_statuss->num_of_child)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == wait_statuss->last_pid)
		{
			if (WIFEXITED(status))
				wait_statuss->exit_status = WEXITSTATUS(status);
			else
				wait_statuss->exit_status = 1;
		}
		if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGQUIT)
				write(2, "Quit (core dumped)\n", 20);
			wait_statuss->exit_status = WTERMSIG(status) + 128;
			g_sig = 0;
		}
		wait_statuss->num_of_child--;
	}
}
