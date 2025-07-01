/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main_subshell.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlee <zlee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 23:35:40 by zlee              #+#    #+#             */
/*   Updated: 2025/07/01 23:35:58 by zlee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	function_tree_subshell(t_ast *node, t_vars *vars)
{
	t_exec	info;

	memset(&info, 0, sizeof(t_exec));
	if (node->cmd->redir_count != 0)
	{
		if (subshell_redir(node) == EXIT_FAILURE)
		{
			reset_fd(vars);
			return (EXIT_FAILURE);
		}
	}
	info.fork_pid[0] = fork();
	if (info.fork_pid[0] < 0)
		perror("subshell\n");
	if (info.fork_pid[0] == 0)
	{
		exec_main(node->left, vars);
		exit(1);
	}
	else
		waitpid(info.fork_pid[0], &info.status, 0);
	reset_fd(vars);
	vars->exit_code = WEXITSTATUS(info.status);
	return (WEXITSTATUS(info.status));
}
