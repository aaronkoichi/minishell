/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlee <zlee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 23:11:14 by zlee              #+#    #+#             */
/*   Updated: 2025/06/26 22:00:59 by zlee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include <term.h>

static char	*ft_strcdup(char *str, char letter)
{
	char	*string;
	size_t	len;
	size_t	i;

	i = 0;
	if (letter == '\0')
		len = ft_strlen(str);
	else
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
	char	*char_location;

	env = vars->env;
	char_location = ft_strchr(*str, '$') + 1;
	key = ft_strcdup(ft_strchr(*str, '$') + 1, find_sym_env(char_location));
	value = NULL;
	while (env)
	{
		if (!ft_strcmp(key, "?"))
		{
			value = ft_itoa(vars->exit_code);
			break ;
		}
		else if (!ft_strcmp(key, env->key))
			value = env->value;
		env = env->next;
	}
	set_key_value(str, key, value);
	if (!ft_strcmp(key, "?"))
		free(value);
	free(key);
}

/* TODO: Fix how to implement:
*		- Make a function to traverse the sentance charac by charac.
*		- if encounter \' just move to the next \'
*		- but if encounter \" see inside got $, if got $, process it until the next \".
*/
char	**detect_env(t_vars *vars, char **arr)
{
	int		i;
	char	*head;
	char	**duped;

	i = 0;
	duped = ft_strdup_arr(arr);
	head = duped[i];
	while (duped[i])
	{
		if (ft_strchr(head, '\"') != NULL)
			if (ft_strchr(head, '$') != NULL)
				key_value_init(vars, &duped[i]);
		if (ft_strchr(head, '\'') != NULL)
		{
			head = move_char(head);
			continue ;
		}
		else if (ft_strchr(head, '$') != NULL)
			key_value_init(vars, &duped[i]);
		else
			i++;
		head = duped[i];
	}
	return (duped);
}
