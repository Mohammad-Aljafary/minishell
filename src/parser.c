
#include <minishell.h>

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

    lst = *list;
    if (ft_strcmp(lst->word , ">") == 0)
        return(in_re);
    else if(ft_strcmp(lst->word ,"<") == 0)
        return(out_re);
    else if(ft_strcmp(lst->word ,"|") == 0)
        return(pipes);
    else if(ft_strcmp(lst->word ,">>") == 0)
        return(here_doc);
    else if(ft_strcmp(lst->word ,"<<") == 0)
        return(appends);
    else
    return(not_defined);
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
        {
            if (lst->prev == NULL)
                lst->type = command;
            else if (lst->prev->type == pipes)
                lst->type = command;
            else if (lst->prev->type == command || lst->prev->type == file)
                lst->type = args;
            else if (check_redirection(lst->prev))
                lst->type = file;
            else if (lst->prev->type == here_doc)
                lst->type = delimiter;
        }
        lst = lst->next;
    }
}
