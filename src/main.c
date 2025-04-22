#include <minishell.h>

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

int	main (int argc, char **argv, char **envp)
{
	char	*line;
	t_all	all;
	
	(void)argc;
	all.tok_lst = NULL;
	all.env_lst = NULL;
	all.exit_status = 0;
	all.num_of_child = 0;
	all.last_pid = 0;
	create_list_env(&all.env_lst, envp);
	increment_shlvl(all.env_lst);
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
		{
			clear_all(&all);
			rl_clear_history();
			break;
		}
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
		if (!expander(&all.tok_lst, all.env_lst, argv[0], all.exit_status))
		{
			clear_list(&all.tok_lst);
			free (line);
			continue;
		}
		if (!join_args(all.tok_lst))
		{
			clear_list(&all.tok_lst);
			continue;
		}
		delete_token(&all.tok_lst, args, 1);
		move_command_to_front(&all.tok_lst);
		execute (&all);
		print_list(all.tok_lst);
		clear_list(&all.tok_lst);
		free(line);
	}
	return (0);
}
