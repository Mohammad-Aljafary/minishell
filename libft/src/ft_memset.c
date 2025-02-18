/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 13:27:20 by malja-fa          #+#    #+#             */
/*   Updated: 2024/08/26 14:47:11 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memset(void *ptr, int x, size_t n)
{
	unsigned char	temp;
	unsigned char	*p;
	size_t			i;

	temp = (unsigned char)x;
	p = (unsigned char *)ptr;
	i = 0;
	while (i < n)
	{
		p[i] = temp;
		i++;
	}
	return ((void *)p);
}
