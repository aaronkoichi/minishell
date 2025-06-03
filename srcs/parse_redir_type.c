/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir_type.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthiew <jthiew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:29:57 by jthiew            #+#    #+#             */
/*   Updated: 2025/05/29 14:31:07 by jthiew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

const t_redir_map	*get_redir_map(void)
{
	static const t_redir_map	table[] = {
	{TOKEN_APPEND, REDIR_APPEND},
	{TOKEN_REDIR_IN, REDIR_IN},
	{TOKEN_REDIR_OUT, REDIR_OUT},
	{TOKEN_HEREDOC, REDIR_HEREDOC},
	{TOKEN_HERESTR, REDIR_HERESTR},
	{TOKEN_FD_IN, REDIR_FD_IN},
	{TOKEN_FD_OUT, REDIR_FD_OUT},
	{TOKEN_EOF, 0}
	};

	return (table);
}

static const t_redir_map	*match_redir(const t_redir_map *table,
								t_token_type type)
{
	while (table->token_type != TOKEN_EOF)
	{
		if (table->token_type == type)
			return (table);
		table++;
	}
	return (NULL);
}

t_redir_type	get_redir_type(t_token *token)
{
	const t_redir_map	*match;

	match = match_redir(get_redir_map(), token->type);
	if (match != NULL)
		return (match->redir_type);
	else
		return (0);
}
