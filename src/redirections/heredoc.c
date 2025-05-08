/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taabu-fe <taabu-fe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 07:39:11 by taabu-fe          #+#    #+#             */
/*   Updated: 2025/05/08 07:39:12 by taabu-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	process_heredoc_line(char **str, t_token *delimiter, int fd,
		t_all *all)
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

static int	read_line(t_token *delimiter, int fd, t_all *all, int temp)
{
	char	*str;

	str = readline("> ");
	if (!str)
		return (0);
	if (ft_strcmp(str, delimiter->word) == 0)
	{
		free(str);
		return (0);
	}
	if (process_heredoc_line(&str, delimiter, fd, all))
	{
		free(str);
		close(temp);
		return (1);
	}
	free(str);
	return (2);
}

static int	read_heredoc_input(int fd, t_token *delimiter, t_all *all, int dups)
{
	int	reads;

	setup_heredoc_signals();
	while (1)
	{
		if (g_sig == 2)
			break ;
		reads = read_line(delimiter, fd, all, dups);
		if (!reads)
			break ;
		else if (reads == 1)
			return (1);
	}
	if (g_sig == 2)
	{
		dup2(dups, STDIN_FILENO);
		close(fd);
		close(dups);
		all->exit_status = 130;
		return (1);
	}
	close(dups);
	return (0);
}

static int	open_heredoc(char **filename, t_token *delimiter, t_all *all)
{
	int	fd;
	int	dups;

	dups = dup(STDIN_FILENO);
	if (dups == -1)
	{
		free(*filename);
		return (-1);
	}
	fd = open(*filename, O_RDWR | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
	{
		free(*filename);
		return (-1);
	}
	if (read_heredoc_input(fd, delimiter, all, dups))
	{
		close(fd);
		close(dups);
		return (1);
	}
	close(fd);
	close(dups);
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
