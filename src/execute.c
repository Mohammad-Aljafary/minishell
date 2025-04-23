#include <minishell.h>

int apply_redirection(t_token **next_node, t_token *node, int in_child)
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
            *next_node = (*next_node)->next;
    }
    if (node->out_fd > 1)
        if (redirect_out(node->out_fd, &node->origin_out, in_child))
            return (1);
    if (node->in_fd > 0)
        if (redirect_in(node->in_fd, &node->origin_in, in_child))
            return (1);
    return (0);
}

void retrieve(t_token *cmd)
{
    if (cmd->origin_in != -1)
    {
        if (dup2(cmd->origin_in, STDIN_FILENO) == -1)
        close(cmd->in_fd);
        cmd->in_fd = STDIN_FILENO;
    }

    if (cmd->origin_out != -1)
    {
        if (dup2(cmd->origin_out, STDOUT_FILENO) == -1)
            perror("dup2_retrieve_output");
        close(cmd->origin_out);
        cmd->origin_out = -1;
    }
    if (cmd->out_fd != STDOUT_FILENO && cmd->out_fd > 1)
    {
        close(cmd->out_fd);
        cmd->out_fd = STDOUT_FILENO;
    }
}

/* int apply_pipes(t_token *cmd, t_token **node)
{
    int fd[2];

    if (pipe(fd) == -1)
    {
        perror("pipe");
        return (1);
    }
    if (cmd->out_fd <= 1)
    {
        if (redirect_out(fd[1], &cmd->origin_out)) 
            return (1);
    }
    if ((*node)->next && (*node)->next->type == command)
    {
        if ((*node)->next->in_fd <= 0)
        {
            if (redirect_in(fd[0], &(*node)->next->origin_in))
                return (1);
        }
    }
    cmd->out_fd = fd[1];
    (*node)->next->in_fd = fd[0];
    (*node) = (*node)->next;
    return (0);
} */

void    execute_command(t_token *cmd, t_all *all, int *exit_status, t_token *node, t_token *search)
{
    if (is_built_in(cmd) && !(cmd->prev && cmd->prev->type == pipes) && !(search && search->type != pipes))
        run_built_in(cmd, exit_status, all, 0);
    else 
        execute_external(cmd, exit_status, all, node);
}

int apply_in_pipe(int fd[2], t_token *cmd)
{
    if (cmd->prev && cmd->prev->type == pipes)
    {
        if (redirect_in(fd[0], &cmd->origin_in, 0))
            return (1); 
    }
    return (0);
}

int apply_out_pipe(int fd[2], t_token *cmd, t_all *all)
{
    if (pipe(fd) == -1)
    {
        perror("pipe");
        clear_all(all);
        exit(EXIT_FAILURE);
    }
    if (cmd->out_fd == 1)
    {
        if (redirect_out(fd[1], &cmd->origin_out, 0))
            return (1);
        return (0);
    }
    close (fd[1]);
    return (0);
}

void    wait_status(t_all *wait_statuss)
{
    int status;
    pid_t pid;

    while (wait_statuss->num_of_child)
    {
        pid = waitpid(-1, &status, 0);
        if (pid == wait_statuss->last_pid)
        {
            if (WIFEXITED(status))
                wait_statuss->exit_status = WEXITSTATUS(status);
            else
                wait_statuss->exit_status = 1;
        }
        wait_statuss->num_of_child--;
    }
}

void    execute(t_all *lists)
{
    t_token *node;
    t_token *cmd;
    t_token *search;

    node = lists->tok_lst;
    cmd = NULL;
    search = NULL;
    while (node)
    {
        if (node->type == command)
        {
            cmd = node;
            node = node->next;
            search = node;
            while (search && search->type != pipes)
                search = search->next;
            if (!search)
                lists->exit_status = apply_redirection(&search, cmd, 0);
            execute_command(cmd, lists, &lists->exit_status, node, search);
            retrieve(cmd);
        }
        else
        {
              while (node && node->type != pipes)
                    node = node->next;
            if (node)
                node = node->next;
        }
    }
    wait_status(lists);
}

