/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taabu-fe <taabu-fe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 07:38:52 by taabu-fe          #+#    #+#             */
/*   Updated: 2025/05/08 07:38:53 by taabu-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	checks(t_token *curr)
{
	if (!curr->next)
	{
		ft_fprintf(2, "syntax error near unexpected token `newline'\n");
		return (1);
	}
	if (check_type(curr) == PIPE && check_type(curr->next) == PIPE)
	{
		ft_fprintf(2, "syntax error near unexpected token `%s'\n",
			curr->next->word);
		return (1);
	}
	if ((check_type(curr) == OUT_RE || check_type(curr) == IN_RE
			|| check_type(curr) == APPENDS || check_type(curr) == HERE_DOC)
		&& (check_type(curr->next) != NOT_DEFINED))
	{
		ft_fprintf(2, "syntax error near unexpected token `%s'\n",
			curr->next->word);
		return (1);
	}
	return (0);
}

int	syntax_error(t_token *list)
{
	t_token	*curr;

	if (!list)
		return (0);
	curr = list;
	if (check_type(curr) == PIPE)
	{
		ft_fprintf(2, "syntax error near unexpected token `%s'\n", curr->word);
		return (1);
	}
	while (curr)
	{
		if (check_type(curr) != NOT_DEFINED)
		{
			if (checks(curr))
				return (1);
		}
		curr = curr->next;
	}
	return (0);
}
