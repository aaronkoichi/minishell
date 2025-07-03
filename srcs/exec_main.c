/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlee <zlee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:34:18 by zlee              #+#    #+#             */
/*   Updated: 2025/07/03 19:45:34 by zlee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "minishell.h"

int	function_tree_seq(t_ast *node, t_vars *vars, t_ast *tree, t_token *token)
{
	int	status;

	status = exec_main(node->left, vars, tree, token);
	if (status == -2)
		return (-2);
	else if (node->right != NULL)
		exec_main(node->right, vars, tree, token);
	return (0);
}

int	function_tree_and(t_ast *node, t_vars *vars, t_ast *tree, t_token *token)
{
	t_exec	info;

	memset(&info, 0, sizeof(t_exec));
	info.status = exec_main(node->left, vars, tree, token);
	if (info.status == 0)
		info.status = exec_main(node->right, vars, tree, token);
	return (info.status);
}

int	function_tree_or(t_ast *node, t_vars *vars, t_ast *tree, t_token *token)
{
	t_exec	info;

	memset(&info, 0, sizeof(t_exec));
	info.status = exec_main(node->left, vars, tree, token);
	if (info.status != 0)
		info.status = exec_main(node->right, vars, tree, token);
	return (info.status);
}

int	function_tree(t_ast *node, t_vars *vars, t_ast *tree, t_token *token)
{
	if (node->type == NODE_SEQUENCE)
		return (function_tree_seq(node, vars, tree, token));
	if (node->type == NODE_SUBSHELL)
		return (function_tree_subshell(node, vars, tree, token));
	else if (node->type == NODE_AND)
		return (function_tree_and(node, vars, tree, token));
	else if (node->type == NODE_OR)
		return (function_tree_or(node, vars, tree, token));
	else if (node->type == NODE_PIPE)
		return (function_tree_pipe(node, vars, tree, token));
	else if (node->type == NODE_COMMAND)
	{
		// printf("node: command : %s %s\n", node->cmd->argv[0], node->cmd->argv[1]);
		return (exec_cmd_main(node, vars));
	}
	return (1);
}

int	exec_main(t_ast *node, t_vars *vars, t_ast *tree, t_token *token)
{
	if (node == NULL
			&& node->cmd->argc == 0)
		return (0);
	if (node->type == NODE_ROOT)
		return (exec_main(node->left, vars, tree, token));
	else
		return (function_tree(node, vars, tree, token));
}
