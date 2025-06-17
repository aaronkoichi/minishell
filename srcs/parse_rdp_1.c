/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rdp_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthiew <jthiew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 19:42:45 by jthiew            #+#    #+#             */
/*   Updated: 2025/06/04 13:41:14 by jthiew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*parse_pipe(t_token **token, int *is_error, t_vars *vars)
{
	t_ast	*left;
	t_ast	*right;

	left = parse_async(token, is_error, vars);
	while (*token != NULL && (*token)->type == TOKEN_PIPE)
	{
		if (is_parse_err(*token, vars) == true)
		{
			ft_lstclear_ast_tree(&left);
			*is_error = 1;
			return (NULL);
		}
		*token = (*token)->next;
		right = parse_async(token, is_error, vars);
		left = create_ast_node(NODE_PIPE, left, right, NULL);
	}
	return (left);
}

t_ast	*parse_and(t_token **token, int *is_error, t_vars *vars)
{
	t_ast	*left;
	t_ast	*right;

	left = parse_pipe(token, is_error, vars);
	while (*token != NULL && (*token)->type == TOKEN_AND)
	{
		if (is_parse_err(*token, vars) == true)
		{
			ft_lstclear_ast_tree(&left);
			*is_error = 1;
			return (NULL);
		}
		*token = (*token)->next;
		right = parse_pipe(token, is_error, vars);
		left = create_ast_node(NODE_AND, left, right, NULL);
	}
	return (left);
}

t_ast	*parse_or(t_token **token, int *is_error, t_vars *vars)
{
	t_ast	*left;
	t_ast	*right;

	left = parse_and(token, is_error, vars);
	while (*token != NULL && (*token)->type == TOKEN_OR)
	{
		if (is_parse_err(*token, vars) == true)
		{
			ft_lstclear_ast_tree(&left);
			*is_error = 1;
			return (NULL);
		}
		*token = (*token)->next;
		right = parse_and(token, is_error, vars);
		left = create_ast_node(NODE_OR, left, right, NULL);
	}
	return (left);
}

t_ast	*parse_sequence(t_token **token, int *is_error, t_vars *vars)
{
	t_ast	*left;
	t_ast	*right;

	left = parse_or(token, is_error, vars);
	while (*token != NULL && (*token)->type == TOKEN_SEQUENCE)
	{
		if (is_parse_err(*token, vars) == true)
		{
			ft_lstclear_ast_tree(&left);
			*is_error = 1;
			return (NULL);
		}
		*token = (*token)->next;
		if ((*token)->type != TOKEN_EOF)
		{
			right = parse_or(token, is_error, vars);
			left = create_ast_node(NODE_SEQUENCE, left, right, NULL);
		}
		else
			left = create_ast_node(NODE_SEQUENCE, left, NULL, NULL);
	}
	return (left);
}

t_ast	*parse_token(t_token *token, t_vars *vars)
{
	t_ast	*root;
	int		is_error;

	if (token->type == TOKEN_EOF)
		return (NULL);
	if (!(token->type == TOKEN_WORD || token->type == TOKEN_LPAREN
			|| is_token_redirs(token) == true))
	{
		print_unexpected_token(token->content, vars);
		return (NULL);
	}
	is_error = 0;
	root = parse_sequence(&token, &is_error, vars);
	if (is_error == 1 || token->type == TOKEN_RPAREN)
	{
		if (token->type == TOKEN_RPAREN)
			print_unexpected_token(token->content, vars);
		ft_lstclear_ast_tree(&root);
		return (NULL);
	}
	return (root);
}
