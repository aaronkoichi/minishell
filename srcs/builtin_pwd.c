/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthiew <jthiew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 16:16:33 by jthiew            #+#    #+#             */
/*   Updated: 2025/07/02 13:18:43 by zlee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(t_cmd *cmd, t_env **env, t_vars *vars, t_str_dat dat)
{
	char	*cwd;

	(void)cmd;
	(void)env;
	(void)vars;
	(void)dat;
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		perror("getcwd error");
		return (1);
	}
	ft_putstr_fd(cwd, 1);
	free(cwd);
	ft_putstr_fd("\n", 1);
	return (0);
}
