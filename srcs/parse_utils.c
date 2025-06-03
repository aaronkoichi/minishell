/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthiew <jthiew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 12:51:29 by jthiew            #+#    #+#             */
/*   Updated: 2025/05/30 11:26:52 by jthiew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*create_ast_node(t_node_type type, t_ast *left,
			t_ast *right, t_cmd *cmd)
{
	t_ast	*node;

	node = malloc(1 * sizeof(t_ast));
	if (node == NULL)
		return (NULL);
	node->type = type;
	node->left = left;
	node->right = right;
	node->cmd = cmd;
	return (node);
}

void	ft_lstclear_ast_tree(t_ast **ast)
{
	t_ast	*left;
	t_ast	*right;

	if (*ast == NULL)
		return ;
	left = (*ast)->left;
	right = (*ast)->right;
	if ((*ast)->cmd != NULL)
	{
		free((*ast)->cmd->argv);
		ft_lstclear_redir(&(*ast)->cmd->redirs);
		free((*ast)->cmd);
	}
	free(*ast);
	if (left != NULL)
		ft_lstclear_ast_tree(&left);
	if (right != NULL)
		ft_lstclear_ast_tree(&right);
}

void	print_unexpected_token(char *content)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(content, 2);
	ft_putstr_fd("'\n", 2);
}

void	print_bad_ending(char *content)
{
	ft_putstr_fd("Opps, minishell no likey command ending with ", 2);
	ft_putstr_fd(content, 2);
	ft_putstr_fd("\n", 2);
}

bool	is_parse_err(t_token *token)
{
	if (is_token_cterm(token->next)
		|| is_token_ops(token->next)
		|| token->next->type == TOKEN_RPAREN
		|| (is_token_redirs(token) && is_token_redirs(token->next))
		|| (is_token_redirs(token) && token->next->type == TOKEN_EOF))
	{
		print_unexpected_token(token->next->content);
		return (true);
	}
	if (!(token->type == TOKEN_SEQUENCE || token->type == TOKEN_ASYNC)
		&& token->next->type == TOKEN_EOF)
	{
		if (is_token_ops(token) == true)
			print_bad_ending("list delimiters");
		if (is_token_cterm(token) == true)
			print_bad_ending("case terminators");
		return (true);
	}
	return (false);
}
