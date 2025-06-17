/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthiew <jthiew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:05:47 by jthiew            #+#    #+#             */
/*   Updated: 2025/06/10 14:19:01 by jthiew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_lstsize_env(t_env *env)
{
	int	size;

	size = 0;
	while (env != NULL)
	{
		size++;
		env = env->next;
	}
	return (size);
}

void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	t_env	*temp;

	temp = *lst;
	if (*lst == NULL)
		*lst = new;
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
}

void	ft_lstclear_env(t_env **env)
{
	t_env	*temp;

	while (*env != NULL)
	{
		temp = (*env)->next;
		free((*env)->key);
		free((*env)->value);
		free(*env);
		*env = temp;
	}
}

char	*get_env_list_value(t_env *env, char *key)
{
	t_env	*temp;
	char	*value;

	temp = env;
	value = NULL;
	while (temp != NULL)
	{
		if (strncmp(temp->key, key, ft_strlen(key) + 1) == 0)
		{
			value = ft_strdup(temp->value);
			if (value == NULL)
				return (NULL);
			break ;
		}
		temp = temp->next;
	}
	return (value);
}
