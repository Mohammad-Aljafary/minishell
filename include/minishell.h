/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:32:29 by taabu-fe          #+#    #+#             */
/*   Updated: 2025/03/08 15:58:43 by malja-fa         ###   ########.fr       */
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

typedef	struct s_env
{
	char	*key;
	char	*value;
	struct s_env	*next;
}					t_env;

/***********************************************************\
\***************** LIST OPERATIONS **************************\
\************************************************************/
t_token				*create(char *str);
void				add_back(t_token **list, t_token *new_node);
void				clear_list(t_token **list);
void				print_list(t_token *list);
void    			create_list_env(t_env **list, char **envp);
void				print_env_list(t_env *list);
void    			clear_list_env(t_env **list);
/************************************************************\
\******************** TOKENIZATION ***************************\
\*************************************************************/
int				tokenize(char *line, t_token **list);
int    			check_type(t_token *list);
void			parser(t_token **list);
int    			syntax_error(t_token *list);


/************************************************************\
\***************** BUILT INS COMMANDS ************************\
\*************************************************************/
int					pwd();
int					cd(char *path);
void				exits(int n);
#endif