#include <minishell.h>

int	handle_single_quotes(t_token **list, char *token, int *i)
{
	int		j;
	char	*temp;
	t_token	*node;

	j = ++*i;
	while (token[j] && token[j] != '\'')
		j++;
	if (token[j] == '\'')
	{
		temp = ft_substr(token, *i, j - *i);
		if (!temp)
			return (0);
		node = create(temp);
		if (!node)
		{
			free(temp);
			return (0);
		}
		node->type = S_QOUTE;
		add_back(list, node);
		*i = j + 1;
	}
	return (1);
}

int	handle_double_utile(t_token **list, char *token, int length, int *i)
{
	char	*temp;
	t_token	*node;

	node = NULL;
	temp = ft_substr(token, *i, length);
	if (!temp)
		return (0);
	node = create(temp);
	if (!node)
	{
		free(temp);
		return (0);
	}
	add_back(list, node);
	return (1);
}

int	handle_double_quotes(t_token **list, char *token, int *i)
{
	int	j;

	j = ++(*i);
	while (token[j] && token[j] != '"')
	{
		if (token[j] == '$')
		{
			if (j > *i)
				if (!handle_double_utile(list, token, j - *i, i))
					return (0);
			if (!handle_variable(list, token, &j))
				return (0);
			*i = j;
			continue ;
		}
		j++;
	}
	if (token[j] == '"')
	{
		if (!handle_double_utile(list, token, j - *i, i))
			return (0);
		*i = j + 1;
	}
	return (1);
}
