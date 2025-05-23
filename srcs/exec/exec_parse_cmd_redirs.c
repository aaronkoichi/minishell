/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_parse_cmd_redirs.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlee <zlee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:19:09 by zlee              #+#    #+#             */
/*   Updated: 2025/05/23 17:41:56 by zlee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	redir_out(t_ast *node, t_redir *redir)
{
	int fd;

	fd = 0;
	if (redir->type == REDIR_OUT)
		fd = open(redir->filename, O_CREAT | O_WRONLY, 0644);
	else
		fd = open(redir->filename, O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (fd < 0)
	{
		perror("output redirection\n");
		return (1);
	}
	dup2(fd, 1);
	close(fd);
	return (0);
}

int	redir_in(t_ast *node, t_redir *redir)
{
	int	fd[2];

	memset(fd, 0, sizeof(int[2]));
	if (redir->type == REDIR_HEREDOC)
	{
		if (pipe(fd) < 0)
			perror("pipe\n");
		write(fd[1], redir->heredoc_content, ft_strlen(redir->heredoc_content));
		dup2(fd[0], 0);
		close(fd[0]);
		close(fd[1]);
	}
	else
	{
		fd[0] = open(redir->filename, O_RDONLY);
		if (fd[0] < 0)
			return (fd[0]);
		dup2(fd[0], 0);
		close(fd[0]);
	}
	return (0);
}

// t_redir [0] --> In | Heredoc, [1] --> Out | Append
t_redir		**determine_redir(t_ast *node)
{
	t_redir		**head;
	t_redir		**redirs;
	
	head = &node->cmd->redirs;
	redirs = ft_calloc(2, sizeof(t_redir));
	if (!redirs)
		return (NULL);
	while (*head)
	{
		if ((*head)->type == REDIR_IN || (*head)->type == REDIR_HEREDOC)
			redirs[0] = (*head);
		head = &(*head)->next;
	}
	head = &node->cmd->redirs;
	while(*head)
	{
		if ((*head)->type == REDIR_OUT | (*head)->type == REDIR_APPEND)
			redirs[1] = (*head);
		head = &(*head)->next;
	}
	return (redirs);
}
