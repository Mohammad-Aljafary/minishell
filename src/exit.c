#include <minishell.h>

int count_args_for_exit(t_token *cmd)
{
	if (args_count(cmd->args) > 2)
	{
		ft_fprintf(2, "exit: too many arguments\n");
		return (1);
	}
	return(0);
}

void	normalize_n (int *n, char *arg, int *i)
{
	*n = ft_atoi(arg);
	if (*n < 0)
		*i = 1;
	while (*n >= 256)
		*n = *n - 256;
	while (*n < 0)
		*n = *n + 256;
}

int	ft_exits(t_token *cmd, t_all *all)
{
	int	n;
	int	i;

	i = 0;
	ft_fprintf(2, "exit\n");
	if (count_args_for_exit(cmd))
		return (EXIT_FAILURE);
	if (!cmd->args[1])
	{
		clear_all(all);
		exit(all->exit_status);
	}
	normalize_n (&n, cmd->args[1], &i);
	while (cmd->args[1][i])
	{
		if (!ft_isdigit(cmd->args[1][i]))
		{
			ft_fprintf(2, "%s: numeric argument required\n", cmd->args[1]);
			clear_all(all);
			exit (2);
		}
		i++;
	}
	clear_all(all);
	exit (n);
}
