/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 07:38:17 by taabu-fe          #+#    #+#             */
/*   Updated: 2025/05/21 16:23:53 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	handle_redirection(t_token **next_node, t_token *node, char **heredoc,
		int *i)
{
	if ((*next_node)->type == OUT_RE)
	{
		if (apply_re_out(next_node, node, 1))
			return (1);
	}
	else if ((*next_node)->type == IN_RE)
	{
		if (apply_re_in(next_node, node))
			return (1);
	}
	else if ((*next_node)->type == APPENDS)
	{
		if (apply_re_out(next_node, node, 2))
			return (1);
	}
	else if ((*next_node)->type == HERE_DOC)
	{
		if (apply_here(node, heredoc[(*i)++], next_node))
			return (1);
	}
	else
		*next_node = (*next_node)->next;
	return (0);
}

int	redirections(t_token **next_node, t_token *node, char **heredoc, int *i)
{
	if (handle_redirection(next_node, node, heredoc, i))
		return (1);
	return (0);
}

int	apply_redirection(t_token **next_node, t_token *node, int in_child,
		t_all *all)
{
	int	i;

	i = 0;
	find_file(node, all->tok_lst, &i);
	while (*next_node && (*next_node)->type != PIPE)
	{
		if (redirections(next_node, node, all->heredoc, &i))
			return (1);
	}
	if (node->out_fd > 1)
		if (redirect_out(node->out_fd, &node->origin_out, in_child))
			return (1);
	if (node->in_fd > 0)
		if (redirect_in(node->in_fd, &node->origin_in, in_child))
			return (1);
	return (0);
}

void	retrieve(t_token *cmd)
{
	if (cmd->origin_in != -1)
	{
		if (dup2(cmd->origin_in, STDIN_FILENO) == -1)
			close(cmd->in_fd);
		cmd->in_fd = STDIN_FILENO;
		close(cmd->origin_in);
		cmd->origin_in = -1;
	}
	if (cmd->origin_out != -1)
	{
		if (dup2(cmd->origin_out, STDOUT_FILENO) == -1)
			perror("dup2_retrieve_output");
		close(cmd->origin_out);
		close(cmd->out_fd);
		cmd->out_fd = STDOUT_FILENO;
		cmd->origin_out = -1;
	}
}
