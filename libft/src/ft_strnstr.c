/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 07:52:59 by malja-fa          #+#    #+#             */
/*   Updated: 2024/08/28 07:53:01 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include <stdio.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*sub_big;
	char	*sub_little;
	size_t	i;
	size_t	j;

	i = 0;
	sub_big = (char *)big;
	sub_little = (char *)little;
	if (*sub_little == '\0')
		return (sub_big);
	while (sub_big[i] && i < len)
	{
		if (sub_big[i] == sub_little[0])
		{
			j = 0;
			while (sub_little[j] && sub_big[i + j] == sub_little[j] && (i
					+ j) < len)
				j++;
			if (!sub_little[j])
				return (sub_big + i);
		}
		i++;
	}
	return (NULL);
}
