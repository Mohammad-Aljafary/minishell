/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 13:46:31 by malja-fa          #+#    #+#             */
/*   Updated: 2025/01/12 13:47:49 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include <stdio.h>
#include <string.h>

int	is_delim(char c, const char *delimiters)
{
	while (*delimiters)
	{
		if (c == *delimiters)
			return (1);
		delimiters++;
	}
	return (0);
}

char	*ft_strtok(char *str, const char *delimiters)
{
	static char	*ptr;
	char		*start;

	if (str)
		ptr = str;
	if (!ptr)
		return (NULL);
	while (*ptr && is_delim(*ptr, delimiters))
		ptr++;
	if (!*ptr)
	{
		ptr = NULL;
		return (NULL);
	}
	start = ptr;
	while (*ptr && !is_delim(*ptr, delimiters))
		ptr++;
	if (*ptr)
	{
		*ptr = '\0';
		ptr++;
	}
	else
		ptr = NULL;
	return (start);
}

/*
int	main(void)
{
	char		str[] = "here !a s&-i|<\tmple test";
	const char	*delimiters = " -!&>\t<|";
	char		*token;

	token = ft_strtok(str, delimiters);
	while (token != NULL)
	{
		printf("%s\n", token);
		token = ft_strtok(NULL, delimiters);
	}
	return (0);
}*/
