NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror -I./minilibx-linux
SRC = FIGHTERS/main.c FIGHTERS/map.c FIGHTERS/movement.c FIGHTERS/render.c FIGHTERS/validation.c
OBJ = $(SRC:.c=.o)
MLX_FLAGS = -L./minilibx-linux -lmlx -lXext -lX11 -lm

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(MLX_FLAGS) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re