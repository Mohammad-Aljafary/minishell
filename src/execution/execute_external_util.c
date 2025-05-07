#include <minishell.h>

int	is_executable(char *cmd, int *exit_status)
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

int	is_absolute_path(t_token *cmd)
{
	if (!cmd->word)
		return (0);
	if (ft_strncmp(cmd->word, "./", 2) == 0 || ft_strncmp(cmd->word, "../",
			3) == 0 || cmd->word[0] == '/')
		return (1);
	return (0);
}

int	count_nodes(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

char	*fill_env(t_env *env, char **envp, int *i)
{
	char	*env_join;

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

char	**list_to_arr(t_env *env)
{
	char	**envp;
	int		i;
	char	*result;

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
