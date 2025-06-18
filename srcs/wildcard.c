/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlee <zlee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:59:27 by zlee              #+#    #+#             */
/*   Updated: 2025/06/18 17:56:16 by zlee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include <dirent.h>

// Plan --> go through every files using opendir, then use the 
// 			ft_fnmatch function to see if the file matches the output.
void	combine_new_execve(t_file *files, t_cmd *cmd)
{
	int		i;
	int		size;

	size = ft_lstsize_file(files);
	i = -1;
	free_arr(cmd->argv);
	cmd->argv = NULL;
	cmd->argv = malloc((size + 1) * sizeof(char *));
	while (++i < size)
	{
		cmd->argv[i] = ft_strdup(files->file); 
		files = files->next;
	}
	cmd->argv[i] = NULL;
}

int detect_wildcard(t_cmd *cmd)
{
	t_file	*new_string;
	int		i;

	new_string = NULL;
	i = -1;
	while (cmd->argv[++i])
	{
		if (ft_strchr(cmd->argv[i], '*') != NULL)
			mk_new_execve(&new_string, cmd->argv[i]);
		else
			ft_lstaddback_file(&new_string, cmd->argv[i]);
	}
	cmd->argc = ft_lstsize_file(new_string);
	combine_new_execve(new_string, cmd);
	ft_lstclear_file(&new_string, free);
	return (EXIT_SUCCESS);
}
