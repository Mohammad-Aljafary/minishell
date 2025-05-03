/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammad-boom <mohammad-boom@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:32:29 by taabu-fe          #+#    #+#             */
/*   Updated: 2025/05/03 17:54:45 by mohammad-bo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/includes/get_next_line.h"
# include "../libft/includes/libft.h"
# include <curses.h>
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <term.h>
# include <unistd.h>
# include <signal.h>

extern int			g_sig;

typedef enum e_type
{
	NOT_DEFINED,
	PIPE,
	OUT_RE,
	IN_RE,
	HERE_DOC,
	COMMAND,
	APPENDS,
	DELIMITER,
	ARGS,
	FILES,
	S_QOUTE
}					t_type;

typedef enum e_quote
{
	SINGLE_QOUTE,
	DOUBLE_QUOTE,
	NOT_QUOTE
}					t_quote;

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

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_all
{
	t_token			*tok_lst;
	t_env			*env_lst;
	t_env			*exp_lst;
	char			*argv;
	int				exit_status;
	int				num_of_child;
	pid_t			last_pid;
}					t_all;

/************************************************************\
\***************** LIST OPERATIONS **************************\
\************************************************************/
t_token				*create(char *str);
void				add_back(t_token **list, t_token *new_node);
void				clear_list(t_token **list);
void				print_list(t_token *list);
void				create_list_env(t_env **list, char **envp);
void				add_back_env(t_env **list, t_env *node);
void				clear_list_env(t_env **list);
void				clear_all(t_all *all);
void				delete_node_env(t_env **list, char *key);
t_env				*create_node_env(char *key, char *value);
void				add_node_env(t_env **list, t_env *node, char *key);
void				add_node_token(t_token **list, t_token *prev_node,
						t_token *node);
void				delete_ptr(t_token **list, t_token *lst);
void				create_list_exp(t_env *env, t_env **exp);

/*************************************************************\
\******************** TOKENIZATION ***************************\
\*************************************************************/
int					tokenize(char *line, t_token **list);
int					check_type(t_token *list);
void				parser(t_token **list);
void    			parser2(t_token *list);
int					syntax_error(t_token *list);
int					is_whitespace(char c);
int					check_redirection(t_token *list);
void				move_command_to_front(t_token **head);

/*************************************************************\
\********************** Expander *****************************\
\*************************************************************/
char				*search_env(t_env *env, char *key);
int					expander(t_token **tok_lst, t_env *env_lst, char *argv,
						int exit_status);
int					break_string(t_token **list, char *token);
int					replace(t_token *p, t_env *envp, char *argv, int exit_status);
int					join_strings(t_token *p, char   **token, t_token *ptr1);

/**************************************************************\
\*********************** Execution ****************************\
\**************************************************************/
void				execute(t_all *lists);
int					join_args(t_token *node);
void				delete_token(t_token **list, t_type type, int flag);
int					apply_re_out(t_token **re_node, t_token *command, int flag);
int					apply_re_in(t_token **re_token, t_token *command);
int					redirect_out(int out_fd, int *origin_out, int in_child);
int					redirect_in(int in_fd, int *origin_in, int in_child);
int 				apply_here(t_token *cmd, char *filename, t_token **re_token);
int					check_ambigious(t_token *node);
int 				apply_redirection(t_token **next_node, t_token *node, int in_child, char **heredoc, t_all *all);
void				retrieve(t_token *cmd);
void				run_built_in(t_token *cmd, int *exit_status, t_all *all,
						int in_child);
int					is_built_in(t_token *cmd);
void				execute_external(t_token *cmd, t_all *all, t_token *node,
						int fd[2], int *prev, char **heredoc);
void    			run_external(t_token *cmd, int *exit_status, t_all *all);


/**************************************************************\
\*********************** Built-ins ****************************\
\**************************************************************/
int					args_count(char **args);
int					ft_cd(t_token *cmd, t_env **env);
int					ft_echo(t_token *cmd);
int					ft_env(t_token *cmd, t_env *list);
int					ft_exits(t_token *cmd, t_all *all);
void				ft_export(t_token *cmd, t_env **env, t_env **exp,
						int *exit_status);
int					ft_pwd(void);
int					ft_unset(t_token *cmd, t_env **env, t_env **exp);

/**************************************************************\
\************************* Signals ****************************\
\**************************************************************/
void	signal_setup();


char    **apply_heredoc(t_all *lists);
void    unlinks (char **heredoc);
int break_heredoc(t_token **list, char *str);
#endif