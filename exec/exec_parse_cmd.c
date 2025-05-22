/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_parse_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlee <zlee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:15:10 by zlee              #+#    #+#             */
/*   Updated: 2025/05/22 16:08:10 by zlee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	parse_cmd_redir_append(t_ast *node, char **envp, char **command)
{
	int	fd;
	int	fork_n;
	int	status;

	fd = open(node->cmd->redirs->filename, O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (fd < 0)
		perror("file");
	fork_n = fork();
	if (fork_n == 0)
	{
		dup2(fd, 1);
		close(fd);
		execve(command[0], command, envp);
		exit(EXIT_FAILURE);
	}
	close(fd);
	waitpid(fork_n, &status, 0);
	return (status);
}

int	parse_cmd_redir_out(t_ast *node, char **envp, char **command)
{
	int	fd;
	int	fork_n;
	int	status;

	fd = open(node->cmd->redirs->filename, O_CREAT | O_WRONLY, 0644);
	if (fd < 0)
		perror("file");
	fork_n = fork();
	if (fork_n == 0)
	{
		dup2(fd, 1);
		close(fd);
		execve(command[0], command, envp);
		exit(EXIT_FAILURE);
	}
	close(fd);
	waitpid(fork_n, &status, 0);
	return (status);
}

int	parse_cmd_redir_in(t_ast *node, char **envp, char **command)
{
	int	fd;
	int	fork_n;
	int	status;

	fd = open(node->cmd->redirs->filename, O_RDONLY);
	if (fd < 0)
		perror("file");
	fork_n = fork();
	if (fork_n == 0)
	{
		dup2(fd, 0);
		close(fd);
		execve(command[0], command, envp);
		exit(EXIT_FAILURE);
	}
	close(fd);
	waitpid(fork_n, &status, 0);
	return (status);
}

int	parse_cmd_fork(t_ast *node, char **envp, char **command)
{
	int	fork_n;
	int	status;

	fork_n = fork();
	if (fork_n == 0)
	{
		execve(command[0], command, envp);
		exit(EXIT_FAILURE);
	}
	waitpid(fork_n, &status, 0);
	return (status);
}

int	parse_cmd(t_ast *node, char **envp)
{
	int		status;
	int		fork_n;
	char	**command;

	command = prep_cmd(node->cmd, envp);
	while (node->cmd->redirs != NULL)
	{
		if (node->cmd->redirs->type == REDIR_IN)
			parse_cmd_redir_in(node, envp, command);
		else if (node->cmd->redirs->type == REDIR_OUT)
			 parse_cmd_redir_out(node, envp, command);
		else if (node->cmd->redirs->type == REDIR_APPEND)
			 parse_cmd_redir_append(node, envp, command);
		else
			 parse_cmd_fork(node, envp, command);
		node->cmd->redirs = node->cmd->redirs->next;
	}
}

