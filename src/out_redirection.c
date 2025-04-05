# include <minishell.h>

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
