/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkurkar <mkurkar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 07:39:32 by taabu-fe          #+#    #+#             */
/*   Updated: 2025/05/30 15:06:24 by mkurkar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	g_sig ;

static void	init_shell(t_all *all, char **envp, char **argv)
{
	ft_bzero(all, sizeof(*all));
	if (*envp)
	{
		if (create_list_env(&all->env_lst, envp) 
			|| create_list_exp(all->env_lst, &all->exp_lst) 
			|| increment_shlvl(all->env_lst))
		{
			clear_all (all);
			exit (1);
		}
		all->argv = argv[0];
	}
}

static int	process_input(char *line, t_all *all)
{
	if (!tokenize(line, &all->tok_lst))
		return (0);
	parser(&all->tok_lst);
	if (syntax_error(all->tok_lst))
		return (0);
	if (!expander(&all->tok_lst, all))
		return (2);
	if (!join_args(all->tok_lst))
		return (2);
	delete_args(&all->tok_lst, ARGS);
	move_command_to_front(&all->tok_lst);
	return (1);
}

static int	handle_signal(t_all *all)
{
	if (g_sig == 2)
	{
		all->exit_status = 130;
		g_sig = 0;
		return (1);
	}
	return (0);
}

static int	handle_line(t_all *all, char *line)
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

int	main(int argc, char **argv, char **envp)
{
	t_all	all;

	(void)argc;
	// check_tty_or_stop_program();
	init_shell(&all, envp, argv);
	shell_loop(&all);
	clear_all(&all);
	rl_clear_history();
	return (all.exit_status);
}
