/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taabu-fe <taabu-fe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 07:38:56 by taabu-fe          #+#    #+#             */
/*   Updated: 2025/05/08 07:38:57 by taabu-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_type(t_token *list)
{
	if (ft_strcmp(list->word, ">") == 0)
		return (OUT_RE);
	else if (ft_strcmp(list->word, "<") == 0)
		return (IN_RE);
	else if (ft_strcmp(list->word, "|") == 0)
		return (PIPE);
	else if (ft_strcmp(list->word, ">>") == 0)
		return (APPENDS);
	else if (ft_strcmp(list->word, "<<") == 0)
		return (HERE_DOC);
	else
		return (NOT_DEFINED);
}

int	check_redirection(t_token *list)
{
	t_token	*lst;

	lst = list;
	if (!list)
		return (-1);
	if (lst->type == APPENDS || lst->type == IN_RE || lst->type == OUT_RE)
		return (1);
	return (0);
}

void	set_command_or_args(t_token *lst)
{
	t_token	*p;

	if (!lst->prev || lst->prev->type == PIPE)
		lst->type = COMMAND;
	else if (lst->prev->type == COMMAND || lst->prev->type == ARGS)
		lst->type = ARGS;
	else if (check_redirection(lst->prev))
		lst->type = FILES;
	else if (lst->prev->type == HERE_DOC)
		lst->type = DELIMITER;
	else if (lst->prev->type == FILES || lst->prev->type == DELIMITER)
	{
		p = lst->prev;
		while (p && p->type != PIPE)
		{
			if (p->type == COMMAND)
			{
				lst->type = ARGS;
				return ;
			}
			p = p->prev;
		}
		lst->type = COMMAND;
	}
}

void	parser(t_token **list)
{
	t_token	*lst;

	if (!list || !*list)
		return ;
	lst = *list;
	while (lst)
	{
		lst->type = check_type(lst);
		if (lst->type == NOT_DEFINED)
			set_command_or_args(lst);
		lst = lst->next;
	}
}

void	parser2(t_token *list)
{
	while (list)
	{
		if (list->type == NOT_DEFINED)
		{
			if (!list->prev || list->prev->type == PIPE)
				list->type = COMMAND;
			else if (list->prev->type == ARGS || list->prev->type == COMMAND)
				list->type = ARGS;
			else if (list->prev->type == IN_RE || list->prev->type == OUT_RE
				|| list->prev->type == FILES || list->prev->type == APPENDS)
				list->type = FILES;
		}
		list = list->next;
	}
}
