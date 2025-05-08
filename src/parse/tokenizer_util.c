/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taabu-fe <taabu-fe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 07:38:58 by taabu-fe          #+#    #+#             */
/*   Updated: 2025/05/08 07:38:59 by taabu-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int	is_operator(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

int	get_op_len(char *str)
{
	if (!str || !*str)
		return (0);
	if ((*str == '>' && *(str + 1) == '>') || (*str == '<' && *(str
				+ 1) == '<'))
		return (2);
	if (*str && is_operator(*str))
		return (1);
	return (0);
}

int	divide_by_qoute(char *line, int *flag, int *j)
{
	char	q;

	q = line[(*j)++];
	while (line[*j] && line[*j] != q)
		(*j)++;
	if (!line[*j])
	{
		ft_putstr_fd("syntax error\n", 2);
		return (0);
	}
	if (line[*j] == q)
		(*j)++;
	if (q == '\'')
		*flag = 1;
	else if (q == '"')
		*flag = 2;
	return (1);
}

int	divide_text(char *line, int i, int *j, int *flag)
{
	*j = i;
	while (line[*j] && !is_whitespace(line[*j]) && !is_operator(line[*j]))
	{
		if (line[*j] == '"' || line[*j] == '\'')
		{
			if (!divide_by_qoute(line, flag, j))
				return (0);
		}
		else
			(*j)++;
	}
	return (1);
}
