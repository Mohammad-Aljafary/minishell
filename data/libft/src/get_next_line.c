/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 09:09:17 by taabu-fe          #+#    #+#             */
/*   Updated: 2025/03/03 01:10:04 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

void	*ft_free(char **buff)
{
	if (*buff)
	{
		free(*buff);
		*buff = NULL;
	}
	return (NULL);
}

char	*fill(int fd, char *re, char *buff, int *bytes_read)
{
	char	*temp;

	*bytes_read = read(fd, buff, BUFFER_SIZE);
	if (*bytes_read == -1)
	{
		ft_free(&buff);
		return (ft_free(&re));
	}
	buff[*bytes_read] = '\0';
	if (re)
	{
		temp = ft_strjoin_gnl(re, buff);
		if (!temp)
		{
			ft_free(&buff);
			return (ft_free(&re));
		}
		re = temp;
	}
	else
		re = ft_strdup_gnl(buff);
	if (!re)
		return (ft_free(&buff));
	return (re);
}

char	*read_line(int fd, char *re)
{
	char	*buff;
	int		bytes_read;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		re = fill(fd, re, buff, &bytes_read);
		if (!re)
			return (NULL);
		if (ft_strchr_gnl(re, '\n'))
			break ;
	}
	ft_free(&buff);
	return (re);
}

char	*extract(char **re, char **line)
{
	char	*temp;
	char	*newline_pos;

	newline_pos = ft_strchr_gnl(*re, '\n');
	if (newline_pos)
	{
		*line = ft_substr_gnl(*re, 0, newline_pos - *re + 1);
		if (!*line)
			return (ft_free(re));
		temp = ft_strdup_gnl(newline_pos + 1);
		if (!temp)
		{
			ft_free(line);
			return (ft_free(re));
		}
		ft_free(re);
		*re = temp;
	}
	else
	{
		*line = ft_strdup_gnl(*re);
		ft_free(re);
		*re = NULL;
	}
	return (*line);
}

char	*get_next_line(int fd)
{
	static char	*re = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	re = read_line(fd, re);
	if (!re)
		return (NULL);
	if (ft_strchr_gnl(re, '\n'))
	{
		if (!extract(&re, &line))
			return (NULL);
		return (line);
	}
	if (*re)
	{
		line = ft_strdup_gnl(re);
		ft_free(&re);
		return (line);
	}
	ft_free(&re);
	return (NULL);
}
/*
int	main(void)
{
	int		fd;
	char	*str;

	fd = open("ggg.txt", O_RDONLY| O_CREAT);
	if (fd == -1)
		return (-1);
	while (1)
	{
		str = get_next_line(fd);
		if (str == NULL)
				break ;
		printf("%s",str);
		free (str);
	}
	if(close(fd) < 0)
			return (-1);
	return (0);
}*/