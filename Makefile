NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX_PATH = /usr/include/minilibx-linux
MLXFLAGS = -L$(MLX_PATH) -lmlx_Linux -lXext -lX11
LIBFT = not_your_libft/libft.a
PRINTF = not_your_printf/libftprintf.a

SRCS = FIGHTERS/main.c FIGHTERS/map.c FIGHTERS/graphics.c FIGHTERS/movement.c FIGHTERS/validation.c \
       PILLARS/map_support.c PILLARS/map_support2.c \
       PILLARS/graphics_support.c PILLARS/movement_support.c PILLARS/validation_support.c
OBJS = $(SRCS:.c=.o)

all: do_build
	@echo "\033[1;32m🐺 So_long Built Successfully! 🐺\033[0m"

do_build: $(OBJS) $(LIBFT) $(PRINTF)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT) $(PRINTF) $(MLXFLAGS)

%.o: %.c
	@$(CC) $(CFLAGS) -I$(MLX_PATH) -c $< -o $@

$(LIBFT):
	@make -s -C not_your_libft

$(PRINTF):
	@make -s -C not_your_printf

clean: do_clean
	@echo "\033[1;31m🐺 Cleaned Successfully! 🐺\033[0m"

do_clean:
	@rm -f $(OBJS)
	@make -s -C not_your_libft clean
	@make -s -C not_your_printf clean

fclean: do_fclean
	@echo "\033[1;33m🐺 Force Cleaned Successfully! 🐺\033[0m"

do_fclean: do_clean
	@rm -f $(NAME)
	@make -s -C not_your_libft fclean
	@make -s -C not_your_printf fclean

re: do_fclean do_build
	@echo "\033[1;34m🐺 Rebuilt Successfully! 🐺\033[0m"

.PHONY: all clean fclean re do_build do_clean do_fclean