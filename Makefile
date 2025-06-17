# CC_ASAN = cc -g -fsanitize=address
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

NAME = ./minishell
HEADERS_DIR = ./includes/
HEADERS_LIST = minishell.h
HEADERS = $(addprefix $(HEADERS_DIR), $(HEADERS_LIST))
INCLUDES = -I$(HEADERS_DIR) -I$(LIBFT_INCLUDES)

SRCS_DIR = ./srcs/
SRCS = $(addprefix $(SRCS_DIR), $(SRCS_LIST))
SRCS_LIST = main.c					\
			env_list.c				\
			env_list_utils.c		\
			parse_cmd.c				\
			parse_rdp_1.c			\
			parse_rdp_2.c			\
			parse_redir.c			\
			parse_redir_type.c		\
			parse_redir_utils.c		\
			parse_utils.c			\
			signal.c				\
			token.c					\
			token_symbol.c			\
			token_utils.c			\
			token_word.c			\
			exec_main.c				\
			exec_parse_cmd.c 		\
			exec_parse_cmd_redirs.c \
			exec_pipe.c				\
			exec_utils.c			\
			prep_cmd.c				\
			vars.c					\
			builtin.c				\
			builtin_cd.c			\
			builtin_cd_utils.c		\
			builtin_echo.c			\
			builtin_exit.c			\
			builtin_env.c			\
			builtin_export.c		\
			builtin_export_prt.c	\
			builtin_pwd.c			\
			builtin_unset.c			\
			wildcard.c 				\
			wildcard_fnmatch.c		\
			wildcard_utils.c		\

OBJS_DIR = objs
OBJS = $(SRCS_LIST:.c=.o)
OBJS_PATH = $(addprefix $(OBJS_DIR)/, $(OBJS))

LIBFT_PATH = ./libft
LIBFT_INCLUDES = ./libft/includes
LIBFT = $(LIBFT_PATH)/libft.a

$(OBJS_DIR)/%.o: $(SRCS_DIR)%.c
	@$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS_DIR) $(OBJS_PATH)
	@$(CC) $(CFLAGS) $(OBJS_PATH) -lreadline -ltermcap $(LIBFT) -o $(NAME)
	@echo "$(NAME) created"

$(LIBFT):
	@make -C $(LIBFT_PATH) all

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)
	@echo "obj dir created"

clean:
	@make -C $(LIBFT_PATH) clean
	@rm -rf $(OBJS_DIR)
	@echo "removed obj dir"

fclean: clean
	@make -C $(LIBFT_PATH) fclean
	@rm -rf $(NAME)
	@echo "removed $(NAME)"

re: fclean all

.PHONY: all clean fclean re libft
