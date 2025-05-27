/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthiew <jthiew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 12:51:29 by jthiew            #+#    #+#             */
/*   Updated: 2025/05/26 13:12:35 by jthiew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*create_ast_node(t_node_type type, t_ast *left,
			t_ast *right, t_cmd *cmd)
{
	t_ast	*node;

	node = malloc(1 * sizeof(t_ast));
	if (node == NULL)
		return (NULL);
	node->type = type;
	node->left = left;
	node->right = right;
	node->cmd = cmd;
	return (node);
}

void	ft_lstclear_ast_tree(t_ast **ast)
{
	t_ast	*left;
	t_ast	*right;

	left = (*ast)->left;
	right = (*ast)->right;
	if ((*ast)->cmd != NULL)
	{
		free((*ast)->cmd->argv);
		ft_lstclear_redir(&(*ast)->cmd->redirs);
		free((*ast)->cmd);
	}
	free(*ast);
	if (left != NULL)
		ft_lstclear_ast_tree(&left);
	if (right != NULL)
		ft_lstclear_ast_tree(&right);
}
