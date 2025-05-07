#include <minishell.h>

char	*access_path(t_token *cmd, char **paths, int *exit_status)
{
	char	*joined_path;
	char	*full_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		joined_path = ft_strjoin(paths[i], "/");
		if (!joined_path)
			return (NULL);
		full_path = ft_strjoin(joined_path, cmd->word);
		free(joined_path);
		if (!full_path)
			return (NULL);
		if (is_executable(full_path, exit_status))
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

void	check_if_dir(t_token *cmd, int *exit_status, t_all *all)
{
	struct stat	sb;

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

char	*chck_if_in_dir(t_all *all, t_token *cmd)
{
	char	*path;
	char	*slash;
	char	*accs;

	check_if_dir(cmd, &all->exit_status, all);
	path = getcwd(NULL, 0);
	if (!path)
	{
		clear_all(all);
		exit(EXIT_FAILURE);
	}
	slash = ft_strjoin(path, "/");
	free(path);
	accs = ft_strjoin(slash, cmd->word);
	free(slash);
	if (!accs)
	{
		clear_all(all);
		exit(EXIT_FAILURE);
	}
	if (is_executable(accs, &all->exit_status))
		return (accs);
	free(accs);
	return (NULL);
}

char	*check_cmd(t_token *cmd, int *exit_status, t_all *all)
{
	char	*path;

	path = chck_if_in_dir(all, cmd);
	if (path)
		return (path);
	if (is_absolute_path(cmd))
	{
		if (!is_executable(cmd->word, exit_status))
		{
			perror(cmd->word);
			clear_all(all);
			exit(*exit_status);
		}
		return (ft_strdup(cmd->word));
	}
	else
	{
		path = find_cmd_path(cmd, exit_status, all);
		if (!path)
		{
			clear_all(all);
			exit(*exit_status);
		}
	}
	return (path);
}
