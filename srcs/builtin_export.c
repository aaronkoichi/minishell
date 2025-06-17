/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthiew <jthiew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 15:48:37 by jthiew            #+#    #+#             */
/*   Updated: 2025/06/17 16:35:09 by zlee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_valid_identifier(char *str)
{
	if (str == NULL || !(ft_isalpha(*str) == 1 || *str == '_'))
		return (false);
	while (*str != '\0' && *str != '=')
	{
		if (!(ft_isalnum(*str) == 1 || *str == '_'))
			return (false);
		str++;
	}
	return (true);
}

bool	is_exist_node_key(t_env *node, t_env *env)
{
	t_env	*temp;

	temp = env;
	while (temp != NULL)
	{
		if (strcmp(temp->key, node->key) == 0)
			return (true);
		temp = temp->next;
	}
	return (false);
}

static void	update_env_value_exp(t_env *node, t_env **env)
{
	t_env	*temp;

	temp = *env;
	while (temp != NULL)
	{
		if (strcmp(temp->key, node->key) == 0)
		{
			if (node->value != NULL)
			{
				free(temp->value);
				temp->value = node->value;
				free(node->key);
				node->value = NULL;
				free(node);
			}
			else
			{
				free(node->key);
				free(node);
			}
			break ;
		}
		temp = temp->next;
	}
}

static int	export_add_entry(t_cmd *cmd, t_env **env)
{
	int		i;
	t_env	*node;

	i = 1;
	while (cmd->argv[i] != NULL)
	{
		if (is_valid_identifier(cmd->argv[i]) == false)
		{
			ft_putstr_fd("export: `", 2);
			ft_putstr_fd(cmd->argv[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return (1);
		}
		node = create_env_node(cmd->argv[i], ft_lstsize_env(*env));
		if (node == NULL)
			return (1);
		if (is_exist_node_key(node, *env) == true)
			update_env_value_exp(node, env);
		else
			ft_lstadd_back_env(env, node);
		i++;
	}
	return (0);
}

int	builtin_export(t_cmd *cmd, t_env **env, t_vars *vars)
{
	(void)vars;
	if (cmd->argc == 1)
	{
		export_print_env(env);
		return (0);
	}
	else
		return (export_add_entry(cmd, env));
}
