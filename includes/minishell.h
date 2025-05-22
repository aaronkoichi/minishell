/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthiew <jthiew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:02:57 by jthiew            #+#    #+#             */
/*   Updated: 2025/05/22 12:54:04 by jthiew           ###   ########.fr       */
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
	TOKEN_EOF
}	t_token_type;

/* changed structs
typedef struct s_token
{
	t_token_type	type;
	char			*content;
}	t_token;

typedef struct s_token_node
{
	t_token				*token;
	struct s_token_node	*next;
}	t_token_node;

typedef struct s_token_list
{
	t_token_node	*head;
	int				num_token;
}	t_token_list;
*/

// added symbol map struct
typedef struct s_sym_map
{
	const char		*symbol;
	t_token_type	type;
}	t_sym_map;

// consolidated s_token and s_token_node
typedef struct s_token
{
	t_token_type	type;
	char			*content;
	struct s_token	*next;
}	t_token;

// can remove this struct
// typedef struct s_token_list
// {
// 	t_token	*head;
// 	int		num_token;
// }	t_token_list;

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}	t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;
	char			*filename;
	char			*heredoc_content;
	char			*heredoc_eof;
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

// token.c
t_token			*tokenize_str(char *str);

// token_symbol.c
const t_sym_map	*get_double_sym(void);
const t_sym_map	*get_single_sym(void);

// token_utils.c
void			ft_lstadd_back_token(t_token **lst, t_token *new);
void			ft_lstclear_token(t_token **token);
int				ft_lstsize_token(t_token *lst);

// token_word.c
char			*token_word(char **str);

// parse.c
t_ast			*parse_token(t_token **token);

#endif
