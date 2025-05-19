/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlee <zlee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 18:31:46 by zlee              #+#    #+#             */
/*   Updated: 2025/05/19 12:49:59 by zlee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H
# include "../minishell.h"
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
void	exec_main(t_ast *node, char **envp);
// exec_utils.c
void	free_arr(char **arr);
int		run_cmd(char **exec, char **envp);
// prep_cmd.c
char	**prep_cmd(t_cmd *cmd, char **envp);
// exec_pipe.c
void	function_tree_pipe_left(t_ast *node, char **envp, t_exec *info);
void	function_tree_pipe_right(t_ast *node, char **envp, t_exec *info);
void	function_tree_pipe(t_ast *node, char **envp);
#endif
