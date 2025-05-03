# include <minishell.h>

int add_text_heredoc(char *str, t_token **list, int *i, int *j)
{
    char    *temp;
    t_token *node;
    
    temp = NULL;
    node = NULL;
    while (str[*j] && str[*j] != '$')
        *j++;
    temp = ft_substr(str, *i, *j - *i);
    if (!temp)
        return (0);
    node = create(temp);
    if (!node)
    {
        free (temp);
        return (0);
    }
    add_back(list, node);
    *i = *j;
    return (1);
}

int add_expand_node(char *str, t_token **list, int *i, int *j)
{
    char    *temp;
    t_token *node;

    temp = NULL;
    node = NULL;
    if (str[*j] == '?')
        *j++;
    else
        while (str[*j] && (ft_isalnum(str[*j]) || str[*j] == '_') && str[*j] != '$')
            *j++;
    if (*j >= *i + 1)
    {
        temp = ft_substr(str, *i, *j - *i);
        if (!temp)
            return (0);
        node = create(temp);
        if (!node)
        {
            free (temp);
            return (0);
        }
        add_back(list, node);
    }
    *i = *j;
    return (1);
}

int break_heredoc(t_token **list, char *str)
{
    int i;
    int j;

    i = 0;
    while (str[i])
    {
        if (str[i] == '$')
        {
            j = i + 1;
            if (!add_expand_node(str, list, &i, &j))
                return (0);
            continue;
        }
        j = i;
        if (!add_text_heredoc(str, list, &i, &j))
            return (0);
    }
    return (1);
}
