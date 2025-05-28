/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlee <zlee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:34:18 by zlee              #+#    #+#             */
/*   Updated: 2025/05/28 20:31:03 by zlee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	function_tree_seq(t_ast *node, char **envp)
{
	exec_main(node->left, envp);
	exec_main(node->right, envp);
	return (0);
}

int	function_tree_subshell(t_ast *node, char **envp)
{
	t_exec	info;

	memset(&info, 0, sizeof(t_exec));
	info.fork_pid[0] = fork();
	if (info.fork_pid[0] < 0)
		perror("subshell\n");
	if (info.fork_pid[0] == 0)
		return (exec_main(node->left, envp));
	else
		waitpid(info.fork_pid[0], &info.status, 0);
	return (WEXITSTATUS(info.status));
}

int	function_tree_and(t_ast *node, char **envp)
{
	t_exec	info;

	memset(&info, 0, sizeof(t_exec));
	info.fork_pid[0]= fork();
	if (info.fork_pid[0] < 0)
		perror("Fork Error\n");
	else if (info.fork_pid[0] == 0)
		exit (exec_main(node->left, envp));
	waitpid(info.fork_pid[0], &info.status, 0);
	if (WEXITSTATUS(info.status) == 0)
		exec_main(node->right, envp);
	return (WEXITSTATUS(info.status));
}

int	function_tree_or(t_ast *node, char **envp)
{
	t_exec	info;

	memset(&info, 0, sizeof(t_exec));
	info.fork_pid[0]= fork();
	if (info.fork_pid[0] < 0)
		perror("Fork Error\n");
	else if (info.fork_pid[0] == 0)
		exit (exec_main(node->left, envp));
	waitpid(info.fork_pid[0], &info.status, 0);
	if (WEXITSTATUS(info.status) != 0)
		exec_main(node->right, envp);
	return (WEXITSTATUS(info.status));
}

int	function_tree(t_ast *node, char **envp)
{
	if (node->type == NODE_SEQUENCE)
		return (function_tree_seq(node, envp));
	else if (node->type == NODE_SUBSHELL)
		return (function_tree_subshell(node, envp));
	else if (node->type == NODE_AND)
		return (function_tree_and(node, envp));
	else if (node->type == NODE_OR)
		return (function_tree_or(node, envp));
	else if (node->type == NODE_PIPE)
		return (function_tree_pipe(node, envp));
	else if (node->type == NODE_COMMAND)
		return (exec_cmd_main(node, envp));
	return (1);
}

int	exec_main(t_ast *node, char **envp)
{
	if (node == NULL || (node->type == NODE_COMMAND
		&& node->cmd->argc == 0))
		return (0);
	if (node->type == NODE_ROOT)
		return (exec_main(node->left, envp));
	else
		return (function_tree(node, envp));
}
