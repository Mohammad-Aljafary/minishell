#include <minishell.h>

int redirect_out(int out_fd, int *origin_out)
{
    *origin_out = dup(STDOUT_FILENO);
    if (*origin_out == -1)
    {
        perror("dup_out fail");
        return (1);
    }
    printf("Duplicated STDOUT_FILENO: %d\n", *origin_out);
    printf("%d\n", out_fd);
    if (dup2(out_fd, STDOUT_FILENO) == -1)
    {
        perror("dup2_out fail");
        return (1);
    }
    printf("Redirection successful, out_fd: %d -> STDOUT_FILENO\n", out_fd);
    return (0);
}

int open_file(char *file, int *out_fd)
{
    *out_fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (*out_fd == -1)
    {
        perror(file);
        return (1);
    }
    return (0);
}

int apply_re_out(t_token **re_node, t_token *command)
{
    if (!(*re_node)->next)
        return (1);
    if (command->out_fd > 1)
        close(command->out_fd);
    if (open_file((*re_node)->next->word, &command->out_fd))
        return (1);
    *re_node = (*re_node)->next->next;
    return (0);
}

int apply_redirection(t_token **next_node, t_token *node)
{
    while (*next_node && (*next_node)->type != pipes)
    {
        if ((*next_node)->type == out_re)
        {
            if (apply_re_out(next_node, node))
                return (1);
        }
        else
        {
            *next_node = (*next_node)->next;
        }
    }
     if (redirect_out(node->out_fd, &node->origin_out))
        return (1); 
    return (0);
}    

void retrieve(t_token *cmd)
{
    if (cmd->in_fd > 0)
    {
        if (dup2(cmd->origin_in, STDIN_FILENO) == -1)
        {
            perror("dup2_retrieve_input");
            return;
        }
        close(cmd->in_fd);
        close(cmd->origin_in);
    }

    if (cmd->out_fd > 1)
    {
        if (dup2(cmd->origin_out, STDOUT_FILENO) == -1)
        {
            perror("dup2_retrieve_output");
            return;
        }
        close(cmd->out_fd);
        close(cmd->origin_out);
    }
}


void execute(t_all *lists)
{
    t_token *node;
    t_env   *envp;
    t_token *cmd;

    node = lists->tok_lst;
    envp = lists->env_lst;
    cmd = NULL;
    while (node)
    {
        if (node->type == command)
        {
            cmd = node;
            node = node->next;
            lists->exit_status = apply_redirection(&node, cmd);
            if (lists->exit_status)
            {
                while (node && node->type != command && node->type != pipes)
                    node = node->next;
                continue;
            }
            // Execute the command here
            // execute_command(cmd, envp);
            retrieve(cmd);
        }
        else
        {
            node = node->next;
        }
    }
}
