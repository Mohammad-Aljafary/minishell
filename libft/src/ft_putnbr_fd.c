/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 10:03:30 by malja-fa          #+#    #+#             */
/*   Updated: 2024/08/31 10:55:36 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static void	fill(unsigned int bb, int fd)
{
	char	c[10];
	int		index;
	int		temp;

	index = 0;
	while (bb > 0)
	{
		temp = bb % 10;
		bb /= 10;
		c[index++] = temp + '0';
	}
	c[index] = '\0';
	while (--index >= 0)
		write(fd, &c[index], 1);
}

void	ft_putnbr_fd(int nb, int fd)
{
	unsigned int	bb;

	if (nb == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (nb == 2147483647)
	{
		write(fd, "2147483647", 10);
		return ;
	}
	if (nb == 0)
	{
		write(fd, "0", 1);
		return ;
	}
	if (nb < 0)
	{
		write(fd, "-", 1);
		bb = (unsigned int)(-nb);
	}
	else
		bb = (unsigned int)nb;
	fill(bb, fd);
}
