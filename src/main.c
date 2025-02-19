/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:06:31 by malja-fa          #+#    #+#             */
/*   Updated: 2025/02/19 10:46:04 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    char    *line;
    (void)envp;
    t_token *list;
    
    list = NULL;
    while (1)
    {
        line = readline("hhiiii> ");
        tokenize(line, &list);
        print_list(list);
        add_history(line);
        clear_list(&list);
        free (line);
    }
    return (0);
}