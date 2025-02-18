/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 10:32:21 by malja-fa          #+#    #+#             */
/*   Updated: 2024/08/26 10:38:28 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*help;
	char	temp;

	help = (char *)s;
	temp = (char)c;
	while (*help != '\0')
	{
		if (*help == temp)
			return (help);
		help++;
	}
	if (temp == '\0')
		return (help);
	return (NULL);
}
