/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_symbol.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthiew <jthiew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:49:35 by jthiew            #+#    #+#             */
/*   Updated: 2025/05/23 12:06:58 by jthiew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

const t_sym_map	*get_double_sym(void)
{
	static const t_sym_map	table[] = {
	{">>", TOKEN_APPEND},
	{"&&", TOKEN_AND},
	{"||", TOKEN_OR},
	{"<<", TOKEN_HEREDOC},
	{NULL, 0}
	};

	return (table);
}

const t_sym_map	*get_single_sym(void)
{
	static const t_sym_map	table[] = {
	{"<", TOKEN_REDIR_IN},
	{">", TOKEN_REDIR_OUT},
	{"|", TOKEN_PIPE},
	{"(", TOKEN_LPAREN},
	{")", TOKEN_RPAREN},
	{";", TOKEN_SEQUENCE},
	{NULL, 0}
	};

	return (table);
}
