/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:32:29 by taabu-fe          #+#    #+#             */
/*   Updated: 2025/05/10 10:35:26 by malja-fa         ###   ########.fr       */
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
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

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
	char			**heredoc;
	int				exit_status;
	int				num_of_child;
	int				pipefd[2];
	pid_t			last_pid;
}					t_all;

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
void				add_front(t_token **list, t_token *new_node);

int					tokenize(char *line, t_token **list);
int					check_type(t_token *list);
void				parser(t_token **list);
void				parser2(t_token *list);
int					syntax_error(t_token *list);
int					is_whitespace(char c);
int					check_redirection(t_token *list);
void				move_command_to_front(t_token **head);
int					divide_by_qoute(char *line, int *flag, int *j);
int					divide_text(char *line, int i, int *j, int *flag);
int					get_op_len(char *str);
int					is_operator(char c);
t_token				*create_token(char *line, int i, int len);

char				*search_env(t_env *env, char *key);
int					expander(t_token **tok_lst, t_all *all);
int					break_string(t_token **list, char *token);
int					replace(t_token *p, t_all *all);
int					join_strings(t_token *p, char **token, t_token *ptr1);
size_t				calculate_tokens_length(t_token *ptr);
int					replace_env(t_token *p, t_env *envp, int *i, int *j);
int					replace_exit_status(char **token, int exit_status);
int					replace_num(char **token, char *minishell_file);
int					word_split(t_token **list);
int					remove_quotes(char **line1);
int					free_return(t_token **p);
int					handle_dollar_sign(t_token *p, t_all *all, int *i);
int					process_token(t_token *p, t_all *all);
int					handle_double_quotes(t_token **list, char *token, int *i);
int					handle_double_utile(t_token **list, char *token, int length,
						int *i);
int					handle_single_quotes(t_token **list, char *token, int *i);
int					handle_variable(t_token **list, char *token, int *i,
						int check);

void				execute(t_all *lists);
int					join_args(t_token *node);
void				delete_args(t_token **list, t_type type);
int					apply_re_out(t_token **re_node, t_token *command, int flag);
int					apply_re_in(t_token **re_token, t_token *command);
int					redirect_out(int out_fd, int *origin_out, int in_child);
int					redirect_in(int in_fd, int *origin_in, int in_child);
int					apply_here(t_token *cmd, char *filename,
						t_token **re_token);
void				handle_redirection_node(t_token **node, t_token *cmd,
						t_all *all, int *prev_fd);
int					check_ambigious(t_token *node);
int					apply_redirection(t_token **next_node, t_token *node,
						int in_child, t_all *all);
void				retrieve(t_token *cmd);
void				run_built_in(t_token *cmd, int *exit_status, t_all *all,
						int in_child);
int					is_built_in(t_token *cmd);
int					is_executable(char *cmd, int *exit_status);
int					is_absolute_path(t_token *cmd);
void				execute_external(t_token *cmd, t_all *all, t_token *node,
						int *prev);
void				run_external(t_token *cmd, int *exit_status, t_all *all);
char				**list_to_arr(t_env *env);
char				*check_cmd(t_token *cmd, int *exit_status, t_all *all);
void				handle_pipe_or_exit(t_all *all);
void				find_file(t_token *cmd, t_token *list, int *i);
void				wait_status(t_all *wait_statuss);
char				*access_path(t_token *cmd, char **paths, int *exit_status);
char				*find_cmd_path(t_token *cmd, int *exit_status, t_all *all);

int					args_count(char **args);
int					ft_cd(t_token *cmd, t_env **env, t_env **exp);
int					ft_echo(t_token *cmd);
int					ft_env(t_token *cmd, t_env *list);
int					ft_exits(t_token *cmd, t_all *all);
int					ft_pwd(void);
int					ft_unset(t_token *cmd, t_env **env, t_env **exp);
void				ft_export(t_token *cmd, t_env **env, t_env **exp,
						int *exit_status);
void				free_env_node(t_env *node);
int					add_to_export(char **key, char **value, t_env **env,
						t_env **exp);
int					split_key_value(char *arg, t_env **env, t_env **exp);

void				setup_signals(void);
void				setup_signals2(void);
void				sigint_handler_heredoc(int sig);
void				setup_heredoc_signals(void);
void				signal_handler(int sig);
char				**apply_heredoc(t_all *lists);
void				unlinks(char **heredoc);
int					break_heredoc(t_token **list, char *str);
char				*check_file(t_token *node, t_all *all);
int					heredoc_count(t_token *lst);
int					expand_all_variables(char **str, t_all *all);
int					file_exist(char *filename);

void				increment_shlvl(t_env *envp);
void				check_tty_or_stop_program(void);
int					check_if_whitspace(char *line);
#endif