
#include <minishell.h>

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

/* void    expander(t_token *tok_lst, t_env *env_lst)
{
    char    *sub;
    char    *temp;
    char    *new_word;
    int     i, j;

    while (tok_lst)  
    {
        i = 0;
        while (tok_lst->word[i])
        {
            if (!ft_strchr(tok_lst->word, '"') && !ft_strchr(tok_lst->word, '\''))
            {
                while (tok_lst->word[i] && tok_lst->word[i] != '$')
                    i++;
                if (!tok_lst->word[i] || tok_lst->word[i] != '$')
                    break;
                j = ++i;
                while (tok_lst->word[j] && tok_lst->word[j] != ' ' && tok_lst->word[j] != '\t' && tok_lst->word[j] != '\0' && tok_lst->word[j] != '$')
                    j++;
                sub = ft_substr(tok_lst->word, i, j - i);
                temp = search_env(env_lst, sub);
                free(sub);

                if (temp)
                {
                    new_word = ft_strjoin(ft_substr(tok_lst->word, 0, i - 1), temp);
                    new_word = ft_strjoin(new_word, ft_substr(tok_lst->word, j, ft_strlen(tok_lst->word) - j));
                    free(tok_lst->word);
                    tok_lst->word = new_word;
                }
                else
                {
                    new_word = ft_substr(tok_lst->word, 0, i - 1);
                    free(tok_lst->word);
                    tok_lst->word = new_word;
                    i++;
                }
            }
            i++;
        }
        tok_lst = tok_lst->next;
    }
} */ 

int    replace_num(char **token, char *argv)
{
    char    *temp;
    char    *joined;

    if ((*token)[1] == '0')
        temp = ft_strdup(argv);
    else
        temp = ft_strdup("");
    if(!temp)
        return (0);
    joined = ft_strjoin(temp, *token + 2);
    free(temp);
    if (!joined)
        return (0);
    free(*token);
    *token = joined;
    return (1);
}

int replace_env (t_token *p, t_env *envp, int *i, int *j)
{
    char    *temp;
    char    *new_word;
    char    *env;

    temp = ft_substr(p->word, *i + 1, *j - (*i + 1));
    if (!temp)
        return (0); 
    env = search_env(envp, temp);  
    free(temp);
    if(!env)
        new_word = ft_strdup("");
    else
        new_word = ft_strdup(env);
    if (!new_word)
        return (0);
    free(p->word);
    p->word = new_word;
    *i += ft_strlen(env);
    p->expaneded = 1;
    return (1);
}

int replace(t_token *p, t_env *envp, char *argv)
{
    int i;
    int j;

    while (p)
    { 
        if (p->type == s_quote)
        {
            p = p->next;
            continue;
        } 
        i = 0;
        while (p->word[i])
        {
            if (p->word[i] == '$')
            {
                j = i + 1;
                if (ft_isdigit(p->word[j]))
                {
                    if (!replace_num(&p->word, argv))
                        return (0);
                    p->expaneded = 1;
                    break;
                }
                while (p->word[j] || p->word[j] == '_')
                    j++;
                if (j == i + 1)
                {
                    i++;
                    continue;
                }
                if (!replace_env(p, envp, &i, &j))
                    return (0);
            }
            else
                i++;
        }
        p = p->next;
    }
    return (1);
} 

int    join_strings(t_token *p, char   **token, t_token *ptr1)
{
    size_t  length;
    t_token *ptr;
    char    *str;

    length = 0;
    ptr = p;
    str = NULL;
    while (ptr)
    {
        if (ptr->word)
            length += ft_strlen(ptr->word);
        ptr = ptr->next;
    }
    str = malloc((length + 1) * sizeof(char));
    if (!str)
        return (0);
    str[0] = '\0';
    while (p)
    {
        if (p->expaneded)
            ptr1->expaneded = 1;
        ft_strlcat(str, p->word, length + 1);
        p = p->next;
    }
    free(*token);
    *token = str;
    return (1);
}

int free_return(t_token **p)
{
    clear_list(p);
    return (0);
}

char *normalize_whitespace(char *str)
{
    char *res = ft_strdup(str);
    int i = 0;

    if (!res)
        return (NULL);
    while (res[i])
    {
        if (res[i] == '\t')
            res[i] = ' ';
        i++;
    }
    return (res);
}

void    delete_ptr(t_token **list, t_token *lst) 
{
    if (lst == *list)
    {
        if (lst->next)
        {
            *list = lst->next;
            (*list)->prev = NULL;
            free (lst->word);
            free(lst);
        }
    }
    else
    {
        lst->next->prev = lst->prev;
        lst->prev->next = lst->next;
        free(lst->word);
        free(lst);
    }

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
        if (lst->expaneded && lst->quotes != double_quote)
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
                    return (0);
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


int    expander(t_token **tok_lst, t_env *env_lst, char *argv)
{
    t_token *p;
    t_token *head;

    p = NULL;
    head = *tok_lst;
    while ((head))
    {
        if ((head)->type == delimiter)
        {
            head = (head)->next;
            continue;
        }
        if (!break_string(&p, head->word))
            return (0);
        if (!replace(p, env_lst, argv))
            return (free_return(&p));
        if (!join_strings(p, &head->word, head ))
            return (free_return(&p));
        clear_list(&p);
        head = head->next;
    }
     if (!word_split((tok_lst)))
        return (0);
    parser2();
    return (1);
}
