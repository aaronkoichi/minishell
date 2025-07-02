/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthiew <jthiew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:05:06 by jthiew            #+#    #+#             */
/*   Updated: 2025/07/02 12:38:48 by zlee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	unset_del_env_node(char *str, t_env **env)
{
	t_env	*prev;
	t_env	*curr;
	t_env	*temp;

	prev = NULL;
	curr = *env;
	while (curr != NULL)
	{
		if (strncmp(curr->key, str, ft_strlen(str) + 1) == 0)
		{
			temp = curr;
			if (prev == NULL)
				*env = curr->next;
			else
				prev->next = curr->next;
			curr = curr->next;
			free(temp->key);
			free(temp->value);
			free(temp);
			break ;
		}
		prev = curr;
		curr = curr->next;
	}
}

int	builtin_unset(t_cmd *cmd, t_env **env, t_vars *vars, t_str_dat dat)
{
	int		i;

	(void)vars;
	(void)dat;
	i = 1;
	while (cmd->argv[i] != NULL)
	{
		unset_del_env_node(cmd->argv[i], env);
		i++;
	}
	return (0);
}
