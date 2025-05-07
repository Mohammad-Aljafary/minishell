#include <minishell.h>

int	check_cd_args(t_token *cmd)
{
	if (args_count(cmd->args) > 2)
	{
		ft_fprintf(2, "cd: too many arguments\n");
		return (1);
	}
	return (0);
}

int	update_oldpwd(t_env **env, char *current)
{
	t_env	*node;

	node = *env;
	while (node)
	{
		if (ft_strcmp(node->key, "OLDPWD") == 0)
			break ;
		node = node->next;
	}
	if (node)
	{
		free(node->value);
		node->value = ft_strdup(current);
		if (!node->value)
			return (1);
	}
	return (0);
}

int	update_pwd(t_env **env)
{
	t_env	*node;
	char	*path;

	node = *env;
	while (node)
	{
		if (ft_strcmp(node->key, "PWD") == 0)
			break ;
		node = node->next;
	}
	if (node)
	{
		free(node->value);
		path = getcwd(NULL, 0);
		if (!path)
			return (1);
		node->value = ft_strdup(path);
		free(path);
		if (!node->value)
			return (1);
	}
	return (0);
}

static int	ft_change_dir(char *path, t_env **env, t_env **exp)
{
	char	*current;

	current = getcwd(NULL, 0);
	if (!current)
	{
		perror(NULL);
		return (1);
	}
	if (chdir(path) == -1)
	{
		perror(path);
		free(current);
		return (1);
	}
	if (update_oldpwd(env, current) || update_pwd(env)
		||update_oldpwd(exp, current) || update_pwd(exp))
	{
		free(current);
		return (1);
	}
	free(current);
	return (0);
}

int	ft_cd(t_token *cmd, t_env **env, t_env **exp)
{
	char	*path;

	if (check_cd_args(cmd))
		return (1);
	if (cmd->args[1])
		path = cmd->args[1];
	else
		path = search_env(*env, "HOME");
	if (ft_change_dir(path, env, exp))
		return (1);
	return (0);
}
