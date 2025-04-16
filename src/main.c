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

int	main (int argc, char **argv, char **envp)
{
	char	*line;
	t_all	all;
	
	(void)argc;
	all.tok_lst = NULL;
	all.env_lst = NULL;
	all.exit_status = 0;
	create_list_env(&all.env_lst, envp);
	env(all.env_lst);
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
		if (!expander(&all.tok_lst, all.env_lst, argv[0]))
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
