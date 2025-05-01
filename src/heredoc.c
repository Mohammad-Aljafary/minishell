# include <minishell.h>

void    unlinks (char **heredoc)
{
    int i;

    i = 0;
    while (heredoc[i])
    {
        if (unlink(heredoc[i]) == -1)
            return ;
        free (heredoc[i]);
        i++;
    }
    free (heredoc);
}

int heredoc_count(t_token *lst)
{
    int count;

    count = 0;
    while (lst)
    {
        if (lst->type == DELIMITER)
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

void remove_newline(char *str)
{
    size_t len;

    len = ft_strlen(str);
    if (len > 0 && str[len - 1] == '\n')
        str[len - 1] = '\0';
}

char    *expand_heredoc(char *str, t_env *env)
{
    int i;
    int j;

    i = 0;
    while (str[i])
    {
        j = 0;
        if (str[i] == '$')
        {
            j = i + 1;
            while (str[j] && str[j] != ' ' && str[j] != '\t' && str[j] != '$')
                j++;
        }
        i++
    }

}

static int    open_heredoc(char **filename, t_token *delimiter, t_env *env)
{
    int     fd;
    char    *str;
    char    *exp;

    exp = NULL;
    fd = open(*filename, O_RDWR | O_CREAT | O_TRUNC, 0600);
    if (fd == -1)
    {
        free (*filename);
        return (-1);
    }
    while (1)
    {
        ft_fprintf(1, "> ");
        if (g_sig == 2)
            return (-1);
        str = get_next_line(STDIN_FILENO);
        if (!str)
        {
            write (1, "\n", 1);
            break;
        }
        remove_newline(str);
        if (ft_strcmp(str, delimiter->word) == 0)
        {
            free (str);
            break;
        }
        if (delimiter->quotes != NOT_QUOTE)
            write(fd, str, ft_strlen(str));
        else
            exp = expand_heredoc(str, env);
        write(fd, "\n", 1);
        free(str);
    }
    //close (0);
    // str = get_next_line(0);
    // free (str);
    close(fd);
    return (0);
}

char    *check_file(t_token *node, t_env *env)
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
    if (open_heredoc(&join, node, env) == -1)
        return (NULL);
    return (join);
}

char    **apply_heredoc(t_all *lists)
{
    char    **num_heredoc;
    int i;
    t_token *node;

    num_heredoc = malloc((heredoc_count(lists->tok_lst) + 1) * sizeof(char *));
    if (!num_heredoc)
        return (NULL);
    i = 0;
    node = lists->tok_lst;
    while (node)
    {
       if (node->type == HERE_DOC)
        {
            num_heredoc[i] = check_file(node->next, lists->env_lst);
            if (!num_heredoc[i])
            {
                unlinks(num_heredoc);
                return (NULL);
            }
            i++;
        }
        node = node->next;
    }
    num_heredoc[i] = NULL;
    return (num_heredoc);
}
