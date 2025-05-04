include src.mk

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
OBJ_DIR = obj
LIBFT = ./libft
NAME = minishell
INCLUDE = -I./include

# Generate obj/*.o from src/*.c
OBJECTS = $(patsubst src/%.c, $(OBJ_DIR)/%.o, $(SRC))

all: libft $(NAME)

$(NAME): $(OBJECTS) $(LIBFT)/libft.a 
	$(CC) $(CFLAGS) $(OBJECTS) -L $(LIBFT) -lft -lreadline -lncurses -o $(NAME)

libft:
	@make -C $(LIBFT)

# Compile rule with automatic directory creation
$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	@make clean -C $(LIBFT)

fclean: clean
	rm -f $(NAME)
	@make fclean -C $(LIBFT)

re: fclean all

.PHONY: all clean fclean re libft
