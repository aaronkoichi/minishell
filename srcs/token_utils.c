/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthiew <jthiew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:49:35 by jthiew            #+#    #+#             */
/*   Updated: 2025/05/29 12:56:48 by jthiew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_back_token(t_token **lst, t_token *new)
{
	t_token	*temp;

	temp = *lst;
	if (*lst == NULL)
		*lst = new;
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
}

void	ft_lstclear_token(t_token **token)
{
	t_token	*temp;

	while (*token != NULL)
	{
		temp = (*token)->next;
		free((*token)->content);
		free(*token);
		*token = temp;
	}
}

bool	is_token_ops(t_token *token)
{
	if (token->type == TOKEN_PIPE
		|| token->type == TOKEN_OR
		|| token->type == TOKEN_AND
		|| token->type == TOKEN_SEQUENCE
		|| token->type == TOKEN_ASYNC)
		return (true);
	return (false);
}

bool	is_token_cterm(t_token *token)
{
	if (token->type == TOKEN_CASE_END
		|| token->type == TOKEN_CASE_NEXT
		|| token->type == TOKEN_CASE_RE_NEXT)
		return (true);
	return (false);
}

bool	is_token_redirs(t_token *token)
{
	if (token->type == TOKEN_REDIR_IN
		|| token->type == TOKEN_REDIR_OUT
		|| token->type == TOKEN_HEREDOC
		|| token->type == TOKEN_APPEND
		|| token->type == TOKEN_HERESTR
		|| token->type == TOKEN_FD_IN
		|| token->type == TOKEN_FD_OUT)
		return (true);
	return (false);
}
