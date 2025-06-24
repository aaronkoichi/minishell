/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlee <zlee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 23:11:14 by zlee              #+#    #+#             */
/*   Updated: 2025/06/24 12:25:14 by zlee             ###   ########.fr       */
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

static void	set_key_value(char **str, char *value)
{
	char	*temp;
	
	temp = ft_strcdup(*str, '$');
	if (!temp)
		return ;
	free(*str);
	*str = NULL;
	if (!value)
		*str = ft_strdup(temp);
	else
		*str = ft_strjoin(temp, value);
	free(temp);
}

static void	key_value_init(t_env *vars, char **str)
{
	char	*key;
	char	*value;

	key = ft_strchr(*str, '$');
	value = NULL;
	while (vars)
	{
		if (!ft_strcmp(key, vars->key))
			value = vars->value;
		vars = vars->next;
	}
	set_key_value(str, value);
}

t_ast	*detect_env(t_env *vars, t_ast **cmd)
{
	int		i;
	
	i = 0;
	while ((*cmd)->cmd->argv[i])
	{
		if (!ft_strchr((*cmd)->cmd->argv[i], '$'))
		{
			key_value_init(vars, &(*cmd)->cmd->argv[i]);
			continue ;
		}
		i++;
	}
	return (*cmd);
}
