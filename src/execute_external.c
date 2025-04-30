# include <minishell.h>

int is_executable (char *cmd, int *exit_status)
{
    if (access(cmd, X_OK | F_OK) == 0)
        return (1);
    else
    {
        if (access(cmd, F_OK) == 0)
            *exit_status = 126;
        else
            *exit_status = 127;
    }
    return (0);
}

int is_absolute_path (t_token *cmd)
{
    if (!cmd->word)
        return (0);
    if (ft_strncmp(cmd->word, "./", 2) == 0 || ft_strncmp(cmd->word, "../", 3) == 0
        || cmd->word[0] == '/')
        return (1);
    return (0);
}

char    *access_path(t_token *cmd, char **paths, int *exit_status)
{
    char    *joined_path;
    char    *full_path;
    int     i;

    i = 0;
    while(paths[i])
    {
        joined_path = ft_strjoin(paths[i], "/");
        if(!joined_path)
            return (NULL);
        full_path = ft_strjoin(joined_path, cmd->word);
        free(joined_path);
        if (!full_path)
            return (NULL);
        if (is_executable(full_path, exit_status))
            return (full_path);
        free (full_path);
        i++;
    }
    return (NULL);
}

char    *find_cmd_path(t_token *cmd, int *exit_status, t_all *all)
{
    char *path;
    char    **splitted_path;

    path = search_env(all->env_lst, "PATH");
    if(!path)
    {
        ft_fprintf(2, "%s: No such file or directory\n", cmd->word);
        return (NULL);
    }
    splitted_path = ft_split(path, ':');
    if(!splitted_path)
        return (NULL);
    path = access_path(cmd, splitted_path, exit_status);
    ft_free_split(splitted_path);
    if (!path)
    {
        if (*exit_status == 127)
            ft_fprintf(2, "%s: command not found\n", cmd->word);
        else if (*exit_status == 126)
            ft_fprintf (2, "%s: Permission denied\n", cmd->word);
        clear_all(all);
        exit (*exit_status);
    }
    return(path);
}

void    check_if_dir(t_token *cmd, int *exit_status, t_all *all)
{
    struct stat sb;

    if (!stat(cmd->word, &sb) && S_ISDIR(sb.st_mode))
    {
        if (ft_strcmp(cmd->word, ".") == 0 || ft_strcmp(cmd->word, "..") == 0)
        {
            ft_fprintf(2, "%s: command not found\n", cmd->word);
            *exit_status = 127;
        }
        else
        {
            ft_fprintf(2, "%s: Is a directory\n", cmd->word);
            *exit_status = 126;
        }
        clear_all(all);
        exit(*exit_status);
    }
}

char    *chck_if_in_dir(t_all *all, t_token *cmd)
{
    char    *path;
    char    *slash;
    char    *accs;

    check_if_dir (cmd, &all->exit_status, all);
    path = getcwd(NULL, 0);
    if (!path)
    {
        clear_all(all);
        exit (EXIT_FAILURE);
    }
    slash = ft_strjoin(path, "/");
    free (path);
    accs = ft_strjoin(slash, cmd->word);
    free (slash);
    if (!accs)
    {
        clear_all(all);
        exit (EXIT_FAILURE);
    }
    if (is_executable(accs, &all->exit_status))
        return (accs);
    free (accs);
    return (NULL);
}

char    *check_cmd(t_token *cmd, int *exit_status, t_all *all)
{
    char    *path;

    path = chck_if_in_dir(all, cmd);
    if (path)
        return (path);
    if (is_absolute_path(cmd))
    {
        if (!is_executable(cmd->word, exit_status))
        {
            perror (cmd->word);
            clear_all(all);
            exit (*exit_status);
        }
        return (ft_strdup(cmd->word));
    }
    else
    {
        path = find_cmd_path(cmd, exit_status, all);
        if(!path)
        {
            clear_all(all);
            exit(*exit_status);
        }
    }
    return (path);
}

int     count_nodes(t_env *env)
{
    int     count;

    count = 0;
    while (env)
    {
        count++;
        env = env->next;
    }
    return (count);
}

char *fill_env(t_env *env, char **envp, int *i)
{
    char *env_join;

    env_join = ft_strjoin(env->key, "=");
    if (!env_join)
    {
        ft_free_split(envp);
        return (NULL);
    }
    envp[++(*i)] = ft_strjoin(env_join, env->value);
    free(env_join);
    if (!envp[*i])
    {
        ft_free_split(envp);
        return (NULL);
    }
    return (envp[*i]);
}

char **list_to_arr(t_env *env)
{
    char **envp;
    int  i;
    char *result;
    
    i = -1;
    envp = malloc((count_nodes(env) + 1) * sizeof(char *));
    if (!envp)
        return (NULL);
    while (env)
    {
        result = fill_env(env, envp, &i);
        if (!result)
            return (NULL);
        env = env->next;
    }
    envp[++i] = NULL;
    return (envp);
}

void    run_external(t_token *cmd, int *exit_status, t_all *all)
{
    char    **envp;
    char    *path;
    
    path = check_cmd(cmd, exit_status, all);
    if (!path)
    {
        clear_all(all);
        exit(*exit_status);
    }
    envp = list_to_arr(all->env_lst);
    if(!envp)
    {
        clear_all(all);
        exit (*exit_status);
    }
    signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
    // fprintf(stderr, "%s    tty: in=%d, out=%d\n", cmd->args[0], isatty(0), isatty(1));
    execve(path, cmd->args, envp);
    perror("execve");
    free (path);
    ft_free_split(envp);
    clear_all(all);
    exit (EXIT_FAILURE);
}

void    duplicate_pipe (int pipefd[2], int *prev)
{
    if (pipefd[0] != -1)
        close (pipefd[0]);
    if (*prev != -1)
    {
        dup2(*prev, STDIN_FILENO);
        close(*prev);
    }
    if (pipefd[1] != -1)
    {
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
    }
}

void    track_child (int *prev, int pipefd[2], t_all *all, int id)
{
    if (*prev != -1)
        close(*prev);
    if (pipefd[1] != -1)
        close(pipefd[1]);
    *prev = pipefd[0];
    all->last_pid = id;
    all->num_of_child++;
}

void    execute_external(t_token *cmd, t_all *all, t_token *node, int pipefd[2], int *prev, char **heredoc)
{
    pid_t id;

    id = fork();
    if(id == -1)
    {
        perror("fork failure");
        all->exit_status = 1;
        return ;
    }
    else if (id == 0)
    {
        duplicate_pipe(pipefd, prev);
        all->exit_status = apply_redirection(&node, cmd, 1, heredoc);
        if (all->exit_status != 0)
        {
            clear_all(all);
            exit(all->exit_status);
        }
        if (is_built_in(cmd))
            run_built_in(cmd, &all->exit_status, all, 1);
        else
            run_external(cmd, &all->exit_status, all);
    }
    track_child(prev, pipefd, all, id);
}

