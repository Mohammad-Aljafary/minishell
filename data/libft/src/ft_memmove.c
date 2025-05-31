/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:17:02 by malja-fa          #+#    #+#             */
/*   Updated: 2024/08/27 13:17:44 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*p;
	unsigned char	*ptr;
	size_t			i;

	p = (unsigned char *)dest;
	ptr = (unsigned char *)src;
	if (!dest && !src)
		return (NULL);
	if (src < dest)
	{
		i = n;
		while (i-- > 0)
			p[i] = ptr[i];
	}
	else
	{
		i = 0;
		while (i < n)
		{
			p[i] = ptr[i];
			i++;
		}
	}
	return (dest);
}
