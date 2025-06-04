/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthiew <jthiew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 15:35:28 by jthiew            #+#    #+#             */
/*   Updated: 2025/06/04 18:54:09 by zlee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "execute.h"
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

// static int	exit_func(char **cmd)
// {
// 	printf("exit\n");
// 	if (cmd[1] != NULL)
// 		exit(ft_atoi(cmd[1]));
// 	exit(EXIT_SUCCESS);
// }
//
// static int	cd_func(char **cmd, char **envp)
// {
// 	int		i;
// 	char	*ptr;
//
// 	ptr = NULL;
// 	i = -1;
// 	if (cmd[1] != NULL)
// 		ptr = cmd[1];
// 	else
// 	{
// 		while(envp[++i])
// 			if (!ft_strncmp("HOME=", envp[i], 5))
// 				break ;
// 		ptr = &envp[i][5];
// 	}
// 	if (opendir(ptr) == NULL)
// 		perror("cd");
// 	else
// 		chdir(ptr);
// 	return (0);
// }
//
// static int export_func(char **cmd, char **envp)
// {
// 	char	**temp;
//
// 	temp = append_envp(envp, cmd[1]);
// 	if (!temp)
// 		return (1);
// 	else
// 		envp = temp;
// 	// DEBUG
// 	int i = -1;
// 	while (envp[++i])
// 		printf("%s\n", envp[i]);
// 	return (0);
// }

// int env_func(char **envp)
// {
// 	int	i;
//
// 	i = -1;
// 	while (envp[++i])
// 		printf("%s\n", envp[i]);
// 	return (0);
// }

static int	builtin_functions_hlpr(char **cmd, const char *builtin)
{
	if (!ft_strncmp(builtin, cmd[0] + 1, ft_strlen(cmd[0] + 1))
		&& ft_strlen(cmd[0] + 1) == ft_strlen(builtin))
		return (0);
	return (1);
}

// int	builtin_functions(char **cmd, char **envp)
// {
// 	if (!builtin_functions_hlpr(cmd, "cd"))
// 		return (cd_func(cmd, envp));
// 	else if (!builtin_functions_hlpr(cmd, "exit"))
// 		return (exit_func(cmd));
// 	else if (!builtin_functions_hlpr(cmd, "export"))
// 		return (export_func(cmd, envp));
// 	else if (!builtin_functions_hlpr(cmd, "env")
// 		|| !builtin_functions_hlpr(cmd, "usr/bin/env"))
// 		return (env_func(envp));
// 	return (1);
// }

// int	env_func(char **cmd, char **envp)
// {
// 	int	i;
//
// 	(void)cmd;
// 	i = 0;
// 	while (envp[i] != NULL)
// 	{
// 		ft_putstr_fd(envp[i], 1);
// 		i++;
// 	}
// 	return (0);
// }

int	cd_home(t_cmd *cmd, t_env **env)
{
	t_env	*temp;
	t_env	*pwd;
	t_env	*old_pwd;
	t_env	*home;

	temp = *env;
	pwd = NULL;
	old_pwd = NULL;
	home = NULL;
	while (temp != NULL)
	{
		if (strncmp(pwd->key, "PWD", 4) == 0)
			pwd = temp;
		else if (strncmp(old_pwd->key, "OLDPWD", 7) == 0)
			old_pwd = temp;
		else if (strncmp(temp->key, "HOME", 5) == 0)
			home = temp;
		temp = temp->next;
	}
	if (pwd == NULL || pwd->value == NULL)
	{
		ft_putstr_fd("cd: PWD not set\n", 2);
		return (1);
	}
	if (old_pwd == NULL || old_pwd->value == NULL)
	{
		ft_putstr_fd("cd: OLDPWD not set\n", 2);
		return (1);
	}
	if (home == NULL || home->value == NULL)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		return (1);
	}
	if (chdir(home->value) != 0)
	{
		ft_putstr_fd("cd: failed to change directory\n", 2);
		return (1);
	}
	free(old_pwd->value);
	old_pwd->value = pwd->value;
	pwd->value = ft_strdup(home->value);
	if (pwd->value == NULL)
	{
		perror("cd: strdup failed");
		return (1);
	}
	return (0);
}

int	cd_path(t_cmd *cmd, t_env **env)
{
	t_env	*temp;
	t_env	*pwd;
	t_env	*old_pwd;

	temp = *env;
	pwd = NULL;
	old_pwd = NULL;
	while (temp != NULL)
	{
		if (strncmp(pwd->key, "PWD", 4) == 0)
			pwd = temp;
		else if (strncmp(old_pwd->key, "OLDPWD", 7) == 0)
			old_pwd = temp;
		temp = temp->next;
	}
	if (pwd == NULL || pwd->value == NULL)
	{
		ft_putstr_fd("cd: PWD not set\n", 2);
		return (1);
	}
	if (old_pwd == NULL || old_pwd->value == NULL)
	{
		ft_putstr_fd("cd: OLDPWD not set\n", 2);
		return (1);
	}
	if (chdir(cmd->argv[1]) != 0)
	{
		ft_putstr_fd("cd: failed to change directory\n", 2);
		return (1);
	}
	free(old_pwd->value);
	old_pwd->value = pwd->value;
	pwd->value = ft_strdup(cmd->argv[1]);
	if (pwd->value == NULL)
	{
		perror("cd: strdup failed");
		return (1);
	}
	return (0);
}

int	cd_oldpwd(t_cmd *cmd, t_env **env)
{
	t_env	*temp;
	t_env	*pwd;
	t_env	*old_pwd;

	temp = *env;
	pwd = NULL;
	old_pwd = NULL;
	while (temp != NULL)
	{
		if (strncmp(pwd->key, "PWD", 4) == 0)
			pwd = temp;
		else if (strncmp(old_pwd->key, "OLDPWD", 7) == 0)
			old_pwd = temp;
		temp = temp->next;
	}
	if (pwd == NULL || pwd->value == NULL)
	{
		ft_putstr_fd("cd: PWD not set\n", 2);
		return (1);
	}
	if (old_pwd == NULL || old_pwd->value == NULL)
	{
		ft_putstr_fd("cd: OLDPWD not set\n", 2);
		return (1);
	}
	if (chdir(old_pwd->value) != 0)
	{
		ft_putstr_fd("cd: failed to change directory\n", 2);
		return (1);
	}
	temp = old_pwd;
	old_pwd->value = pwd->value;
	pwd->value = temp->value;
	return (0);
}

// return exit code 1 if cd error
int	builtin_cd(t_cmd *cmd, t_env **env)
{
	t_env	*pwd;
	t_env	*old_pwd;
	t_env	*home;

	if (cmd->argc > 2 && ft_strncmp(cmd->argv[1], "--", 3) != 0)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (1);
	}
	if (cmd->argc == 1)
		return (cd_home(cmd, env));
	if (ft_strncmp(cmd->argv[1], ".", 2) == 0)
		return (0);
	if (ft_strncmp(cmd->argv[1], "-", 2) == 0)
		return (cd_oldpwd(cmd, env));
	return (cd_path(cmd, env));
}

typedef int	(*t_builtin_func)(t_cmd *cmd, t_env **env);

typedef struct s_builtin_map
{
	const char		*cmd;
	t_builtin_func	func;
}	t_builtin_map;

const t_builtin_map	*get_builtin_map(void)
{
	static const t_builtin_map	table[] = {
	{"export", builtin_export},
	{"unset", builtin_unset},
	{"echo", builtin_echo},
	{"exit", builtin_exit},
	{"env", builtin_env},
	{"pwd", builtin_pwd},
	{"cd", builtin_cd},
	{NULL, NULL}
	};

	return (table);
}

static const t_builtin_map	*match_builtin(const t_builtin_map *table,
											t_cmd *cmd)
{
	size_t	len;

	while (table->cmd != NULL)
	{
		len = ft_strlen(table->cmd);
		if (ft_strncmp(cmd->argv[0], table->cmd, len + 1) == 0)
			return (table);
		table++;
	}
	return (NULL);
}

int	builtin_functions(t_cmd *cmd, t_env *env)
{
	// TODO: fix export builtin, if key present, just update value, NOT create
	// new key value pair
	const t_builtin_map	*match;

	match = match_builtin(get_builtin_map(), cmd);
	if (match != NULL)
		return (match->func(cmd, &env));
	return (-1);
}
