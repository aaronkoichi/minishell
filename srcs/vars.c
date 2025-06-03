/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthiew <jthiew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 13:54:15 by jthiew            #+#    #+#             */
/*   Updated: 2025/06/02 14:09:41 by jthiew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	destroy_vars(t_vars *vars)
{
	close(vars->ori_stdin);
	close(vars->ori_stdout);
	close(vars->ori_stderr);
	ft_lstclear_env(&vars->env);
	free(vars->home_dir);
	free(vars->pwd_dir);
	free(vars->oldpwd_dir);
}

static int	get_var_dirs(t_vars *vars)
{
	vars->home_dir = get_env_list_value(vars->env, "HOME");
	if (vars->home_dir == NULL)
		return (1);
	vars->pwd_dir = get_env_list_value(vars->env, "PWD");
	if (vars->pwd_dir == NULL)
	{
		free(vars->home_dir);
		return (1);
	}
	vars->oldpwd_dir = get_env_list_value(vars->env, "OLDPWD");
	if (vars->oldpwd_dir == NULL)
	{
		free(vars->home_dir);
		free(vars->pwd_dir);
		return (1);
	}
	return (0);
}

void	init_vars(t_vars *vars, char **envp)
{
	vars->token_list = NULL;
	vars->ast_tree = NULL;
	vars->exit_code = 0;
	vars->ori_stdin = dup(STDIN_FILENO);
	vars->ori_stdout = dup(STDOUT_FILENO);
	vars->ori_stderr = dup(STDERR_FILENO);
	vars->env = get_env_list(envp);
	if (vars->env == NULL)
	{
		close(vars->ori_stdin);
		close(vars->ori_stdout);
		close(vars->ori_stderr);
		exit (1);
	}
	if (get_var_dirs(vars) == 1)
	{
		close(vars->ori_stdin);
		close(vars->ori_stdout);
		close(vars->ori_stderr);
		ft_lstclear_env(&vars->env);
		exit (1);
	}
}
