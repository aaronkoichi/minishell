/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_symbol.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthiew <jthiew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:49:35 by jthiew            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/05/23 12:06:58 by jthiew           ###   ########.fr       */
=======
/*   Updated: 2025/05/26 21:31:38 by jthiew           ###   ########.fr       */
>>>>>>> 382a5b90820d9d64723eecd6b1f99c1d42123032
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

const t_sym_map	*get_double_or_triple_sym(void)
{
	static const t_sym_map	table[] = {
	{"<<<", TOKEN_HERESTR},
	{";;&", TOKEN_CASE_RE_NEXT},
	{">>", TOKEN_APPEND},
	{"&&", TOKEN_AND},
	{"||", TOKEN_OR},
	{"<<", TOKEN_HEREDOC},
	{"<&", TOKEN_FD_IN},
	{">&", TOKEN_FD_OUT},
	{";;", TOKEN_CASE_END},
	{";&", TOKEN_CASE_NEXT},
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
	{"&", TOKEN_ANDPS},
	{NULL, 0}
	};

	return (table);
}
