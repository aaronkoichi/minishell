/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlee <zlee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 23:11:14 by zlee              #+#    #+#             */
/*   Updated: 2025/06/24 00:31:06 by zlee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static char	*ft_strcdup(char *str, char letter)
{
	char	*string;
	size_t	len;
	int		i;
	
	i = -1;
	if (ft_strchr(str, letter) == NULL)
		return (NULL);
	len = ft_strchr(str, letter) - str;
	string = malloc((len + 1) * sizeof(char));
	while (++i < len)
		string[i] = str[i];
	string[i] = 0;
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
	t_env	**head;

	key = ft_strchr(*str, '$');
	value = NULL;
	head = &vars;
	while (vars)
	{
		if (!ft_strncmp(key, vars->key, ft_strlen(vars->key)))
			value = vars->value;
		vars = vars->next;
	}
	set_key_value(str, value);
}

t_cmd	*detect_env(t_env *vars, t_cmd **cmd)
{
	int		i;
	
	i = -1;
	while ((*cmd)->argv[++i])
		if (ft_strchr((*cmd)->argv[i], '$') != NULL)
			key_value_init(vars, &(*cmd)->argv[i]);
	return (*cmd);
}
