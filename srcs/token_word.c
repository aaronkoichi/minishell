/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthiew <jthiew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 12:21:40 by jthiew            #+#    #+#             */
/*   Updated: 2025/05/22 12:22:50 by jthiew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_symbol(char c)
{
	if (c == '<' || c == '>' || c == '|' || c == '(' || c == ')' || c == '&')
		return (true);
	return (false);
}

char	*get_word(char *start, size_t len)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((len + 1) * sizeof(char));
	if (word == NULL)
		return (NULL);
	while (len > 0)
	{
		word[i] = start[i];
		i++;
		len--;
	}
	word[i] = '\0';
	return (word);
}

size_t	get_word_len_quo(char **str, char quo_type)
{
	size_t	len;
	int		is_quo;

	len = 0;
	is_quo = 1;
	while (**str != '\0' && is_quo == 1)
	{
		(*str)++;
		len++;
		if (**str == quo_type)
		{
			(*str)++;
			len++;
			is_quo = 0;
		}
	}
	return (len);
}

size_t	get_word_len(char **str)
{
	size_t	len;

	len = 0;
	while (**str != '\0' && ft_isspace(**str) != 1
		&& is_symbol(**str) != true)
	{
		if (**str == '\'')
			len += get_word_len_quo(str, '\'');
		else if (**str == '\"')
			len += get_word_len_quo(str, '\"');
		else
		{
			(*str)++;
			len++;
		}
	}
	return (len);
}

char	*token_word(char **str)
{
	char	*start;
	char	*word;
	size_t	len;

	start = *str;
	len = get_word_len(str);
	word = get_word(start, len);
	return (word);
}
