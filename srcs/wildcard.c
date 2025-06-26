/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlee <zlee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:59:27 by zlee              #+#    #+#             */
/*   Updated: 2025/06/26 20:33:24 by zlee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

// Plan --> go through every files using opendir, then use the 
// 			ft_fnmatch function to see if the file matches the output.
static char	**combine_new_execve(t_file *files, char **cmd)
{
	int		i;
	int		size;

	size = ft_lstsize_file(files);
	i = -1;
	cmd = malloc((size + 1) * sizeof(char *));
	while (++i < size)
	{
		cmd[i] = ft_strdup(files->file); 
		files = files->next;
	}
	cmd[i] = NULL;
	return (cmd);
}

char	**detect_wildcard(t_cmd *cmd)
{
	t_file	*new_string;
	int		i;
	char	**new_arr;
	char	*temp;

	new_string = NULL;
	new_arr = NULL;
	i = -1;
	temp = cmd->argv[++i];
	while (temp)
	{
		if (ft_strchr(temp, 39) || ft_strchr(temp, 34))
		{
			temp = move_char_wild(temp);
			continue ;
		}
		if (ft_strchr(temp, '*') != NULL)
		{
			temp = cmd->argv[i];
			mk_new_execve(&new_string, temp);
		}
		else
		{	
			temp = cmd->argv[i];
			ft_lstaddback_file(&new_string, temp);
			temp = cmd->argv[++i];
		}
	}
	cmd->argc = ft_lstsize_file(new_string);
	free_arr(cmd->argv);
	new_arr = combine_new_execve(new_string, new_arr);
	ft_lstclear_file(&new_string, free);
	return (new_arr);
}
