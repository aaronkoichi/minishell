/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlee <zlee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:59:33 by zlee              #+#    #+#             */
/*   Updated: 2025/05/08 20:55:56 by zlee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARD_H
# define WILDCARD_H
# include "libft/libft.h"

typedef struct s_pos
{
	int	x;
	int y;
}	t_pos;

/*Utils*/
void	free_array(char **arr);
int		count_trim_lines(char **arr, const char *filename);

int		ft_fnmatch(const char *pattern, const char *filename);
char	**wildcard(const char *pattern, const char *path);
#endif
