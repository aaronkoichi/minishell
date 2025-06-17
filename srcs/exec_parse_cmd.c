/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_parse_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlee <zlee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:15:10 by zlee              #+#    #+#             */
/*   Updated: 2025/06/18 00:44:44 by zlee             ###   ########.fr       */
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
			ft_strlen(redirs[1]->filename)) != 0 && (head->type == REDIR_OUT
			|| head->type == REDIR_APPEND))
				fd = open(head->filename, O_CREAT, 0644);
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

int	exec_cmd(t_ast *node, t_redir **redirs, char **command, t_vars *vars)
{
	int	status;
	int	fork_pid;
	char	**envp;

	status = 0;
	envp = NULL;
	fork_pid = fork();
	if (fork_pid == 0)
		exit (run_cmd(command, vars, redirs, envp));
	waitpid(fork_pid, &status, 0);
	if (status == 0 && redirs != NULL && redirs[1] != NULL)
		touch_files(node, redirs);
	free_arr(command);
	if (envp != NULL)
		free_arr(envp);
	free(redirs);
	reset_fd(vars);
	return (status);
}

int	exec_cmd_main(t_ast *node, t_vars *vars)
{
	char	**command;
	t_redir	**redirs;
	int		status;
	
	if (builtin_functions(node->cmd, vars) != -1)
		return (0);
	command = prep_cmd(node->cmd, vars);
	if (node->cmd->redir_count != 0)
		redirs = determine_redir(node);
	else
	 	redirs = NULL;
	status = exec_cmd(node, redirs, command, vars);
	if (status == 127)
		vars->exit_code = 127;
	else
		vars->exit_code = WEXITSTATUS(status);
	return (vars->exit_code);
}

