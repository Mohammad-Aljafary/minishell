/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taabu-fe <taabu-fe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 07:39:32 by taabu-fe          #+#    #+#             */
/*   Updated: 2025/05/08 08:02:59 by taabu-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	g_sig ;

static void	init_shell(t_all *all, char **envp, char **argv)
{
	ft_bzero(all, sizeof(*all));
	if (*envp)
	{
		create_list_env(&all->env_lst, envp);
		create_list_exp(all->env_lst, &all->exp_lst);
		increment_shlvl(all->env_lst);
	}
	all->argv = argv[0];
}

static int	process_input(char *line, t_all *all)
{
	if (!tokenize(line, &all->tok_lst))
		return (0);
	parser(&all->tok_lst);
	if (syntax_error(all->tok_lst))
		return (0);
	if (!expander(&all->tok_lst, all))
		return (0);
	if (!join_args(all->tok_lst))
		return (0);
	delete_args(&all->tok_lst, ARGS);
	move_command_to_front(&all->tok_lst);
	return (1);
}

static int	handle_signal(t_all *all)
{
	if (g_sig == 2)
	{
		all->exit_status = 130;
		g_sig = 1;
		return (1);
	}
	return (0);
}

static void	shell_loop(t_all *all)
{
	char	*line;

	while (1)
	{
		setup_signals();
		line = readline("minishell> ");
		if (!line)
		{
			ft_fprintf(2, "exit\n");
			break ;
		}
		setup_signals2();
		handle_signal(all);
		if (line[0] != '\0' && !check_if_whitspace(line))
			add_history(line);
		if (process_input(line, all))
			execute(all);
		clear_list(&all->tok_lst);
		free(line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_all	all;

	(void)argc;
	check_tty_or_stop_program();
	init_shell(&all, envp, argv);
	shell_loop(&all);
	if (g_sig == 1)
		all.exit_status = 130;
	clear_all(&all);
	rl_clear_history();
	return (all.exit_status);
}
