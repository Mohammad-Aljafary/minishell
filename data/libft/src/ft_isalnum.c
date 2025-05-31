/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alnum.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 09:21:59 by malja-fa          #+#    #+#             */
/*   Updated: 2024/08/26 09:29:25 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_isalnum(int c)
{
	char	temp;

	temp = (char)c;
	if (temp >= '0' && temp <= '9')
		return (8);
	else if (temp >= 'A' && temp <= 'Z')
		return (8);
	else if (temp >= 'a' && temp <= 'z')
		return (8);
	else
		return (0);
}
