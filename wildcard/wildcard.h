/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlee <zlee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:59:33 by zlee              #+#    #+#             */
/*   Updated: 2025/05/08 16:14:25 by zlee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARD_H
# define WILDCARD_H
# include "libft/libft.h"

int		ft_fnmatch(const char *pattern, const char *filename);
char	**wildcard(const char *pattern, const char *path);
#endif
