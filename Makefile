include src.mk

CC = cc
CFLAGS = -Wall -Wextra -Werror
OBJ_DIR = obj
LIBFT = ./libft
NAME = minishell
INCLUDE = -I./include
OBJECTS =$(patsubst src/%.c, obj/%.o, $(SRC))

all: libft $(NAME)


$(NAME): $(OBJECTS) $(LIBFT)/libft.a 
	$(CC) $(CFLAGS) $(OBJECTS) -L $(LIBFT) -lft -lreadline -o $(NAME)

libft:
	@make -C $(LIBFT)
obj/%.o: src/%.c
	@mkdir -p obj
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -rf obj
	@make clean -C $(LIBFT)

fclean: clean
	rm -f $(NAME)
	@make fclean -C $(LIBFT)

re: fclean all

.PHONY: all clean fclean re libft