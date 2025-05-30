/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taabu-fe <taabu-fe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 07:39:36 by taabu-fe          #+#    #+#             */
/*   Updated: 2025/05/29 15:34:42 by taabu-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	set_shlvl(t_env *envp, char *old_value)
{
	t_env	*new_node;
	int		shlvl;
	char	*new_value;

	if (!old_value)
	{
		new_node = create_node_env("SHLVL", "1");
		if (!new_node)
			return (1);
		add_back_env(&envp, new_node);
		return (0);
	}
	shlvl = ft_atoi(old_value);
	if (shlvl < 0)
		shlvl = -1;
	new_value = ft_itoa(shlvl + 1);
	if (!new_value)
		return (1);
	new_node = create_node_env("SHLVL", new_value);
	free(new_value);
	if (!new_node)
		return (1);
	add_node_env(&envp, new_node, "SHLVL");
	return (0);
}

int	increment_shlvl(t_env *envp)
{
	char	*shlvl;

	if (!envp)
		return (1);
	shlvl = search_env(envp, "SHLVL");
	if (set_shlvl(envp, shlvl))
		return (1);
	return (0);
}

void	check_tty_or_stop_program(void)
{
	if (!isatty(0) || !isatty(1) || !isatty(2))
		exit(1);
}

int	check_if_whitspace(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!is_whitespace(line[i]))
			return (0);
		i++;
	}
	return (1);
}
