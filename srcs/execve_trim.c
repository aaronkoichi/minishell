/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_trim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlee <zlee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:48:42 by zlee              #+#    #+#             */
/*   Updated: 2025/07/02 00:29:02 by zlee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static size_t	count_without_quotes(char *arr)
{
	int		hold_char;
	int		i;
	size_t	count;

	hold_char = -1;
	count = 0;
	i = -1;
	while (arr[++i])
	{
		if (hold_char != -1)
		{
			if (arr[i] == hold_char)
				hold_char = -1;
			else
				count++;
		}
		else
		{
			if (arr[i] == 34 || arr[i] == 39)
				hold_char = arr[i];
			else
				count++;
		}
	}
	return (count);
}

static void	increment_quoted(char **string, char original,
				char **data, int *j)
{
	(*data)[++(*j)] = 'Q';
	(*string)[*j] = original;
}

static void	increment_unquoted(char **string, char original,
				char **data, int *j)
{
	(*data)[++(*j)] = 'U';
	(*string)[*j] = original;
}

static void	alloc_words_without_quotes(char **string, char *original,
			char **data)
{
	t_pos	num;
	int		hold_char;

	num.x = -1;
	num.y = -1;
	hold_char = -1;
	while (original[++num.x])
	{
		if (hold_char != -1)
		{
			if (original[num.x] == hold_char)
				hold_char = -1;
			else
				increment_quoted(string, original[num.x], data, &(num.y));
		}
		else
		{
			if (original[num.x] == 34 || original[num.x] == 39)
				hold_char = original[num.x];
			else
				increment_unquoted(string, original[num.x], data, &(num.y));
		}
	}
	(*string)[++num.y] = '\0';
	(*data)[num.y] = '\0';
}

char	**trim_execve(t_cmd *cmd)
{
	size_t	size;
	int		i;
	char	*temp;
	char	**data;

	i = 0;
	size = 0;
	temp = NULL;
	while (cmd->argv[i])
		i++;
	data = malloc((i + 1) * sizeof(char *));
	i = 0;
	while (cmd->argv[i])
	{
		size = count_without_quotes(cmd->argv[i]);
		temp = malloc((size + 1) * sizeof(char));
		data[i] = malloc((size + 1) * sizeof(char));
		alloc_words_without_quotes(&temp, cmd->argv[i], &data[i]);
		free(cmd->argv[i]);
		cmd->argv[i] = temp;
		i++;
	}
	data[i] = 0;
	return (data);
}
