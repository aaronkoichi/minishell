/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthiew <jthiew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 18:58:16 by jthiew            #+#    #+#             */
/*   Updated: 2025/06/10 19:00:49 by jthiew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_home(t_env **env, t_vars *vars)
{
	t_env	*home;
	t_env	*pwd;
	t_env	*oldpwd;

	home = find_env_node_key(*env, "HOME");
	if (home == NULL)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		return (1);
	}
	if (chdir(home->value) != 0)
	{
		ft_putstr_fd("cd: failed to change directory\n", 2);
		return (1);
	}
	if (update_pwd_dirs(vars) == 1)
		return (1);
	oldpwd = find_env_node_key(*env, "OLDPWD");
	if (oldpwd != NULL && update_env_value(oldpwd, vars->oldpwd_dir) == 1)
		return (1);
	pwd = find_env_node_key(*env, "PWD");
	if (pwd != NULL && update_env_value(pwd, vars->pwd_dir) == 1)
		return (1);
	return (0);
}

int	cd_oldpwd(t_env **env, t_vars *vars)
{
	t_env	*pwd;
	t_env	*oldpwd;

	oldpwd = find_env_node_key(*env, "OLDPWD");
	if (oldpwd == NULL || oldpwd->value == NULL)
	{
		ft_putstr_fd("cd: OLDPWD not set\n", 2);
		return (1);
	}
	if (chdir(oldpwd->value) != 0)
	{
		ft_putstr_fd("cd: failed to change directory\n", 2);
		return (1);
	}
	if (update_pwd_dirs(vars) == 1)
		return (1);
	oldpwd = find_env_node_key(*env, "OLDPWD");
	if (oldpwd != NULL && update_env_value(oldpwd, vars->oldpwd_dir) == 1)
		return (1);
	pwd = find_env_node_key(*env, "PWD");
	if (pwd != NULL && update_env_value(pwd, vars->pwd_dir) == 1)
		return (1);
	return (0);
}

int	cd_path(t_cmd *cmd, t_env **env, t_vars *vars)
{
	t_env	*pwd;
	t_env	*oldpwd;

	if (chdir(cmd->argv[1]) != 0)
	{
		ft_putstr_fd("cd: failed to change directory\n", 2);
		return (1);
	}
	if (update_pwd_dirs(vars) == 1)
		return (1);
	oldpwd = find_env_node_key(*env, "OLDPWD");
	if (oldpwd != NULL && update_env_value(oldpwd, vars->oldpwd_dir) == 1)
		return (1);
	pwd = find_env_node_key(*env, "PWD");
	if (pwd != NULL && update_env_value(pwd, vars->pwd_dir) == 1)
		return (1);
	return (0);
}

int	builtin_cd(t_cmd *cmd, t_env **env, t_vars *vars)
{
	(void)env;
	if (cmd->argc > 2)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (1);
	}
	if (cmd->argc == 1)
		return (cd_home(env, vars));
	if (ft_strncmp(cmd->argv[1], ".", 2) == 0)
		return (0);
	if (ft_strncmp(cmd->argv[1], "-", 2) == 0)
		return (cd_oldpwd(env, vars));
	return (cd_path(cmd, env, vars));
}
