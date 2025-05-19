/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlee <zlee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:34:18 by zlee              #+#    #+#             */
/*   Updated: 2025/05/19 15:17:42 by zlee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	function_tree_seq(t_ast *node, char **envp)
{
	exec_main(node->left, envp);
	exec_main(node->right, envp);
}

void	function_tree_subshell(t_ast *node, char **envp)
{
	t_exec	info;

	memset(&info, 0, sizeof(t_exec));
	info.fork_pid[0] = fork();
	if (info.fork_pid[0] < 0)
		perror("subshell\n");
	if (info.fork_pid[0] == 0)
		exec_main(node->left, envp);
	else
		waitpid(info.fork_pid[0], &info.status, 0);
	if (info.status != 0)
		;
	return ;
}

void	function_tree_and(t_ast *node, char **envp)
{
	t_exec	info;

	memset(&info, 0, sizeof(t_exec));
	info.fork_pid[0]= fork();
	if (info.fork_pid[0] < 0)
		perror("Fork Error\n");
	else if (info.fork_pid[0] == 0)
		exec_main(node->left, envp);
	else
		waitpid(info.fork_pid[0], &info.status, 0);
	if (info.status == 0)
		exec_main(node->right, envp);
	else
		return ;
}

void	function_tree_or(t_ast *node, char **envp)
{
	t_exec	info;

	memset(&info, 0, sizeof(t_exec));
	info.fork_pid[0]= fork();
	if (info.fork_pid[0] < 0)
		perror("Fork Error\n");
	else if (info.fork_pid[0] == 0)
		exec_main(node->left, envp);
	else
		waitpid(info.fork_pid[0], &info.status, 0);
	if (info.status != 0)
		exec_main(node->right, envp);
	else
		return ;
}

void	function_tree(t_ast *node, char **envp)
{
	if (node->type == NODE_SEQUENCE)
		function_tree_seq(node, envp);
	else if (node->type == NODE_SUBSHELL)
		function_tree_subshell(node, envp);
	else if (node->type == NODE_AND)
		function_tree_and(node, envp);
	else if (node->type == NODE_OR)
		function_tree_or(node, envp);
	else if (node->type == NODE_PIPE)
		function_tree_pipe(node, envp);
	else if (node->type == NODE_COMMAND)
		parse_cmd(node, envp);
	return ;
}

void	exec_main(t_ast *node, char **envp)
{
	if (node->type == NODE_ROOT)
		exec_main(node->left, envp);
	if (node == NULL)
		return ;
	else
		function_tree(node, envp);
}
