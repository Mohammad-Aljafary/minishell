/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taabu-fe <taabu-fe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:32:29 by taabu-fe          #+#    #+#             */
/*   Updated: 2025/03/17 11:58:52 by taabu-fe         ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/stat.h>

typedef enum	e_type
{
	not_defined,
	pipes,
	out_re,
	in_re,
	here_doc,
	command,
	appends,
	delimiter,
	args,
	file	
}				t_type;

typedef struct s_token
{
	char			*word;
	t_type			type;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

typedef	struct s_env
{
	char	*key;
	char	*value;
	struct s_env	*next;
}					t_env;

typedef struct s_tree
{
	char	**arg;
	t_type	type;
	struct s_tree	*left;
	struct s_tree	*right;
}				t_tree;

typedef struct s_all
{
	t_token	*tok_lst;
	t_env	*env_lst;
	t_tree	*syn_tree;
}	t_all;

/***********************************************************\
\***************** LIST OPERATIONS **************************\
\************************************************************/
t_token				*create(char *str);
void				add_back(t_token **list, t_token *new_node);
void				clear_list(t_token **list);
void				print_list(t_token *list);
void    			create_list_env(t_env **list, char **envp);
void				add_back_env(t_env **list, t_env *node);
void				env(t_env *list);
void    			clear_list_env(t_env **list);
void    			clear_all(t_all *all);
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
int				pwd();
int 			cd(char *path, t_env **env);
void			exits(char *str);
int 			ft_echo(char **str);

/************************************************************\
\********************** Expander *****************************\
\*************************************************************/
char    		*search_env(t_env *env, char *key);
void    		expander(t_token *tok_lst, t_env *env_lst);
void    		execute(t_token *node, t_env *env);
#endif