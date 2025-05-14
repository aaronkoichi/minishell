/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlee <zlee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:34:18 by zlee              #+#    #+#             */
/*   Updated: 2025/05/14 16:23:17 by zlee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	parse_cmd(t_ast *node)
{
	int fd;
	int	fork;
	int	status;
	// Skip the heredoc part for now
	// Check for redir before running execve
	// Check for redir
	if (node->cmd->redirs->type == REDIR_IN)
	{
		status = access(node->cmd->redirs->filename, F_OK | R_OK);
		if (status == -1)
			; // Some error handling
		else
			fd = open(node->cmd->redirs->filename, O_RDONLY);
	}
	else if (node->cmd->redirs->type == REDIR_OUT)
	{
	
	}
	else if (node->cmd->redirs->type == REDIR_APPEND)
	{


	}
}

void	function_tree(t_ast *node)
{
	int	status;
	int	fork_pid[2];
	int	pipefd[2];

	status = 0;
	memset(&fork_pid, 0, sizeof(int[2]));
	if (node->type == NODE_SEQUENCE)
	{
		exec_main(node->left);
		exec_main(node->right);
		return ;
	}
	else if (node->type == NODE_SUBSHELL)
	{
		fork_pid[0] = fork();
		if (fork_pid[0] < 0)
			perror("Fork Error\n");
		if (fork_pid[0] == 0)
			exec_main(node->left);
		else
			waitpid(fork_pid[0], &status, 0);
		if (status != 0)
			return ;
	}
	else if (node->type == NODE_AND)
	{
		fork_pid[0] = fork();
		if (fork_pid[0] < 0)
			perror("Fork Error\n");
		if (fork_pid[0] == 0)
			exec_main(node->left);
		else
			waitpid(fork_pid[0], &status, 0);
		if (status == 0)
			exec_main(node->right);
		else
			return ;
	}
	else if (node->type == NODE_OR)
	{
		fork_pid[0] = fork();
		if (fork_pid[0] < 0)
			perror("Fork Error\n");
		if (fork_pid[0] == 0)
			exec_main(node->left);
		else
			waitpid(fork_pid[0], &status, 0);
		if (status != 0)
			exec_main(node->right);
		else
			return ;

	}
	else if (node->type == NODE_PIPE)
	{
		if (pipe(pipefd) < 0)
		{
			perror("pipe\n");
			exit (EXIT_FAILURE);
		}
		fork_pid[0] = fork();
		if (fork_pid[0] < 0)
			perror("Fork Error\n");
		if (fork_pid[0] == 0)
		{
			dup2(pipefd[1], 1);
			close(pipefd[0]);
			close(pipefd[1]);
			exec_main(node->left);
			exit(EXIT_SUCCESS);
		}
		fork_pid[1] = fork();
		if (fork_pid[1] < 0)
			perror("Fork Error\n");
		if (fork_pid[1] == 0)
		{
			dup2(pipefd[0], 0);
			close(pipefd[0]);
			close(pipefd[1]);
			exec_main(node->right);
			exit(EXIT_SUCCESS);
		}
		close(pipefd[0]);
		close(pipefd[1]);
		waitpid(fork_pid[0], NULL, 0);
		waitpid(fork_pid[1], NULL, 0);

	}
	else if (node->type == NODE_COMMAND)
	{
		parse_cmd(node);
	}
}

void	exec_main(t_ast *node)
{
	if (node->type == NODE_ROOT)
		exec_main(node->left);
	if (node == NULL)
		return ;
	else
		function_tree(node);
}
