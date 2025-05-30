/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rdp_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthiew <jthiew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 19:48:16 by jthiew            #+#    #+#             */
/*   Updated: 2025/05/30 14:50:12 by jthiew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*parse_cmd(t_token **token)
{
	t_cmd	*cmd;

	cmd = init_cmd(*token);
	if (cmd == NULL)
		return (NULL);
	while (token != NULL && (is_token_redirs(*token) == true
			|| (*token)->type == TOKEN_WORD))
		*token = (*token)->next;
	return (cmd);
}

t_ast	*parse_subshell(t_token **token, int *is_error)
{
	t_ast	*subshell;
	t_cmd	*cmd;

	*token = (*token)->next;
	subshell = parse_sequence(token, is_error);
	if ((*token)->type != TOKEN_RPAREN)
	{
		ft_putstr_fd("Opps, minishell no likey unclosed parenthesis\n", 2);
		ft_lstclear_ast_tree(&subshell);
		*is_error = 1;
		return (NULL);
	}
	*token = (*token)->next;
	cmd = parse_cmd(token);
	return (create_ast_node(NODE_SUBSHELL, subshell, NULL, cmd));
}

t_ast	*parse_cmd_or_subshell(t_token **token, int *is_error)
{
	t_cmd	*cmd;

	if ((*token)->type == TOKEN_LPAREN)
		return (parse_subshell(token, is_error));
	cmd = parse_cmd(token);
	if (cmd == NULL)
	{
		*is_error = 1;
		return (NULL);
	}
	return (create_ast_node(NODE_COMMAND, NULL, NULL, cmd));
}

t_ast	*parse_cterm(t_token **token, int *is_error)
{
	t_ast	*left;
	t_ast	*right;
	t_token	*temp;

	left = parse_cmd_or_subshell(token, is_error);
	while (*token != NULL && is_token_cterm(*token) == true)
	{
		if (is_parse_err(*token) == true)
		{
			ft_lstclear_ast_tree(&left);
			*is_error = 1;
			return (NULL);
		}
		temp = *token;
		*token = (*token)->next;
		right = parse_cmd_or_subshell(token, is_error);
		if (right != NULL)
			print_unexpected_token(temp->content);
		*is_error = 1;
		ft_lstclear_ast_tree(&left);
		ft_lstclear_ast_tree(&right);
		return (NULL);
	}
	return (left);
}

t_ast	*parse_async(t_token **token, int *is_error)
{
	t_ast	*left;
	t_ast	*right;

	left = parse_cterm(token, is_error);
	while (*token != NULL && (*token)->type == TOKEN_ASYNC)
	{
		if (is_parse_err(*token) == true)
		{
			ft_lstclear_ast_tree(&left);
			*is_error = 1;
			return (NULL);
		}
		*token = (*token)->next;
		right = parse_cterm(token, is_error);
		if (right != NULL)
		{
			ft_putstr_fd("Opps, minishell no likey asynchronous ", 2);
			ft_putstr_fd("execution\n", 2);
		}
		*is_error = 1;
		ft_lstclear_ast_tree(&left);
		ft_lstclear_ast_tree(&right);
		return (NULL);
	}
	return (left);
}
