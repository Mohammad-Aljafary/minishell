#include <minishell.h>

int apply_redirection(t_token **next_node, t_token *node)
{
    while (*next_node && (*next_node)->type != pipes)
    {
        if ((*next_node)->type == out_re)
        {
            if (apply_re_out(next_node, node, 1))
                return (1);
        }
        else if ((*next_node)->type == in_re)
        {
            if (apply_re_in(next_node, node))
                return (1);
        }
        else if ((*next_node)->type == appends)
        {
            if (apply_re_out(next_node, node, 2))
                return (1);
        }
        else
        {
            *next_node = (*next_node)->next->next;
        }
    }
    if (redirect_out(node->out_fd, &node->origin_out))
        return (1);
    if (redirect_in(node->in_fd, &node->origin_in))
        return (1);
    return (0);
}

void retrieve(t_token *cmd)
{
    if (cmd->origin_in != STDIN_FILENO)
    {
        if (dup2(cmd->origin_in, STDIN_FILENO) == -1)
        {
            perror("dup2_retrieve_input");
            return;
        }
        if (cmd->in_fd != STDIN_FILENO)
            close(cmd->in_fd);
        close(cmd->origin_in);
    }
    if (cmd->origin_out != STDOUT_FILENO)
    {
        if (dup2(cmd->origin_out, STDOUT_FILENO) == -1)
        {
            perror("dup2_retrieve_output");
            return;
        }
        if (cmd->out_fd != STDOUT_FILENO)
            close(cmd->out_fd);
        close(cmd->origin_out);
    }
}


void execute(t_all *lists)
{
    t_token *node = lists->tok_lst;
    t_token *cmd = NULL;

    while (node)
    {
        if (node->type == command)
        {
            cmd = node;
            node = node->next;
            lists->exit_status = apply_redirection(&node, cmd);
            if (lists->exit_status)
            {
                while (node && node->type != pipes)
                    node = node->next;
                continue;
            }
            // Execute the command (placeholder)
            //word splitting here =)
            // execute_command(cmd, lists->env_lst);
            retrieve(cmd); 
        }
        else
        {
            node = node->next;
        }
    }
}

