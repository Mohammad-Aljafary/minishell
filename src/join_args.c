#include <minishell.h>

int count_args(t_token *node, t_token **cmd)
{
    int count;

    *cmd = NULL;
    count = 0;
    while (node)
    {
        if (node->type == command)
            *cmd = node;
        if (node->type == args)
            count++;
        if (node->type == pipes)
            break;
        node = node->next;
    }
    return (count);
}

int allocate_args(t_token *cmd, int count)
{
    cmd->args = malloc((count + 2) * sizeof(char *));
    if (!cmd->args)
        return (0);
    cmd->args[0] = ft_strdup(cmd->word);
    if (!cmd->args[0])
    {
        ft_free_split(cmd->args);
        return (0);
    }
    return (1);
}

int fill_args(t_token *cmd, t_token *node)
{
    int i;

    i = 1;
    while (node && node->type != pipes)
    {
        if (node->type == args)
        {
            cmd->args[i++] = ft_strdup(node->word);
            if (!cmd->args[i - 1])
            {
                ft_free_split(cmd->args);
                return (0);
            }
        }
        node = node->next;
    }
    cmd->args[i] = NULL;
    if (node)
        return (join_args(node->next));
    return (1);
}

int join_args(t_token *node)
{
    t_token *cmd;
    int     count;

    count = count_args(node, &cmd);
    if (!cmd || !allocate_args(cmd, count))
        return (0);
    return (fill_args(cmd, cmd->next));
}
