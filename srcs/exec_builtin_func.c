/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_func.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlee <zlee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:38:46 by zlee              #+#    #+#             */
/*   Updated: 2025/05/28 18:00:05 by zlee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execute.h"
#include <dirent.h>

static int	exit_func(char **cmd)
{
	printf("exit\n");
	if (cmd[1] != NULL)
		exit(ft_atoi(cmd[1]));
	exit(EXIT_SUCCESS);
}

static int	cd_func(char **cmd, char **envp)
{
	int		i;
	char	*ptr;

	ptr = NULL;
	i = -1;
	if (cmd[1] != NULL)
		ptr = cmd[1];
	else
	{
		while(envp[++i])
			if (!ft_strncmp("HOME=", envp[i], 5))
				break ;
		ptr = &envp[i][5];
	}
	if (opendir(ptr) == NULL)
		perror("cd");
	else
		chdir(ptr);
	return (0);
}

static int	builtin_functions_hlpr(char **cmd, const char *builtin)
{
	if (!ft_strncmp(builtin, cmd[0] + 1, ft_strlen(cmd[0] + 1))
		&& ft_strlen(cmd[0] + 1) == ft_strlen(builtin))
		return (0);
	return (1);
}

int	builtin_functions(char **cmd, char **envp)
{
	if (!builtin_functions_hlpr(cmd, "cd"))
		return (cd_func(cmd, envp));
	else if (!builtin_functions_hlpr(cmd, "exit"))
		return (exit_func(cmd));
	return (1);
}
