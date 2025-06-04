/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthiew <jthiew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:49:35 by jthiew            #+#    #+#             */
/*   Updated: 2025/06/04 17:42:10 by zlee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "execute.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <unistd.h>

// ------------------------- test print token ---------------------------------
int	ft_lstsize_token(t_token *lst)
{
	int	size;

	size = 0;
	while (lst != NULL)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}

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
	if (cmd->argc != 0)
	{
		printf("%s%sCommand: ", prefix, is_last ? "└──" : "├──");
		while (i < cmd->argc)
		{
			printf("%s ", cmd->argv[i]);
			i++;
		}
		printf("\n");
	}
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
	if (node->type == NODE_SUBSHELL && node->cmd->redirs != NULL)
		print_redirs(node->cmd->redirs, prefix);
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

// Limitations of minishell:
// - does not handle unclosed quotes
// 	(return NULL for token->content)
//
// - does not handle line continuation, a.k.a backslash character --> '\'
// 	(treat as valid word character)
//
// - does not handle commenting --> '#'
//	(treat as valid word character)
//
// - does not handle command ending with list delimiters --> '|', '&', ';', etc
// 	(return NULL for ast_tree node, parsing error)
//
// - does not handle here_string redirection --> "<<<"
// 	(return NULL for redir node, parsing error)
//
// - does not handle fd_in & fd_out redirection --> "<&", ">&"
// 	(return NULL for redir node, parsing error)
//
// - does not handle async execution --> '&'
// 	(return NULL for ast_tree node, parsing error)
//
// - does not handle unclosed parenthesis
// 	(return NULL for ast_tree node, parsing error)
//
// - does not handle arithmetic expansion
// 	(treat as subshell in another subshell)
//
// - does not handle brace expansion
//	(treat as valid word character)
//
// - does not handle tilde expansion
//	(treat as valid word character)
//
// - does not handle command substitution
//	(treat as valid word character followed by subshell)
//
// - does not handle word splitting
//	(non-existent behaviour)
//
// - does not handle case conditional construct --> case `word' in
//	(non-existent behaviour)
//
// - does not handle loops --> `while', `for'
//	(non-existent behaviour)

volatile sig_atomic_t	g_signal = 0;
// TODO: $? exit code 130 for SIGINT --> ctrl + c
// TODO: use reset_signal() function in child process before execution
// TODO: reset fds in exec_main() before coming back to readline input gathering
// TODO: store vars->exit_code after execution

t_ast	*parse_input(t_token **token_list, char *input, t_vars *vars)
{
	t_ast	*ast_tree;

	*token_list = tokenize_str(input);
	if (token_list == NULL)
	{
		free(input);
		return (NULL);
	}
	vars->token_list = *token_list;
	test_print_tokens(*token_list);
	ast_tree = parse_token(*token_list);
	if (ast_tree == NULL)
	{
		free(input);
		ft_lstclear_token(token_list);
		return (NULL);
	}
	vars->ast_tree = ast_tree;
	test_print_ast_tree(ast_tree);
	return (ast_tree);
}

// void	start_usr_input(char *envp[])
void	start_usr_input(t_vars *vars)
{
	char	*input;
	t_token	*token_list;
	t_ast	*ast_tree;

	while (1)
	{
		set_signal_interact();
		input = readline("minishell$ ");
		if (input == NULL)
			break ;
		add_history(input);
		ast_tree = parse_input(&token_list, input, vars);
		set_signal_noninteract();
		if (ast_tree == NULL)
			continue ;
		exec_main(vars->ast_tree, vars);
		ft_lstclear_ast_tree(&ast_tree);
		ft_lstclear_token(&token_list);
		free(input);
	}
	rl_clear_history();
}

int	main(int argc, char *argv[], char *envp[])
{
	int		i;
	t_vars	vars;

	if (argc != 1)
	{
		ft_putstr_fd("Error: Usage: ./minishell\n", 2);
		return (1);
	}
	rl_catch_signals = 0;
	init_vars(&vars, envp);
	i = 0;
	while (envp[i])
		i++;
	(void)argv;
	(void)argc;
	(void)envp;
	// envp = dup_envp(envp, i);
	start_usr_input(&vars);
	destroy_vars(&vars);
	// start_usr_input(envp);
	return (0);
}
