/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlee <zlee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:40:14 by zlee              #+#    #+#             */
/*   Updated: 2025/05/19 15:13:57 by zlee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	function_tree_pipe_left(t_ast *node, char **envp, t_exec *info)
{
	dup2(info->pipe_fd[0], 0);
	close(info->pipe_fd[0]);
	close(info->pipe_fd[1]);
	exec_main(node->left, envp);
	exit(EXIT_SUCCESS);
}

void	function_tree_pipe_right(t_ast *node, char **envp, t_exec *info)
{
	dup2(info->pipe_fd[1], 1);
	close(info->pipe_fd[0]);
	close(info->pipe_fd[1]);
	exec_main(node->right, envp);
	exit(EXIT_SUCCESS);
}

void	function_tree_pipe(t_ast *node, char **envp)
{
	t_exec	info;

	memset(&info, 0, sizeof(t_exec));
	if (pipe(info.pipe_fd) < 0)
	{
		perror("pipe\n");
		exit(0);
	}
	info.fork_pid[0] = fork();
	if (info.fork_pid[0] < 0)
		perror("fork_error\n");
	if (info.fork_pid[0] == 0)
		function_tree_pipe_left(node, envp, &info);
	info.fork_pid[1] = fork();
	if (info.fork_pid[1] < 0)
		perror("fork_error\n");
	if (info.fork_pid[1] == 0)
		function_tree_pipe_right(node, envp, &info);
	close(info.pipe_fd[0]);
	close(info.pipe_fd[1]);
	waitpid(info.fork_pid[0], NULL, 0);
	waitpid(info.fork_pid[1], NULL, 0);
}
