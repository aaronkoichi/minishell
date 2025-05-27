/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthiew <jthiew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:49:35 by jthiew            #+#    #+#             */
/*   Updated: 2025/05/27 11:52:38 by jthiew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ------------------------- test print token ---------------------------------
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
// ----------------------------------------------------------------------------

// -------------------------- test print tree ---------------------------------
#define ANSI_RESET   "\033[0m"
#define ANSI_RED     "\033[1;31m"
#define ANSI_GREEN   "\033[1;32m"
#define ANSI_YELLOW  "\033[1;33m"
#define ANSI_BLUE    "\033[1;34m"
#define ANSI_MAGENTA "\033[1;35m"
#define ANSI_CYAN    "\033[1;36m"
#define ANSI_WHITE   "\033[1;37m"

char *get_color(int level)
{
	static char *colors[] = {
		ANSI_RED, ANSI_GREEN, ANSI_YELLOW,
		ANSI_BLUE, ANSI_MAGENTA, ANSI_CYAN,
		ANSI_RED, ANSI_GREEN, ANSI_YELLOW,
		ANSI_BLUE, ANSI_MAGENTA, ANSI_CYAN
	};
	int count;

	count = sizeof(colors) / sizeof(colors[0]);
	return (colors[level % count]);
}

const char *node_type_to_str(t_node_type type)
{
	if (type == NODE_ROOT)
		return ("ROOT");
	else if (type == NODE_COMMAND)
		return ("COMMAND");
	else if (type == NODE_PIPE)
		return ("PIPE");
	else if (type == NODE_AND)
		return ("AND");
	else if (type == NODE_OR)
		return ("OR");
	else if (type == NODE_SEQUENCE)
		return ("SEQUENCE");
	else if (type == NODE_SUBSHELL)
		return ("SUBSHELL");
	else
		return ("UNKNOWN");
}

void print_ast_node(t_ast *node, int level, const char *prefix, int is_last);

char	*redir_type_to_str(t_redir_type type)
{
	if (type == REDIR_IN)
		return ("REDIR_IN");
	else if (type == REDIR_OUT)
		return ("REDIR OUT");
	else if (type == REDIR_HEREDOC)
		return ("HEREDOC");
	else
		return ("APPEND");
}

void print_redirs(t_redir *redir, const char *prefix)
{
	int		pad_len;
	int		i;
	char	*type_str;

	while (redir != NULL)
	{
		i = 0;
		pad_len = strlen(prefix);
		char pad[pad_len + 1];
		while (i < pad_len)
		{
			pad[i] = prefix[i];
			i++;
		}
		pad[i] = '\0';
		type_str = redir_type_to_str(redir->type);
		if (redir->filename != NULL)
			printf("%s   Redirection: %s -> %s\n",
				pad, type_str, redir->filename);
		else
		{
			printf("%s   Redirection: %s -> %s\n",
				pad, type_str, redir->heredoc_eof);
			printf("%s      Heredoc Content: %s\n",
				pad, redir->heredoc_content);
		}
		redir = redir->next;
	}
}

void print_command(t_cmd *cmd, const char *prefix, int is_last)
{
	int	i;

	i = 0;
	printf("%s%sCommand: ", prefix, is_last ? "└──" : "├──");
	while (i < cmd->argc)
	{
		printf("%s ", cmd->argv[i]);
		i++;
	}
	printf("\n");
	if (cmd->redirs != NULL)
		print_redirs(cmd->redirs, prefix);
}

void print_ast_node(t_ast *node, int level, const char *prefix, int is_last)
{
	char	*color;
	char	new_prefix[256];
	int		has_left;
	int		has_right;

	if (node == NULL)
		return ;
	color = get_color(level);
	printf("%s%s%sNode Type: %s%s\n", prefix, is_last ? "└──" : "├──", color,
		node_type_to_str(node->type), ANSI_RESET);
	snprintf(new_prefix, sizeof(new_prefix), "%s%s",
				prefix, is_last ? "   " : "│  ");
	if (node->type == NODE_COMMAND)
		print_command(node->cmd, new_prefix, 1);
	has_left = 0;
	has_right = 0;
	if (node->left != NULL)
		has_left = 1;
	if (node->right != NULL)
		has_right = 1;
	if (has_left == 1 && has_right == 1)
	{
		print_ast_node(node->left, level + 1, new_prefix, 0);
		print_ast_node(node->right, level + 1, new_prefix, 1);
	}
	else if (has_left == 1)
		print_ast_node(node->left, level + 1, new_prefix, 1);
	else if (has_right == 1)
		print_ast_node(node->right, level + 1, new_prefix, 1);
}

void test_print_ast_tree(t_ast *root) {
	printf("=== AST Tree ===\n");
	print_ast_node(root, 0, "", 1);
	printf("================\n");
}
// ---------------------------- test print tree --------------------

// bool	is_valid_tokens(t_token *token)
// {
// 	if (is_valid_case(token) == false || is_valid_redir(token) == false)
// 		// || is_valid_op(token) == false)
// 	{
// 		return (false);
// 	}
// 	return (true);
// }

int	main(int argc, char *argv[])
{
	char	*input;
	t_token	*token_list;
	t_ast	*ast_tree;

	(void)argv;
	(void)argc;
	while (1)
	{
		input = readline("minishell$ ");
		if (input == NULL)
			return (1);
		token_list = tokenize_str(input);
		if (token_list == NULL)
		{
			free(input);
			continue ;
		}
		test_print_tokens(token_list);
		// if (is_valid_tokens(token_list) == false)
		// {
		// 	free(input);
		// 	ft_lstclear_token(&token_list);
		// 	continue ;
		// }
		ast_tree = parse_token(token_list);
		if (ast_tree == NULL)
		{
			free(input);
			ft_lstclear_token(&token_list);
			continue ;
		}
		test_print_ast_tree(ast_tree);
		ft_lstclear_ast_tree(&ast_tree);
		ft_lstclear_token(&token_list);
		free(input);
		// start execute command
	}
	return (0);
}
