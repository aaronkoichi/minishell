/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthiew <jthiew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 15:35:28 by jthiew            #+#    #+#             */
/*   Updated: 2025/07/07 09:39:52 by jthiew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	builtin_functions(t_cmd *cmd, t_vars *vars, t_str_dat dat, int *status)
{
	const t_builtin_map	*match;

	match = match_builtin(get_builtin_map(), cmd);
	if (match != NULL)
	{
		*status = match->func(cmd, &vars->env, vars, dat);
		return (*status);
	}
	return (-1);
}
