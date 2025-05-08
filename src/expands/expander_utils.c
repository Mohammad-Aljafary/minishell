/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taabu-fe <taabu-fe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 07:38:30 by taabu-fe          #+#    #+#             */
/*   Updated: 2025/05/08 07:38:31 by taabu-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	handle_variable(t_token **list, char *token, int *i, int check)
{
	int		j;
	t_token	*node;

	j = *i + 1;
	if (token[j] == '?')
		j++;
	else
		while (token[j] && (ft_isalnum(token[j]) || token[j] == '_'))
			j++;
	if (j > *i + 1)
	{
		node = create_token(token, *i, j - *i);
		if (!node)
			return (0);
		if (!check)
			node->quotes = DOUBLE_QUOTE;
		add_back(list, node);
	}
	*i = j;
	return (1);
}

int	add_normal_text(t_token **list, char *token, int *i)
{
	int		j;
	t_token	*node;

	j = *i;
	while (token[j] && token[j] != '"' && token[j] != '\'' && token[j] != '$')
		j++;
	if (j > *i)
	{
		node = create_token(token, *i, j - *i);
		if (!node)
			return (0);
		add_back(list, node);
	}
	*i = j;
	return (1);
}

int	qoutes(char *token, int *i, t_token **list)
{
	if (token[*i] == '\'')
	{
		if (!handle_single_quotes(list, token, i))
		{
			clear_list(list);
			return (0);
		}
	}
	else if (token[*i] == '"')
	{
		if (!handle_double_quotes(list, token, i))
		{
			clear_list(list);
			return (0);
		}
	}
	return (1);
}

int	handle_quotes_and_var(t_token **list, char *token, int *i)
{
	if (token[*i] == '\'' || token[*i] == '"')
	{
		if (!qoutes(token, i, list))
			return (0);
	}
	else if (token[*i] == '$')
	{
		if (!handle_variable(list, token, i, 1))
		{
			clear_list(list);
			return (0);
		}
	}
	return (1);
}

int	break_string(t_token **list, char *token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (!handle_quotes_and_var(list, token, &i))
			return (0);
		else if (!add_normal_text(list, token, &i))
		{
			clear_list(list);
			return (0);
		}
	}
	return (1);
}
