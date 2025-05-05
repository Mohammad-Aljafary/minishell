#include <minishell.h>

int	g_sig ;

void	print_env(char **env)
{
	int i = 0;
	while (env[i])
	{
		printf ("%s\n", env[i]);
		i++;
	}
}

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

static void	restore_prompt(int sig)
{
	g_sig = sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void	signal_handler(int sig)
{
	g_sig = sig;
}

void	setup_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = restore_prompt;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

void	setup_signals2(void)
{
	struct sigaction	sa;

	sa.sa_handler = signal_handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

static void	check_tty_or_stop_program()
{
	if (!isatty(0) || !isatty(1) || !isatty(2))
		exit(1);
}

int	main (int argc, char **argv, char **envp)
{
	char	*line;
	t_all	all;
	
	(void)envp;
	(void)argc;
	check_tty_or_stop_program();
	ft_bzero(&all, sizeof(all));
	if (*envp)
	{
		create_list_env(&all.env_lst, envp);
		create_list_exp(all.env_lst, &all.exp_lst);
		increment_shlvl(all.env_lst);
	}
	all.argv = argv[0];
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
		if (g_sig == 2)
		{
			all.exit_status = 130;
			g_sig = 0;
		}
		if (line[0] != '\0')
			add_history(line);
		if (!tokenize(line, &all.tok_lst))
		{
			clear_list(&all.tok_lst);
			free(line);
			continue;
		}
		parser(&all.tok_lst);
		if (syntax_error(all.tok_lst))
		{
			clear_list(&all.tok_lst);
			free(line);
			continue;
		}
		if (!expander(&all.tok_lst, &all))
		{
			clear_list(&all.tok_lst);
			free (line);
			continue;
		}
		if (!join_args(all.tok_lst))
		{
			clear_list(&all.tok_lst);
			free (line);
			continue;
		}
		delete_args(&all.tok_lst, ARGS);
		move_command_to_front(&all.tok_lst);
		//print_list(all.tok_lst);
		execute (&all);
		clear_list(&all.tok_lst);
		free(line);
	}
	clear_all(&all);
	rl_clear_history();
	return (all.exit_status);
}

