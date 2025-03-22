NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX_PATH = /usr/include/minilibx-linux
MLXFLAGS = -L$(MLX_PATH) -lmlx_Linux -lXext -lX11
LIBFT = not_your_libft/libft.a
PRINTF = not_your_printf/libftprintf.a

SRCS = main.c map.c graphics.c movement.c validation.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(PRINTF)
	@echo "Linking with MLX from $(MLX_PATH)..."
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT) $(PRINTF) $(MLXFLAGS)
	@if [ $$? -ne 0 ]; then \
		echo "Linker failed. Checking MLX and libft setup:"; \
		ls -l $(MLX_PATH)/libmlx* 2>/dev/null || echo "MLX files not found"; \
		ar t $(LIBFT) | grep ft_strcmp || echo "ft_strcmp not in libft.a"; \
		exit 1; \
	fi

%.o: %.c
	$(CC) $(CFLAGS) -I$(MLX_PATH) -c $< -o $@

$(LIBFT):
	make -C not_your_libft

$(PRINTF):
	make -C not_your_printf

clean:
	rm -f $(OBJS)
	make -C not_your_libft clean
	make -C not_your_printf clean

fclean: clean
	rm -f $(NAME)
	make -C not_your_libft fclean
	make -C not_your_printf fclean

re: fclean all

.PHONY: all clean fclean re