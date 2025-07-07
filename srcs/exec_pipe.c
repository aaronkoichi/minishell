/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlee <zlee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:40:14 by zlee              #+#    #+#             */
/*   Updated: 2025/07/07 09:16:12 by jthiew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Redirect the output into stdin.
int	function_tree_pipe_left(t_ast *node, t_vars *vars,
		t_exec *info, t_wrapper wrapper)
{
	dup2(info->pipe_fd[1], 1);
	close(info->pipe_fd[0]);
	close(info->pipe_fd[1]);
	reset_signal();
	info->status = exec_main(node->left, vars, wrapper.tree, wrapper.token);
	ft_lstclear_ast_tree(&wrapper.tree);
	ft_lstclear_token(&wrapper.token);
	destroy_vars(vars);
	close_fds();
	exit(info->status);
}

int	function_tree_pipe_right(t_ast *node, t_vars *vars,
		t_exec *info, t_wrapper wrapper)
{
	dup2(info->pipe_fd[0], 0);
	close(info->pipe_fd[0]);
	close(info->pipe_fd[1]);
	reset_signal();
	info->status = exec_main(node->right, vars, wrapper.tree, wrapper.token);
	ft_lstclear_ast_tree(&wrapper.tree);
	ft_lstclear_token(&wrapper.token);
	destroy_vars(vars);
	close_fds();
	exit(info->status);
}

t_wrapper	wrapper_func(t_ast *tree, t_token *token)
{
	t_wrapper	wrapper;

	wrapper.tree = tree;
	wrapper.token = token;
	return (wrapper);
}

void	close_pipe_parent_fds(t_exec info)
{
	close(info.pipe_fd[0]);
	close(info.pipe_fd[1]);
}

int	function_tree_pipe(t_ast *node, t_vars *vars, t_ast *tree, t_token *token)
{
	t_exec		info;
	t_wrapper	wrapper;

	wrapper = wrapper_func(tree, token);
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
		function_tree_pipe_left(node, vars, &info, wrapper);
	info.fork_pid[1] = fork();
	if (info.fork_pid[1] < 0)
		perror("fork_error\n");
	if (info.fork_pid[1] == 0)
		function_tree_pipe_right(node, vars, &info, wrapper);
	close_pipe_parent_fds(info);
	waitpid(info.fork_pid[0], NULL, 0);
	waitpid(info.fork_pid[1], &info.status, 0);
	vars->exit_code = WEXITSTATUS(info.status);
	return (vars->exit_code);
}
