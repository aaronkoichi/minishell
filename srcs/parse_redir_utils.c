/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthiew <jthiew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 19:49:51 by jthiew            #+#    #+#             */
/*   Updated: 2025/05/30 14:01:02 by jthiew           ###   ########.fr       */
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

int	is_supported_redir(t_token *token)
{
	if (token->type == TOKEN_HERESTR || token->type == TOKEN_FD_IN
		|| token->type == TOKEN_FD_OUT)
	{
		if (token->type == TOKEN_HERESTR)
			ft_putstr_fd("Opps, minishell no likey here_string\n", 2);
		else
			ft_putstr_fd("Opps, minishell no likey fd redirections\n", 2);
		return (false);
	}
	return (true);
}

size_t	get_strip_len(char *str)
{
	size_t	len;
	char	quo_type;

	len = 0;
	while (*str != '\0')
	{
		if (*str == '\'' || *str == '\"')
		{
			quo_type = *str++;
			while (*str != '\0' && *str != quo_type)
			{
				str++;
				len++;
			}
			if (*str == quo_type)
				str++;
		}
		else
		{
			str++;
			len++;
		}
	}
	return (len);
}

char	*strip_quotes_eof(char *str)
{
	size_t	len;
	size_t	i;
	char	*strip_str;
	char	quo_type;

	len = get_strip_len(str);
	strip_str = malloc((len + 1) * sizeof(char));
	if (strip_str == NULL)
		return (NULL);
	i = 0;
	while (*str != '\0' && i < len)
	{
		if (*str == '\'' || *str == '\"')
		{
			quo_type = *str++;
			while (*str != '\0' && *str != quo_type)
				strip_str[i++] = *str++;
			if (*str == quo_type)
				str++;
		}
		else
			strip_str[i++] = *str++;
	}
	strip_str[i] = '\0';
	return (strip_str);
}
