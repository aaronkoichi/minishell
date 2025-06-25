/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_trim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlee <zlee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 20:09:08 by zlee              #+#    #+#             */
/*   Updated: 2025/06/25 20:58:08 by zlee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"


/* Remove all of the unecessary quotes, and backslashes
 * echo "hi""hi" = echo hihi
 * echo \bye = echo bye
 * echo "\bye" = bye
 * My understanding is, \ after another character will be preserved.
*/
// char	**trim_execve(char **arr)
// {
// 	return (NULL);
// }

/*
 * Move a string into another quote.
 * Example: <"nice"cool> will be moved to <cool>.
 * */
char *move_char(char *arr)
{
	char *charac;

	charac = ft_strchr(arr, 39);
	if (charac)
		arr = charac + 1;
	charac = ft_strchr(arr, 39);
	if (charac)
		arr = charac + 1;
	return (arr);
}
