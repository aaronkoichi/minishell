/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rdp_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthiew <jthiew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 19:48:16 by jthiew            #+#    #+#             */
/*   Updated: 2025/05/26 12:16:34 by jthiew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*init_cmd(t_token *token)
{
	t_cmd	*cmd;

	cmd = malloc(1 * sizeof(t_cmd));
	if (cmd == NULL)
		return (NULL);
	cmd->redir_count = -1;
	cmd->redirs = get_cmd_redirs(token, cmd);
	if (cmd->redirs == NULL && cmd->redir_count != -1)
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

t_cmd	*parse_cmd(t_token **token)
{
	t_cmd	*cmd;

	cmd = init_cmd(*token);
	if (cmd == NULL)
		return (NULL);
	while (token != NULL && (is_token_redirs(*token) == true
			|| (*token)->type == TOKEN_WORD))
		*token = (*token)->next;
	return (cmd);
}

t_ast	*parse_subshell(t_token **token)
{
	t_ast	*subshell;

	*token = (*token)->next;
	subshell = parse_or(token);
	if ((*token)->type != TOKEN_RPAREN)
		return (NULL);
	*token = (*token)->next;
	return (create_ast_node(NODE_SUBSHELL, subshell, NULL, NULL));
}

t_ast	*parse_cmd_or_subshell(t_token **token)
{
	t_cmd	*cmd;

	if ((*token)->type == TOKEN_LPAREN)
		return (parse_subshell(token));
	cmd = parse_cmd(token);
	if (cmd == NULL)
		return (NULL);
	return (create_ast_node(NODE_COMMAND, NULL, NULL, cmd));
}
