/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 07:39:14 by taabu-fe          #+#    #+#             */
/*   Updated: 2025/05/08 19:24:44 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	file_exist(char *filename)
{
	struct stat	buffer;

	if (stat(filename, &buffer) == 0)
		return (1);
	return (0);
}

int	redirect_in(int in_fd, int *origin_in, int in_child)
{
	if (!in_child)
	{
		*origin_in = dup(STDIN_FILENO);
		if (*origin_in == -1)
		{
			perror("dup_out fail");
			return (1);
		}
	}
	if (dup2(in_fd, STDIN_FILENO) == -1)
	{
		perror("dup2_out fail");
		return (1);
	}
	close(in_fd);
	return (0);
}

int	open_in(char *file, int *in_fd)
{
	*in_fd = open(file, O_RDONLY);
	if (*in_fd == -1)
	{
		perror(file);
		return (1);
	}
	return (0);
}

int	apply_re_in(t_token **re_token, t_token *command)
{
	if (!(*re_token)->next)
	{
		ft_fprintf(2, "%s: ambiguous redirect\n", (*re_token)->word);
		return (1);
	}
	if (!check_ambigious((*re_token)->next))
	{
		ft_fprintf(2, "%s: ambiguous redirect\n", (*re_token)->next->word);
		return (1);
	}
	if (command->in_fd != -1)
		close(command->in_fd);
	if (open_in((*re_token)->next->word, &command->in_fd))
		return (1);
	*re_token = (*re_token)->next->next;
	return (0);
}
