/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taabu-fe <taabu-fe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 07:37:32 by taabu-fe          #+#    #+#             */
/*   Updated: 2025/05/08 07:37:33 by taabu-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_env(t_token *cmd, t_env *list)
{
	if (args_count(cmd->args) > 1)
	{
		ft_fprintf(2, "env: ‘%s’: No such file or directory\n", cmd->args[1]);
		return (127);
	}
	while (list)
	{
		if (list->value)
			printf("%s=%s\n", list->key, list->value);
		else
			printf("%s=\n", list->key);
		list = list->next;
	}
	return (0);
}
