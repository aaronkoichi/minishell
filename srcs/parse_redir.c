/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthiew <jthiew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 19:46:29 by jthiew            #+#    #+#             */
/*   Updated: 2025/05/26 12:55:01 by jthiew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*append_line(char *content, char *input, int ind)
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

char	*get_hdoc_content(char *eof)
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
		input = readline("heredoc>");
		if (input == NULL)
		{
			free(content);
			return (NULL);
		}
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

const t_redir_map	*get_redir_map(void)
{
	static const t_redir_map	table[] = {
	{TOKEN_APPEND, REDIR_APPEND},
	{TOKEN_REDIR_IN, REDIR_IN},
	{TOKEN_REDIR_OUT, REDIR_OUT},
	{TOKEN_HEREDOC, REDIR_HEREDOC},
	{TOKEN_EOF, 0}
	};

	return (table);
}

static const t_redir_map	*match_redir(const t_redir_map *table,
								t_token_type type)
{
	while (table->token_type != TOKEN_EOF)
	{
		if (table->token_type == type)
			return (table);
		table++;
	}
	return (NULL);
}

t_redir_type	get_redir_type(t_token *token)
{
	const t_redir_map	*match;

	match = match_redir(get_redir_map(), token->type);
	if (match != NULL)
		return (match->redir_type);
	else
		return (0);
}
