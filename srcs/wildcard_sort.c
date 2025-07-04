/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlee <zlee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 13:23:24 by zlee              #+#    #+#             */
/*   Updated: 2025/07/04 13:51:09 by zlee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	ft_strcmp_lower(char *s1, char *s2)
{
	char	*temp;
	char	*temp2;
	int		i;

	if (!s1 || !s2)
		return (-1);
	temp = ft_strdup(s1);
	temp2 = ft_strdup(s2);
	i = -1;
	while (s1[++i])
		temp[i] = ft_tolower(s1[i]);
	i = -1;
	while (s2[++i])
		temp2[i] = ft_tolower(s2[i]);
	i = ft_strcmp(temp, temp2);
	free(temp);
	free(temp2);
	return (i);
}
