/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:32:29 by taabu-fe          #+#    #+#             */
/*   Updated: 2025/04/17 16:53:46 by malja-fa         ###   ########.fr       */
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
# include <errno.h>

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
	file,
	s_quote	
}				t_type;

typedef enum	e_quote
{
	single_quote,
	double_quote,
	not_quoted
}				t_quote;

typedef struct s_token
{
	char			*word;
	t_type			type;
	char			**args;
	int				out_fd;
	int				in_fd;
	int				origin_out;
	int				origin_in;
	int				expaneded;
	t_quote			quotes;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

typedef	struct s_env
{
	char	*key;
	char	*value;
	struct s_env	*next;
}					t_env;

typedef struct s_all
{
	t_token	*tok_lst;
	t_env	*env_lst;
	int		exit_status;
}	t_all;

/************************************************************\
\***************** LIST OPERATIONS **************************\
\************************************************************/
t_token				*create(char *str);
void				add_back(t_token **list, t_token *new_node);
void				clear_list(t_token **list);
void				print_list(t_token *list);
void    			create_list_env(t_env **list, char **envp);
void				add_back_env(t_env **list, t_env *node);
void				env(t_env *list);
void 				print_env_export(t_env *list);
void    			clear_list_env(t_env **list);
void    			clear_all(t_all *all);
void				delete_node_env(t_env **list, char *key);
t_env 				*create_node_env(char *key, char *value);
void    			add_node_env(t_env **list, t_env *node, char *key);
void				add_node_token(t_token **list, t_token *prev_node, t_token *node);
void 				delete_ptr(t_token **list, t_token *lst);
/*************************************************************\
\******************** TOKENIZATION ***************************\
\*************************************************************/
int				tokenize(char *line, t_token **list);
int    			check_type(t_token *list);
void			parser(t_token **list);
int    			syntax_error(t_token *list);
int				is_whitespace(char c);
int 			check_redirection(t_token *list);
void 			move_command_to_front(t_token **head);

/*************************************************************\
\***************** BUILT INS COMMANDS ************************\
\*************************************************************/
int				pwd();
int 			cd(char *path, t_env **env);
void			exits(char *str);
void     		unset(char *str, t_env **env);
int				export(t_token *str, t_env **env);
void 			ft_echo(t_token *args);

/*************************************************************\
\********************** Expander *****************************\
\*************************************************************/
char    		*search_env(t_env *env, char *key);
int    			expander(t_token **tok_lst, t_env *env_lst, char *argv);
int 			break_string(t_token **list, char *token);

/**************************************************************\
\*********************** Execution ****************************\
\**************************************************************/
void 			execute(t_all *lists);
int 			join_args(t_token *node);
void			delete_token(t_token **list, t_type type, int flag);
int 			apply_re_out(t_token **re_node, t_token *command, int flag);
int 			apply_re_in(t_token **re_token, t_token *command);
int 			redirect_out(int out_fd, int *origin_out);
int 			redirect_in(int in_fd, int *origin_in);
int 			check_ambigious (t_token *node);
void 			retrieve(t_token *cmd);
void			run_built_in(t_token *cmd, int *exit_status, t_env *env, int in_child);
int				is_built_in(t_token *cmd);
void    		execute_external(t_token *cmd, int *exit_status, t_env *env);
#endif