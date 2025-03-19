NAME = so_long

SRC =	FIGHTERS/main.c \
		FIGHTERS/map.c \
		FIGHTERS/movement.c \
		FIGHTERS/render.c \
		FIGHTERS/validation.c

OBJ = $(SRC:.c=.o)

MLX_LIB = ./minilibx-linux/libmlx.a
PRINTF_LIB = ./not_your_printf/libftprintf.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -I./minilibx-linux -I./not_your_printf
LDFLAGS = -L./minilibx-linux -lmlx -L./not_your_printf -lftprintf -lXext -lX11 -lm

REBUILDING = 0

all: $(NAME)

$(NAME): $(OBJ) $(MLX_LIB) $(PRINTF_LIB)
	@$(CC) $(OBJ) $(LDFLAGS) -o $(NAME)
	@if [ $(REBUILDING) -eq 0 ]; then \
		printf "\033[1;32m🐺 So_long Built Successfully! 🐺\033[0m\n"; \
	fi

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(MLX_LIB):
	@make -s -C ./minilibx-linux > /dev/null 2>&1

$(PRINTF_LIB):
	@make -s -C ./not_your_printf

clean:
	@rm -f $(OBJ)
	@make -s -C ./minilibx-linux clean > /dev/null 2>&1
	@make -s -C ./not_your_printf clean
	@if [ $(REBUILDING) -eq 0 ] && [ "$(MAKECMDGOALS)" = "clean" ]; then \
		printf "\033[1;31m🐺 Cleaned Successfully! 🐺\033[0m\n"; \
	fi

fclean: clean
	@rm -f $(NAME)
	@make -s -C ./not_your_printf fclean
	@if [ $(REBUILDING) -eq 0 ] && [ "$(MAKECMDGOALS)" = "fclean" ]; then \
		printf "\033[1;33m🐺 Force Cleaned Successfully! 🐺\033[0m\n"; \
	fi

re:
	@$(MAKE) --no-print-directory fclean REBUILDING=1
	@$(MAKE) --no-print-directory all REBUILDING=0
	@printf "\033[1;34m🐺 Rebuilt Successfully! 🐺\033[0m\n"

.PHONY: all clean fclean re