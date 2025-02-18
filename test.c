/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:06:31 by malja-fa          #+#    #+#             */
/*   Updated: 2025/02/18 14:41:39 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main()
{
    while (1)
    {
        char *line = readline("hhiiii> ");
        printf ("%s\n", line);
        add_history(line);
        //rl_clear_history();
        free (line);
    }
    return (0);
}