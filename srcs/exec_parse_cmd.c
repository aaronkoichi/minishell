/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_parse_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlee <zlee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:15:10 by zlee              #+#    #+#             */
/*   Updated: 2025/07/07 09:36:23 by jthiew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	reset_free_default(char **command, t_vars *vars,
				t_redir **redirs, char **envp)
{
	free_arr(command);
	if (redirs != NULL)
		reset_fd(vars);
	free(redirs);
	if (envp != NULL)
		free_arr(envp);
}

static int	perform_run_cmd(char **command, t_vars *vars,
				t_redir **redirs, char **envp)
{
	run_cmd(command, vars, redirs, envp);
	free_arr(command);
	free(redirs);
	reset_fd(vars);
	if (envp != NULL)
		free_arr(envp);
	close_fds();
	return (-2);
}

/* stat_fork: 0 --> status, 1 --> fork_pid. */
int	exec_cmd(t_ast *node, t_redir **redirs, t_str_dat dat, t_vars *vars)
{
	int		stat_fork[2];
	char	**envp;

	stat_fork[0] = 0;
	envp = NULL;
	if (node->cmd->redir_count != 0)
		redirs = determine_redir(node);
	else
		redirs = NULL;
	stat_fork[0] = redirect_fd(redirs);
	if (stat_fork[0] != 0)
		return (EXIT_FAILURE);
	if (builtin_functions(node->cmd, vars, dat, &stat_fork[0]) != -1)
		;
	else
	{
		stat_fork[1] = fork();
		if (stat_fork[1] == 0)
			return (perform_run_cmd(dat.command, vars, redirs, envp));
		waitpid(stat_fork[1], &stat_fork[0], 0);
	}
	if (stat_fork[0] == 0 && redirs != NULL && redirs[1] != NULL)
		touch_files(node, redirs);
	reset_free_default(dat.command, vars, redirs, envp);
	return (stat_fork[0]);
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
	t_str_dat	dat;
	t_redir		**redirs;
	int			status;

	redirs = NULL;
	dat.original = node->cmd->argv;
	prep_wildcards_env(node, vars);
	dat.command = prep_cmd(node->cmd, vars);
	status = exec_cmd(node, redirs, dat, vars);
	if (status == 127)
		vars->exit_code = 127;
	else if (status == -2)
		vars->exit_code = -2;
	else if (status < 2)
		vars->exit_code = status;
	else
		vars->exit_code = WEXITSTATUS(status);
	free_arr(node->cmd->argv);
	node->cmd->argv = dat.original;
	return (vars->exit_code);
}
