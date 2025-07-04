/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_mk_new_exev.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlee <zlee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 17:33:56 by zlee              #+#    #+#             */
/*   Updated: 2025/07/05 01:15:30 by zlee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	char	**arr;
	char	**sorted;

	arr = create_arr_from_t_file(unsorted);
	if (!arr)
		return (NULL);
	sorted = qsort_main(arr);
	free_arr(arr);
	return (sorted);
}

static void	readdir_three_times(DIR *directory, struct dirent **file)
{
	*file = readdir(directory);
	*file = readdir(directory);
	*file = readdir(directory);
}

static char	**create_fnmatch(char *str, char *metadata)
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
		if (ft_fnmatch(str, file->d_name, metadata) && file->d_name[0] != '.')
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
