/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthiew <jthiew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 19:46:29 by jthiew            #+#    #+#             */
/*   Updated: 2025/06/04 13:46:52 by jthiew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*append_line(char *content, char *input, int ind)
{
	char	*temp;
	char	*joined;

	if (ind != 0)
		temp = ft_strjoin("\n", input);
	else
		temp = ft_strjoin(input, "");
	if (temp == NULL)
	{
		free(input);
		free(content);
		return (NULL);
	}
	joined = ft_strjoin(content, temp);
	free(input);
	free(temp);
	free(content);
	if (joined == NULL)
		return (NULL);
	return (joined);
}

int	hdoc_handle_input(char *input, char **content, t_vars *vars)
{
	if (g_signal == 2)
	{
		g_signal = 0;
		free(*content);
		*content = NULL;
		vars->exit_code = 130;
		return (1);
	}
	if (input == NULL)
	{
		ft_putstr_fd("heredoc delimited by EOF\n", 1);
		g_signal = 0;
		return (1);
	}
	return (0);
}

char	*get_hdoc_input(char *eof, t_vars *vars)
{
	char	*content;
	char	*input;
	int		i;

	i = 0;
	content = ft_calloc(1, sizeof(char));
	if (content == NULL)
		return (NULL);
	while (1)
	{
		g_signal = 1;
		input = readline("heredoc> ");
		if (hdoc_handle_input(input, &content, vars) == 1)
			break ;
		g_signal = 0;
		if (ft_strncmp(input, eof, ft_strlen(eof) + 1) == 0)
			break ;
		content = append_line(content, input, i);
		if (content == NULL)
			return (NULL);
		i++;
	}
	free(input);
	return (content);
}

char	*get_hdoc_content(char *eof, t_vars *vars)
{
	char	*content;
	char	*eof_strip;

	eof_strip = strip_quotes_eof(eof);
	if (eof_strip == NULL)
		return (NULL);
	content = get_hdoc_input(eof_strip, vars);
	free(eof_strip);
	if (content == NULL)
		return (NULL);
	return (content);
}

t_redir	*create_redir_node(t_token **token, t_vars *vars)
{
	t_redir	*redir;

	if (is_parse_err(*token, vars) == true
		|| is_supported_redir(*token) == false)
		return (NULL);
	redir = ft_calloc(1, sizeof(t_redir));
	if (redir == NULL)
		return (NULL);
	redir->type = get_redir_type(*token);
	if ((*token)->type == TOKEN_HEREDOC)
	{
		redir->heredoc_eof = (*token)->next->content;
		redir->heredoc_content = get_hdoc_content(redir->heredoc_eof, vars);
		if (redir->heredoc_content == NULL)
		{
			free(redir);
			return (NULL);
		}
	}
	else
		redir->filename = (*token)->next->content;
	*token = (*token)->next;
	redir->next = NULL;
	return (redir);
}
