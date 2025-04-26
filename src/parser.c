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

void set_command_or_args(t_token *lst)
{
    t_token *p;

    if (!lst->prev || lst->prev->type == pipes)
        lst->type = command;
    else if (lst->prev->type == command || lst->prev->type == args)
        lst->type = args;
    else if (check_redirection(lst->prev))
        lst->type = file;
    else if (lst->prev->type == here_doc)
        lst->type = delimiter;
    else if (lst->prev->type == file || lst->prev->type == delimiter)
    {
        p = lst->prev;
        while (p && p->type != pipes)
        {
            if (p->type == command)
            {
                lst->type = args;
                return;
            }
            p = p->prev;
        }
        lst->type = command;
    }
}

void parser(t_token **list)
{
    t_token *lst;

    if (!list || !*list)
        return;
    lst = *list;
    while (lst)
    {
        lst->type = check_type(lst);
        if (lst->type == not_defined)
            set_command_or_args(lst);
        lst = lst->next;
    }
}

int syntax_error(t_token *list)
{
    t_token *curr;

    if (!list)
        return (0);
    curr = list;
    if (check_type(curr) == pipes)
    {
        ft_fprintf(2, "syntax error near unexpected token `%s'\n", curr->word);
        return (1);
    }
    while (curr)
    {
        if (check_type(curr) != not_defined)
        {
            if (!curr->next)
            {
                ft_fprintf(2, "syntax error near unexpected token `newline'\n");
                return (1);
            }
            if (check_type(curr) == pipes && check_type(curr->next) == pipes)
            {
                ft_fprintf(2, "syntax error near unexpected token `%s'\n", curr->next->word);
                return (1);
            }
            if ((check_type(curr) == out_re || check_type(curr) == in_re
                 || check_type(curr) == appends || check_type(curr) == here_doc)
                && (check_type(curr->next) != not_defined))
            {
                ft_fprintf(2, "syntax error near unexpected token `%s'\n", curr->next->word);
                return (1);
            }
        }
        curr = curr->next;
    }
    return (0);
}
