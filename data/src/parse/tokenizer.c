/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taabu-fe <taabu-fe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 07:39:01 by taabu-fe          #+#    #+#             */
/*   Updated: 2025/05/08 07:39:02 by taabu-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_token	*create_token(char *line, int i, int len)
{
	char	*temp;
	t_token	*node;

	temp = ft_substr(line, i, len);
	if (!temp)
		return (NULL);
	node = create(temp);
	if (!node)
	{
		free(temp);
		return (NULL);
	}
	return (node);
}

static int	handle_text_token(char *line, int i, t_token **list)
{
	t_token	*node;
	int		j;
	int		flag;

	flag = 0;
	if (!divide_text(line, i, &j, &flag))
		return (0);
	node = create_token(line, i, j - i);
	if (!node)
		return (0);
	if (flag == 1)
		node->quotes = SINGLE_QOUTE;
	else if (flag == 2)
		node->quotes = DOUBLE_QUOTE;
	add_back(list, node);
	return (j);
}

static int	handle_operator_token(char *line, int i, t_token **list)
{
	t_token	*node;
	int		len;

	len = get_op_len(&line[i]);
	node = create_token(line, i, len);
	if (!node)
		return (0);
	add_back(list, node);
	return (i + len);
}

static int	skip_whitespace(char *line, int i)
{
	while (is_whitespace(line[i]))
		i++;
	return (i);
}

int	tokenize(char *line, t_token **list)
{
	int	i;
	int	next_pos;

	i = 0;
	while (line[i])
	{
		i = skip_whitespace(line, i);
		if (!line[i])
			break ;
		if (!is_operator(line[i]))
		{
			next_pos = handle_text_token(line, i, list);
			if (!next_pos)
				return (0);
			i = next_pos;
		}
		else
		{
			next_pos = handle_operator_token(line, i, list);
			if (!next_pos)
				return (0);
			i = next_pos;
		}
	}
	return (1);
}
