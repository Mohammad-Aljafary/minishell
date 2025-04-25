# include <minishell.h>

/* int count_args_for_exit(t_token *cmd)
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
} */
int count_args_for_exit(t_token *cmd)
{
	if (args_count(cmd->args) > 2)
	{
		ft_fprintf(2, "exit: too many arguments\n");
		return (1);
	}
	return (0);
}
 int	ft_atoll(const char *str, long long *out)
{
	long long	result;
	int			sign;
	int 		digit;
	result = 0;
	sign = 1;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		digit = *str - '0';
		if ((sign == 1 && result > (LLONG_MAX - digit) / 10 )
			|| (sign == -1 && result > (-(LLONG_MIN + digit) / 10)))
			return (0);

		result = result * 10 + digit;
		str++;
	}
	*out = result * sign;
	return (1);
}
int	ft_exits(t_token *cmd, t_all *all)
{
	long long	value;
	int			i;

	i = 0;
	ft_fprintf(2, "exit\n");
	if (count_args_for_exit(cmd))
		return (EXIT_FAILURE);
	if (!cmd->args[1])
	{
		clear_all(all);
		exit(all->exit_status);
	}
	if ((cmd->args[1][0] == '+' || cmd->args[1][0] == '-') && cmd->args[1][1])
		i++;
	if (cmd->args[1][1] && cmd->args[1][1] == '-' && !cmd->args[1][2])
		i++;
	while (cmd->args[1][i])
	{
		if (!ft_isdigit(cmd->args[1][i]))
		{
			ft_fprintf(2, "exit: %s: numeric argument required\n", cmd->args[1]);
			clear_all(all);
			exit(2);
		}
		i++;
	}
	if (!ft_atoll(cmd->args[1], &value))
	{
		ft_fprintf(2, "exit: %s: numeric argument required\n", cmd->args[1]);
		clear_all(all);
		exit(2);
	}
	clear_all(all);
	exit((unsigned char)value);
} 
