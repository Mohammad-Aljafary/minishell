/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_util_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taabu-fe <taabu-fe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 07:38:21 by taabu-fe          #+#    #+#             */
/*   Updated: 2025/05/08 07:38:22 by taabu-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*search_env(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
		{
			return (env->value);
		}
		env = env->next;
	}
	return (NULL);
}

int	word_split_util(char *tok, t_token **last_inserted, t_token **list)
{
	char	*temp;
	t_token	*node;

	node = NULL;
	temp = ft_strdup(tok);
	if (!temp)
		return (0);
	node = create(temp);
	if (!node)
	{
		free(temp);
		return (0);
	}
	if (!(*last_inserted))
		add_front(list, node);
	else
		add_node_token(list, *last_inserted, node);
	*last_inserted = node;
	return (1);
}

int	word_split(t_token **list)
{
	t_token	*lst;
	t_token	*next;
	char	*tok;
	t_token	*last_inserted;

	lst = *list;
	while (lst)
	{
		next = lst->next;
		if (lst->expaneded && lst->quotes != DOUBLE_QUOTE)
		{
			tok = ft_strtok(lst->word, " \t");
			last_inserted = lst->prev;
			while (tok != NULL)
			{
				if (!word_split_util(tok, &last_inserted, list))
					return (0);
				tok = ft_strtok(NULL, " \t");
			}
			delete_ptr(list, lst);
		}
		lst = next;
	}
	return (1);
}

int	concatenate_tokens(t_token *p, char *str, size_t length, t_token *ptr1)
{
	while (p)
	{
		if (p->expaneded && ptr1 && p->quotes != DOUBLE_QUOTE)
		{
			ptr1->expaneded = 1;
			ptr1->quotes = NOT_QUOTE;
		}
		ft_strlcat(str, p->word, length + 1);
		p = p->next;
	}
	return (1);
}

int	join_strings(t_token *p, char **token, t_token *ptr1)
{
	size_t	length;
	char	*str;

	length = calculate_tokens_length(p);
	str = malloc((length + 1) * sizeof(char));
	if (!str)
		return (0);
	str[0] = '\0';
	if (!concatenate_tokens(p, str, length, ptr1))
	{
		free(str);
		return (0);
	}
	if (*token)
		free(*token);
	*token = str;
	return (1);
}
