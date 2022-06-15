# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: grenato- <grenato-@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/24 19:19:45 by grenato-          #+#    #+#              #
#    Updated: 2022/06/07 22:51:43 by grenato-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# $(NAME), all, clean, fclean and re.
# define the C compiler
#CC = clang
CC = gcc

# define any compile-time flags
#CFLAGS = -Wall -Wextra -Werror
CFLAGS = -Wall -Wextra -g

# library flags
LDFLAGS = -L. -g

# name of the project
NAME = libft.a

# name of include folder
INCLUDE = inc

# name of source folder
SRC_DIR = src ft_printf

HEADERS = -I/usr/include -I$(INCLUDE)

OBJ_DIR = obj

SOURCES =	src/ft_atoi.c\
			src/ft_bzero.c\
			src/ft_calloc.c\
			src/ft_isalnum.c\
			src/ft_isalpha.c\
			src/ft_isascii.c\
			src/ft_isdigit.c\
			src/ft_isprint.c\
			src/ft_itoa.c\
			src/ft_memccpy.c\
			src/ft_memchr.c\
			src/ft_memcmp.c\
			src/ft_memcpy.c\
			src/ft_memmove.c\
			src/ft_memset.c\
			src/ft_putchar_fd.c\
			src/ft_putendl_fd.c\
			src/ft_putnbr_fd.c\
			src/ft_putstr_fd.c\
			src/ft_split.c\
			src/ft_strchr.c\
			src/ft_strdup.c\
			src/ft_striteri.c\
			src/ft_strjoin.c\
			src/ft_strlcat.c\
			src/ft_strlcpy.c\
			src/ft_strlen.c\
			src/ft_strmapi.c\
			src/ft_strncmp.c\
			src/ft_strnstr.c\
			src/ft_strrchr.c\
			src/ft_strtrim.c\
			src/ft_substr.c\
			src/ft_tolower.c\
			src/ft_toupper.c\
			src/ft_lstadd_back.c\
			src/ft_lstadd_front.c\
			src/ft_lstclear.c\
			src/ft_lstdelone.c\
			src/ft_lstiter.c\
			src/ft_lstlast.c\
			src/ft_lstmap.c\
			src/ft_lstnew.c\
			src/ft_lstsize.c\
			src/get_next_line.c\
			ft_printf/ft_printf.c\
			ft_printf/print_address.c\
			ft_printf/print_number.c\
			ft_printf/print_words.c

OBJECTS = $(addprefix $(OBJ_DIR)/, $(notdir $(SOURCES:%.c=%.o)))

$(OBJ_DIR)/%.o: */%.c $(OBJ_DIR)
	$(CC) $(CFLAGS) $(HEADERS) -O3 -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJECTS)
	ar rcs $(NAME) $(OBJECTS)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)/ft_printf

clean:
	rm -rf $(OBJECTS)

fclean: clean
	rm -rf ${NAME}

re: fclean all