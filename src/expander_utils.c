#include <minishell.h>

int handle_variable(t_token **list, char *token, int *i)
{
    int j; 
    char *temp;
    t_token *node;

    j = *i + 1;
    while ((token[j] && (ft_isalnum(token[j]) || token[j] == '_')) || token[j] == '?')
        j++;
    if (j > *i)
    {
        temp = ft_substr(token, *i, j - *i);
        if (!temp)
            return (0);
        node = create(temp);
        if (!node)
        {
            free (temp);
            return (0);
        }
        add_back(list, node);
        *i = j;
    }
    return (1);
}

int add_normal_text(t_token **list, char *token, int *i)
{
    int j; 
    char *temp;
    t_token *node;

    j = *i;
    while (token[j] && token[j] != '"' && token[j] != '\'' && token[j] != '$')
        j++;
    if (j > *i)
    {
        temp = ft_substr(token, *i, j - *i);
        if (!temp)
            return (0);
        node = create(temp);
        if (!node)
        {
            free (temp);
            return (0);
        }
        add_back(list, node);
        *i = j;
    }
    return (1);
}

int handle_single_quotes(t_token **list, char *token, int *i)
{
    int j;
    char *temp;
    t_token *node;

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
            free (temp);
            return (0);
        }
        node->type = s_quote;
        add_back(list, node);
        *i = j + 1;
    }
    return (1);
}

int handle_double_utile(t_token **list, char *token, int length, int *i)
{
    char    *temp;
    t_token *node;

    temp = NULL;
    node = NULL;
    temp = ft_substr(token, *i, length);
    if (!temp)
        return (0);
    node = create(temp);
    if(!node)
    {
        free (temp);
        return (0);
    }
    add_back(list, node);
    return (1);
}

int handle_double_quotes(t_token **list, char *token, int *i)
{
    int j;

    j = ++*i;
    while (token[j] && token[j] != '"')
    {
        if (token[j] == '$')
        {
            if (j > *i)
            {
                if (!handle_double_utile(list, token, j - *i, i))
                    return (0);
            }
            handle_variable(list, token, &j);
            *i = j;
            continue;
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

int qoutes (char *token, int *i, t_token **list)
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
		if (!handle_variable(list, token, i))
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

