/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_prt.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthiew <jthiew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:15:33 by jthiew            #+#    #+#             */
/*   Updated: 2025/06/10 14:16:08 by jthiew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	swap_env_nodes(t_env *n1, t_env *n2)
{
	char	*temp_key;
	char	*temp_value;
	int		temp_ind;

	temp_key = n1->key;
	temp_value = n1->value;
	temp_ind = n1->ind;
	n1->key = n2->key;
	n1->value = n2->value;
	n1->ind = n2->ind;
	n2->key = temp_key;
	n2->value = temp_value;
	n2->ind = temp_ind;
}

void	sort_env_by_key(t_env *env)
{
	t_env	*curr;
	int		sorted;

	sorted = 0;
	while (sorted == 0)
	{
		sorted = 1;
		curr = env;
		while (curr->next != NULL)
		{
			if (ft_strcmp(curr->key, curr->next->key) > 0)
			{
				swap_env_nodes(curr, curr->next);
				sorted = 0;
			}
			curr = curr->next;
		}
	}
}

void	sort_env_by_ind(t_env *env)
{
	t_env	*curr;
	int		sorted;

	sorted = 0;
	while (sorted == 0)
	{
		sorted = 1;
		curr = env;
		while (curr->next != NULL)
		{
			if (curr->ind > curr->next->ind)
			{
				swap_env_nodes(curr, curr->next);
				sorted = 0;
			}
			curr = curr->next;
		}
	}
}

void	export_print_env(t_env **env)
{
	t_env	*temp;

	sort_env_by_key(*env);
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
	sort_env_by_ind(*env);
}
