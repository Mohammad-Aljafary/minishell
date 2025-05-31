/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taabu-fe <taabu-fe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 13:50:05 by taabu-fe          #+#    #+#             */
/*   Updated: 2025/05/31 13:50:06 by taabu-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	handle_line(t_all *all, char *line)
{
	int	process_status;
	int	execute_status;

	if (line[0] != '\0' && !check_if_whitspace(line))
		add_history(line);
	process_status = process_input(line, all);
	if (process_status == 1)
	{
		execute_status = execute(all);
		if (execute_status == -1)
		{
			ft_fprintf(2, "minishell: fatal system error\n");
			clear_all(all);
			exit(EXIT_FAILURE);
		}
	}
	else if (process_status == 2)
	{
		ft_fprintf(2, "minishell: memory failures\n");
		clear_all(all);
		exit(EXIT_FAILURE);
	}
	clear_list(&all->tok_lst);
	return (0);
}

void	shell_loop(t_all *all)
{
	char	*line;

	while (1)
	{
		setup_signals();
		line = readline("minishell> ");
		if (!line)
		{
			ft_fprintf(2, "exit\n");
			if (g_sig)
				all->exit_status = 130;
			break ;
		}
		setup_signals2();
		handle_signal(all);
		handle_line(all, line);
		free(line);
	}
}