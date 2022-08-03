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

SRC =	srcs/minishell.c \
		srcs/parsing/parsing.c \
		srcs/environment.c \
		srcs/first_parse.c

LIBFT_DIR = ./libft
INC = -I . -I ./libft/include/
LIB = -L ./libft -lft -lreadline

CCFLAGS = gcc -Wall -Wextra -Werror

DEP = ./libft/libft.a

RM = rm -f

COLOUR_GREEN=\033[7;1;32m
COLOUR_YELLOW=\033[7;1;33m
COLOUR_END=\033[0m

$(NAME): $(DEP) $(OBJS)
	@ $(CCFLAGS) $(INC) $(SRC) $(LIB) -o $(NAME)
	@echo "$(COLOUR_GREEN) minishell is ready to use $(COLOUR_END)"

all : $(NAME)

clean:
	@ $(RM) $(NAME)

./libft/libft.a:
	@make -s -C $(LIBFT_DIR)

submodule:
	@git submodule update --init --recursive

fclean: clean
	@make fclean -s -C $(LIBFT_DIR)
	@echo "$(COLOUR_YELLOW) minishell cleaned $(COLOUR_END)"


re: fclean all

.PHONY: clean fclean all re
