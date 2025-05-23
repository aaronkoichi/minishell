/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_parse_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlee <zlee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:15:10 by zlee              #+#    #+#             */
/*   Updated: 2025/05/23 14:45:07 by zlee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	redirect_fd(t_ast *node, t_redir **redirs)
{
	int	status;

	status = 0;
	if (*redirs != NULL)
	{
		if (redirs[0] != NULL)
		{
			status = redir_in(node, redirs[0]);
			if (status < 0)
				return (-1);
		}
		if (redirs[1] != NULL)
		{
			status = redir_out(node, redirs[1]);
			if (status < 0)
				return (-1);
		}
	}
	return (0);
}

int	exec_cmd(t_ast *node, t_redir **redirs, char **command, char **envp)
{
	int	status;
	int	fork_pid;

	status = 0;
	fork_pid = fork();
	if (fork_pid == 0)
	{
		status = redirect_fd(node, redirs);
		if (status != 0)
			exit (EXIT_FAILURE);
		execve(command[0], command, envp);
		perror("execve\n");
		exit (EXIT_FAILURE);
	}
	waitpid(fork_pid, &status, NULL);
	free_arr(command);
	return (status);
}

int	parse_cmd(t_ast *node, char **envp)
{
	int		status;
	int		fork_n;
	char	**command;
	t_redir	**redirs;

	command = prep_cmd(node->cmd, envp);
	if (node->cmd->redirs != NULL)
		redirs = determine_redir(node);
	else
		redirs = NULL;
	return (exec_cmd(node, redirs, command, envp));
}

