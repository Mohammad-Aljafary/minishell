
#include <minishell.h>

int replace(t_token *p, t_env *envp, char *argv, int exit_status)
{
    int i;
    int j;

    while (p)
    { 
        if (p->type == S_QOUTE)
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
                if (p->word[j] == '?')
                {
                    if (!replace_exit_status(&p->word, exit_status))
                        return (0);
                    p->expaneded = 1;
                    break;
                } 
                if (ft_isdigit(p->word[j]))
                {
                    if (!replace_num(&p->word, argv))
                        return (0);
                    p->expaneded = 1;
                    break;
                }
                while (p->word[j] && (ft_isalnum(p->word[j]) || p->word[j] == '_'))
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

int    expander(t_token **tok_lst, t_env *env_lst, char *argv, int exit_status)
{
    t_token *p;
    t_token *head;

    p = NULL;
    head = *tok_lst;
    while ((head))
    {
        if ((head)->type == DELIMITER)
        {
            if (head->quotes != NOT_QUOTE)
            {
                if (!remove_quotes(&head->word))
                    return (0);
            }
            head = (head)->next;
            continue;
        }
        if (!break_string(&p, head->word))
            return (0);
        if (!replace(p, env_lst, argv, exit_status))
            return (free_return(&p));
        if (!join_strings(p, &head->word, head))
            return (free_return(&p));
        clear_list(&p);
        head = head->next;
    }
    if (!word_split((tok_lst)))
        return (0); 
    head = *tok_lst;
    parser2 (head);
    return (1);
}
