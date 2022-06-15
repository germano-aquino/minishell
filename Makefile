# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/24 19:19:45 by grenato-          #+#    #+#              #
#    Updated: 2022/06/15 01:55:49 by grenato-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# define the C compiler
#CC = clang
CC = gcc

# define any compile-time flags
#CFLAGS = -Wall -Wextra -Werror
CFLAGS = -g -Wall -Wextra

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

SOURCE_FILES = main.c tokenizer.c input.c

C_SOURCE = $(addprefix $(SRC_DIR)/, $(SOURCE_FILES))

#BONUS_FILES = 

#B_SOURCE = $(addprefix $(BONUS_DIR)/, $(BONUS_FILES))

OBJ = $(C_SOURCE:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
#B_OBJ = $(B_SOURCE:$(BONUS_DIR)/%.c=$(B_OBJ_DIR)/%.o)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(HEADERS) -O3 -c $< -o $@

#$(B_OBJ_DIR)/%.o: $(BONUS_DIR)/%.c
	$(CC) $(CFLAGS) $(HEADERS) -O3 -c $< -o $@

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

.PHONY: bonus clean fclean re