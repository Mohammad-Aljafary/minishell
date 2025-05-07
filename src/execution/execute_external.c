#include <minishell.h>

char	*find_cmd_path(t_token *cmd, int *exit_status, t_all *all)
{
	char	*path;
	char	**splitted_path;

	path = search_env(all->env_lst, "PATH");
	if (!path)
	{
		ft_fprintf(2, "%s: No such file or directory\n", cmd->word);
		*exit_status = 127;
		return (NULL);
	}
	splitted_path = ft_split(path, ':');
	if (!splitted_path)
		return (NULL);
	path = access_path(cmd, splitted_path, exit_status);
	ft_free_split(splitted_path);
	if (!path)
	{
		if (*exit_status == 127)
			ft_fprintf(2, "%s: command not found\n", cmd->word);
		else if (*exit_status == 126)
			ft_fprintf(2, "%s: Permission denied\n", cmd->word);
		clear_all(all);
		exit(*exit_status);
	}
	return (path);
}

void	run_external(t_token *cmd, int *exit_status, t_all *all)
{
	char	**envp;
	char	*path;

	path = check_cmd(cmd, exit_status, all);
	if (!path)
	{
		clear_all(all);
		exit(*exit_status);
	}
	envp = list_to_arr(all->env_lst);
	if (!envp)
	{
		clear_all(all);
		exit(*exit_status);
	}
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	execve(path, cmd->args, envp);
	perror("execve");
	free(path);
	ft_free_split(envp);
	clear_all(all);
	exit(EXIT_FAILURE);
}

void	duplicate_pipe(int pipefd[2], int *prev)
{
	if (*prev != -1)
	{
		dup2(*prev, STDIN_FILENO);
		close(*prev);
	}
	if (pipefd[1] != -1)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
	if (pipefd[0] != -1)
		close(pipefd[0]);
}

void	track_child(int *prev, int pipefd[2], t_all *all, int id)
{
	if (*prev != -1)
		close(*prev);
	if (pipefd[1] != -1)
		close(pipefd[1]);
	*prev = pipefd[0];
	all->last_pid = id;
	all->num_of_child++;
}

void	execute_external(t_token *cmd, t_all *all, t_token *node, int *prev)
{
	pid_t	id;

	id = fork();
	if (id == -1)
	{
		perror("fork failure");
		all->exit_status = 1;
		return ;
	}
	else if (id == 0)
	{
		if (check_type(cmd) != NOT_DEFINED && check_type(cmd) != PIPE)
			handle_redirection_node(&node, cmd, all, prev);
		duplicate_pipe(all->pipefd, prev);
		all->exit_status = apply_redirection(&node, cmd, 1, all);
		ft_free_split(all->heredoc);
		if (all->exit_status != 0)
		{
			clear_all(all);
			exit(all->exit_status);
		}
		if (is_built_in(cmd))
			run_built_in(cmd, &all->exit_status, all, 1);
		else
			run_external(cmd, &all->exit_status, all);
	}
	track_child(prev, all->pipefd, all, id);
}
