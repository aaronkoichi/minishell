/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthiew <jthiew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 19:49:51 by jthiew            #+#    #+#             */
/*   Updated: 2025/05/26 15:08:58 by jthiew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_back_redir(t_redir **lst, t_redir *new)
{
	t_redir	*temp;

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

void	ft_lstclear_redir(t_redir **lst)
{
	t_redir	*temp;

	while (*lst != NULL)
	{
		temp = (*lst)->next;
		if ((*lst)->type == REDIR_HEREDOC)
			free((*lst)->heredoc_content);
		free(*lst);
		*lst = temp;
	}
}

int	ft_lstsize_redir(t_redir *lst)
{
	int	size;

	size = 0;
	while (lst != NULL)
	{
		size++;
		lst = lst->next;
	}
	return (size);
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
