
#include <minishell.h>

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int	is_operator(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

int get_op_len(char *str)
{
    if (!str || !*str)
        return (0);
    if ((*str == '>' && *(str + 1) == '>')
        || (*str == '<' && *(str + 1) == '<'))
        return (2);
    if (*str && is_operator(*str))
        return (1);
    return (0);
}


/*void handle_operator(char *line, int *i, t_token **list)
{
	int		len;
	t_token	*node;

	len = get_op_len(&line[*i]);
		node = create(ft_substr(line, *i, len));
	add_back(list, node);
	*i += len;
}

void	tokenize(char *line, t_token **list)
{
	int		i;
	int		j;
	t_token	*node;

	i = 0;
	while(line[i])
	{
		while(is_whitespace(line[i]))
			i++;
		if (!line[i])
			break ;
		if (is_operator(line[i]))
			handle_operator(line, &i, list);
		else
		{
			j = i;
			while (line[j] && !is_whitespace(line[j]) && !is_operator(line[j]))
				j++;
			node = create(ft_substr(line, i, j - i));
			add_back(list, node);
			i = j;
		}
    }
}*/
