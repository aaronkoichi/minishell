/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlee <zlee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 18:31:46 by zlee              #+#    #+#             */
/*   Updated: 2025/05/14 20:52:35 by zlee             ###   ########.fr       */
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

typedef enum e_fd
{
	PIPE,
	NORMAL
}	t_fd;
// exec_main.c
void	exec_main(t_ast *node);
// exec_utils.c
void	free_arr(char **arr);
int		run_cmd(char **exec, char **envp);
// prep_cmd.c
char	**prep_cmd(t_cmd *cmd, char **envp);
#endif
