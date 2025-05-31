/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 07:31:16 by malja-fa          #+#    #+#             */
/*   Updated: 2024/09/03 07:31:18 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include <stdlib.h>

static int	count_digits(int n)
{
	int	counter;

	counter = 0;
	if (n <= 0)
		counter = 1;
	while (n != 0)
	{
		n = n / 10;
		counter++;
	}
	return (counter);
}

char	*ft_itoa(int n)
{
	char	*p;
	int		len;
	long	num;

	num = n;
	len = count_digits(n);
	p = malloc((len + 1) * sizeof(char));
	if (!p)
		return (NULL);
	p[len] = '\0';
	if (num < 0)
	{
		p[0] = '-';
		num = -num;
	}
	while (len-- > 0 && num > 0)
	{
		p[len] = (num % 10) + '0';
		num /= 10;
	}
	if (n == 0)
		p[0] = '0';
	return (p);
}
