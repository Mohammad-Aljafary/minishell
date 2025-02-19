/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:32:29 by taabu-fe          #+#    #+#             */
/*   Updated: 2025/02/19 10:21:54 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/includes/libft.h"


typedef struct s_token
{
    char        *word;
    int         type;
    struct s_token *prev;
    struct s_token *next;
}       t_token;


t_token   *create(char *str);
void    add_back(t_token **list, t_token *new_node);
void    clear_list(t_token **list);
void    print_list(t_token *list);
void    tokenize(char *line, t_token **list);
#endif