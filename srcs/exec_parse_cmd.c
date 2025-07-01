/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_parse_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlee <zlee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:15:10 by zlee              #+#    #+#             */
/*   Updated: 2025/07/01 22:59:47 by zlee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "minishell.h"

int	exec_cmd(t_ast *node, t_redir **redirs, char **command, t_vars *vars)
{
	int	status;
	int	fork_pid;
	char	**envp;

	status = 0;
	envp = NULL;
	if (node->cmd->redir_count != 0)
		redirs = determine_redir(node);
	else
		redirs = NULL;
	status = redirect_fd(redirs);
	if (status != 0)
		return (EXIT_FAILURE);
	if (builtin_functions(node->cmd, vars) != -1)
		reset_fd(vars);
	else
	{
		fork_pid = fork();
		if (fork_pid == 0)
		{
			run_cmd(command, vars, redirs, envp);
			free_arr(command);
			free(redirs);
			reset_fd(vars);
			close_fds();
			return (-2);
		}
		waitpid(fork_pid, &status, 0);
	}
	if (status == 0 && redirs != NULL && redirs[1] != NULL)
		touch_files(node, redirs);
	free_arr(command);
	if (envp != NULL)
		free_arr(envp);
	free(redirs);
	reset_fd(vars);
	return (status);
}

static void	prep_wildcards_env(t_ast *node, t_vars *vars)
{
	char	**temp;
	char	**wildcard_temp;
	char	**data;

	temp = ft_strdup_arr(node->cmd->argv);
	temp = detect_env(vars, temp);
	node->cmd->argv = temp;
	data = trim_execve(node->cmd);
	wildcard_temp = detect_wildcard(node->cmd, data);
	free_arr(node->cmd->argv);
	free_arr(data);
	node->cmd->argv = wildcard_temp;
}

int	exec_cmd_main(t_ast *node, t_vars *vars)
{
	char	**command;
	t_redir	**redirs;
	int		status;
	char	**original;
	
	if (!ft_strcmp(node->cmd->argv[0], "exit"))
		exit (builtin_functions(node->cmd, vars));
	redirs = NULL;
	original = node->cmd->argv;
	prep_wildcards_env(node, vars);
	command = prep_cmd(node->cmd, vars);
	status = exec_cmd(node, redirs, command, vars);
	if (status == 127)
		vars->exit_code = 127;
	else if (status == -2)
		vars->exit_code = -2;
	else
		vars->exit_code = WEXITSTATUS(status);
	free_arr(node->cmd->argv);
	node->cmd->argv = original;
	return (vars->exit_code);
}

