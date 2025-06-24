/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlee <zlee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 18:31:46 by zlee              #+#    #+#             */
/*   Updated: 2025/06/24 21:21:43 by zlee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H
# include "../includes/minishell.h"
# include <unistd.h>
# include <sys/wait.h>
# include <dirent.h>
# include "../libft/libft.h"
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

typedef struct s_pos
{
	int	x;
	int y;
}	t_pos;

typedef struct s_file
{
	char			*file;
	struct s_file	*next;
}					t_file;

// exec_main.c
int			exec_main(t_ast *node, t_vars *vars);
// exec_utils.c
void		free_arr(char **arr);
int			run_cmd(char **exec, t_vars *vars, t_redir **redirs, char **envp);
void		reset_fd(t_vars *vars);
char		**construct_envp(t_vars *vars);
// prep_cmd.c
char		**prep_cmd(t_cmd *cmd, t_vars *vars);
// exec_pipe.c
int			function_tree_pipe_left(t_ast *node, t_vars *vars, t_exec *info);
int			function_tree_pipe_right(t_ast *node, t_vars *vars, t_exec *info);
int			function_tree_pipe(t_ast *node, t_vars *vars);
// exec_parse_cmd.c
int			exec_cmd_main(t_ast *node, t_vars *vars);
int			redirect_fd(t_redir **redirs);
// exec_parse_cmd_redirs.c
int			redir_out(t_redir *redir);
int			redir_in(t_redir *redir);
t_redir		**determine_redir(t_ast *node);
int			subshell_redir(t_ast *node);

// for handling the wildcards
// wildcard.c
char		**detect_wildcard(t_cmd *cmd);
// wildcard_fnmatch.c
int			ft_fnmatch(const char *pattern, const char *filename);
/*wildcard_utils.c*/
void		free_array(char **arr);
int			count_trim_lines(char **arr, const char *filename);
void		ft_lstaddback_file(t_file **file, char *string);
int			ft_lstsize_file(t_file *file);
void		ft_lstclear_file(t_file **file, void (*del)(void *));
// wildcard_mk_new_exev.c
t_file		*mk_new_execve(t_file **files, char *str);

// Handle env.
void		detect_env(t_vars *vars, char **arr);
#endif
