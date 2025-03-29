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
	create_list_env(&all.env_lst, envp);
	env(all.env_lst);
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
		{
			clear_all(&all);
			clear_history();
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
		if (!expander(all.tok_lst, all.env_lst, argv[0]))
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
		execute (all.tok_lst, all.env_lst);
		print_list(all.tok_lst);
		clear_list(&all.tok_lst);
		free(line);
	}
	return (0);
}
