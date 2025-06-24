/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlee <zlee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 23:11:14 by zlee              #+#    #+#             */
/*   Updated: 2025/06/24 15:14:44 by zlee             ###   ########.fr       */
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
	printf("set_key_value=%s\n", *str);
	if (!before_key)
		return ;
	num = ft_strlen(key) + ft_strlen(before_key) + 1;
	temp = ft_strdup(*str);
	free(*str);
	if (!value)
		*str = ft_strdup(before_key);
	else
		*str = ft_strjoin(before_key, value);
	printf("set_key_value *str=%s\n", *str);
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

static void	key_value_init(t_env *vars, char **str)
{
	char	*key;
	char	*value;

	printf("key_value_init=%s\n", *str);
	key = ft_strcdup(ft_strchr(*str, '$') + 1, '$');
	if (!key)
		key = ft_strdup(ft_strchr(*str, '$') + 1);
	value = NULL;
	while (vars)
	{
		if (!ft_strcmp(key, vars->key))
		{
			value = vars->value;
			break ;
		}
		vars = vars->next;
	}
	set_key_value(str, key, value);
	free(key);
}

t_ast	*detect_env(t_env *vars, t_ast *node)
{
	int		i;
	
	i = 0;
	while (node->cmd->argv[i])
	{
		if (ft_strchr(node->cmd->argv[i], '$') != NULL)
		{
			key_value_init(vars, &node->cmd->argv[i]);
			printf("detect_env=%s\n", node->cmd->argv[i]);
		}
		else
			i++;
	}
	return (node);
}
