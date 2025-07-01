/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlee <zlee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:23:40 by zlee              #+#    #+#             */
/*   Updated: 2025/07/02 00:29:49 by zlee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "minishell.h"

static char	**find_full_cmd(char **path, char **cmd_arr)
{
	char	*new_path;
	int		i;

	i = -1;
	while (path[++i])
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

static char	**prep_envp_cmd(char **cmd_arr, t_vars *vars)
{
	char	**path;
	char	*temp;
	t_env	**temp_env;

	temp = NULL;
	temp_env = &vars->env;
	while (*temp_env)
	{
		if (ft_strncmp((*temp_env)->key, "PATH", 4) == 0)
			break ;
		temp_env = &(*temp_env)->next;
	}
	path = ft_split((*temp_env)->value, ':');
	temp = ft_strjoin("/", cmd_arr[0]);
	free(cmd_arr[0]);
	cmd_arr[0] = temp;
	return (find_full_cmd(path, cmd_arr));
}

static char	**init_cmd_exec(int ac, char **av)
{
	char	**cmd;
	int		i;

	i = 0;
	cmd = malloc((ac + 1) * sizeof(char *));
	if (!cmd)
		return (NULL);
	while ((ac - i) != 0)
	{
		cmd[i] = ft_strdup(av[i]);
		i++;
	}
	cmd[i] = NULL;
	return (cmd);
}

char	**prep_cmd(t_cmd *cmd, t_vars *vars)
{
	char	**cmd_arr;

	cmd_arr = init_cmd_exec(cmd->argc, cmd->argv);
	if (!cmd)
		return (NULL);
	if (access(cmd_arr[0], X_OK | F_OK) == 0)
		return (cmd_arr);
	else
		cmd_arr = prep_envp_cmd(cmd_arr, vars);
	return (cmd_arr);
}
