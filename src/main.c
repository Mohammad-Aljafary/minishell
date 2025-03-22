/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 18:21:35 by malja-fa          #+#    #+#             */
/*   Updated: 2025/03/22 13:12:32 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int setup_terminal(void)
{
    char *term_type;
	int success;
	
	term_type = getenv("TERM");
    if (!term_type)
    {
        ft_putstr_fd("TERM environment variable not set.\n", 2);
        return (-1);
    }
	success = tgetent(NULL, term_type);
    if (success < 0)
    {
        ft_putstr_fd("Could not access the termcap database.\n", 2);
        return (-1);
    }
    if (success == 0)
    {
        ft_putstr_fd("Terminal type is not defined in termcap.\n", 2);
        return (-1);
    }
    return (0);
}

void	print_screenn()
{
	int	fd;
	char	*line;

	fd = open("./src/texture.txt", O_RDONLY);
	if (fd < 0)
    {
        perror("Error opening texture.txt");
        return;
    }
	line = get_next_line(fd);
	while (line)
	{
		printf("\033[1;35m %s", line);
		free (line);
		line = get_next_line(fd);
	}
	printf("\033[1;37m");
	close (fd);
}

void	clear_screenn()
{
	char	*clear;
	
	clear = tgetstr("cl", NULL);
	if (clear)
		tputs(clear, 1, ft_putchar); 
}

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
	if (!setup_terminal())
		clear_screenn();
	print_screenn();
	create_list_env(&all.env_lst, envp);
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
		print_list(all.tok_lst);
		clear_list(&all.tok_lst);
		free(line);
	}
	return (0);
}
