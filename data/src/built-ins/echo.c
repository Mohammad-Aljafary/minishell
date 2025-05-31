/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 07:37:29 by taabu-fe          #+#    #+#             */
/*   Updated: 2025/05/08 12:28:10 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	check_n_flag(t_token *cmd, int *i, int *ne)
{
	int	j;

	while (cmd->args[*i])
	{
		if (cmd->args[*i][0] != '-')
			return ;
		if (cmd->args[*i][1] != 'n' && cmd->args[*i][1] != 'e')
			return ;
		j = 2;
		while (cmd->args[*i][j] && (cmd->args[*i][j] == 'n'
				|| cmd->args[*i][j] == 'e'))
			j++;
		if (cmd->args[*i][j] == '\0')
		{
			*ne = 0;
			(*i)++;
		}
		else
			return ;
	}
}

int	ft_echo(t_token *cmd)
{
	int	ne;
	int	i;

	ne = 1;
	i = 1;
	if (cmd && cmd->args[i] && (ft_strncmp(cmd->args[i], "-n", 2) == 0
			|| ft_strncmp(cmd->args[i], "-en", 3) == 0))
	{
		check_n_flag(cmd, &i, &ne);
	}
	while (cmd->args[i])
	{
		printf("%s", cmd->args[i]);
		if (cmd->args[i + 1])
			printf(" ");
		i++;
	}
	if (ne == 1)
		printf("\n");
	return (0);
}
