#include <minishell.h>

int	g_sig ;

void	increment_shlvl(t_env *envp)
{
	char	*shlvl;
	t_env	*create_shlvl;
	int		convert_atoi;

	convert_atoi = 0;
	create_shlvl = NULL;
	shlvl = search_env(envp, "SHLVL");
	if(!shlvl)
	{
		create_shlvl = create_node_env("SHLVL", "1");
		if (!create_shlvl)
			return ;
		add_back_env(&envp,create_shlvl);
	}
	convert_atoi = ft_atoi(shlvl);
	if (convert_atoi < 0)
		convert_atoi = -1;
	shlvl = ft_itoa(convert_atoi + 1);
	if(!shlvl)
		return ;
	create_shlvl = create_node_env("SHLVL", shlvl);
	free (shlvl);
	if (!create_shlvl)
		return ;
	add_node_env(&envp, create_shlvl, "SHLVL");
}

static void	check_tty_or_stop_program()
{
	if (!isatty(0) || !isatty(1) || !isatty(2))
		exit(1);
}


/**
 * @brief Initialize the shell environment
 * 
 * @param all The main program structure
 * @param envp Environment variables
 * @param argv Program arguments
 */
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

/**
 * @brief Process the input line
 * 
 * @param line User input
 * @param all The main program structure
 * @return int 1 on success, 0 on failure
 */
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

/**
 * @brief Handle signal interruption
 * 
 * @param all The main program structure
 * @return int 1 if signal was triggered, 0 otherwise
 */
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

/**
 * @brief Shell main loop
 * 
 * @param all The main program structure
 */
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
			break;
		}
		setup_signals2();
		handle_signal(all);
		if (line[0] != '\0')
			add_history(line);
		if (process_input(line, all))
		execute(all);
		clear_list(&all->tok_lst);
		free(line);
	}
}

/**
 * @brief Main function of minishell
 * 
 * @param argc Argument count
 * @param argv Argument values
 * @param envp Environment variables
 * @return int Exit status
 */
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
