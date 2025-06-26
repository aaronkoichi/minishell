/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlee <zlee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:41:04 by zlee              #+#    #+#             */
/*   Updated: 2025/06/26 16:58:27 by zlee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

/* Finds where the string should end.
 * Continue if is_alnum is true. or "_" is true.
 * return NULL if not found. Which is good.
 * */
char	find_sym_env(char *string)
{
	char	*temp;

	temp = string;
	while (ft_isalnum(*temp) || *temp == '_')
		temp++;
	return (*temp);
}

char	**ft_strdup_arr(char **arr)
{
	char	**duped;
	int		i;

	i = 0;
	duped = NULL;
	if (!arr || !*arr)
		return (NULL);
	while (arr[i])
		i++;
	duped = malloc(sizeof(char *) * (i + 1));
	if (!duped)
		return (NULL);
	i = -1;
	while (arr[++i])
		duped[i] = ft_strdup(arr[i]);
	duped[i] = NULL;
	return (duped);
}
