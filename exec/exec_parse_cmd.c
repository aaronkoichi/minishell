/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_parse_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlee <zlee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:15:10 by zlee              #+#    #+#             */
/*   Updated: 2025/05/19 15:17:35 by zlee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	parse_cmd(t_ast *node, char **envp)
{
	int fd;
	int	fork_n;
	int	status;
	char	**command;
	command = prep_cmd(node->cmd, envp);
	if (node->cmd->redirs->type == REDIR_IN)
	{
		fd = open(node->cmd->redirs->filename, O_CREAT | O_RDONLY, 0644);
		if (fd < 0)
			perror("file.");
		fork_n = fork();
		if (fork_n == 0)
		{
			dup2(fd, 0);
			close(fd);
		}
	}
	else if (node->cmd->redirs->type == REDIR_OUT)
	{
		fd = open(node->cmd->redirs->filename, O_CREAT | O_RDWR, 0644);
		if (fd < 0)
			perror("file");
		fork_n = fork();
		if (fork_n == 0)
		{
			dup2(fd, 1);
			close(fd);
		}
	}
	else if (node->cmd->redirs->type == REDIR_APPEND)
	{
		fd = open(node->cmd->redirs->filename, O_CREAT | O_APPEND, 0644);
		if (fd < 0)
			perror("file.");
		fork_n = fork();
		if (fork_n == 0)
		{
			dup2(fd, 1);
			close(fd);
		}
	}
}
