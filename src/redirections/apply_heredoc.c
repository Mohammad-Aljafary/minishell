/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taabu-fe <taabu-fe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 07:39:05 by taabu-fe          #+#    #+#             */
/*   Updated: 2025/05/14 13:09:43 by taabu-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	setup_heredoc_signals(void)
{
	signal(SIGINT, sigint_handler_heredoc);
	signal(SIGQUIT, SIG_IGN);
}

void	unlinks(char **heredoc)
{
	int	i;

	i = 0;
	while (heredoc[i])
	{
		if (unlink(heredoc[i]) == -1)
			return ;
		free(heredoc[i]);
		i++;
	}
	if (heredoc)
		free(heredoc);
}

int	open_heredoc(char *filename, int *in_fd)
{
	*in_fd = open(filename, O_RDONLY);
	if (*in_fd == -1)
	{
		perror(filename);
		return (1);
	}
	return (0);
}

int	apply_here(t_token *cmd, char *filename, t_token **re_token)
{
	if (cmd->in_fd > 0)
		close(cmd->in_fd);
	if (open_heredoc(filename, &cmd->in_fd))
		return (1);
	*re_token = (*re_token)->next->next;
	return (0);
}

char	**apply_heredoc(t_all *lists)
{
	char	**num_heredoc;
	int		i;
	t_token	*node;

	num_heredoc = malloc((heredoc_count(lists->tok_lst) + 1) * sizeof(char *));
	if (!num_heredoc)
		return (NULL);
	i = 0;
	node = lists->tok_lst;
	while (node)
	{
		if (node->type == HERE_DOC)
		{
			num_heredoc[i] = check_file(node->next, lists);
			if (!num_heredoc[i])
			{
				unlinks(num_heredoc);
				return (NULL);
			}
			i++;
		}
		node = node->next;
	}
	num_heredoc[i] = NULL;
	return (num_heredoc);
}
