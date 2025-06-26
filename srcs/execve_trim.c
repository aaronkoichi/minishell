/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_trim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlee <zlee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:48:42 by zlee              #+#    #+#             */
/*   Updated: 2025/06/26 17:53:10 by zlee             ###   ########.fr       */
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
			if (arr[i] == hold_char)
				hold_char = -1;
			else
				count++;
		else
			if (arr[i] == 34 || arr[i] == 39)
				hold_char = arr[i];
			else
				count++;
	}
	return (count);
}

static void	alloc_words_without_quotes(char **string, char *original)
{
	int	i;
	int	j;
	int	hold_char;

	i = -1;
	j = -1;
	hold_char = -1;
	while (original[++i])
	{
		if (hold_char != -1)
			if (original[i] == hold_char)
				hold_char = -1;
			else
				(*string)[++j] = original[i];
		else
			if (original[i] == 34 || original[i] == 39)
				hold_char = original[i];
			else
				(*string)[++j] = original[i];
	}
	(*string)[++j] = '\0';
}

char	**trim_execve(char **arr)
{
	size_t	size;
	int		i;
	char	*temp;

	i = 0;
	size = 0;
	temp = NULL;
	while (arr[i])
	{
		size = count_without_quotes(arr[i]);
		temp = malloc((size + 1) * sizeof(char));
		alloc_words_without_quotes(&temp, arr[i]);
		free(arr[i]);
		arr[i] = temp;
		i++;
	}
	return (arr);
}
