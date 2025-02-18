/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 14:21:32 by malja-fa          #+#    #+#             */
/*   Updated: 2024/06/30 14:22:28 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static size_t	str_len(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p;
	size_t	i;
	size_t	j;
	size_t	len1;
	size_t	len2;

	len1 = str_len(s1);
	len2 = str_len(s2);
	if (!s1 || !s2)
		return (NULL);
	p = malloc((len1 + len2 + 1) * sizeof(char));
	if (!p)
		return (NULL);
	j = 0;
	i = 0;
	while (s1[i] != '\0')
	{
		p[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
		p[i++] = s2[j++];
	p[i] = '\0';
	return (p);
}
