# include <minishell.h>

int break_heredoc(t_token **list, char *str)
{
    int i = 0;
    int j;
    char *temp;
    t_token *node;

    while (str[i])
    {
        if (str[i] == '$')
        {
            j = i + 1;
            if (str[j] == '?')
                j++;
            else
                while (str[j] && (ft_isalnum(str[j]) || str[j] == '_') && str[j] != '$')
                    j++;
            if (j >= i + 1)
            {
                temp = ft_substr(str, i, j - i);
                if (!temp)
                    return (0);
                node = create(temp);
                if (!node)
                {
                    free (temp);
                    return (0);
                }
                add_back(list, node);
                i = j;
                continue;
            }
        }
        j = i;
        while (str[j] && str[j] != '$')
            j++;
        temp = ft_substr(str, i, j - i);
        if (!temp)
            return (0);
        node = create(temp);
        if (!node)
        {
            free (temp);
            return (0);
        }
        add_back(list, node);
        i = j;
    }
    return (1);
}

