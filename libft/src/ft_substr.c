/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 10:10:58 by malja-fa          #+#    #+#             */
/*   Updated: 2024/08/28 10:10:59 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t	alloc_len;
	char	*sub;
	size_t	s_len;

	s_len = ft_strlen(s);
	alloc_len = s_len - start;
	if (alloc_len > len)
		alloc_len = len;
	if (!s)
		return (NULL);
	if (start >= s_len)
		return (ft_strdup(""));
	sub = malloc((alloc_len + 1) * sizeof(char));
	if (!sub)
	{
		return (NULL);
	}
	ft_strlcpy(sub, s + start, alloc_len + 1);
	return (sub);
}
