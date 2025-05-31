/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 15:04:54 by malja-fa          #+#    #+#             */
/*   Updated: 2024/08/27 15:04:56 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	unsigned char	*p;
	unsigned char	*ptr;
	size_t			i;

	p = (unsigned char *)str1;
	ptr = (unsigned char *)str2;
	i = 0;
	while (i < n)
	{
		if (p[i] != ptr[i])
			return (p[i] - ptr[i]);
		i++;
	}
	return (0);
}
