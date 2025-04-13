# include <minishell.h>

int redirect_in(int in_fd, int *origin_in)
{
    *origin_in = dup(STDIN_FILENO);
    if (*origin_in == -1)
    {
        perror("dup_out fail");
        return (1);
    }
    printf("Duplicated STDIN_FILENO: %d\n", *origin_in);
    printf("%d\n", in_fd);
    if (dup2(in_fd, STDIN_FILENO) == -1)
    {
        perror("dup2_out fail");
        return (1);
    }
    printf("Redirection successful, in_fd: %d -> STDIN_FILENO\n", in_fd);
    return (0);
}

int open_in (char *file, int *in_fd)
{
    *in_fd = open(file, O_RDONLY);
    if (*in_fd == -1)
    {
        perror(file);
        return (1); 
    }
    return (0);
}

int apply_re_in(t_token **re_token, t_token *command)
{
    if (!(*re_token)->next)
        return (1);
    if (command->in_fd > 0)
        close(command->in_fd);
    if (open_in((*re_token)->next->word, &command->in_fd))
        return (1);
    *re_token = (*re_token)->next->next;
    return (0);
}