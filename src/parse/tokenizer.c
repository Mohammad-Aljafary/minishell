
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

int	tokenize(char *line, t_token **list)
{
	int		i;
	int		j;
	t_token	*node;
	char	q;
	int		len;
	char	*temp;
	int		flag; // here

	i = 0;
	len = 0;
	flag = 0;
	while (line[i])
	{
		flag = 0;
		while (is_whitespace(line[i]))
			i++;
		if (!line[i])
			break ;
		if (!is_whitespace(line[i]) && !is_operator(line[i]))
		{
			j = i;
			while (line[j] && !is_whitespace(line[j]) && !is_operator(line[j]))
			{
				if (line[j] == '"' || line[j] == '\'')
				{
					q = line[j++];
					while (line[j] && line[j] != q)
						j++;
					if (!line[j])
					{
						ft_putstr_fd("syntax error\n", 2);
						return (0);
					}
					if (line[j] == q)
						j++;
					if (q == '\'')
						// here i put a flag that we found a quotes to put it in the token
						flag = 1;
					// cause we remove the quotes in the expander i needed to put it
					else if (q == '"')
						// due to some edge cases we gonna face in the execution
						flag = 2;
					// i'll leave the norm for you i know that you can do it =)
				}
				else
					j++;
			}
			temp = ft_substr(line, i, j - i);
			if (!temp)
				return (0);
			node = create(temp);
			if (!node)
			{
				free(temp);
				return (0);
			}
			if (flag == 1)
				node->quotes = SINGLE_QOUTE;
			else if (flag == 2)
				node->quotes = DOUBLE_QUOTE; // here is the changes
			add_back(list, node);
			i = j;
		}
		else if (is_operator(line[i]))
		{
			len = get_op_len(&line[i]);
			temp = ft_substr(line, i, len);
			if (!temp)
				return (0);
			node = create(temp);
			if (!node)
			{
				free(temp);
				return (0);
			}
			add_back(list, node);
			i += len;
		}
	}
	return (1);
}
