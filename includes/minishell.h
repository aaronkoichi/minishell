/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthiew <jthiew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:02:57 by jthiew            #+#    #+#             */
/*   Updated: 2025/07/07 16:04:04 by zlee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <term.h>
# include <unistd.h>

// PARSING
typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_OR,
	TOKEN_AND,
	TOKEN_REDIR_IN,
	TOKEN_HEREDOC,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND,
	TOKEN_LPAREN,
	TOKEN_RPAREN,
	TOKEN_SEQUENCE,
	TOKEN_ASYNC,
	TOKEN_HERESTR,
	TOKEN_FD_IN,
	TOKEN_FD_OUT,
	TOKEN_CASE_END,
	TOKEN_CASE_NEXT,
	TOKEN_CASE_RE_NEXT,
	TOKEN_EOF
}	t_token_type;

typedef struct s_sym_map
{
	const char		*symbol;
	t_token_type	type;
}	t_sym_map;

typedef struct s_token
{
	t_token_type	type;
	char			*content;
	struct s_token	*next;
}	t_token;

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
	REDIR_HERESTR,
	REDIR_FD_IN,
	REDIR_FD_OUT
}	t_redir_type;

typedef struct s_redir_map
{
	t_token_type	token_type;
	t_redir_type	redir_type;
}	t_redir_map;

typedef struct s_redir
{
	t_redir_type	type;
	char			*filename;
	char			*heredoc_content;
	char			*heredoc_eof;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char	**argv;
	int		argc;
	t_redir	*redirs;
	int		redir_count;
}	t_cmd;

typedef enum e_node_type
{
	NODE_ROOT,
	NODE_COMMAND,
	NODE_PIPE,
	NODE_AND,
	NODE_OR,
	NODE_SEQUENCE,
	NODE_SUBSHELL
}	t_node_type;

typedef struct s_ast
{
	t_node_type		type;
	struct s_ast	*left;
	struct s_ast	*right;
	t_cmd			*cmd;
}	t_ast;

typedef struct s_env
{
	char			*key;
	char			*value;
	int				ind;
	struct s_env	*next;
}	t_env;

typedef struct s_vars
{
	t_token	*token_list;
	t_ast	*ast_tree;
	t_env	*env;
	int		ori_stdin;
	int		ori_stdout;
	int		ori_stderr;
	int		exit_code;
	char	*home_dir;
	char	*pwd_dir;
	char	*oldpwd_dir;
}	t_vars;

typedef struct s_str_dat
{
	char	**command;
	char	**original;
}	t_str_dat;

typedef int	(*t_builtin_func)(t_cmd *cmd, t_env **env,
				t_vars *vars, t_str_dat dat);

typedef struct s_builtin_map
{
	const char		*cmd;
	t_builtin_func	func;
}	t_builtin_map;

extern volatile
sig_atomic_t g_signal;

// ==========================EXECUTION========================
typedef struct s_exec
{
	int	status;
	int	fork_pid[2];
	int	pipe_fd[2];
}	t_exec;

/* only used in wildcards.*/
typedef struct s_pos
{
	int	x;
	int	y;
}	t_pos;

typedef struct s_file
{
	char			*file;
	struct s_file	*next;
}					t_file;

typedef struct s_wrapper
{
	t_ast	*tree;
	t_token	*token;
}	t_wrapper;

// ==========================BUILTINS========================
// builtin_cd.c
int				builtin_cd(t_cmd *cmd, t_env **env, t_vars *vars,
					t_str_dat dat);

// builtin_cd_utils.c
t_env			*find_env_node_key(t_env *env, char *key);
int				update_pwd_dirs(t_vars *vars);
int				update_env_value(t_env *node, char *value);

// builtin_echo.c
int				builtin_echo(t_cmd *cmd, t_env **env, t_vars *vars,
					t_str_dat dat);

// builtin_env.c
int				builtin_env(t_cmd *cmd, t_env **env, t_vars *vars,
					t_str_dat dat);

// builtin_exit.c
int				builtin_exit(t_cmd *cmd, t_env **env, t_vars *vars,
					t_str_dat dat);

// builtin_export.c
int				builtin_export(t_cmd *cmd, t_env **env, t_vars *vars,
					t_str_dat dat);

// builtin_export_prt.c
void			export_print_env(t_env **env);

// builtin_pwd.c
int				builtin_pwd(t_cmd *cmd, t_env **env, t_vars *vars,
					t_str_dat dat);

// builtin_unset.c
int				builtin_unset(t_cmd *cmd, t_env **env, t_vars *vars,
					t_str_dat dat);

// builtin.c
int				builtin_functions(t_cmd *cmd, t_vars *vars,
					t_str_dat dat, int *status);

// ==========================PARSING========================
// envp.c
char			*get_env_key(char *env_line, int *i);
char			*get_env_value(char *env_line);
t_env			*create_env_node(char *env_line, int ind);
t_env			*get_env_list(char **env);

// env_list_utils.c
int				ft_lstsize_env(t_env *env);
void			ft_lstadd_back_env(t_env **lst, t_env *new);
void			ft_lstclear_env(t_env **env);
char			*get_env_list_value(t_env *env, char *key);

// parse_cmd.c
t_cmd			*init_cmd(t_token *token, t_vars *vars);

// parse_rdp_1.c
t_ast			*parse_pipe(t_token **token, int *is_error, t_vars *vars);
t_ast			*parse_and(t_token **token, int *is_error, t_vars *vars);
t_ast			*parse_or(t_token **token, int *is_error, t_vars *vars);
t_ast			*parse_sequence(t_token **token, int *is_error, t_vars *vars);
t_ast			*parse_token(t_token *token, t_vars *vars);

// parse_rdp_2.c
t_cmd			*parse_cmd(t_token **token, t_vars *vars);
t_ast			*parse_subshell(t_token **token, int *is_error, t_vars *vars);
t_ast			*parse_cmd_or_subshell(t_token **token,
					int *is_error, t_vars *vars);
t_ast			*parse_cterm(t_token **token, int *is_error, t_vars *vars);
t_ast			*parse_async(t_token **token, int *is_error, t_vars *vars);

// parse_redir.c
t_redir			*create_redir_node(t_token **token, t_vars *vars);

// parse_redir_type.c
t_redir_type	get_redir_type(t_token *token);

// parse_redir_utils.c
void			ft_lstadd_back_redir(t_redir **lst, t_redir *new);
void			ft_lstclear_redir(t_redir **lst);
int				is_supported_redir(t_token *token);
char			*strip_quotes_eof(char *str);

// parse_utils.c
t_ast			*create_ast_node(t_node_type type, t_ast *left,
					t_ast *right, t_cmd *cmd);
void			ft_lstclear_ast_tree(t_ast **ast);
void			print_unexpected_token(char *content, t_vars *vars);
void			print_bad_ending(char *content);
bool			is_parse_err(t_token *token, t_vars *vars);

// signal.c
void			set_signal_noninteract(void);
void			set_signal_interact(void);
void			reset_signal(void);

// token.c
t_token			*tokenize_str(char *str);

// token_symbol.c
const t_sym_map	*get_double_or_triple_sym(void);
const t_sym_map	*get_single_sym(void);

// token_utils.c
void			ft_lstadd_back_token(t_token **lst, t_token *new);
void			ft_lstclear_token(t_token **token);
bool			is_token_ops(t_token *token);
bool			is_token_cterm(t_token *token);
bool			is_token_redirs(t_token *token);

// token_word.c
char			*token_word(char **str);

// vars.c
void			destroy_vars(t_vars *vars);
void			init_vars(t_vars *vars, char **envp);

// main.c
t_ast			*parse_input(t_token **token_list, char *input, t_vars *vars);
void			start_usr_input(t_vars *vars);

// ==========================EXECUTION========================
// exec_main.c
int				exec_main(t_ast *node, t_vars *vars,
					t_ast *tree, t_token *token);
// exec_main_subshell.c
int				function_tree_subshell(t_ast *node, t_vars *vars, t_ast *tree,
					t_token *token);
// exec_utils.c
void			free_arr(char **arr);
int				run_cmd(char **exec, t_vars *vars, t_redir **redirs,
					char **envp);
void			reset_fd(t_vars *vars);
char			**construct_envp(t_vars *vars);
// prep_cmd.c
char			**prep_cmd(t_cmd *cmd, t_vars *vars);
// exec_pipe.c
int				function_tree_pipe_left(t_ast *node, t_vars *vars, t_exec *info,
					t_wrapper wrapper);
int				function_tree_pipe_right(t_ast *node, t_vars *vars,
					t_exec *info, t_wrapper wrapper);
int				function_tree_pipe(t_ast *node, t_vars *vars, t_ast *tree,
					t_token *token);
// exec_parse_cmd.c
int				exec_cmd_main(t_ast *node, t_vars *vars);
// exec_parse_cmd_utils.c
void			touch_files(t_ast *node, t_redir **redirs);
int				redirect_fd(t_redir **redirs);
void			close_fds(void);
int				redirect_fail(char **cmd, t_redir **redirs);
// exec_parse_cmd_redirs.c
int				redir_out(t_redir *redir);
int				redir_in(t_redir *redir);
t_redir			**determine_redir(t_ast *node);
int				subshell_redir(t_ast *node);
// for handling the wildcards
// wildcard.c
char			**detect_wildcard(t_cmd *cmd, char **metadata);
// wildcard_fnmatch.c
int				ft_fnmatch(const char *pattern, const char *filename,
					const char *metadata);
/*wildcard_utils.c*/
void			free_array(char **arr);
int				count_trim_lines(char **arr, const char *filename);
void			ft_lstaddback_file(t_file **file, char *string);
int				ft_lstsize_file(t_file *file);
void			ft_lstclear_file(t_file **file, void (*del)(void *));
// wildcard_mk_new_exev.c
t_file			*mk_new_execve(t_file **files, char *str, char *metadata);
// wildcard_qsort.c
char			**qsort_main(char **arr);
// environ_main.c
char			**detect_env(t_vars *vars, char **arr);
// environ_utils.c
char			**ft_strdup_arr(char **arr);
char			find_sym_env(char *string);
// exec_environ_trim.c
char			*move_char(char *arr);
char			*move_char_wild(char *arr);
// execve_trim.c
char			**trim_execve(t_cmd *cmd);

#endif
