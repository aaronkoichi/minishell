/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlee <zlee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:23:40 by zlee              #+#    #+#             */
/*   Updated: 2025/05/14 21:02:38 by zlee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "../libft/libft.h"

static char	**find_full_cmd(char **path, char **cmd_arr, char **envp)
{
	char	*new_path;
	int		i;
	int		pid;

	i = -1;
	while(path[++i])
	{
		new_path = ft_strjoin(path[i], cmd_arr[0]);
		if (access(new_path, F_OK | X_OK) == 0)
		{
			free(cmd_arr[0]);
			cmd_arr[0] = new_path;
			free_arr(path);
			return (cmd_arr);
		}
		else
		{
			free(new_path);
			new_path = NULL;
		}
	}
	free_arr(path);
	return (cmd_arr);
}

static char	**prep_envp_cmd(char **cmd_arr, char **envp)
{
	char	**path;
	int		i;
	char	*temp;

	i = -1;
	temp = NULL;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
	}
	path = ft_split(envp[i] + 5, ':');
	i = -1;
	temp = ft_strjoin("/", cmd_arr[0]);
	free(cmd_arr[0]);
	cmd_arr[0] = temp;
	return (find_full_cmd(path, cmd_arr, envp));
}

static char	**init_cmd(int ac, char **av)
{
	char	**cmd;
	int		i;

	i = 0;
	cmd = malloc((ac) * sizeof(char *));
	if (!cmd)
		return (NULL);
	while ((ac - 1 - i) != 0)
	{
		cmd[i] = ft_strdup(av[i + 1]);
		i++;
	}
	cmd[i] = NULL;
	return (cmd);
}

char	**prep_cmd(t_cmd *cmd, char **envp)
{
	char **cmd_arr;

	cmd_arr = init_cmd(cmd->argc, cmd->argv);
	if (!cmd)
		return (NULL);
	if (access(cmd_arr[0], X_OK | F_OK) == 0)
		return(cmd_arr);
	else
		cmd_arr = prep_envp_cmd(cmd_arr, envp);
	return (cmd_arr);
}
