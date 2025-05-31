/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_util_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taabu-fe <taabu-fe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 07:38:24 by taabu-fe          #+#    #+#             */
/*   Updated: 2025/05/08 07:38:25 by taabu-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	handle_quoted_segment(char *line, int *i, t_token **lst)
{
	char	q;
	int		j;
	t_token	*node;

	q = line[(*i)++];
	j = *i;
	while (line[j] && line[j] != q)
		j++;
	if (!line[j])
		return (0);
	node = create_token(line, *i, j - *i);
	if (!node)
		return (0);
	add_back(lst, node);
	*i = j + 1;
	return (1);
}

static int	handle_unquoted_segment(char *line, int *i, t_token **lst)
{
	int		j;
	t_token	*node;

	j = *i;
	while (line[j] && line[j] != '"' && line[j] != '\'')
		j++;
	node = create_token(line, *i, j - *i);
	if (!node)
		return (0);
	add_back(lst, node);
	*i = j;
	return (1);
}

int	remove_quotes(char **line1)
{
	int		i;
	t_token	*lst;

	i = 0;
	lst = NULL;
	while ((*line1)[i])
	{
		if ((*line1)[i] == '"' || (*line1)[i] == '\'')
		{
			if (!handle_quoted_segment(*line1, &i, &lst))
				return (free_return(&lst));
		}
		else
		{
			if (!handle_unquoted_segment(*line1, &i, &lst))
				return (free_return(&lst));
		}
	}
	if (!join_strings(lst, line1, lst))
		return (free_return(&lst));
	clear_list(&lst);
	return (1);
}

int	process_token(t_token *p, t_all *all)
{
	int	i;
	int	ret;

	if (p->type == S_QOUTE)
		return (1);
	i = 0;
	while (p->word[i])
	{
		if (p->word[i] == '$')
		{
			ret = handle_dollar_sign(p, all, &i);
			if (ret == 0)
				return (0);
			if (ret == -1)
				break ;
		}
		else
			i++;
	}
	return (1);
}
