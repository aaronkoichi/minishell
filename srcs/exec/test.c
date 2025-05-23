/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlee <zlee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:00:24 by zlee              #+#    #+#             */
/*   Updated: 2025/05/22 15:53:49 by zlee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int main(void)
{
	t_ast *node;

	// root node
	node->type = NODE_ROOT;
	
	// pipe Node
	node->left->type = NODE_PIPE;


	// pipe == left node
	node->left->left->type = NODE_COMMAND;

	node->left->left->cmd->argv = malloc(2 * sizeof(char *));
	node->left->left->cmd->argv[0] = malloc(5 * sizeof(char));
	node->left->left->cmd->argv[0] = "echo";
	node->left->left->cmd->argv[0] = malloc(6 * sizeof(char));
	node->left->left->cmd->argv[0] = "hello";
	node->left->left->cmd->argc = 2;

	// pipe == right node
	node->left->right->type = NODE_COMMAND;
	node->left->right->cmd->argv = malloc(2 * sizeof(char *));
	node->left->right->cmd->argv[0] = malloc(3 * sizeof(char));
	node->left->right->cmd->argv[0] = "cat";
	node->left->right->cmd->argv[0] = malloc(2 * sizeof(char));
	node->left->right->cmd->argv[0] = "-e";
	node->left->right->cmd->argc = 2;

}
