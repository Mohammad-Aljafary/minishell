# include <minishell.h>

int ft_unset(t_token *cmd, t_env **env, t_env **exp)
{
	int	i;

	i = 1;
	while (cmd->args[i])
	{
		delete_node_env(env, cmd->args[i]);
		delete_node_env(exp, cmd->args[i]);
		i++;
	}
	return (0);
}
