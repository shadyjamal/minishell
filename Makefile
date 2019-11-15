NAME = minishell

DIR_LFT = libft

FLAGS = -Wall -Werror -Wextra -g

SRC = $(wildcard srcs/*.c)

INC = -Iincludes/

CC = gcc

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft/
	@$(CC) $(FLAGS) $(INC) $(OBJ) -L$(DIR_LFT) -lft -o $(NAME)

srcs/%.o: srcs/%.c
	@echo "$^->$@"
	@$(CC) $(FLAGS) $(INC) -c $< -o $@

clean:
	@(echo "Delete .o of $(NAME) and Libft")
	@/bin/rm -f $(OBJ)
	@(cd $(DIR_LFT) && make clean)

fclean: clean
	@(echo "Delete .o and $(NAME)")
	@/bin/rm -f $(NAME)
	@(cd $(DIR_LFT) && make fclean)

re: fclean all