/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthiew <jthiew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 19:00:07 by jthiew            #+#    #+#             */
/*   Updated: 2025/06/10 19:00:46 by jthiew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*find_env_node_key(t_env *env, char *key)
{
	t_env	*temp;

	temp = env;
	while (temp != NULL)
	{
		if (strcmp(temp->key, key) == 0)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

int	update_pwd_dirs(t_vars *vars)
{
	char	*new_pwd;
	char	*new_oldpwd;

	new_pwd = getcwd(NULL, 0);
	if (new_pwd == NULL)
	{
		ft_putstr_fd("cd: failed to update vars directory\n", 2);
		return (1);
	}
	new_oldpwd = ft_strdup(vars->pwd_dir);
	if (new_oldpwd == NULL)
	{
		free(new_pwd);
		ft_putstr_fd("cd: failed to update vars directory\n", 2);
		return (1);
	}
	free(vars->pwd_dir);
	free(vars->oldpwd_dir);
	vars->pwd_dir = new_pwd;
	vars->oldpwd_dir = new_oldpwd;
	return (0);
}

int	update_env_value(t_env *node, char *value)
{
	char	*temp;

	temp = ft_strdup(value);
	if (temp == NULL)
		return (1);
	free(node->value);
	node->value = temp;
	return (0);
}
