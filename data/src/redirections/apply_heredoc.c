/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taabu-fe <taabu-fe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 07:39:05 by taabu-fe          #+#    #+#             */
/*   Updated: 2025/05/31 14:00:44 by taabu-fe         ###   ########.fr       */
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
	if (!heredoc)
		return ;
	while (heredoc[i])
	{
		if (unlink(heredoc[i]) == -1)
			return ;
		free(heredoc[i]);
		i++;
	}
	if (heredoc)
		free(heredoc);
	heredoc = NULL;
}

// Check if file doesn't exist due to previous creation failures
// In this case, skip the error message to avoid duplicate messages
// File doesn't exist, likely due to creation failure
// Error was already reported during creation
int	open_heredoc(char *filename, int *in_fd)
{
	*in_fd = open(filename, O_RDONLY);
	if (*in_fd == -1)
	{
		if (access(filename, F_OK) == -1)
			return (1);
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

// For system call errors in heredoc creation,
// use a placeholder to indicate failed heredoc
// This allows the shell to continue running
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
				num_heredoc[i] = ft_strdup("/dev/null");
				if (!num_heredoc[i])
					return (NULL);
			}
			i++;
		}
		node = node->next;
	}
	num_heredoc[i] = NULL;
	return (num_heredoc);
}
