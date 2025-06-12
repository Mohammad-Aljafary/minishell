/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammad-boom <mohammad-boom@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 07:39:32 by taabu-fe          #+#    #+#             */
/*   Updated: 2025/06/12 16:01:34 by mohammad-bo      ###   ########.fr       */
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

int	process_input(char *line, t_all *all)
{
	if (!tokenize(line, &all->tok_lst))
		return (2);
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

void	handle_signal(t_all *all)
{
	if (g_sig == 2)
	{
		all->exit_status = 130;
		g_sig = 0;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_all	all;

	(void)argc;
	check_tty_or_stop_program();
	init_shell(&all, envp, argv);
	shell_loop(&all);
	clear_all(&all);
	rl_clear_history();
	return (all.exit_status);
}
