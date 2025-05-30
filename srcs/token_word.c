/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthiew <jthiew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 12:21:40 by jthiew            #+#    #+#             */
/*   Updated: 2025/05/28 13:42:56 by jthiew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_symbol(char c)
{
	if (c == '<' || c == '>' || c == '|' || c == '(' || c == ')' || c == '&'
		|| c == ';')
		return (true);
	return (false);
}

char	*get_word(char *str, size_t len)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((len + 1) * sizeof(char));
	if (word == NULL)
		return (NULL);
	while (len > 0)
	{
		word[i] = str[i];
		len--;
		i++;
	}
	word[i] = '\0';
	return (word);
}

size_t	get_word_len_quo(char **str, char quo_type, int *is_unclose)
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
	if (is_quo == 1)
		*is_unclose = 1;
	return (len);
}

size_t	get_word_len(char *str, int *is_unclose)
{
	size_t	len;

	len = 0;
	while (*str != '\0' && ft_isspace(*str) == 0
		&& is_symbol(*str) == false)
	{
		if (*str == '\'')
			len += get_word_len_quo(&str, '\'', is_unclose);
		else if (*str == '\"')
			len += get_word_len_quo(&str, '\"', is_unclose);
		else
		{
			str++;
			len++;
		}
	}
	return (len);
}

char	*token_word(char **str)
{
	char	*word;
	size_t	len;
	int		is_unclose;

	is_unclose = 0;
	len = get_word_len(*str, &is_unclose);
	if (is_unclose == 1)
	{
		ft_putstr_fd("Opps, minishell no likey unclosed quotes\n", 2);
		return (NULL);
	}
	word = get_word(*str, len);
	(*str) += len;
	if (word == NULL)
		return (NULL);
	return (word);
}
