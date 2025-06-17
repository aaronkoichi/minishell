/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlee <zlee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:59:27 by zlee              #+#    #+#             */
/*   Updated: 2025/06/17 20:07:02 by zlee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

// Plan --> go through every files using opendir, then use the 
// 			ft_fnmatch function to see if the file matches the output.
//

t_file	*mk_new_execve(t_file *files, char *str)
{
	DIR				*directory;
	struct dirent	*file;

	directory = opendir(".");
	file = readdir(directory);
	file = readdir(directory);
	file = readdir(directory);
	while (file)
	{
		if (ft_fnmatch(str, file->d_name))
			ft_lstaddback_file(&files, file->d_name);
		file = readdir(directory);
	}
	closedir(directory);
	return (files);
}

int detect_wildcard(char **execv)
{
	char	**head;
	t_file	*new_string;
	int		i;

	new_string = NULL;
	head = execv;
	i = 0;
	while (head[++i])
	{
		if (ft_strchr(head[i], '*') != NULL)
			mk_new_execve(new_string, head[i]);
	}
	// Next step: combine into proper execve.
	return (EXIT_SUCCESS);
}
