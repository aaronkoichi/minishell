/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthiew <jthiew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:49:35 by jthiew            #+#    #+#             */
/*   Updated: 2025/05/22 13:16:27 by jthiew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	test_print_tokens(t_token *token_list)
{
	int	i;

	i = 0;
	printf("num token [%d]\n", ft_lstsize_token(token_list));
	while (token_list != NULL)
	{
		printf("token [%d], content = [%s]\n", i, token_list->content);
		i++;
		token_list = token_list->next;
	}
}

int	main(int argc, char *argv[])
{
	char	*input;
	t_token	*token_list;
	// t_ast	*ast_tree;

	(void)argv;
	(void)argc;
	input = readline("minishell>");
	token_list = tokenize_str(input);
	if (token_list == NULL)
	{
		free(input);
		return (1);
	}
	test_print_tokens(token_list);
	// ast_tree = parse_token(&token_list);
	ft_lstclear_token(&token_list);
	free(input);
	// parse tokens, put into AST
	// start execute command
	return (0);
}
