/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthiew <jthiew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 16:16:33 by jthiew            #+#    #+#             */
/*   Updated: 2025/06/24 20:58:50 by zlee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(t_cmd *cmd, t_env **env, t_vars *vars)
{
	char	*cwd;

	(void)cmd;
	(void)env;
	(void)vars;
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		perror("getcwd error");
		return (1);
	}
	ft_putstr_fd(cwd, 1);
	ft_putstr_fd("\n", 1);
	return (0);
}
