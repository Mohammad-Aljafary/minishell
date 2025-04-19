/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taabu-fe <taabu-fe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 09:55:45 by malja-fa          #+#    #+#             */
/*   Updated: 2025/04/19 14:45:58 by taabu-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include <stdio.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*s;
	unsigned char	*ss;
	size_t			i;

	s = (unsigned char *)s1;
	ss = (unsigned char *)s2;
	i = 0;
	if (n == 0)
	{
		return (0);
	}
	while ((s[i] || ss[i]) && i < n)
	{
		if (s[i] - ss[i] != 0)
		{
			return (s[i] - ss[i]);
		}
		i++;
	}
	return (0);
}
/*
int	main(void)
{
	char *str1 = "moh";
	char *str2 = "mt";
	int v =ft_strncmp(str1, str2,0);
	printf("%i",v);
}*/
