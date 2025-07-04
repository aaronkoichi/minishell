/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlee <zlee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:59:27 by zlee              #+#    #+#             */
/*   Updated: 2025/07/05 01:17:45 by zlee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	**detect_wildcard(t_cmd *cmd, char **metadata)
{
	t_file	*new_string;
	int		i;
	char	**new_arr;

	new_string = NULL;
	new_arr = NULL;
	i = -1;
	while (cmd->argv[++i])
	{
		if (ft_strchr(cmd->argv[i], '*') != NULL)
			mk_new_execve(&new_string, cmd->argv[i], metadata[i]);
		else
			ft_lstaddback_file(&new_string, cmd->argv[i]);
	}
	cmd->argc = ft_lstsize_file(new_string);
	new_arr = combine_new_execve(new_string, new_arr);
	ft_lstclear_file(&new_string, free);
	return (new_arr);
}
