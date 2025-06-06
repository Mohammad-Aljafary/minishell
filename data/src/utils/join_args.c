/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taabu-fe <taabu-fe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 07:39:26 by taabu-fe          #+#    #+#             */
/*   Updated: 2025/05/08 07:39:27 by taabu-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	count_args(t_token *node, t_token **cmd)
{
	int	count;

	*cmd = NULL;
	count = 0;
	while (node)
	{
		if (node->type == COMMAND && !*cmd)
			*cmd = node;
		if (node->type == ARGS)
			count++;
		if (node->type == PIPE)
			break ;
		node = node->next;
	}
	return (count);
}

int	fill_args(t_token *cmd, t_token *node)
{
	int	i;

	i = 1;
	while (node && node->type != PIPE)
	{
		if (node->type == ARGS)
		{
			cmd->args[i++] = ft_strdup(node->word);
			if (!cmd->args[i - 1])
			{
				ft_free_split(cmd->args);
				return (0);
			}
		}
		node = node->next;
	}
	cmd->args[i] = NULL;
	if (node && node->type == PIPE && node->next)
		return (join_args(node->next));
	return (1);
}

int	allocate_args(t_token *cmd, int count)
{
	cmd->args = malloc((count + 2) * sizeof(char *));
	if (!cmd->args)
		return (0);
	cmd->args[0] = ft_strdup(cmd->word);
	if (!cmd->args[0])
	{
		ft_free_split(cmd->args);
		return (0);
	}
	return (1);
}

int	join_args(t_token *node)
{
	t_token	*cmd;
	int		count;
	int		result;

	while (node && node->type != COMMAND && node->type != PIPE)
		node = node->next;
	if (!node || node->type == PIPE)
	{
		if (node && node->type == PIPE && node->next)
			return (join_args(node->next));
		return (1);
	}
	cmd = NULL;
	count = count_args(node, &cmd);
	if (!cmd)
		return (1);
	else if (!allocate_args(cmd, count))
		return (0);
	result = fill_args(cmd, cmd->next);
	return (result);
}
