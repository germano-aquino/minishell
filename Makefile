# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/24 19:19:45 by grenato-          #+#    #+#              #
#    Updated: 2022/09/21 15:47:36 by maolivei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				:= minishell

HEADER_PATH			:= inc
HEADER_FILES		:= minishell.h internals.h

SOURCE_DIRS			:= .
SOURCE_DIRS			+= builtins execute hash_table heredoc input lexer prompt
SOURCE_DIRS			+= signal tokenizer utils
SOURCE_PATH			:= $(addprefix src/, $(SOURCE_DIRS))
SOURCE_FILES		:= main.c
SOURCE_FILES		+= builtin_cd.c builtin_env.c builtin_pwd.c builtin_echo.c
SOURCE_FILES		+= builtin_export.c builtin_unset.c builtin_exit.c
SOURCE_FILES		+= builtin_utils.c
SOURCE_FILES		+= builtin_execution.c child_routine.c child_utils.c
SOURCE_FILES		+= command_execution.c parent_routine.c set_wstatus.c
SOURCE_FILES		+= wait_utils.c
SOURCE_FILES		+= enviroment_variable.c get_env_from_ht.c hash_table.c
SOURCE_FILES		+= hash_table_utils.c
SOURCE_FILES		+= heredoc.c heredoc_signals.c
SOURCE_FILES		+= buff_to_input.c input.c input_utils.c
SOURCE_FILES		+= lexer.c lexer_cmd.c lexer_io.c lexer_subsh.c
SOURCE_FILES		+= lexer_connector.c create_program.c
SOURCE_FILES		+= minishell.c prompt.c redisplay.c shell_loop.c
SOURCE_FILES		+= dead_child.c signal.c
SOURCE_FILES		+= dollar_handler.c tokenizer.c tokens_handler.c
SOURCE_FILES		+= wildcard_dir_objs.c wildcard_handler.c
SOURCE_FILES		+= dup.c error.c free.c init.c syntax_error.c
SOURCE_FILES		+= token_checker.c utils.c validation.c

LIBFT_PATH			:= libft
LIBFT				:= $(LIBFT_PATH)/libft.a

OBJECT_PATH			:= obj
OBJECT				:= $(SOURCE_FILES:%.c=$(OBJECT_PATH)/%.o)

CC					:= cc
CFLAGS				:= -Wall -Wextra -Werror
REMOVE				:= rm -rf
VALGRIND			:= valgrind
LDFLAGS				:= -L $(LIBFT_PATH) -lft -lreadline
IFLAGS				:= -I $(HEADER_PATH)
VGFLAGS				:= --leak-check=full --show-leak-kinds=all
VGFLAGS				+= --trace-children=yes --track-fds=yes
VGSUPRESS			:= --suppressions=readline.supp

vpath				%.c $(SOURCE_PATH)
vpath				%.h $(HEADER_PATH)

ifdef C_DEBUG
	CFLAGS += -g3
endif

all:				$(NAME)

$(OBJECT_PATH)/%.o:	%.c $(HEADER_FILES) Makefile | $(OBJECT_PATH)
					$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(NAME):			$(OBJECT_PATH) $(LIBFT) $(OBJECT)
					$(CC) $(CFLAGS) -o $@ $(OBJECT) $(LDFLAGS)

$(LIBFT):
					$(MAKE) -C $(LIBFT_PATH)

$(OBJECT_PATH):
					mkdir -p $@

clean:
					$(REMOVE) $(OBJECT_PATH)
					$(MAKE) -C $(LIBFT_PATH) clean

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
