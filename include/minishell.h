/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taabu-fe <taabu-fe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:32:29 by taabu-fe          #+#    #+#             */
/*   Updated: 2025/02/18 16:40:01 by taabu-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

enum    e_type
{
    command,
    arg,
    option
} t_type;

enum    e_operator
{
    herdoc,
    pipes,
    outRed,
    inRed,
    append,
    simecolon
}   t_openator;

typedef struct s_token
{
    char        *word;
    int         type;
    struct s_token *prev;
    struct s_token *next;
}       t_token;

#endif