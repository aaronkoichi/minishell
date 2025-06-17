/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthiew <jthiew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:09:16 by jthiew            #+#    #+#             */
/*   Updated: 2025/06/10 14:09:29 by jthiew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_key(char *env_line, int *i)
{
	int		len;
	int		j;
	char	*key;

	len = 0;
	while (env_line[len] != '\0' && env_line[len] != '=')
		len++;
	key = malloc((len + 1) * sizeof(char));
	if (key == NULL)
		return (NULL);
	j = 0;
	while (j < len)
	{
		key[j] = env_line[*i];
		j++;
		(*i)++;
	}
	key[j] = '\0';
	return (key);
}

char	*get_env_value(char *env_line)
{
	int		value_len;
	int		j;
	char	*value;

	if (*env_line != '\0' && *env_line == '=')
		env_line++;
	value_len = ft_strlen(env_line);
	value = malloc((value_len + 1) * sizeof(char));
	if (value == NULL)
		return (NULL);
	j = 0;
	while (j < value_len)
	{
		value[j] = *env_line;
		j++;
		env_line++;
	}
	value[j] = '\0';
	return (value);
}

t_env	*create_env_node(char *env_line, int ind)
{
	t_env	*env;
	int		i;

	i = 0;
	env = malloc(1 * sizeof(t_env));
	if (env == NULL)
		return (NULL);
	ft_memset(env, 0, sizeof(t_env));
	env->ind = ind;
	env->key = get_env_key(env_line, &i);
	if (env->key == NULL)
	{
		free(env);
		return (NULL);
	}
	if (env_line[i] == '\0')
		return (env);
	env->value = get_env_value(env_line + i);
	if (env->value == NULL)
	{
		free(env->key);
		free(env);
		return (NULL);
	}
	return (env);
}

t_env	*get_env_list(char **env)
{
	t_env	*head;
	t_env	*node;
	int		ind;

	head = NULL;
	ind = 0;
	while (*env != NULL)
	{
		node = create_env_node(*env, ind);
		if (node == NULL)
		{
			ft_lstclear_env(&head);
			return (NULL);
		}
		ft_lstadd_back_env(&head, node);
		ind++;
		env++;
	}
	return (head);
}
