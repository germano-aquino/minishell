# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/24 19:19:45 by grenato-          #+#    #+#              #
#    Updated: 2022/07/10 14:49:05 by grenato-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# define the C compiler
#CC = clang
CC = gcc

# define any compile-time flags
#CFLAGS = -Wall -Wextra -Werror -fsanitize=address
CFLAGS = -g -O0 -Wall -Wextra

# library flags
LDFLAGS = -g -L. -lreadline

# name of the project
NAME = minishell

B_NAME = minishell

# name of include folder
INCLUDE = inc

INCLUDE_BONUS = inc_bonus

# name of source folder
SRC_DIR = src

BONUS_DIR = src_bonus
# name of libft folder
LIBFT_DIR = libft

UTILS_DIR = src/utils

LIBFT = libft/libft.a

HEADERS = -I/usr/include -I$(INCLUDE) -I$(LIBFT_DIR) -I$(INCLUDE_BONUS)

OBJ_DIR = obj
B_OBJ_DIR = obj_bonus

SOURCE_FILES = main.c tokenizer.c input.c input_utils.c hash_table.c hash_table_utils.c
SOURCE_FILES += lexer.c lexer_io.c lexer_cmd.c quotes_to_word.c tokens_handler.c utils.c
SOURCE_FILES += command_execution.c display.c free.c enviroment_variable.c

VPATH = src src/hash_table src/tokenizer src/lexer src/execute src/signal src/input
VPATH += src/utils 

#BONUS_FILES = 

#B_SOURCE = $(addprefix $(BONUS_DIR)/, $(BONUS_FILES))

OBJ = $(SOURCE_FILES:%.c=$(OBJ_DIR)/%.o)
#B_OBJ = $(B_SOURCE:$(BONUS_DIR)/%.c=$(B_OBJ_DIR)/%.o)

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

#$(B_OBJ_DIR)/%.o: $(BONUS_DIR)/%.c
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ_DIR) $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(HEADERS) $(OBJ) -o $(NAME) $(LIBFT) $(LDFLAGS)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(B_OBJ_DIR):
	mkdir -p $(B_OBJ_DIR)

bonus: $(B_NAME)

#$(B_NAME): $(B_OBJ_DIR) $(LIBFT) $(B_OBJ)
#	$(CC) $(CFLAGS) $(HEADERS) $(B_OBJ) -o $(B_NAME) $(LIBFT) $(LDFLAGS)

clean:
	rm -rf $(OBJ)
	rm -rf $(B_OBJ)
	$(MAKE) -C ${LIBFT_DIR} clean

fclean: clean
	rm -rf $(NAME)
	rm -rf $(B_NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./minishell
.PHONY: bonus clean fclean re