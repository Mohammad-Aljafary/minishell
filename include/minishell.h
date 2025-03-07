/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taabu-fe <taabu-fe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:32:29 by taabu-fe          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/03/05 11:50:53 by malja-fa         ###   ########.fr       */
=======
/*   Updated: 2025/03/06 13:36:50 by taabu-fe         ###   ########.fr       */
>>>>>>> origin/tamara
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/includes/libft.h"
# include "../libft/includes/get_next_line.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <term.h>
# include <curses.h>

typedef enum	e_type
{
	not_defined,
	pipes,
	out_re,
	in_re,
	here_doc,
	command,
	option,
	appends,
	delimiter,
	args,
	file	
}				t_type;
typedef struct s_token
{
	char			*word;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

/***********************************************************\
\***************** LIST OPERATIONS **************************\
\************************************************************/
t_token				*create(char *str);
void				add_back(t_token **list, t_token *new_node);
void				clear_list(t_token **list);
void				print_list(t_token *list);

/************************************************************\
\******************** TOKENIZATION ***************************\
\*************************************************************/
int				tokenize(char *line, t_token **list);


/************************************************************\
\***************** BUILT INS COMMANDS ************************\
\*************************************************************/
int					pwd();
int					cd(char *path);
void				exits(int n);
#endif