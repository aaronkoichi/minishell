/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eof_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlee <zlee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:31:05 by zlee              #+#    #+#             */
/*   Updated: 2025/05/22 14:58:19 by zlee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "eof.h"

int	prompt_process(t_ast *node)
{
	char	**heredoc_ptr;
	char	**heredoc_EOF;
	char	*prompt;
	char	*temp;

	heredoc_ptr = &node->cmd->redirs->heredoc_content;
	*heredoc_ptr = malloc(sizeof(char));
	if (!*heredoc_ptr)
		return (1);
	prompt = NULL;
	heredoc_EOF = &node->cmd->redirs->heredoc_EOF;
	prompt = readline("heredok>> ");
	while (ft_strncmp(prompt, *heredoc_EOF, ft_strlen(prompt)) != 0)
	{
		temp = ft_strjoin(*heredoc_ptr, prompt);
		free(*heredoc_ptr);
		free(prompt);
		*heredoc_ptr = temp;
		prompt = readline("heredok>> ");
	}
	return (0);
}

int process_eof(t_ast *node)
{
	if (node->left != NULL)
		process_eof(node->left);
	else if (node->right != NULL)
		process_eof(node->right);
	if (node->cmd->redirs->type == REDIR_HEREDOC)
	{
		return (prompt_process(node));
	}
	return (0);
}
