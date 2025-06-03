/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthiew <jthiew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:02:57 by jthiew            #+#    #+#             */
/*   Updated: 2025/06/03 16:11:35 by jthiew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"

# include <dirent.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <term.h>
# include <unistd.h>

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

extern volatile sig_atomic_t	g_signal;

// builtin_echo.c
int				builtin_echo(t_cmd *cmd, t_env **env);

// builtin_env.c
int				builtin_env(t_cmd *cmd, t_env **env);

// builtin_exit.c
int				builtin_exit(t_cmd *cmd, t_env **env);

// builtin_export.c
int				builtin_export(t_cmd *cmd, t_env **env);

// builtin_pwd.c
int				builtin_pwd(t_cmd *cmd, t_env **env);

// builtin_unset.c
int				builtin_unset(t_cmd *cmd, t_env **env);

// envp.c
char			*get_env_key(char **env_line);
char			*get_env_value(char *env_line);
t_env			*create_env_node(char *env_line);
void			ft_lstadd_back_env(t_env **lst, t_env *new);
void			ft_lstclear_env(t_env **env);
t_env			*get_env_list(char **env);
char			*get_env_list_value(t_env *env, char *key);

// parse_cmd.c
t_cmd			*init_cmd(t_token *token);

// parse_rdp_1.c
t_ast			*parse_pipe(t_token **token, int *is_error);
t_ast			*parse_and(t_token **token, int *is_error);
t_ast			*parse_or(t_token **token, int *is_error);
t_ast			*parse_sequence(t_token **token, int *is_error);
t_ast			*parse_token(t_token *token);

// parse_rdp_2.c
t_cmd			*parse_cmd(t_token **token);
t_ast			*parse_subshell(t_token **token, int *is_error);
t_ast			*parse_cmd_or_subshell(t_token **token, int *is_error);
t_ast			*parse_cterm(t_token **token, int *is_error);
t_ast			*parse_async(t_token **token, int *is_error);

// parse_redir.c
t_redir			*create_redir_node(t_token **token);

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
void			print_unexpected_token(char *content);
void			print_bad_ending(char *content);
bool			is_parse_err(t_token *token);

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

t_ast			*parse_input(t_token **token_list, char *input, t_vars *vars);
void			start_usr_input(t_vars *vars);

#endif
