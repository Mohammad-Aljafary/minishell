# include <minishell.h>

char    *search_env(t_env *env, char *key)
{
    while (env)
    {
        if (ft_strcmp(env->key, key) == 0)
        {
            return (env->value);
        }
        env = env->next;
    }
    return (NULL);
}

int word_split(t_token **list)
{
    t_token *lst;
    t_token *next;
    char    *tok;
    t_token *node;
    t_token *last_inserted;
    char    *temp;

    lst = *list;
    temp = NULL;
    while (lst)
    {
        next = lst->next;
        if (lst->expaneded && lst->quotes != DOUBLE_QUOTE)
        {
            tok = ft_strtok(lst->word, " \t");
            last_inserted = lst;
            while (tok != NULL)
            {
                temp = ft_strdup(tok);
                if (!temp)
                    return (0);
                node = create(temp);
                if (!node)
                {
                    free (temp);
                    return (0);
                }
                add_node_token(list, last_inserted, node);
                last_inserted = node;
                tok = ft_strtok(NULL, " \t");
            }
            delete_ptr(list, lst);
        } 
        lst = next;
    }
    return (1);
}

int remove_quotes(char **line1)
{
    int         i;
    int         j;
    char        q;
    char        *temp;
    char        *line;
    t_token     *lst;
    t_token     *node;

    i = 0;
    lst = NULL;
    line = *line1;
    while (line[i])
    {
        if (line[i] == '"' || line[i] == '\'')
        {
            q = line[i++];
            j = i;
            while (line[j] && line[j] != q)
                j++;
            if (!line[j])
                return (free_return(&lst));
            temp = ft_substr(line, i, j - i);
            if (!temp)
                return (free_return(&lst));
            if (line[j] == q)
                j++;
        }
        else
        {
            j = i;
            while (line[j] && line[j] != '"' && line[j] != '\'')
                j++;
            temp = ft_substr(line, i, j - i);
            if (!temp)
                return (free_return(&lst));
        }
        node = create(temp);
        if (!node)
        {
            free(temp);
            return (free_return(&lst));
        }
        add_back(&lst, node);
        i = j;
    }
    if (!join_strings(lst, line1, node)) 
        return (free_return(&lst));
    clear_list(&lst);
    return (1);
}

