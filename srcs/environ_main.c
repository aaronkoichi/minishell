/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlee <zlee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 23:11:14 by zlee              #+#    #+#             */
/*   Updated: 2025/07/01 23:09:30 by zlee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

/* Duplicate a new malloc string but until before the letter given. */
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

/* Create a new allocated string with the key subsituted by the value. */
static void	set_key_value(char **str, char *key, char *value, char *addr)
{
	char	*before_key;
	char	*temp;
	size_t	num;

	before_key = ft_strcdup(*str, *addr);
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

/* Finds the key-value pair from the env struct, the parse it onto 
 * set-key value. */
static void	key_value_init(t_vars *vars, char **str, char *addr)
{
	char	*key;
	char	*value;
	t_env	*env;

	env = vars->env;
	if (*addr == '$' && *(addr + 1) == '?')
		key = ft_strdup("?");
	else
		key = ft_strcdup(addr + 1, find_sym_env(addr + 1));
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
	set_key_value(str, key, value, addr);
	if (!ft_strcmp(key, "?"))
		free(value);
	free(key);
}

/* Seperate function to disregard single quotes when inside double quotes. */
static void	check_inside_dbl_quotes(t_vars *vars, char **head,
				char **string)
{
	char	*ptr;

	ptr = *head;
	ptr++;
	while (*ptr && *ptr != '\"')
	{
		if (*ptr == '$')
		{
			key_value_init(vars, string, ptr);
			ptr = *string + (ptr - *head);
		}
		else
			ptr++;
	}
	if (*ptr && *ptr == '\"')
		ptr++;
	*head = ptr;
}

/* detects '$' signs to proceed with expansions. */
char	**detect_env(t_vars *vars, char **duped)
{
	int		i;
	char	*head;

	i = 0;
	head = duped[i];
	while (duped[i])
	{
		while (head && *head)
		{
			if (*head == '\"')
				check_inside_dbl_quotes(vars, &head, &duped[i]);
			else if (*head == '\'')
				head = move_char(head);
			else if (*head == '$')
			{
				key_value_init(vars, &duped[i], head);
				head = duped[i];
			}
			else
				head++;
		}
		head = duped[++i];
	}
	return (duped);
}
