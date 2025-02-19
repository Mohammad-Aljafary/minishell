/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 09:46:18 by malja-fa          #+#    #+#             */
/*   Updated: 2025/02/19 10:30:58 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void tokenize(char *line, t_token **list)
{
    char    *token;
    t_token *temp;

    token = ft_strtok(line, " \n<>;|"); 
    while (token) 
    {
        temp = create(token);
        add_back(list, temp);
        token = ft_strtok(NULL, " \n<>;|");
    }
}
