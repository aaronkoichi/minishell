/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main_subshell.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlee <zlee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 23:35:40 by zlee              #+#    #+#             */
/*   Updated: 2025/07/03 16:22:54 by zlee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "minishell.h"

int	function_tree_subshell(t_ast *node, t_vars *vars, t_ast *tree, t_token *token)
{
	t_exec	info;

	memset(&info, 0, sizeof(t_exec));
	if (node->cmd->redir_count != 0)
	{
		if (subshell_redir(node) == EXIT_FAILURE)
		{
			reset_fd(vars);
			return (EXIT_FAILURE);
		}
	}
	info.fork_pid[0] = fork();
	if (info.fork_pid[0] < 0)
		perror("subshell\n");
	if (info.fork_pid[0] == 0)
	{
		info.status = exec_main(node->left, vars, tree, token);
		close_fds();
		ft_lstclear_ast_tree(&tree);
		ft_lstclear_token(&token);
		destroy_vars(vars);
		exit(info.status);
	}
	else
		waitpid(info.fork_pid[0], &info.status, 0);
	reset_fd(vars);
	vars->exit_code = WEXITSTATUS(info.status);
	return (info.status);
}
