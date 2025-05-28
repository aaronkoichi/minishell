/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_dup_envp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlee <zlee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 18:24:38 by zlee              #+#    #+#             */
/*   Updated: 2025/05/28 20:30:44 by zlee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execute.h"

void	free_envp(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
		free(envp[i]);
	free(envp);
	envp = NULL;
}

char	**dup_envp(char **envp, int	len)
{
	char	**new_envp;
	int		i;

	i = 0;
	new_envp = malloc((len + 1) * sizeof(char *));
	i = -1;
	while (envp[++i])
		new_envp[i] = ft_strdup(envp[i]);
	new_envp[i] = NULL;
	return(new_envp);
}

char **append_envp(char **envp, char *var)
{
	char **new_envp;
	int		len;

	len = 0;
	while (envp[len])
		len++;
	if (ft_strchr(var, '=') == NULL)
		return (NULL);
	new_envp = dup_envp(envp, len + 1);
	free_envp(envp);
	envp = new_envp;
	envp[len] = var;
	envp[len + 1] = NULL;
	return (envp);
}
