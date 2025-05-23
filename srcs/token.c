/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthiew <jthiew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:49:35 by jthiew            #+#    #+#             */
/*   Updated: 2025/05/23 14:34:38 by jthiew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token(t_token_type type, char *content)
{
	t_token	*token;

	token = malloc(1 * sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->type = type;
	token->content = content;
	if (token->content == NULL)
	{
		free(token);
		return (NULL);
	}
	token->next = NULL;
	return (token);
}

static const t_sym_map	*match_sym(const t_sym_map *table, char *str)
{
	size_t	len;

	while (table->symbol != NULL)
	{
		len = ft_strlen(table->symbol);
		if (ft_strncmp(str, table->symbol, len) == 0)
			return (table);
		table++;
	}
	return (NULL);
}

void	get_type_content(t_token_type *type, char **content, char **str)
{
	const t_sym_map	*match;

	match = match_sym(get_double_sym(), *str);
	if (match != NULL)
	{
		*type = match->type;
		*content = ft_strdup(match->symbol);
		*str += ft_strlen(match->symbol);
		return ;
	}
	match = match_sym(get_single_sym(), *str);
	if (match != NULL)
	{
		*type = match->type;
		*content = ft_strdup(match->symbol);
		*str += ft_strlen(match->symbol);
		return ;
	}
	else
	{
		*type = TOKEN_WORD;
		*content = token_word(str);
	}
}

int	create_and_add_token(t_token_type type, char *content, t_token **head)
{
	t_token			*token;

	token = create_token(type, content);
	if (token == NULL)
	{
		ft_lstclear_token(head);
		return (1);
	}
	ft_lstadd_back_token(head, token);
	return (0);
}

// TODO handle parse error like <<<< and >>>
t_token	*tokenize_str(char *str)
{
	t_token			*head;
	t_token_type	type;
	char			*content;

	head = NULL;
	while (*str != '\0')
	{
		if (ft_isspace(*str) == 1)
			str++;
		else
		{
			get_type_content(&type, &content, &str);
			if (create_and_add_token(type, content, &head) == 1)
				return (NULL);
		}
	}
	if (create_and_add_token(TOKEN_EOF, ft_strdup("\0"), &head) == 1)
		return (NULL);
	return (head);
}
