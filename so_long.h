/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:52:04 by bchiki            #+#    #+#             */
/*   Updated: 2025/03/26 00:52:04 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft/libft.h"
# include "ft_printf/ft_printf.h"
# include "/usr/include/minilibx-linux/mlx.h"

# define TILE_SIZE 40

typedef struct s_nbr
{
	int		x;
	int		y;
	int		i;
	int		j;
	int		fd;
	int		len;
	int		size;
	int		height;
	int		last_line_start;
}			t_nbr;

typedef struct s_move
{
	int		new_x;
	int		new_y;
	int		new_pos;
	int		old_pos;
}			t_move;

typedef struct s_count
{
	int		i;
	int		x;
	int		y;
	int		exit_count;
	int		player_count;
}			t_count;

typedef struct s_flood
{
	int		x;
	int		y;
	int		collectibles;
	int		exit;
	int		width;
	int		height;
}			t_flood;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	void	*img[30];
	char	*map;
	int		width;
	int		height;
	int		player_x;
	int		player_y;
	int		collectibles;
	int		moves;
	int		exit_x;
	int		exit_y;
	int		last_dx;
	int		last_dy;
	int		current_frame;
	int		frame_counter;
	int		is_moving;
}			t_game;

/* MAIN */
int			main(int ac, char **av);

/* MAP */
char		*read_map(char *file);
void		count_elements(t_game *game);
int			check_map_validity(t_game *game);
int			check_player_exit(t_game *game, t_count *count);

/* MAP_SUPPORT */
int			get_file_size(char *file);
int			get_map_width(t_game *game);
int			check_start_line(t_game *game);
int			check_map_lines(t_game *game, int *all_walls);
int			check_line_length(t_game *game, int *i, int *all_walls);

/* MAP_SUPPORT2 */
int			check_final_validations(t_game *game);
void		init_counts(t_game *game, t_count *count);
int			check_symbol(t_game *game, t_count *count);
int			check_end_conditions(t_game *game, int all_walls);

/* GRAPHICS */
void		render_map(t_game *game);
void		init_graphics(t_game *game);
void		load_textures(t_game *game);
void		destroy_images(t_game *game);
int			update_animation(t_game *game);

/* GRAPHICS_SUPPORT */
void		render_exit(t_game *game, int x, int y);
void		render_player(t_game *game, int x, int y);

/* MOVEMENT */
int			close_window(t_game *game);
int			key_press(int key, t_game *game);
void		move_player(t_game *game, int dx, int dy);
void		update_player_texture(t_game *game, int dx, int dy);

/* MOVEMENT_SUPPORT */
int			check_exit(t_game *game, t_move *move);
void		update_move(t_game *game, t_move *move);
void		init_move(t_game *game, t_move *move, int dx, int dy);

/* VALIDATION */
int			check_walls(t_game *game);
int			check_empty_lines(char *map);
int			check_accessibility(t_game *game);

/* VALIDATION_SUPPORT */
t_flood		check_cell(char *map, t_flood state);
void		update_state(t_flood *state, t_flood new_state);
int			is_valid_position(t_flood state, int x, int y, char *map);

#endif
