/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 10:43:54 by malja-fa          #+#    #+#             */
/*   Updated: 2024/08/26 10:50:19 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char		*p;
	const char	*help;
	char		temp;

	p = NULL;
	help = s;
	temp = (char)c;
	while (*help != '\0')
	{
		if (*help == temp)
		{
			p = (char *)help;
		}
		help++;
	}
	if (temp == '\0')
		return ((char *)help);
	return (p);
}
