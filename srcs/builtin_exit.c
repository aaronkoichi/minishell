/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthiew <jthiew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 14:39:56 by jthiew            #+#    #+#             */
/*   Updated: 2025/07/02 00:40:27 by zlee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execute.h"

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

static void	close_fd(t_vars *vars)
{
	close(0);
	close(1);
	close(2);
	dup2(vars->ori_stdin, 0);
	dup2(vars->ori_stdout, 1);
	dup2(vars->ori_stderr, 2);
	close(0);
	close(1);
	close(2);
}

int	builtin_exit(t_cmd *cmd, t_env **env, t_vars *vars)
{
	unsigned int	code;

	(void)env;
	ft_putstr_fd("exit\n", 1);
	if (cmd->argc > 2 && is_valid_num(cmd->argv[1]) == true)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (1);
	}
	if (cmd->argc == 1)
		code = 0;
	else if (is_valid_num(cmd->argv[1]) == false)
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(cmd->argv[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		code = 2;
	}
	else
		code = ft_atoi(cmd->argv[1]);
	close_fd(vars);
	ft_lstclear_ast_tree(&vars->ast_tree);
	ft_lstclear_token(&vars->token_list);
	destroy_vars(vars);
	exit(code % 256);
}
