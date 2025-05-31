/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 15:48:26 by malja-fa          #+#    #+#             */
/*   Updated: 2024/08/28 15:48:27 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	inset(char const *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

static char	*trim(char *p, char *start, char *sub)
{
	while (start <= sub)
	{
		*p++ = *start++;
	}
	*p = '\0';
	return (p);
}

char	*ft_strtrim(char const *s, char const *set)
{
	char	*str;
	char	*sub;
	char	*p;

	if (!s || !set)
		return (NULL);
	str = (char *)s;
	sub = (char *)s + ft_strlen(s) - 1;
	if (*str == '\0')
	{
		p = malloc(1);
		if (p)
			*p = '\0';
		return (p);
	}
	while (*str && inset(set, *str))
		str++;
	while (sub > str && inset(set, *sub))
		sub--;
	p = malloc((sub - str + 2) * sizeof(char));
	if (!p)
		return (NULL);
	trim(p, str, sub);
	return (p);
}
