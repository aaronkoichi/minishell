/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rdp_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthiew <jthiew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 19:42:45 by jthiew            #+#    #+#             */
/*   Updated: 2025/05/25 19:43:17 by jthiew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*parse_pipe(t_token **token)
{
	t_ast	*left;
	t_ast	*right;

	left = parse_cmd_or_subshell(token);
	while (*token != NULL && (*token)->type == TOKEN_PIPE)
	{
		*token = (*token)->next;
		right = parse_cmd_or_subshell(token);
		left = create_ast_node(NODE_PIPE, left, right, NULL);
	}
	return (left);
}

t_ast	*parse_and(t_token **token)
{
	t_ast	*left;
	t_ast	*right;

	left = parse_pipe(token);
	while (*token != NULL && (*token)->type == TOKEN_AND)
	{
		*token = (*token)->next;
		right = parse_pipe(token);
		left = create_ast_node(NODE_AND, left, right, NULL);
	}
	return (left);
}

t_ast	*parse_or(t_token **token)
{
	t_ast	*left;
	t_ast	*right;

	left = parse_and(token);
	while (*token != NULL && (*token)->type == TOKEN_OR)
	{
		*token = (*token)->next;
		right = parse_and(token);
		left = create_ast_node(NODE_OR, left, right, NULL);
	}
	return (left);
}

t_ast	*parse_sequence(t_token **token)
{
	t_ast	*left;
	t_ast	*right;

	left = parse_or(token);
	while (*token != NULL && (*token)->type == TOKEN_SEQUENCE)
	{
		*token = (*token)->next;
		right = parse_or(token);
		left = create_ast_node(NODE_SEQUENCE, left, right, NULL);
	}
	return (left);
}

t_ast	*parse_token(t_token *token)
{
	t_ast	*root;

	root = parse_sequence(&token);
	return (root);
}
