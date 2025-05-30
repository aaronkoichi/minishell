/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthiew <jthiew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 19:45:16 by jthiew            #+#    #+#             */
/*   Updated: 2025/05/29 14:26:01 by jthiew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_cmd_argc(t_token *token, t_cmd *cmd)
{
	int	total_size;

	total_size = 0;
	while (token != NULL && (is_token_redirs(token) == true
			|| token->type == TOKEN_WORD))
	{
		total_size++;
		token = token->next;
	}
	return (total_size - (cmd->redir_count * 2));
}

char	**get_cmd_argv(t_token *token, t_cmd *cmd)
{
	char	**argv;
	int		i;

	argv = malloc((cmd->argc + 1) * sizeof(char *));
	if (argv == NULL)
		return (NULL);
	i = 0;
	while (i < cmd->argc || is_token_redirs(token) == true)
	{
		if (is_token_redirs(token) == true)
			token = token->next->next;
		else
		{
			argv[i] = token->content;
			i++;
			token = token->next;
		}
	}
	argv[i] = NULL;
	return (argv);
}

int	create_and_add_redir(t_token **token, t_redir **head)
{
	t_redir	*redir;

	redir = create_redir_node(token);
	if (redir == NULL)
	{
		ft_lstclear_redir(head);
		return (1);
	}
	ft_lstadd_back_redir(head, redir);
	return (0);
}

t_redir	*get_cmd_redirs(t_token *token, t_cmd *cmd)
{
	t_redir	*head;

	head = NULL;
	while (token != NULL && (is_token_redirs(token) == true
			|| token->type == TOKEN_WORD))
	{
		if (is_token_redirs(token) == true)
		{
			cmd->redir_count++;
			if (create_and_add_redir(&token, &head) == 1)
				return (NULL);
		}
		token = token->next;
	}
	return (head);
}

t_cmd	*init_cmd(t_token *token)
{
	t_cmd	*cmd;

	cmd = malloc(1 * sizeof(t_cmd));
	if (cmd == NULL)
		return (NULL);
	cmd->redir_count = 0;
	cmd->redirs = get_cmd_redirs(token, cmd);
	if (cmd->redirs == NULL && cmd->redir_count != 0)
	{
		free(cmd);
		return (NULL);
	}
	cmd->argc = get_cmd_argc(token, cmd);
	cmd->argv = get_cmd_argv(token, cmd);
	if (cmd->argv == NULL)
	{
		ft_lstclear_redir(&cmd->redirs);
		free(cmd);
		return (NULL);
	}
	return (cmd);
}
