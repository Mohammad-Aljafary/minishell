/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 17:04:32 by malja-fa          #+#    #+#             */
/*   Updated: 2024/08/28 17:04:34 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	count_word(char *s, char c)
{
	int	in_word;
	int	count;

	in_word = 0;
	count = 0;
	while (*s)
	{
		if (*s != c && in_word == 0)
		{
			count++;
			in_word = 1;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static int	word_len(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i])
	{
		i++;
	}
	return (i);
}

static void	str_copy(char *s, char *str, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		s[i] = str[i];
		i++;
	}
	s[len] = '\0';
}

static void	fill_split(char **ptr, const char *s, char c)
{
	int	i;
	int	size;

	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			size = word_len((char *)s, c);
			ptr[i] = malloc((size + 1) * sizeof(char));
			if (!ptr[i])
			{
				while (i-- > 0)
					free(ptr[i]);
				free(ptr);
				return ;
			}
			str_copy(ptr[i], (char *)s, size);
			i++;
			s += size;
		}
		else
			s++;
	}
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	int		count;

	if (!s)
		return (NULL);
	count = count_word((char *)s, c);
	ptr = (char **)malloc((count + 1) * sizeof(char *));
	if (!ptr)
		return (NULL);
	ptr[count] = NULL;
	fill_split(ptr, s, c);
	return (ptr);
}

/*int	main(void)
{
	char	**result;
	int		i;
	char	*str = "Hello world, this is a test string";
	char	delimiter = ' ';

	// Call ft_split with str and delimiter
	result = ft_split(str, delimiter);
	if (!result)
	{
		printf("ft_split failed\n");
		return (1);
	}

	// Print the split result
	i = 0;
	while (result[i] != NULL)
	{
		printf("Substring %d: %s\n", i, result[i]);
		free(result[i]); // Free each substring
		i++;
	}
	free(result); // Free the array itself

	return (0);
}*/
