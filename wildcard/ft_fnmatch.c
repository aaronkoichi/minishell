/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fnmatch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlee <zlee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:03:10 by zlee              #+#    #+#             */
/*   Updated: 2025/05/08 17:59:07 by zlee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

/*
 * For example --> Word*second => Word
 * 			   --> second => second
 * */
char *trim_word_before_asterisk(const char *pattern)
{
	int	i;
	int	c;
	char *temp;

	i = -1;
	while (pattern[++i] != '*' && pattern[i] != '\0')
		c++;
	temp = malloc((c + 1) * sizeof(char));	
	temp[c] = '\0';
	while (--c >= 0)
		temp[c] = pattern[c];
	return (temp);
}

/*
 * Description: See if the pattern and the filename matches the wildcard.
 * 			--> If matches, return 1
 * 			--> If not, return 0
 * */
/*Plan --> maybe use iteration?
 * */
int	ft_fnmatch(const char *pattern, const char *filename)
{
	int		c_p;
	int		c_f;
	char	*temp;
	char 	*trim;
	int		checker;
	
	c_p = 0;
	c_f = 0;
	temp = NULL;
	trim = NULL;
	while (filename[c_f] != '\0')
	{
		checker = 0;
		if (pattern[c_p] == '*' &&
	  		filename[c_f] != pattern[c_p + 1])
		{
			c_f++;
			continue ;
		}
		else if (filename[c_f] == pattern[c_p + 1])
		{
			trim = trim_word_before_asterisk(&pattern[c_p + 1]);
			temp = ft_strnstr(&filename[c_f], trim, ft_strlen(&filename[c_f]));
			if (temp == NULL)
			{
				c_f++;
				free(trim);
				continue ;
			}
			c_f += ft_strlen(trim) - 1;
			c_p += ft_strlen(trim) - 1;
			free(trim);
			checker = 1;
		}
		else if (filename[c_f] == pattern[c_p])
		{
			c_f++;
			c_p++;
			checker = 1;
		}
		else
			break ;
	}
	return (checker);
}
