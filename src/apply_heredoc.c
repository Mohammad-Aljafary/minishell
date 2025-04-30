# include <minishell.h>

int open_heredoc(char *filename, int *in_fd)
{
    *in_fd = open(filename, O_RDONLY);
    if (*in_fd == -1)
    {
        perror(filename);
        return (1); 
    }
    return (0);
}

int apply_here(t_token *cmd, char *filename, t_token **re_token)
{
    if (cmd->in_fd > 0)
        close(cmd->in_fd);
    if (open_heredoc(filename, &cmd->in_fd))
        return (1);
    *re_token = (*re_token)->next->next;
    return (0);
}
