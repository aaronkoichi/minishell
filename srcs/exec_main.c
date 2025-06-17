/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlee <zlee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:34:18 by zlee              #+#    #+#             */
/*   Updated: 2025/06/17 16:01:05 by zlee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "minishell.h"

int	function_tree_seq(t_ast *node, t_vars *vars)
{
	exec_main(node->left, vars);
	exec_main(node->right, vars);
	return (0);
}

int	function_tree_subshell(t_ast *node, t_vars *vars)
{
	t_exec	info;

	memset(&info, 0, sizeof(t_exec));
	if (node->cmd->redir_count != 0)
		if (subshell_redir(node) != -1)
		{
			reset_fd(vars);
			return (EXIT_FAILURE);
		}
	info.fork_pid[0] = fork();
	if (info.fork_pid[0] < 0)
		perror("subshell\n");
	if (info.fork_pid[0] == 0)
		return (exec_main(node->left, vars));
	else
		waitpid(info.fork_pid[0], &info.status, 0);
	reset_fd(vars);
	vars->exit_code = WEXITSTATUS(info.status);
	return (WEXITSTATUS(info.status));
}

int	function_tree_and(t_ast *node, t_vars *vars)
{
	t_exec	info;

	memset(&info, 0, sizeof(t_exec));
	if (exec_main(node->left, vars) == 0)
		exec_main(node->right, vars);
	return (WEXITSTATUS(info.status));
}

int	function_tree_or(t_ast *node, t_vars *vars)
{
	t_exec	info;

	memset(&info, 0, sizeof(t_exec));
	if (exec_main(node->left, vars) != 0)
		exec_main(node->right, vars);
	return (WEXITSTATUS(info.status));
}

int	function_tree(t_ast *node, t_vars *vars)
{
	if (node->type == NODE_SEQUENCE)
		return (function_tree_seq(node, vars));
	else if (node->type == NODE_SUBSHELL)
		return (function_tree_subshell(node, vars));
	else if (node->type == NODE_AND)
		return (function_tree_and(node, vars));
	else if (node->type == NODE_OR)
		return (function_tree_or(node, vars));
	else if (node->type == NODE_PIPE)
		return (function_tree_pipe(node, vars));
	else if (node->type == NODE_COMMAND)
		return (exec_cmd_main(node, vars));
	return (1);
}

int	exec_main(t_ast *node, t_vars *vars)
{
	if (node == NULL || (node->type == NODE_COMMAND
		&& node->cmd->argc == 0))
		return (0);
	if (node->type == NODE_ROOT)
		return (exec_main(node->left, vars));
	else
		return (function_tree(node, vars));
}
