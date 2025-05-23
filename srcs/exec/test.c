/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlee <zlee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:00:24 by zlee              #+#    #+#             */
/*   Updated: 2025/05/23 17:17:07 by zlee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int main(int ac, char **av, char **envp)
{
	t_ast *node;

	// root node
	node = ft_calloc(1, sizeof(t_ast));
	node->type = NODE_ROOT;
	

	node->left = ft_calloc(1, sizeof(t_ast));
	node->left->type = NODE_COMMAND;
	node->left->cmd = malloc(sizeof(t_cmd));
	node->left->cmd->argv = malloc(2 * sizeof(char *));
	node->left->cmd->argv[0] = malloc(4 * sizeof(char));
	node->left->cmd->argv[0] = "cat";
	node->left->cmd->argv[1] = malloc(3 * sizeof(char));
	node->left->cmd->argv[1] = "-e";
	node->left->cmd->argc = 2;
	// node->left->cmd->redirs = NULL;
	node->left->cmd->redir_count = 1;

	// redirection test
	node->left->cmd->redirs = malloc(sizeof(t_redir));
	node->left->cmd->redirs->type = REDIR_IN;
	node->left->cmd->redirs->filename = "redir_in";
	node->left->cmd->redirs->next = NULL;
	node->left->cmd->redirs->heredoc_eof = NULL;
	node->left->cmd->redirs->heredoc_content = NULL;
	exec_main(node, envp);
	// // pipe Node
	// node->left = ft_calloc(1, sizeof(t_ast));
	// node->left->type = NODE_PIPE;

	// // pipe == left node
	// node->left->left = ft_calloc(1, sizeof(t_ast));
	// node->left->left->type = NODE_COMMAND;
	// node->left->left->cmd = malloc(sizeof(t_cmd));
	// node->left->left->cmd->argv = malloc(2 * sizeof(char *));
	// node->left->left->cmd->argv[0] = malloc(5 * sizeof(char));
	// node->left->left->cmd->argv[0] = "echo";
	// node->left->left->cmd->argv[0] = malloc(6 * sizeof(char));
	// node->left->left->cmd->argv[0] = "hello";
	// node->left->left->cmd->argc = 2;
	//
	// exec_main(node, envp);

	// // pipe == right node
	// node->left->right->type = NODE_COMMAND;
	// node->left->right->cmd->argv = malloc(2 * sizeof(char *));
	// node->left->right->cmd->argv[0] = malloc(3 * sizeof(char));
	// node->left->right->cmd->argv[0] = "cat";
	// node->left->right->cmd->argv[0] = malloc(2 * sizeof(char));
	// node->left->right->cmd->argv[0] = "-e";
	// node->left->right->cmd->argc = 2;
}
