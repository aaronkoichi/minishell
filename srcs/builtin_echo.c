/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthiew <jthiew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 18:47:07 by jthiew            #+#    #+#             */
/*   Updated: 2025/07/02 12:39:18 by zlee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	echo_print(t_cmd *cmd, int i)
{
	while (cmd->argv[i] != NULL)
	{
		ft_putstr_fd(cmd->argv[i], 1);
		if (cmd->argv[i + 1] != NULL)
			ft_putstr_fd(" ", 1);
		i++;
	}
}

int	builtin_echo(t_cmd *cmd, t_env **env, t_vars *vars, t_str_dat dat)
{
	int	i;

	(void)vars;
	(void)env;
	(void)dat;
	i = 1;
	if (ft_strncmp(cmd->argv[i], "-n", 3) == 0)
		echo_print(cmd, i + 1);
	else
	{
		echo_print(cmd, i);
		ft_putstr_fd("\n", 1);
	}
	return (0);
}
