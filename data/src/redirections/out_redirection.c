/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkurkar <mkurkar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 07:39:17 by taabu-fe          #+#    #+#             */
/*   Updated: 2025/05/30 13:53:19 by mkurkar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_ambigious(t_token *node)
{
	if (node->type == FILES)
	{
		if (node->next && node->next->type == FILES)
			return (0);
		else
			return (1);
	}
	return (0);
}
// trace this system call error this should free and close the parent process
int	redirect_out(int out_fd, int *origin_out, int in_child)
{
	if (!in_child)
	{
		*origin_out = dup(STDOUT_FILENO);
		if (*origin_out == -1)
		{
			perror("dup_out fail");
			return (1);
		}
	}
	if (dup2(out_fd, STDOUT_FILENO) == -1)
	{
		perror("dup2_out fail");
		return (1);
	}
	close(out_fd);
	return (0);
}
// trace this system call error this should free and close the parent process
int	open_file(char *file, int *out_fd, int flag)
{
	if (flag == 1)
		*out_fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else if (flag == 2)
		*out_fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (*out_fd == -1)
	{
		perror(file);
		return (1);
	}
	return (0);
}

int	apply_re_out(t_token **re_node, t_token *command, int flag)
{
	if (!(*re_node)->next)
	{
		ft_fprintf(2, "%s: ambiguous redirect\n", (*re_node)->word);
		return (1);
	}
	if (!check_ambigious((*re_node)->next))
	{
		ft_fprintf(2, "%s: ambiguous redirect\n", (*re_node)->next->word);
		return (1);
	}
	if (command->out_fd != -1)
		close(command->out_fd);
	if (open_file((*re_node)->next->word, &command->out_fd, flag))
		return (1);
	*re_node = (*re_node)->next->next;
	return (0);
}
