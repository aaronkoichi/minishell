/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlee <zlee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 20:47:07 by zlee              #+#    #+#             */
/*   Updated: 2025/06/04 17:39:43 by zlee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

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

int	run_cmd(char **exec, t_vars *vars)
{
	int pid;
	int	status;

	(void)vars;
	pid = fork();
	status = 0;
	if (pid == 0)
	{
		execve(exec[0], exec, NULL);
		perror("execve error\n");
		exit(EXIT_FAILURE);
	}
	waitpid(pid, &status, 0);
	free_arr(exec);
	if (status != 0)
		return (EXIT_FAILURE);
	else
		return (EXIT_SUCCESS);
}
