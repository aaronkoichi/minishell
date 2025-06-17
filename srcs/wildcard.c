/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlee <zlee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:59:27 by zlee              #+#    #+#             */
/*   Updated: 2025/06/18 00:36:55 by zlee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

// Plan --> go through every files using opendir, then use the 
// 			ft_fnmatch function to see if the file matches the output.
char	**combine_new_execve(t_file *files, char **execv)
{
	char	*cmd;
	int		i;
	int		size;
// Next Step: Change this so that it calls exec_main_cmd each time.
	size = ft_lstsize_file(files);
	i = 0;
	cmd = ft_strdup(execv[0]);
	free_arr(execv);
	execv = NULL;
	execv = malloc((size + 2) * sizeof(char *));
	execv[0] = cmd;
	while (++i < size)
	{
		execv[i] = ft_strdup(files->file); 
		files = files->next;
	}
	execv[i] = NULL;
	return (execv);
}

t_file	*mk_new_execve(t_file **files, char *str)
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
			ft_lstaddback_file(files, file->d_name);
		file = readdir(directory);
	}
	closedir(directory);
	return (*files);
}

int detect_wildcard(t_cmd *cmd)
{
	t_file	*new_string;
	int		i;
	int		check;

	new_string = NULL;
	i = 0;
	check = 0;
	while (cmd->argv[++i])
	{
		if (ft_strchr(cmd->argv[i], '*') != NULL)
		{
			check++;
			mk_new_execve(&new_string, cmd->argv[i]);
		}
	}
	if (check == 0)
		return (EXIT_FAILURE);
	cmd->argv = combine_new_execve(new_string, cmd->argv);
	ft_lstclear_file(&new_string, free);
	return (EXIT_SUCCESS);
}
