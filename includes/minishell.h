/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthiew <jthiew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Updated: 2025/05/26 21:21:56 by jthiew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"

# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

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
	TOKEN_ANDPS,
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
	REDIR_HEREDOC
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

// parse_cmd.c
int				get_cmd_argc(t_token *token, t_cmd *cmd);
char			**get_cmd_argv(t_token *token, t_cmd *cmd);
int				create_and_add_redir(t_token **token, t_redir **head);
t_redir			*get_cmd_redirs(t_token *token, t_cmd *cmd);

// parse_rdp_1.c
t_ast			*parse_token(t_token *token);
t_ast			*parse_or(t_token **token);

// parse_rdp_2.c
t_ast			*parse_cmd_or_subshell(t_token **token);

// parse_redir.c
char			*get_hdoc_content(char *eof);
t_redir_type	get_redir_type(t_token *token);

// parse_redir_utils.c
void			ft_lstadd_back_redir(t_redir **lst, t_redir *new);
void			ft_lstclear_redir(t_redir **lst);
int				ft_lstsize_redir(t_redir *lst);
bool			is_token_redirs(t_token *token);

// parse_utils.c
t_ast			*create_ast_node(t_node_type type, t_ast *left,
					t_ast *right, t_cmd *cmd);
void			ft_lstclear_ast_tree(t_ast **ast);

// token.c
t_token			*tokenize_str(char *str);

// token_symbol.c
const t_sym_map	*get_double_or_triple_sym(void);
const t_sym_map	*get_single_sym(void);

// token_utils.c
void			ft_lstadd_back_token(t_token **lst, t_token *new);
void			ft_lstclear_token(t_token **token);
int				ft_lstsize_token(t_token *lst);

// token_valid_case.c
bool			is_valid_case(t_token *token);

// token_valid_op.c
bool			is_valid_op(t_token *token);

// token_valid_redir.c
bool			is_valid_redir(t_token *token);

// token_word.c
char			*token_word(char **str);
#endif
