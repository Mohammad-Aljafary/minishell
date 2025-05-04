#include <minishell.h>

int	args_count(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

int	is_built_in(t_token *cmd)
{
	if (!ft_strcmp(cmd->word, "export") || !ft_strcmp(cmd->word, "echo")
		|| !ft_strcmp(cmd->word, "cd") || !ft_strcmp(cmd->word, "pwd")
		|| !ft_strcmp(cmd->word, "exit") || !ft_strcmp(cmd->word, "unset")
		|| !ft_strcmp(cmd->word, "env"))
		return (1);
	return (0);
}

void	run_built_in(t_token *cmd, int *exit_status, t_all *all, int in_child)
{
	if (!ft_strcmp(cmd->word, "export"))
		ft_export(cmd, &all->env_lst, &all->exp_lst, exit_status);
	else if (!ft_strcmp(cmd->word, "echo"))
		*exit_status = ft_echo(cmd);
	else if (!ft_strcmp(cmd->word, "cd"))
		*exit_status = ft_cd(cmd, &all->env_lst);
	else if (!ft_strcmp(cmd->word, "pwd"))
		*exit_status = ft_pwd();
	else if (!ft_strcmp(cmd->word, "exit"))
		*exit_status = ft_exits(cmd, all);
	else if (!ft_strcmp(cmd->word, "unset"))
		*exit_status = ft_unset(cmd, &all->env_lst, &all->exp_lst);
	else if (!ft_strcmp(cmd->word, "env"))
		*exit_status = ft_env(cmd, all->env_lst);
	if (in_child)
	{
		clear_all(all);
		exit(*exit_status);
	}
}
