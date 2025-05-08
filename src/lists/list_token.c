/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taabu-fe <taabu-fe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 07:38:48 by taabu-fe          #+#    #+#             */
/*   Updated: 2025/05/08 07:38:49 by taabu-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_token	*create(char *str)
{
	t_token	*node;

	node = malloc(sizeof(t_token));
	if (!node)
		return (NULL);
	node->word = str;
	node->prev = NULL;
	node->next = NULL;
	node->type = NOT_DEFINED;
	node->quotes = NOT_QUOTE;
	node->args = NULL;
	node->in_fd = -1;
	node->out_fd = -1;
	node->origin_in = -1;
	node->origin_out = -1;
	node->expaneded = 0;
	return (node);
}

void	add_back(t_token **list, t_token *new_node)
{
	t_token	*temp;

	temp = *list;
	if (temp)
	{
		while (temp->next)
			temp = temp->next;
		temp->next = new_node;
		new_node->prev = temp;
		new_node->next = NULL;
	}
	else
	{
		*list = new_node;
		(*list)->prev = NULL;
		(*list)->next = NULL;
	}
}

void	add_node_token(t_token **list, t_token *node, t_token *new_node)
{
	t_token	*lst;

	lst = *list;
	while (lst)
	{
		if (lst == node)
		{
			new_node->next = lst->next;
			new_node->prev = lst;
			if (lst->next)
				lst->next->prev = new_node;
			lst->next = new_node;
			return ;
		}
		lst = lst->next;
	}
	add_back(list, new_node);
}

void	add_front(t_token **list, t_token *new_node)
{
	if (!list || !new_node)
		return ;
	new_node->next = *list;
	if (*list)
		(*list)->prev = new_node;
	new_node->prev = NULL;
	*list = new_node;
}

void	print_list(t_token *list)
{
	int	i;

	while (list)
	{
		printf("string:%s type:%d expanded:%d\n", list->word, list->type,
			list->expaneded);
		if (list->type == COMMAND && list->args)
		{
			i = 0;
			while (list->args[i])
			{
				printf("  arg[%d]: %s\n", i, list->args[i]);
				i++;
			}
		}
		printf("\n");
		list = list->next;
	}
}
