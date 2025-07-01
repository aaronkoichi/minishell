/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_mk_new_exev.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlee <zlee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 17:33:56 by zlee              #+#    #+#             */
/*   Updated: 2025/07/01 19:33:12 by zlee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include <stddef.h>

static char	**create_arr_from_t_file(t_file *file)
{
	char	**arr;
	int		i;

	i = -1;
	arr = malloc((ft_lstsize_file(file) + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	while (file)
	{
		arr[++i] = ft_strdup(file->file);
		file = file->next;
	}
	arr[++i] = NULL;
	return (arr);
}

static char	**sort_readdir_helper(t_file *unsorted)
{
	char	*temp;
	char	**sorted;
	int		i;

	temp = NULL;
	i = -1;
	sorted = create_arr_from_t_file(unsorted);
	if (!sorted)
		return (NULL);
	while (sorted[++i + 1])
	{
		if (ft_strcmp(sorted[i], sorted[i + 1]) > 0)
		{
			temp = sorted[i];
			sorted[i] = sorted[i + 1];
			sorted[i + 1] = temp;
			i = -1;
		}
	}
	return (sorted);
}

static void	readdir_three_times(DIR *directory, struct dirent **file)
{
	*file = readdir(directory);
	*file = readdir(directory);
	*file = readdir(directory);
}

static char **create_fnmatch(char *str, char *metadata)
{
	DIR				*directory;
	struct dirent	*file;
	t_file			*tmp;
	char			**sorted;
	size_t			count;
	
	count = 0;
	directory = opendir(".");
	tmp = NULL;
	readdir_three_times(directory, &file);
	while (file)
	{
		if (ft_fnmatch(str, file->d_name, metadata))
		{
			ft_lstaddback_file(&tmp, file->d_name);
			count++;
		}
		file = readdir(directory);
	}
	closedir(directory);
	if (count == 0)
		ft_lstaddback_file(&tmp, str);
	sorted = sort_readdir_helper(tmp);
	ft_lstclear_file(&tmp, free);
	return (sorted);
}

t_file	*mk_new_execve(t_file **files, char *str, char *metadata)
{
	char	**append;
	int		i;

	i = -1;
	append = create_fnmatch(str, metadata);
	while (append[++i])
		ft_lstaddback_file(files, append[i]);
	free_arr(append);
	return (*files);
}
