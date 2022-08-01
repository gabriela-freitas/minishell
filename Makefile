# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gafreita <gafreita@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/30 20:14:45 by gafreita          #+#    #+#              #
#    Updated: 2022/07/30 20:14:45 by gafreita         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = minishell.c

LIBFT_DIR = ./libft
INC = -I . -I ./libft/include/
LIB = -L ./libft -lft

CCFLAGS = gcc -Wall -Wextra -Werror

DEP = ./libft/libft.a

RM = rm -f

$(NAME): $(DEP)
	@ $(CCFLAGS) $(INC) -D BUFFER_SIZE=10000 $(SRC) $(LIB) -o $(NAME)

all : $(NAME)

clean:
	@ $(RM) $(NAME)

./libft/libft.a:
	@make -s -C $(LIBFT_DIR)

submodule:
	@git submodule update --init --recursive

fclean: clean

re: fclean all

.PHONY: clean fclean all re
