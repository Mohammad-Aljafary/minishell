#include <minishell.h>

void    find_file(t_token *cmd, t_token *list, int *i)
{
    while (list != cmd)
    {
        if (list->type == HERE_DOC)
            *i += 1;
        list = list->next;
    }
}

int redirections (t_token **next_node, t_token *node, char **heredoc, t_all *all)
{
    int i;

    i = 0;
    find_file(node, all->tok_lst, &i);
    if ((*next_node)->type == OUT_RE)
    {
        if (apply_re_out(next_node, node, 1))
            return (1);
    }
    else if ((*next_node)->type == IN_RE)
    {
        if (apply_re_in(next_node, node))
            return (1);
    }
    else if ((*next_node)->type == APPENDS)
    {
        if (apply_re_out(next_node, node, 2))
            return (1);
    }
    else if ((*next_node)->type == HERE_DOC)
    {
        if (apply_here(node, heredoc[i++], next_node))
            return (1);
    }
    else
        *next_node = (*next_node)->next;
    return (0);

}

int apply_redirection(t_token **next_node, t_token *node, int in_child, char **heredoc, t_all *all)
{
    while (*next_node && (*next_node)->type != PIPE)
    {
        if (redirections(next_node, node, heredoc, all))
            return (1);
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
        close (cmd->origin_in);
        cmd->origin_in = -1;
    }

    if (cmd->origin_out != -1)
    {
        if (dup2(cmd->origin_out, STDOUT_FILENO) == -1)
            perror("dup2_retrieve_output");
        close(cmd->origin_out);
        close(cmd->out_fd);
        cmd->out_fd = STDOUT_FILENO;
        cmd->origin_out = -1;
    }
}

void    execute_command(t_token *cmd, t_all *all, t_token *node, int pipefd[2], int *prev, char **heredoc)
{
    if (is_built_in(cmd) && !(cmd->prev && cmd->prev->type == PIPE) 
        && pipefd[0] == -1 && pipefd[1] == -1)
        run_built_in(cmd, &all->exit_status, all, 0);
    else 
        execute_external(cmd, all, node, pipefd, prev, heredoc);
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
        if (WIFSIGNALED(status))
        {
            if (WTERMSIG(status) == SIGQUIT)
                write (1, "Quit (core dumped)\n", 20);
            wait_statuss->exit_status = WTERMSIG(status) + 128;
            g_sig = 0;
        }
        wait_statuss->num_of_child--;
    }
}

void    execute(t_all *lists)
{
    t_token *node;
    t_token *node;
    t_token *cmd    = NULL;
    t_token *search = NULL;
    int     pipefd[2];
    int     prev_fd;
    char    **heredoc;

    node = lists->tok_lst;
    prev_fd = -1;
    pipefd[0] = -1;
    pipefd[1] = -1;
    heredoc = apply_heredoc(lists);
    if (!heredoc)
        return ;
    while (node)
    {
        if (node->type == COMMAND)
        {
            cmd   = node;
            node  = node->next;
            search = node;
            while (search && search->type != PIPE)
                search = search->next;
            if (!search
                && is_built_in(cmd)
                && !(cmd->prev && cmd->prev->type == PIPE))
            {
                lists->exit_status = apply_redirection(&node, cmd, 0, heredoc, lists);
                if (lists->exit_status)
                    continue;
            }
            else if (search && search->type == PIPE)
            {
                if (pipe(pipefd) == -1)
                {
                    perror("pipe");
                    clear_all(lists);
                    unlinks (heredoc);
                    exit (EXIT_FAILURE);
                }
            }
            execute_command(cmd, lists, node, pipefd, &prev_fd, heredoc);
            retrieve(cmd);
            node = search;
            if (node && node->type == PIPE)
                node = node->next;
        }
        else
        {
            cmd = node;
            lists->exit_status = apply_redirection(&node, cmd, 0, heredoc, lists);
            if (lists->exit_status)
            {
                node = node->next;
                continue ;
            }
            if (node && node->type == PIPE)
            {
                if (pipe(pipefd) == -1)
                {
                    perror("pipe");
                    unlinks (heredoc);
                    clear_all(lists);
                    exit (EXIT_FAILURE);
                }
                close (pipefd[1]);
                node = node->next;
            }
            retrieve(cmd);
        }
    }
    if (pipefd[0] != -1)
        close(pipefd[0]);
    if (pipefd[1] != -1)
        close (pipefd[1]);
    wait_status(lists);
    unlinks (heredoc);
}
