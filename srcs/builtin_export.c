/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthiew <jthiew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 15:48:37 by jthiew            #+#    #+#             */
/*   Updated: 2025/05/31 15:58:08 by jthiew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_valid_identifier(char *str)
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

static void	export_print_env(t_env **env)
{
	t_env	*temp;

	temp = *env;
	while (temp != NULL)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(temp->key, 1);
		if (temp->value != NULL)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(temp->value, 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putstr_fd("\n", 1);
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
		node = create_env_node(cmd->argv[i]);
		if (node == NULL)
		{
			perror("export node");
			return (1);
		}
		ft_lstadd_back_env(env, node);
		i++;
	}
	return (0);
}

int	builtin_export(t_cmd *cmd, t_env **env)
{

	if (cmd->argc == 1)
	{
		export_print_env(env);
		return (0);
	}
	else
		return (export_add_entry(cmd, env));
}
