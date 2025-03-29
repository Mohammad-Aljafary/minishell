#include <minishell.h>

int join_args(t_token *node)
{
    t_token *p;
    int     count;
    int     i;

    p = NULL;
    count = 0;
    while (node)
    {
        if (node->type == command)
            p = node;
        if (node->type == args)
            count++;
        if (node->type == pipes)
            break;
        node = node->next;
    }
    if (!p)
        return (0);
    p->args = malloc((count + 2) * sizeof(char *));
    if (!p->args)
        return (0);
    i = 0;
    node = p->next;
    p->args[i++] = ft_strdup(p->word);
    if (!p->args[i - 1])
    {
        ft_free_split(p->args);
        return (0);
    }
    while (node && node->type != pipes)
    {
        if (node->type == args)
        {
            p->args[i++] = ft_strdup(node->word);
            if (!p->args[i - 1])
            {
                ft_free_split(p->args);
                return (0);
            }
        }
        node = node->next;
    }
    p->args[i] = NULL;
    if (node)
        return (join_args(node->next));
    return (1);
}
