/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthiew <jthiew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 19:45:16 by jthiew            #+#    #+#             */
/*   Updated: 2025/05/26 12:54:18 by jthiew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_cmd_argc(t_token *token, t_cmd *cmd)
{
	int	total_size;
	int	redir_size;

	redir_size = ft_lstsize_redir(cmd->redirs) * 2;
	total_size = 0;
	while (token != NULL && (is_token_redirs(token) == true
			|| token->type == TOKEN_WORD))
	{
		total_size++;
		token = token->next;
	}
	return (total_size - redir_size);
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

t_redir	*create_redir_node(t_token **token)
{
	t_redir	*redir;
	t_token	*temp;

	temp = *token;
	redir = ft_calloc(1, sizeof(t_redir));
	if (redir == NULL)
		return (NULL);
	redir->type = get_redir_type(temp);
	*token = (*token)->next;
	if (temp->type != TOKEN_HEREDOC)
		redir->filename = (*token)->content;
	else
	{
		redir->heredoc_eof = (*token)->content;
		redir->heredoc_content = get_hdoc_content(redir->heredoc_eof);
		if (redir->heredoc_content == NULL)
		{
			free(redir);
			return (NULL);
		}
	}
	redir->next = NULL;
	return (redir);
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
			if (cmd->redir_count == -1)
				cmd->redir_count = 0;
			cmd->redir_count++;
			if (create_and_add_redir(&token, &head) == 1)
				return (NULL);
		}
		token = token->next;
	}
	return (head);
}
