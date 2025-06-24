/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlee <zlee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 23:11:14 by zlee              #+#    #+#             */
/*   Updated: 2025/06/24 21:57:43 by zlee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static char	*ft_strcdup(char *str, char letter)
{
	char	*string;
	size_t	len;
	size_t	i;
	
	i = 0;
	if (ft_strchr(str, letter) == NULL)
		return (NULL);
	len = ft_strchr(str, letter) - str;
	string = malloc((len + 1) * sizeof(char));
	while (i < len)
	{
		string[i] = str[i];
		i++;
	}
	string[i] = '\0';
	return (string);
}

static void	set_key_value(char **str, char *key, char *value)
{
	char	*before_key;
	char	*temp;
	size_t	num;
	
	before_key = ft_strcdup(*str, '$');
	if (!before_key)
		return ;
	num = ft_strlen(key) + ft_strlen(before_key) + 1;
	temp = ft_strdup(*str);
	free(*str);
	if (!value)
		*str = ft_strdup(before_key);
	else
		*str = ft_strjoin(before_key, value);
	temp = temp + num;
	free(before_key);
	if (*temp != '\0')
	{
		before_key = ft_strjoin(*str, temp);
		free(*str);
		*str = before_key;
	}
	temp = temp - num;
	free(temp);
}

static void	key_value_init(t_vars *vars, char **str)
{
	char	*key;
	char	*value;
	t_env	*env;

	env = vars->env;
	key = ft_strcdup(ft_strchr(*str, '$') + 1, '$');
	if (!key)
		key = ft_strdup(ft_strchr(*str, '$') + 1);
	value = NULL;
	while (env)
	{
		if (!ft_strcmp(key, "?"))
			value = ft_itoa(vars->exit_code);
		if (!ft_strcmp(key, env->key))
		{
			value = vars->env->value;
			break ;
		}
		env = env->next;
	}
	set_key_value(str, key, value);
	free(key);
}

void	detect_env(t_vars *vars, char **arr)
{
	int		i;
	
	i = 0;
	while (arr[i])
	{
		if (ft_strchr(arr[i], '$') != NULL)
			key_value_init(vars, &arr[i]);
		else
			i++;
	}
}
