# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ccamargo <ccamargo@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/20 19:31:21 by mcarecho          #+#    #+#              #
#    Updated: 2023/05/21 17:43:57 by ccamargo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell

LIBFT_DIR		= ./libs/libft/
LIBFT 			= $(LIBFT_DIR)/libft.a
HEADER_LIBFT	= $(addprefix $(LIBFT_DIR), include/)

HEADER_DIR		= ./include/
HEADER			= minishell.h
HEADER_PATH		= $(addprefix $(HEADER_DIR), $(HEADER))

SRC_DIR			= ./src/
SRC				=	main.c \
					closing/close_utils.c \
					errors/errors.c \
					errors/errors_2.c \
					initialization/initialization_utils.c \
					signals/signals_utils.c \
					signals/signals_utils_2.c \
					utils/cmd_var_expansion.c \
					utils/cmd_var_expansion_2.c \
					utils/shell_utils.c \
					utils/token_utils.c \
					tokenization/token.c \
					tokenization/split_cmd.c \
					tokenization/parser.c \
					tokenization/normalize_lexer.c \
					tokenization/lexer.c \
					tokenization/check_symbol.c \
					builtins/built_in_parser.c \
					builtins/cd_built_in.c \
					builtins/echo_built_in.c \
					builtins/env_built_in.c \
					builtins/exit_built_in.c \
					builtins/export_built_in.c \
					builtins/export_built_in_2.c \
					builtins/pwd_built_in.c \
					builtins/unset_built_in.c \
					execution/redirect_infile.c \
					execution/redirect_output.c \
					execution/run_command.c \
					execution/set_fds.c \
					execution/token_execution.c

SRC_PATH		= $(addprefix $(SRC_DIR), $(SRC))

CC				= gcc
CFLAGS			= -Wall -Wextra -Werror
CLINK			= -lft -lreadline

BIN				= ./bin/
BINARY_OUT		= $(addprefix $(BIN), $(NAME))

all: $(BINARY_OUT)

$(BINARY_OUT): $(SRC_PATH) $(HEADER_PATH)
	@ $(MAKE) -C $(LIBFT_DIR)
	@ cp $(LIBFT) $(NAME)
	@ mkdir -p $(BIN)
	@ $(CC) $(CFLAGS) $(SRC_PATH) -I $(HEADER_DIR) -I $(HEADER_LIBFT) -L $(LIBFT_DIR) $(CLINK) -o $(NAME)
	@ mv $(NAME) $(BIN)
	@ echo "$(NAME) compiled successfully!"

clean:
	@ $(MAKE) clean -C $(LIBFT_DIR)
	@ echo "libft object files erased successfully!"

fclean: clean
	@ $(MAKE) fclean -C $(LIBFT_DIR)
	@ rm -f $(BINARY_OUT)
	@ rm -rf $(BIN)
	@ echo "$(NAME) binaries erased successfully!"
	@ rm -f $(BINARY_OUT_BONUS)
	@ rm -rf $(BIN_BONUS)
	@ echo "$(NAME_BONUS) binaries erased successfully!"

re: fclean all

leaks:
	@ $(MAKE) -C $(LIBFT_DIR)
	@ cp $(LIBFT) $(NAME)
	@ mkdir -p $(BIN)
	@ $(CC) $(CFLAGS) -g $(SRC_PATH) -I $(HEADER_DIR) -I $(HEADER_LIBFT) -L $(LIBFT_DIR) $(CLINK) -o $(NAME)
	@ mv $(NAME) $(BIN)
	@ echo "$(NAME) with leak check option compiled successfully!"

simple:
	@ $(MAKE) -C $(LIBFT_DIR)
	@ cp $(LIBFT) $(NAME)
	@ mkdir -p $(BIN)
	@ $(CC) -g $(SRC_PATH) -I $(HEADER_DIR) -I $(HEADER_LIBFT) -L $(LIBFT_DIR) $(CLINK) -o $(NAME)
	@ mv $(NAME) $(BIN)
	@ echo "$(NAME) without compile flags compiled successfully!"

.PHONY: all clean fclean re
