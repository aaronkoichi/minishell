/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fnmatch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlee <zlee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:03:10 by zlee              #+#    #+#             */
/*   Updated: 2025/05/08 19:54:01 by zlee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

/*
 * Description: See if the pattern and the filename matches the wildcard.
 * 			--> If matches, return 1
 * 			--> If not, return 0
*/ 			
int	ft_fnmatch(const char *pattern, const char *filename)
{
	if (*pattern == '\0' || *filename == '\0')
		return (1);
	else
		if (*pattern != '*')
		{
			if (*pattern == *filename)
				return (ft_fnmatch(++pattern, ++filename));
			else
				return (0);
		}
		else
		{
			pattern++;
			if ((*pattern) != *filename)
				return (ft_fnmatch(--pattern, ++filename));
			else
				return (ft_fnmatch(pattern, filename));
		}
}
