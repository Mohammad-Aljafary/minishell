/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taabu-fe <taabu-fe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 07:39:36 by taabu-fe          #+#    #+#             */
/*   Updated: 2025/05/13 19:07:38 by taabu-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	increment_shlvl(t_env *envp)
{
	char	*shlvl;
	t_env	*create_shlvl;
	int		convert_atoi;

	convert_atoi = 0;
	create_shlvl = NULL;
	shlvl = search_env(envp, "SHLVL");
	if (!shlvl)
	{
		create_shlvl = create_node_env("SHLVL", "1");
		if (!create_shlvl)
			return ;
		add_back_env(&envp, create_shlvl);
	}
	convert_atoi = ft_atoi(shlvl);
	if(!convert_atoi)
		return ;
	if (convert_atoi < 0)
		convert_atoi = -1;
	shlvl = ft_itoa(convert_atoi + 1);
	if (!shlvl)
		return ;
	create_shlvl = create_node_env("SHLVL", shlvl);
	free (shlvl);
	if (!create_shlvl)
		return ;
	add_node_env(&envp, create_shlvl, "SHLVL");
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
