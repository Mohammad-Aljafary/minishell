#include <minishell.h>

int	add_token(t_token **lst, char *str)
{
	t_token	*node;

	node = create(str);
	if (!node)
	{
		free(str);
		return (0);
	}
	add_back(lst, node);
	return (1);
}

static int	handle_quoted_segment(char *line, int *i, t_token **lst)
{
	char	q;
	char	*temp;
	int		j;

	q = line[(*i)++];
	j = *i;
	while (line[j] && line[j] != q)
		j++;
	if (!line[j])
		return (0);
	temp = ft_substr(line, *i, j - *i);
	if (!temp)
		return (0);
	if (!add_token(lst, temp))
		return (0);
	*i = j + 1;
	return (1);
}

static int	handle_unquoted_segment(char *line, int *i, t_token **lst)
{
	int		j;
	char	*temp;

	j = *i;
	while (line[j] && line[j] != '"' && line[j] != '\'')
		j++;
	temp = ft_substr(line, *i, j - *i);
	if (!temp)
		return (0);
	if (!add_token(lst, temp))
		return (0);
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
			ret = handle_dollar_sign(p, all, i);
			if (ret == 0)
				return (0);
			if (ret == -1)
				break ;
			i = ret;
		}
		else
			i++;
	}
	return (1);
}
