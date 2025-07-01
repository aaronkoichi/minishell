/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_environ_trim.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlee <zlee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 20:09:08 by zlee              #+#    #+#             */
/*   Updated: 2025/07/01 23:34:07 by zlee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

char	*move_char_wild(char *arr)
{
	char	*charac;

	charac = NULL;
	if (ft_strchr(arr, '\''))
		return (move_char(arr));
	else
	{
		charac = ft_strchr(arr, '\"');
		if (charac)
			arr = charac + 1;
		charac = ft_strchr(arr, '\"');
		if (charac)
			arr = charac + 1;
		return (arr);
	}
}

char	*move_char(char *arr)
{
	char	*charac;

	charac = ft_strchr(arr, '\'');
	if (charac)
		arr = charac + 1;
	charac = ft_strchr(arr, '\'');
	if (charac)
		arr = charac + 1;
	return (arr);
}
