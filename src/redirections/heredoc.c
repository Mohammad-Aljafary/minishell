#include <minishell.h>

void	sigint_handler_heredoc(int sig)
{
	(void)sig;
	g_sig = sig;
	write (1, "\n", 1);
	close(STDIN_FILENO);
}

void	setup_heredoc_signals(void)
{
	signal(SIGINT, sigint_handler_heredoc);
	signal(SIGQUIT, SIG_IGN);
}


int	file_exist(char *filename)
{
	struct stat	buffer;

	if (stat(filename, &buffer) == 0)
		return (1);
	return (0);
}

static int	process_heredoc_line(char **str, t_token *delimiter,
								int fd, t_all *all)
{
	if (delimiter->quotes == NOT_QUOTE && *str[0] != '\0')
	{
		if (!expand_all_variables(str, all))
		{
			close(fd);
			return (1);
		}
	}
	write(fd, *str, ft_strlen(*str));
	write(fd, "\n", 1);
	return (0);
}

static int	read_heredoc_input(int fd, t_token *delimiter, t_all *all)
{
	char	*str;
	int		temp;

	temp = dup(STDIN_FILENO);
	while (1)
	{
		setup_heredoc_signals();
		if (g_sig == 2)
			break;
		str = readline("> ");
		if (!str)
			break ;
		if (ft_strcmp(str, delimiter->word) == 0)
		{
			free(str);
			break ;
		}
		if (process_heredoc_line(&str, delimiter, fd, all))
		{
			free (str);
			return (1);
		}
		free (str);
	}
	if (g_sig == 2)
	{
		dup2(temp, STDIN_FILENO);
		close (fd);
		close(temp);
		all->exit_status = 130;
		return (1);
	}
	close (temp);
	return (0);
}

static int	open_heredoc(char **filename, t_token *delimiter, t_all *all)
{
	int		fd;
	
	fd = open(*filename, O_RDWR | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
	{
		free(*filename);
		return (-1);
	}
	if (read_heredoc_input(fd, delimiter, all))
		return (1);
	close(fd);
	setup_signals2();
	return (0);
}

char	*check_file(t_token *node, t_all *all)
{
	static int	i = 0;
	char		*num_to_ch;
	char		*join;

	while (1)
	{
		num_to_ch = ft_itoa(i);
		if (!num_to_ch)
			return (NULL);
		join = ft_strjoin("/tmp/file", num_to_ch);
		free(num_to_ch);
		if (!join)
			return (NULL);
		if (file_exist(join))
		{
			i++;
			free(join);
			continue ;
		}
		break ;
	}
	if (open_heredoc(&join, node, all) == -1)
		return (NULL);
	return (join);
}
