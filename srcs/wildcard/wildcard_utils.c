/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlee <zlee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 20:34:53 by zlee              #+#    #+#             */
/*   Updated: 2025/05/08 21:08:42 by zlee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while(arr[i])
	{
		free(arr[i++]);
	}
	free(arr[i]);
	free(arr);
}

int	count_trim_lines(char **arr, const char *filename)
{
	int	c;
	int	i;

	c = 0;
	i = 0;
	if (filename[0] == '*')
		c++;
	while(arr[i])
		c += ft_strlen(arr[i++]) + 1;
	if (filename[ft_strlen(filename) - 1] != '*')
		c--;
	return (c);
}

