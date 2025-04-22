# include <minishell.h>

int unset(t_token *cmd, t_env **env)
{
	int	i;

	i = 1;
	while (cmd->args[i])
	{
		delete_node_env(env, cmd->args[i]);
		i++;
	}
	return (0);
}
