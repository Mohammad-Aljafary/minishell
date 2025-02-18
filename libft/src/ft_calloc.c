/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 09:09:16 by malja-fa          #+#    #+#             */
/*   Updated: 2024/08/31 13:13:11 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	char	*p;
	size_t	i;

	ptr = malloc(nmemb * size);
	i = 0;
	if (!ptr)
		return (NULL);
	p = (char *)ptr;
	while (i < nmemb * size)
	{
		p[i] = 0;
		i++;
	}
	return (ptr);
}
