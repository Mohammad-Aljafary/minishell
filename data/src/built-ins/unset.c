/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taabu-fe <taabu-fe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 07:37:57 by taabu-fe          #+#    #+#             */
/*   Updated: 2025/05/08 07:37:58 by taabu-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_unset(t_token *cmd, t_env **env, t_env **exp)
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
