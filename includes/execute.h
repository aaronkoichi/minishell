/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlee <zlee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 18:31:46 by zlee              #+#    #+#             */
/*   Updated: 2025/06/04 15:48:11 by zlee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H
# include "../includes/minishell.h"
# include <unistd.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>

typedef struct s_exec
{
	int	status;
	int	fork_pid[2];
	int	pipe_fd[2];
}	t_exec;
// exec_main.c
int			exec_main(t_ast *node, t_vars *vars);
// exec_utils.c
void		free_arr(char **arr);
int			run_cmd(char **exec, t_vars *vars);
// prep_cmd.c
char		**prep_cmd(t_cmd *cmd, t_vars *vars);
// exec_pipe.c
int			function_tree_pipe_left(t_ast *node, t_vars *vars, t_exec *info);
int			function_tree_pipe_right(t_ast *node, t_vars *vars, t_exec *info);
int			function_tree_pipe(t_ast *node, t_vars *vars);
// exec_parse_cmd.c
int			exec_cmd_main(t_ast *node, t_vars *vars);
// exec_parse_cmd_redirs.c
int			redir_out(t_redir *redir);
int			redir_in(t_redir *redir);
t_redir		**determine_redir(t_ast *node);
#endif
