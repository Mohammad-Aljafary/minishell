/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammad-boom <mohammad-boom@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 07:38:10 by taabu-fe          #+#    #+#             */
/*   Updated: 2025/06/12 16:10:47 by mohammad-bo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	execute_command(t_token *cmd, t_all *all, t_token *node, int *prev)
{
	if (is_built_in(cmd) && !(cmd->prev && cmd->prev->type == PIPE)
		&& all->pipefd[0] == -1 && all->pipefd[1] == -1)
		run_built_in(cmd, &all->exit_status, all, 0);
	else
		execute_external(cmd, all, node, prev);
}

void	handle_redirection_node(t_token **node, t_token *cmd, t_all *all,
		int *prev_fd)
{
	if (*prev_fd != -1)
	{
		close(*prev_fd);
		*prev_fd = -1;
	}
	if (all->pipefd[0] != -1)
		close(all->pipefd[0]);
	if (all->pipefd[1] != -1)
		close(all->pipefd[1]);
	*node = cmd;
	all->exit_status = apply_redirection(node, cmd, 1, all);
	ft_free_split(all->heredoc);
	if (all->exit_status)
	{
		*node = (*node)->next;
		clear_all(all);
		exit(EXIT_FAILURE);
	}
	if (*node && (*node)->type == PIPE)
		*node = (*node)->next;
	retrieve(cmd);
	clear_all(all);
	exit(EXIT_SUCCESS);
}

void	handle_command_node(t_token *cmd, t_token **node, t_all *lists,
		int *prev_fd)
{
	t_token	*search;

	cmd = *node;
	*node = (*node)->next;
	search = *node;
	while (search && search->type != PIPE)
		search = search->next;
	if (!search && is_built_in(cmd) && *node && !(cmd->prev
			&& cmd->prev->type == PIPE))
	{
		lists->exit_status = apply_redirection(node, cmd, 0, lists);
		if (lists->exit_status)
			return ;
	}
	else if (search && search->type == PIPE)
	{
		if (pipe(lists->pipefd) == -1)
			handle_pipe_or_exit(lists);
	}
	execute_command(cmd, lists, *node, prev_fd);
	retrieve(cmd);
	*node = search;
	if (*node && (*node)->type == PIPE)
		*node = (*node)->next;
}

void	init(t_token **cmd, t_token **node, int *prev_fd, t_all *lists)
{
	*cmd = NULL;
	*node = lists->tok_lst;
	*prev_fd = -1;
	lists->pipefd[0] = -1;
	lists->pipefd[1] = -1;
}

int	execute(t_all *lists)
{
	t_token	*node;
	t_token	*cmd;
	int		prev_fd;

	init(&cmd, &node, &prev_fd, lists);
	lists->heredoc = apply_heredoc(lists);
	if (!lists->heredoc && g_sig != 2)
		return (-1);
	if (g_sig == 2)
	{
		g_sig = 0;
		return (0);
	}
	while (node)
		handle_command_node(cmd, &node, lists, &prev_fd);
	wait_status(lists);
	if (lists->pipefd[0] != -1)
		close(lists->pipefd[0]);
	if (lists->pipefd[1] != -1)
		close(lists->pipefd[1]);
	unlinks(lists->heredoc);
	return (0);
}
