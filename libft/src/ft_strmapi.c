/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 12:22:21 by malja-fa          #+#    #+#             */
/*   Updated: 2024/08/28 12:22:23 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*p;
	size_t	i;
	char	*ptr;

	if (!s || !f)
		return (NULL);
	ptr = (char *)s;
	p = malloc((ft_strlen(ptr) + 1) * sizeof(char));
	i = 0;
	if (!p)
		return (NULL);
	while (ptr[i] != '\0')
	{
		p[i] = f((unsigned int)i, ptr[i]);
		i++;
	}
	p[i] = '\0';
	return (p);
}
