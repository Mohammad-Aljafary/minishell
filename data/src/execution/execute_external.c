/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_external.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 07:38:04 by taabu-fe          #+#    #+#             */
/*   Updated: 2025/05/10 07:15:09 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

void	run_command(t_token *cmd, t_all *all)
{
	if (is_built_in(cmd))
		run_built_in(cmd, &all->exit_status, all, 1);
	else
		run_external(cmd, &all->exit_status, all);
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
		if (check_redirection(cmd) || cmd->type == HERE_DOC)
			handle_redirection_node(&node, cmd, all, prev);
		duplicate_pipe(all->pipefd, prev);
		all->exit_status = apply_redirection(&node, cmd, 1, all);
		ft_free_split(all->heredoc);
		if (all->exit_status != 0)
		{
			clear_all(all);
			exit(all->exit_status);
		}
		run_command(cmd, all);
	}
	track_child(prev, all->pipefd, all, id);
}
