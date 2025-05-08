/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fnmatch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlee <zlee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:03:10 by zlee              #+#    #+#             */
/*   Updated: 2025/05/08 23:00:10 by zlee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

/*
 * Description: See if the pattern and the filename matches the wildcard.
 * 			--> If matches, return 1
 * 			--> If not, return 0
*/ 			
static int	fn_match_helper(const char *pattern, const char *filename)
{
	if (*pattern == '\0' && *filename == '\0')
		return (1);
	else if (*pattern == '\0' && *filename != '\0')
		return (0);
	else if (*pattern == '*' && *(++pattern) == '\0')
		return (1);
	--pattern;
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
		if (!fn_match_helper(pattern, filename))
			return (fn_match_helper(--pattern, ++filename));
		else
			return (1);
	}
}

static void	alloc_with_asterisks(char **string_join, const char *pattern, int characters, char **arr)
{
	t_pos	pos;
	int		i;

	i = 0;
	pos.y = -1;
	if (pattern[0] == '*')
		(*string_join)[i++] = '*';
	while(arr[++pos.y])
	{
		pos.x = -1;
		while (arr[pos.y][++pos.x])
			(*string_join)[i++] = arr[pos.y][pos.x];
		(*string_join)[i++] = '*';
	}
	if (pattern[ft_strlen(pattern) - 1] == '*')
		(*string_join)[i] = '\0';
	else
		(*string_join)[--i] = '\0';
}

/*
 * Make multiple asterisks into one
 * For example: He***or**ld => He*or*ld
 * */
char	*trim_pattern(const char *pattern)
{
	char	**removed_asterisks;
	char	*string_join;
	int		characters;
	t_pos	pos;
	int		i;

	pos.y = -1;
	i = 0;
	removed_asterisks = ft_split(pattern, '*');
	characters = count_trim_lines(removed_asterisks, pattern);
	string_join = malloc((characters + 1) * sizeof(char));
	if (!string_join)
		return (NULL);
	alloc_with_asterisks(&string_join, pattern, characters, removed_asterisks);
	free_array(removed_asterisks);
	if (!string_join)
		return (0);
	return (string_join);
}

int	ft_fnmatch(const char *pattern, const char *filename)
{
	int		checker;
	char	*trimmed_pattern;

	trimmed_pattern = trim_pattern(pattern);
	checker = fn_match_helper(trimmed_pattern, filename);
	free(trimmed_pattern);
	return (checker);
}
//
// int main(void)
// {
// 	char *pattern = "**food*cook***test";
// 	char *p2 = trim_pattern(pattern);
// 	ft_printf("%s\n", p2);
// 	free(p2);
// }
