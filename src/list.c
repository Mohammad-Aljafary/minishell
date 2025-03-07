/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taabu-fe <taabu-fe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:39:29 by taabu-fe          #+#    #+#             */
/*   Updated: 2025/03/07 13:48:37 by taabu-fe         ###   ########.fr       */
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
	node->type = not_defined;
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

void	clear_list(t_token **list)
{
	t_token	*temp;

	while (*list)
	{
		temp = (*list);
		*list = (*list)->next;
		free(temp->word);
		temp->next = NULL;
		temp->prev = NULL;
		free(temp);
	}
}

void	print_list(t_token *list)
{
	while (list)
	{
		printf("%s %d\n", list->word, list->type);
		list = list->next;
	}
}
