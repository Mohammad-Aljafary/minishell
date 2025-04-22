#include <minishell.h>

int count_args_for_exit(t_token *cmd)
{
	if (count_args(cmd->args) > 2)
	{
		ft_fprintf(2, "exit: too many arguments\n");
		return (1);
	}
	return(0);
}
int	ft_exits(t_token *cmd)
{
	int	n;
	int	i;

	i = 0;
	printf("exit\n");
	if (count_args_for_exit(cmd))
		return (1);
	n = ft_atoi(cmd->args[1]);
	if (n < 0)
		i = 1;
	while (cmd->args[1][i])
	{
		if (!ft_isdigit(cmd->args[1][i]))
		{
			ft_fprintf(2, "%s: numeric argument required\n", cmd->args[1]);
			return (2);
		}
		i++;
	}
	while (n >= 256)
		n = n - 256;
	while (n < 0)
		n = n + 256;
	exit(n);
	return (0);
}
