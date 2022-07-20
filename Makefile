# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/24 19:19:45 by grenato-          #+#    #+#              #
#    Updated: 2022/07/19 22:04:44 by maolivei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				= minishell

CC					= gcc
CFLAGS				= -g3 -O0 -Wall -Wextra #-Werror
LDFLAGS				= -lreadline
REMOVE				= rm -rf

HEADER_PATH			= inc
HEADER				= minishell.h

SOURCE_PATH			= src src/hash_table src/tokenizer src/lexer src/execute src/signal src/input \
					src/utils src/heredoc
SOURCE_FILES		= main.c tokenizer.c input.c input_utils.c hash_table.c hash_table_utils.c \
					lexer.c lexer_io.c lexer_cmd.c quotes_to_word.c tokens_handler.c utils.c \
					command_execution.c display.c free.c enviroment_variable.c signal.c heredoc.c

LIBFT_PATH			= libft
LIBFT				= libft/libft.a

OBJ_PATH			= obj
OBJ					= $(SOURCE_FILES:%.c=$(OBJ_PATH)/%.o)

vpath				%.c $(SOURCE_PATH)
vpath				%.h $(HEADER_PATH)

all:				$(NAME)

$(OBJ_PATH)/%.o:	%.c $(HEADER) Makefile | $(OBJ_PATH)
					$(CC) $(CFLAGS) -I $(HEADER_PATH) -c $< -o $@

$(NAME):			$(OBJ_PATH) $(LIBFT) $(OBJ)
					$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LDFLAGS) -o $@

$(LIBFT):
					$(MAKE) -C $(LIBFT_PATH)

$(OBJ_PATH):
					mkdir -p $(OBJ_PATH)

clean:
					$(REMOVE) $(OBJ)
					$(MAKE) -C ${LIBFT_PATH} clean

fclean:				clean
					$(REMOVE) $(NAME)
					$(MAKE) -C $(LIBFT_PATH) fclean

re:					fclean all

vg:					all
					valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all --trace-children=yes --track-fds=yes ./minishell

.PHONY:				all clean fclean re vg
