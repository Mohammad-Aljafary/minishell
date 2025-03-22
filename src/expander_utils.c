#include <minishell.h>

void handle_variable(t_token **list, char *token, int *i)
{
    int j; 
    char *temp;
    t_token *node;

    j = *i + 1;
    while (token[j] && (ft_isalnum(token[j]) || token[j] == '_'))
        j++;
    if (j > *i)
    {
        temp = ft_substr(token, *i, j - *i);
        if (!temp)
            return;
        node = create(temp);
        add_back(list, node);
        *i = j;
    }
}

void add_normal_text(t_token **list, char *token, int *i)
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
            return;
        node = create(temp);
        add_back(list, node);
        *i = j;
    }
}

void handle_single_quotes(t_token **list, char *token, int *i)
{
    int j;
    char *temp;
    t_token *node;

    j = *i + 1;
    while (token[j] && token[j] != '\'')
        j++;

    if (token[j] == '\'')
    {
        temp = ft_substr(token, *i, j - *i + 1);
        if (!temp)
            return;
        node = create(temp);
        node->type = s_quote;
        add_back(list, node);
        *i = j + 1;
    }
}

void handle_double_quotes(t_token **list, char *token, int *i)
{
    int j;
    char *temp;
    t_token *node;

    j = *i + 1;
    while (token[j] && token[j] != '"')
    {
        if (token[j] == '$')
        {
            if (j >= *i + 1)
            {
                temp = ft_substr(token, *i, j - *i);
                if (!temp)
                    return;
                node = create(temp);
                add_back(list, node);
            }
            handle_variable(list, token, &j);
            *i = j;
            continue;
        }
        j++;
    }
    if (token[j] == '"')
    {
        temp = ft_substr(token, *i, j - *i + 1);
        if (!temp)
            return;
        node = create(temp);
        add_back(list, node);
        *i = j + 1;
    }
}

void break_string(t_token **list, char *token)
{
    int i = 0;

    while (token[i])
    {
        add_normal_text(list, token, &i);

        if (token[i] == '\'')
            handle_single_quotes(list, token, &i);
        else if (token[i] == '"')
            handle_double_quotes(list, token, &i);
        else if (token[i] == '$')
            handle_variable(list, token, &i);
        else
            i++;
    }
}
