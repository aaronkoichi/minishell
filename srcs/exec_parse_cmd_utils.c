/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_parse_cmd_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlee <zlee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 22:48:14 by zlee              #+#    #+#             */
/*   Updated: 2025/07/01 23:47:07 by zlee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "minishell.h"

void	touch_files(t_ast *node, t_redir **redirs)
{
	t_redir	*head;
	int		fd;

	fd = 0;
	head = node->cmd->redirs;
	while (head != NULL)
	{
		if (ft_strncmp(head->filename, redirs[1]->filename,
				ft_strlen(redirs[1]->filename)) != 0
			&& (head->type == REDIR_OUT || head->type == REDIR_APPEND))
		{
			fd = open(head->filename, O_CREAT, 0644);
			close(fd);
		}
		else
			(void)fd;
		head = head->next;
	}
}

int	redirect_fd(t_redir **redirs)
{
	int	status;

	status = 0;
	if (redirs != NULL)
	{
		if (redirs[0] != NULL)
		{
			status = redir_in(redirs[0]);
			if (status < 0)
				return (-1);
		}
		if (redirs[1] != NULL)
		{
			status = redir_out(redirs[1]);
			if (status < 0)
				return (-1);
		}
	}
	return (0);
}

void	close_fds(void)
{
	close(0);
	close(1);
	close(2);
}
