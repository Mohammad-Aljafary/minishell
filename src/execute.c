#include <minishell.h>

int apply_redirection(t_token **next_node, t_token *node, int in_child)
{
    while (*next_node && (*next_node)->type != PIPE)
    {
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

void    execute_command(t_token *cmd, t_all *all, t_token *node, int pipefd[2], int *prev)
{
    if (is_built_in(cmd) && !(cmd->prev && cmd->prev->type == PIPE) && pipefd[0] == -1 && pipefd[1] == -1)
        run_built_in(cmd, &all->exit_status, all, 0);
    else 
        execute_external(cmd, all, node, pipefd, prev);
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

int heredoc_counter(t_token *lst)
{
    int count;

    count = 0;
    while (lst)
    {
        if (lst->type == HERE_DOC)
            count++;
        lst = lst->next;
    }
    return (count);
}
int file_exist(char *filename)
{
    struct stat buffer;
    
    if(stat(filename, &buffer) == 0)
        return (1);
    return (0);
}

int    open_heredoc(char **filename, t_token *delimiter)
{
    int fd;
    char    *str;

    fd = open(*filename, O_RDWR | O_CREAT, 0666);
    if (fd == -1)
    {
        free (*filename);
        return (-1);
    }
    while (1)
    {
        ft_fprintf(1, "> ");
        str = get_next_line(0);
        if (ft_strcmp (str, delimiter->word) == 0)
        {
            free (str);
            break;
        }    
        write(fd, str, ft_strlen(str));
        write(fd, "\n", 1);
        //ft_fprintf(fd, "%s\n", str);
        free(str);
    }
    close(fd);
    return (0);
}

char    *check_file(t_token *node)
{
    static int  i = 0;
    char    *num_to_ch;
    char    *join;

    while (1)
    {
        num_to_ch = ft_itoa(i);
        if (!num_to_ch)
            return (NULL);
        join = ft_strjoin("/tmp/file", num_to_ch);
        free(num_to_ch);
        if(!join)
            return(NULL);
        if(file_exist(join))
        {
            i++;
            free (join);
            continue;
        }
        else
            break;
    }
    if (open_heredoc(&join, node) == -1)
        return (NULL);
    return (join);
}
char    **apply_heredoc(t_all *lists)
{
    char    **num_heredoc;
    int i;
    t_token *node;

    num_heredoc = malloc((heredoc_counter(lists->tok_lst) + 1) * sizeof(char *));
    if (!num_heredoc)
        return (NULL);
    i = 0;
    node = lists->tok_lst;
    while (node)
    {
        if(node->type == HERE_DOC)
        {
            num_heredoc[i++] = check_file(node);
        }
        node = node->next;
    }
    num_heredoc[i] = NULL;
}

void    execute(t_all *lists)
{
    t_token *node;
    t_token *cmd    = NULL;
    t_token *search = NULL;
    int     pipefd[2];
    int     prev_fd;

    node = lists->tok_lst;
    prev_fd = -1;
    apply_heredoc(lists);
    while (node)
    {
        pipefd[0] = -1;
        pipefd[1] = -1;
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
                lists->exit_status = apply_redirection(&node, cmd, 0);
                if (lists->exit_status)
                    continue;
            }
            else if (search && search->type == PIPE)
            {
                if (pipe(pipefd) == -1)
                {
                    perror("pipe");
                    clear_all(lists);
                    exit (EXIT_FAILURE);
                }
            }
            execute_command(cmd, lists, node, pipefd, &prev_fd);
            retrieve(cmd);
            node = search;
            if (node && node->type == PIPE)
                node = node->next;
        }
        else
        {
            cmd = node;
            lists->exit_status = apply_redirection(&node, cmd, 0);
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
}


