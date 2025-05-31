/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 02:17:24 by taabu-fe          #+#    #+#             */
/*   Updated: 2025/03/03 01:09:53 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

int	ft_strlen_gnl(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr_gnl(const char *s, int c)
{
	char			cc;
	unsigned int	i;

	i = 0;
	cc = (char)c;
	while (s[i] != '\0')
	{
		if (s[i] == cc)
			return ((char *)&s[i]);
		i++;
	}
	if (cc == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

char	*ft_strjoin_gnl(char *str1, char *str2)
{
	char	*str;
	int		i;
	int		j;

	i = -1;
	j = -1;
	if (!str1 && !str2)
		return (NULL);
	str = malloc((ft_strlen_gnl(str1) + ft_strlen_gnl(str2) + 1)
			* sizeof(char));
	if (!str)
		return (NULL);
	while (str1[++i])
		str[i] = str1[i];
	while (str2[++j])
		str[i++] = str2[j];
	str[i] = '\0';
	ft_free(&str1);
	return (str);
}

char	*ft_strdup_gnl(char *str1)
{
	int		i;
	char	*dest;

	i = 0;
	dest = malloc((ft_strlen_gnl(str1) + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	while (str1[i])
	{
		dest[i] = str1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_substr_gnl(char *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;
	size_t	len_s;

	len_s = ft_strlen_gnl(s);
	if (!s || start >= len_s)
		return (ft_strdup_gnl(""));
	if (len > ft_strlen_gnl(s) - start)
		len = len_s - start;
	substr = malloc((len + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}
