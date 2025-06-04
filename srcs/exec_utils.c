/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlee <zlee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 20:47:07 by zlee              #+#    #+#             */
/*   Updated: 2025/06/04 18:52:21 by zlee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "minishell.h"

void	free_arr(char **arr)
{
	int i;

	i = 0;
	while(arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr[i]);
	free(arr);
}

int	run_cmd(char **exec, t_vars *vars, t_redir **redirs, char **envp)
{
	int	status;

	envp = construct_envp(vars);
	status = redirect_fd(redirs);
	if (status != 0)
		return (EXIT_FAILURE);
	reset_signal();
	execve(exec[0], exec, NULL);
	perror("execve");
	return (127);
}

void	reset_fd(t_vars *vars)
{
	dup2(0, vars->ori_stdin);
	dup2(1, vars->ori_stdout);
	dup2(2, vars->ori_stderr);
}

int	env_size(t_env *env)
{
	t_env	*head;
	int		i;

	head = env;
	i = 0;
	while (head)
	{
		i++;
		head = head->next;
	}
	return (i);
}

char	**construct_envp(t_vars *vars)
{
	char	**string;
	t_env	*head;
	char	*temp;
	int		i;

	head = vars->env;
	i = 0;
	string = malloc((env_size(head) + 1) * sizeof(char *));
	while (head)
	{
		string[i] = ft_strjoin(head->key, "=");
		temp = ft_strjoin(string[i], head->value);
		free(string[i]);
		string[i] = temp;
		i++;
		head = head->next;
	}
	string[i] = 0;
	return (string);
}
