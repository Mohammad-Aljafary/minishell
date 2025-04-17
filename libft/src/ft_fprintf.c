/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 19:59:58 by taabu-fe          #+#    #+#             */
/*   Updated: 2025/04/16 17:42:22 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include <stdarg.h>
#include <unistd.h>

int	ft_handle_string(int fd, char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (write(fd, "(null)", 6));
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
	return (i);
}

int	ft_handle_putchar(int fd, int c)
{
	return (write(fd, &c, 1));
}

int	ft_printnbr(int fd, int n)
{
	char	c;
	int		count;

	count = 0;
	if (n == -2147483648)
		return (write(fd, "-2147483648", 11));
	if (n < 0)
	{
		count += write(fd, "-", 1);
		n = -n;
	}
	if (n >= 10)
		count += ft_printnbr(fd, n / 10);
	c = ((n % 10) + '0');
	count += write(fd, &c, 1);
	return (count);
}

static int	ft_handle_format(const char *format, va_list arg, int fd)
{
	int	count;

	count = 0;
	if (*format == 'c')
		count += ft_handle_putchar(fd, va_arg(arg, int));
	else if (*format == 's')
		count += ft_handle_string(fd, va_arg(arg, char *));
	else if (*format == 'd' || *format == 'i')
		count += ft_printnbr(fd, va_arg(arg, int));
	return (count);
}

int	ft_fprintf(int fd, const char *format, ...)
{
	va_list		arg;
	int			count;

	va_start (arg, format);
	count = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (*format)
				count += ft_handle_format(format, arg, fd);
		}
		else
			count += write(1, format, 1);
		format++;
	}
	va_end(arg);
	return (count);
}
