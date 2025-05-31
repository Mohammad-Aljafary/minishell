/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taabu-fe <taabu-fe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 07:38:33 by taabu-fe          #+#    #+#             */
/*   Updated: 2025/05/08 07:38:34 by taabu-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	replace(t_token *p, t_all *all)
{
	while (p)
	{
		if (!process_token(p, all))
			return (0);
		p = p->next;
	}
	return (1);
}

size_t	calculate_tokens_length(t_token *ptr)
{
	size_t	length;

	length = 0;
	while (ptr)
	{
		if (ptr->word)
			length += ft_strlen(ptr->word);
		ptr = ptr->next;
	}
	return (length);
}

static int	process_token_2(t_token *head, t_all *all)
{
	t_token	*p;

	p = NULL;
	if (!break_string(&p, head->word))
		return (0);
	if (!replace(p, all))
		return (free_return(&p));
	if (!join_strings(p, &head->word, head))
		return (free_return(&p));
	clear_list(&p);
	return (1);
}

static int	expand_tokens(t_token **tok_lst, t_all *all)
{
	t_token	*head;

	head = *tok_lst;
	while (head)
	{
		if (head->type == DELIMITER && head->quotes != NOT_QUOTE)
		{
			if (!remove_quotes(&head->word))
				return (0);
		}
		else if (head->type != DELIMITER && check_type(head) == NOT_DEFINED)
		{
			if (!process_token_2(head, all))
				return (0);
		}
		head = head->next;
	}
	return (1);
}

int	expander(t_token **tok_lst, t_all *all)
{
	if (!expand_tokens(tok_lst, all))
		return (0);
	if (!word_split(tok_lst))
		return (0);
	parser2(*tok_lst);
	return (1);
}
