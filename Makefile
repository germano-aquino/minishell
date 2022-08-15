# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/24 19:19:45 by grenato-          #+#    #+#              #
#    Updated: 2022/08/15 12:02:44 by maolivei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				:= minishell

HEADER_PATH			:= inc
HEADER				:= minishell.h

SOURCE_DIRS			:= hash_table tokenizer lexer execute input utils heredoc builtins prompt
SOURCE_PATH			:= $(addprefix src/, $(SOURCE_DIRS))
SOURCE_FILES		:= main.c tokenizer.c input.c input_utils.c hash_table.c hash_table_utils.c
SOURCE_FILES		+= lexer.c lexer_io.c lexer_cmd.c dollar_handler.c tokens_handler.c utils.c
SOURCE_FILES		+= command_execution.c display.c free.c enviroment_variable.c signal.c heredoc.c
SOURCE_FILES		+= error.c builtin_utils.c builtin_exit.c builtin_echo.c builtin_export.c
SOURCE_FILES		+= builtin_env.c builtin_unset.c builtin_pwd.c builtin_cd.c builtin_execution.c
SOURCE_FILES		+= builtin_single_io.c pipes_and_pid.c bin_path_validation.c heredoc_signals.c
SOURCE_FILES		+= prompt.c init.c minishell.c get_env_from_ht.c

LIBFT_PATH			:= libft
LIBFT				:= libft/libft.a

OBJ_PATH			:= obj
OBJ					:= $(SOURCE_FILES:%.c=$(OBJ_PATH)/%.o)

CC					:= gcc
CFLAGS				:= -g3 -O0 -Wall -Wextra -Werror
REMOVE				:= rm -rf
VALGRIND			:= valgrind
LDFLAGS				:= -L $(LIBFT_PATH) -lft -lreadline
IFLAGS				:= -I $(HEADER_PATH)
VGFLAGS				:= --leak-check=full --show-leak-kinds=all --trace-children=yes --track-fds=yes
VGSUPRESS			:= --suppressions=readline.supp

vpath				%.c $(SOURCE_PATH)
vpath				%.h $(HEADER_PATH)

all:				$(NAME)

$(OBJ_PATH)/%.o:	%.c $(HEADER) Makefile | $(OBJ_PATH)
					$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(NAME):			$(OBJ_PATH) $(LIBFT) $(OBJ)
					$(CC) $(CFLAGS) -o $@ $(OBJ) $(LDFLAGS)

$(LIBFT):
					$(MAKE) -C $(LIBFT_PATH)

$(OBJ_PATH):
					mkdir -p $@

clean:
					$(REMOVE) $(OBJ)
					$(MAKE) -C ${LIBFT_PATH} clean

fclean:				clean
					$(REMOVE) $(NAME)
					$(MAKE) -C $(LIBFT_PATH) fclean

re:					fclean all

run:				all
					./$(NAME)

vg:					all
					$(VALGRIND) $(VGSUPRESS) $(VGFLAGS) ./$(NAME)

test:				all
					cd minishell_tester && ./tester

.PHONY:				all clean fclean re run vg test
