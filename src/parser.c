
#include<minishell.h>

int check_type(t_token *list)
{
    if (ft_strcmp(list->word, ">") == 0)
        return (out_re);
    else if (ft_strcmp(list->word, "<") == 0)
        return (in_re);
    else if (ft_strcmp(list->word, "|") == 0)
        return (pipes);
    else if (ft_strcmp(list->word, ">>") == 0)
        return (appends);
    else if (ft_strcmp(list->word, "<<") == 0)
        return (here_doc);
    else
        return (not_defined);
}

int check_redirection(t_token *list)
{
    t_token *lst;

    lst = list;
    if (!list)
        return (-1);
    if (lst->type == appends || lst->type == in_re
         || lst->type == out_re)
        return (1);
    return (0);
}

void parser(t_token **list)
{
    t_token *lst;
    t_token *p;

    p = NULL;
    if (!list || !*list)
        return;
    lst = *list;
    while (lst)
    {
        lst->type = check_type(lst);
        if (lst->type == not_defined)
        {
            if (!lst->prev || lst->prev->type == pipes)
                lst->type = command;
            else if (lst->prev->type == command
                    || lst->prev->type == args)
                lst->type = args;
            else if (check_redirection(lst->prev))
                lst->type = file;
            else if (lst->prev->type == here_doc)
                lst->type = delimiter;
            else if (lst->prev->type == file || lst->prev->type == delimiter)
            {
                p = lst;
                while (p)
                {
                    if (p->type == command)
                    {
                        lst->type = args;
                        break;
                    }
                    p = p->prev;
                }
                if (!p)
                    lst->type = command;
            }
        }
        lst = lst->next;
    }
}

int syntax_error(t_token *list)
{
    t_token *lst;

    if (!list)
        return (0);
    if (check_type(list) == pipes)
    {
        ft_fprintf(2, "syntax error near unexpected token `%s'\n", list->word);
        return (1);
    }
    lst = list;
    while (lst->next) 
    {
        if (check_type(lst) != not_defined && check_type(lst->next) != not_defined)
        {
            ft_fprintf(2, "syntax error near unexpected token `%s'\n", lst->next->word);
            return (1);
        }
        lst = lst->next;
    }
    if (check_type(lst) != not_defined && check_type(lst) != pipes)
    {
        ft_fprintf(2, "syntax error near unexpected token `newline'\n");
        return (1);
    }
    return (0);
}
