/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taabu-fe <taabu-fe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:06:31 by malja-fa          #+#    #+#             */
/*   Updated: 2025/02/20 17:45:05 by taabu-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_token	*list;

	(void)argc;
	(void)argv;
	(void)envp;
	list = NULL;
	while (1)
	{
		line = readline("hhiiii> ");
		add_history(line);
		tokenize(line, &list);
		print_list(list);
		clear_list(&list);
		free(line);
	}
	return (0);
}
