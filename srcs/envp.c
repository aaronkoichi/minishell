/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthiew <jthiew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 18:42:32 by jthiew            #+#    #+#             */
/*   Updated: 2025/06/03 16:12:36 by jthiew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//
// #include <stdlib.h>
// #include <stdio.h>
// #include <stddef.h>
//
// size_t	ft_strlen(const char *s)
// {
// 	size_t	i;
//
// 	i = 0;
// 	while (s[i] != '\0')
// 	{
// 		i++;
// 	}
// 	return (i);
// }
//
// void	*ft_memset(void *s, int c, size_t n)
// {
// 	unsigned char	*ptr;
//
// 	ptr = s;
// 	while (n > 0)
// 	{
// 		*ptr = (unsigned char)c;
// 		ptr++;
// 		n--;
// 	}
// 	return (s);
// }
//
// typedef struct s_env
// {
// 	char			*key;
// 	char			*value;
// 	struct s_env	*next;
// }	t_env;

// int	get_env_lines(char **env_list)
// {
// 	int	num_line;
//
// 	num_line = 0;
// 	while (env_list[num_line] != NULL)
// 	{
// 		num_line++;
// 	}
// 	return (num_line);
// }
//
// void	free_env_arr(t_env *env)
// {
// 	int	i;
//
// 	i = 0;
// 	while (env[i].key != NULL)
// 	{
// 		free(env[i].key);
// 		free(env[i].value);
// 		i++;
// 	}
// 	free(env);
// }

// t_env	*get_env_struct(char **env_list)
// {
// 	t_env	*env;
// 	int		num_line;
// 	int		i;
//
// 	num_line = get_env_lines(env_list);
// 	env = malloc((num_line + 1) * sizeof(t_env));
// 	i = 0;
// 	while (i < num_line)
// 	{
// 		ft_memset(&env[i], 0, sizeof(t_env));
// 		env[i].key = get_env_key(*env_list);
// 		env[i].value = get_env_value(*env_list);
// 		if (env[i].key == NULL || env[i].value == NULL)
// 		{
// 			free_env_arr(env);
// 			return (NULL);
// 		}
// 		i++;
// 		env_list++;
// 	}
// 	env[i].key = NULL;
// 	env[i].value = NULL;
// 	return (env);
// }

char	*get_env_key(char **env_line)
{
	int		len;
	int		i;
	char	*key;

	len = 0;
	while ((*env_line)[len] != '\0' && (*env_line)[len] != '=')
		len++;
	key = malloc((len + 1) * sizeof(char));
	if (key == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		key[i] = **env_line;
		i++;
		(*env_line)++;
	}
	if (**env_line != '\0' && **env_line == '=')
		(*env_line)++;
	key[i] = '\0';
	return (key);
}

char	*get_env_value(char *env_line)
{
	int		value_len;
	int		i;
	char	*value;

	if (*env_line == '\0')
		return (NULL);
	value_len = ft_strlen(env_line);
	value = malloc((value_len + 1) * sizeof(char));
	if (value == NULL)
		return (NULL);
	i = 0;
	while (i < value_len)
	{
		value[i] = *env_line;
		i++;
		env_line++;
	}
	value[i] = '\0';
	return (value);
}

t_env	*create_env_node(char *env_line)
{
	t_env	*env;

	env = malloc(1 * sizeof(t_env));
	if (env == NULL)
		return (NULL);
	env->key = get_env_key(&env_line);
	if (env->key == NULL)
	{
		free(env);
		return (NULL);
	}
	if (*env_line == '\0')
	{
		env->value = NULL;
		return (env);
	}
	env->value = get_env_value(env_line);
	if (env->value == NULL)
	{
		free(env->key);
		free(env);
		return (NULL);
	}
	env->next = NULL;
	return (env);
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

t_env	*get_env_list(char **env)
{
	t_env	*head;
	t_env	*node;

	head = NULL;
	while (*env != NULL)
	{
		node = create_env_node(*env);
		if (node == NULL)
		{
			ft_lstclear_env(&head);
			return (NULL);
		}
		ft_lstadd_back_env(&head, node);
		env++;
	}
	return (head);
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

// int	main(int argc, char *argv[], char *envp[])
// {
// 	t_env	*env;
// 	int		i;
//
// 	env = get_env_list(envp);
// 	if (env == NULL)
// 	{
// 		printf("env NULL\n");
// 		return (1);
// 	}
// 	func_do_thing(env);
// 	while (env != NULL)
// 	{
// 		printf("key = [%s]\n", env->key);
// 		printf("value = [%s]\n\n", env->value);
// 		env = env->next;
// 	}
// }
