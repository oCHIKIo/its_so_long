NAME = so_long

SRC_DIR = FIGHTERS
PILLARS_DIR = PILLARS
LIBFT_DIR = not_your_libft
PRINTF_DIR = not_your_printf
MLX_DIR = minilibx-linux

SRC =	$(SRC_DIR)/main.c \
		$(SRC_DIR)/map.c \
		$(SRC_DIR)/movement.c \
		$(SRC_DIR)/render.c \
		$(SRC_DIR)/validation.c \
		$(PILLARS_DIR)/main_support_1.c \
		$(PILLARS_DIR)/main_support_2.c \
		$(PILLARS_DIR)/main_support_3.c \
		$(PILLARS_DIR)/main_support_4.c \
		$(PILLARS_DIR)/map_support_1.c \
		$(PILLARS_DIR)/map_support_2.c \
		$(PILLARS_DIR)/map_support_3.c \
		$(PILLARS_DIR)/movement_support_1.c \
		$(PILLARS_DIR)/movement_support_2.c \
		$(PILLARS_DIR)/movement_support_3.c \
		$(PILLARS_DIR)/render_support_1.c \
		$(PILLARS_DIR)/validation_support_1.c \
		$(PILLARS_DIR)/validation_support_2.c \
		$(PILLARS_DIR)/validation_support_3.c \
		$(PILLARS_DIR)/validation_support_4.c \
		$(PILLARS_DIR)/validation_support_5.c
		
OBJ = $(SRC:.c=.o)

MLX_LIB = $(MLX_DIR)/libmlx.a
LIBFT_LIB = $(LIBFT_DIR)/libft.a
PRINTF_LIB = $(PRINTF_DIR)/libftprintf.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(MLX_DIR) -I$(PRINTF_DIR) -I$(LIBFT_DIR)
LDFLAGS = -L$(MLX_DIR) -lmlx -L$(LIBFT_DIR) -lft -L$(PRINTF_DIR) -lftprintf -lXext -lX11 -lm

REBUILDING = 0

all: $(NAME)

$(MLX_LIB):
	@make -s -C $(MLX_DIR) > /dev/null 2>&1

$(NAME): $(MLX_LIB) $(LIBFT_LIB) $(PRINTF_LIB) $(OBJ)
	@$(CC) $(OBJ) $(LDFLAGS) -o $(NAME)
	@if [ $(REBUILDING) -eq 0 ] && { [ "$(MAKECMDGOALS)" = "all" ] || [ "$(MAKECMDGOALS)" = "" ]; }; then \
		printf "\033[1;32m🐺 So_long Built Successfully! 🐺\033[0m\n"; \
	fi

%.o: %.c so_long.h $(LIBFT_DIR)/libft.h
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT_LIB): $(LIBFT_DIR)/libft.h
	@make -s -C $(LIBFT_DIR) > /dev/null 2>&1

$(PRINTF_LIB):
	@make -s -C $(PRINTF_DIR) > /dev/null 2>&1

clean:
	@rm -f $(OBJ)
	@make -s -C $(LIBFT_DIR) clean > /dev/null 2>&1
	@make -s -C $(PRINTF_DIR) clean > /dev/null 2>&1
	@make -s -C $(MLX_DIR) clean > /dev/null 2>&1
	@if [ $(REBUILDING) -eq 0 ] && [ "$(MAKECMDGOALS)" = "clean" ]; then \
		printf "\033[1;31m🐺 Cleaned Successfully! 🐺\033[0m\n"; \
	fi

fclean: clean
	@rm -f $(NAME)
	@make -s -C $(LIBFT_DIR) fclean > /dev/null 2>&1
	@make -s -C $(PRINTF_DIR) fclean > /dev/null 2>&1
	@make -s -C $(MLX_DIR) clean > /dev/null 2>&1
	@if [ $(REBUILDING) -eq 0 ] && [ "$(MAKECMDGOALS)" = "fclean" ]; then \
		printf "\033[1;33m🐺 Force Cleaned Successfully! 🐺\033[0m\n"; \
	fi

re:
	@$(MAKE) --no-print-directory fclean REBUILDING=1
	@$(MAKE) --no-print-directory all REBUILDING=1
	@printf "\033[1;34m🐺 Rebuilt Successfully! 🐺\033[0m\n"

.PHONY: all clean fclean re