/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthiew <jthiew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 14:39:56 by jthiew            #+#    #+#             */
/*   Updated: 2025/06/01 14:41:41 by jthiew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_valid_num(char *str)
{
	if (!(ft_isdigit(*str) == 1 || *str == '-' || *str == '+'))
		return (false);
	str++;
	while (*str != '\0')
	{
		if (ft_isdigit(*str) == 0)
			return (false);
		str++;
	}
	return (true);
}

int	builtin_exit(t_cmd *cmd, t_env **env)
{
	unsigned int	code;

	(void)env;
	if (is_valid_num(cmd->argv[1]) == false)
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(cmd->argv[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(2);
	}
	if (cmd->argc > 2 && is_valid_num(cmd->argv[1]) == true)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (1);
	}
	code = ft_atoi(cmd->argv[1]);
	// cleanup
	exit(code);
}
