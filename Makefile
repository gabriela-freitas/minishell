GNL = get_next_line

NAME = minishell

SRC = $(GNL)/get_next_line.c $(GNL)/get_next_line_utils.c ./minishell.c

INC = -I . -I./get_next_line

#FLAGS = -Wall -Wextra -Werror

RM = rm -f

$(NAME):
	@ $(CC) $(INC) -L.local/lib -lreadline -D BUFFER_SIZE=10000 $(PRINTF) $(SRC) -o $(NAME)

all : $(NAME)

clean:
	@ $(RM) $(NAME)

fclean: clean

re: fclean all

.PHONY: clean fclean all re
