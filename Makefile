NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX_PATH = /usr/include/minilibx-linux
MLXFLAGS = -L$(MLX_PATH) -lmlx_Linux -lXext -lX11
INCLUDES = -I$(MLX_PATH) -Ibonus -Ibonus/not_your_libft -Ibonus/not_your_printf

LIBFT_DIR = not_your_libft
PRINTF_DIR = not_your_printf
LIBFT = $(LIBFT_DIR)/libft.a
PRINTF = $(PRINTF_DIR)/libftprintf.a

SRCS = source/main.c source/map.c source/graphics.c source/movement.c source/validation.c \
       support/map_support.c support/map_support2.c support/map_support3.c \
       support/graphics_support.c support/movement_support.c support/validation_support.c \
       support/main_support.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(PRINTF)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT) $(PRINTF) $(MLXFLAGS)
	@echo "\033[1;32m🐺 So_long Built Successfully! 🐺\033[0m"

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@make -sC $(LIBFT_DIR)

$(PRINTF):
	@make -sC $(PRINTF_DIR)

clean:
	@rm -f $(OBJS)
	@make -sC $(LIBFT_DIR) clean
	@make -sC $(PRINTF_DIR) clean
	@echo "\033[1;31m🐺 Cleaned Successfully! 🐺\033[0m"

fclean:
	@rm -f $(NAME) $(OBJS)
	@make -sC $(LIBFT_DIR) fclean
	@make -sC $(PRINTF_DIR) fclean
	@echo "\033[1;33m🐺 Force Cleaned Successfully! 🐺\033[0m"

re:
	@make -s fclean >/dev/null
	@make -s all >/dev/null
	@echo "\033[1;34m🐺 Rebuilt Successfully! 🐺\033[0m"

.PHONY: all clean fclean re