#include<minishell.h>

int check_type(t_token *list)
{
    if (ft_strcmp(list->word, ">") == 0)
        return (OUT_RE);
    else if (ft_strcmp(list->word, "<") == 0)
        return (IN_RE);
    else if (ft_strcmp(list->word, "|") == 0)
        return (PIPE);
    else if (ft_strcmp(list->word, ">>") == 0)
        return (APPENDS);
    else if (ft_strcmp(list->word, "<<") == 0)
        return (HERE_DOC);
    else
        return (NOT_DEFINED);
}

int check_redirection(t_token *list)
{
    t_token *lst;

    lst = list;
    if (!list)
        return (-1);
    if (lst->type == APPENDS || lst->type == IN_RE
         || lst->type == OUT_RE)
        return (1);
    return (0);
}

void set_command_or_args(t_token *lst)
{
    t_token *p;

    if (!lst->prev || lst->prev->type == PIPE)
        lst->type = COMMAND;
    else if (lst->prev->type == COMMAND || lst->prev->type == ARGS)
        lst->type = ARGS;
    else if (check_redirection(lst->prev))
        lst->type = FILES;
    else if (lst->prev->type == HERE_DOC)
        lst->type = DELIMITER;
    else if (lst->prev->type == FILES || lst->prev->type == DELIMITER)
    {
        p = lst->prev;
        while (p && p->type != PIPE)
        {
            if (p->type == COMMAND)
            {
                lst->type = ARGS;
                return;
            }
            p = p->prev;
        }
        lst->type = COMMAND;
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
        if (lst->type == NOT_DEFINED)
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
    if (check_type(curr) == PIPE)
    {
        ft_fprintf(2, "syntax error near unexpected token `%s'\n", curr->word);
        return (1);
    }
    while (curr)
    {
        if (check_type(curr) != NOT_DEFINED)
        {
            if (!curr->next)
            {
                ft_fprintf(2, "syntax error near unexpected token `newline'\n");
                return (1);
            }
            if (check_type(curr) == PIPE && check_type(curr->next) == PIPE)
            {
                ft_fprintf(2, "syntax error near unexpected token `%s'\n", curr->next->word);
                return (1);
            }
            if ((check_type(curr) == OUT_RE || check_type(curr) == IN_RE
                 || check_type(curr) == APPENDS || check_type(curr) == HERE_DOC)
                && (check_type(curr->next) != NOT_DEFINED))
            {
                ft_fprintf(2, "syntax error near unexpected token `%s'\n", curr->next->word);
                return (1);
            }
        }
        curr = curr->next;
    }
    return (0);
}
