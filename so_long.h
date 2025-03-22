/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 18:09:54 by bchiki            #+#    #+#             */
/*   Updated: 2025/03/22 03:06:05 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../minilibx-linux/mlx.h"
# include "../not_your_libft/libft.h"
# include "../not_your_printf/ft_printf.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define TILE_SIZE 40

typedef struct s_nbr
{
	int			x;
	int			y;
	int			fd;
	int			bytes;
}				t_nbr;

typedef struct s_textures
{
	void		*wall;
	void		*floor;
	void		*player_looking_right;
	void		*player_looking_left;
	void		*player_looking_back;
	void		*player_looking_direct;
	void		*collectible;
	void		*exit;
	void		*exit_open;
	void		*in_top_of_exit;
}				t_textures;

typedef struct s_keys
{
	int			w_pressed;
	int			a_pressed;
	int			s_pressed;
	int			d_pressed;
}				t_keys;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	char		**map;
	int			width;
	int			height;
	int			player_x;
	int			player_y;
	int			exit_x;
	int			exit_y;
	int			collectibles;
	int			moves;
	int			won;
	int			tried_to_exit;
	void		*current_player_tex;
	t_textures	tex;
	t_keys		keys;
	long int	last_move_time;
}				t_game;

/* main.c */
int				main(int argc, char **argv);

/* map.c */
void			allocate_map(t_game *game, char *content);
void			parse_map(t_game *game, char *filename);

/* movement.c */
void			move_player(t_game *game, int dx, int dy);

/* render.c */
void			render_map(t_game *game);

/* validation.c */
int				validate_map(t_game *game);

/* main_support.c */
void			free_map_on_error(t_game *game);
void			free_map(t_game *game);
int				validate_arguments(int argc, char **argv);
int				initialize_map(t_game *game, char *filename);
int				parse_and_validate_map(t_game *game, char *filename);
int				close_window(t_game *game);
void			cleanup_and_exit(t_game *game);
void			destroy_window_and_display(t_game *game);
void			destroy_textures(t_game *game);
void			search_for_exit(t_game *game);
void			init_game_state(t_game *game);
int				setup_mlx(t_game *game);
void			start_game(t_game *game);
int				find_exit_position(t_game *game);
int				update_game(t_game *game);
int				handle_player_movement(t_game *game, long current_time);

/* map_support.c */
void			count_map_height(t_game *game, char *content);
void			set_map_width(t_game *game);
char			*resize_buffer(char *buffer, size_t total_bytes,
					size_t new_size);
void			handle_error(char *buffer, int fd);
char			*read_in_chunks(t_nbr *nbr, char *buffer);
char			*read_and_process(t_nbr *nbr, char *buffer);
char			*read_file(char *filename);
char			*open_and_allocate(char *filename, t_nbr *nbr);
void			split_map_line(t_game *game, char *temp, int i, char *content);
void			split_map_content(t_game *game, char *content);
void			check_trailing_newlines(char *content, size_t len);
void			check_consecutive_newlines(char *content, size_t len);
void			check_trailing_empty_lines(char *content);
char			*process_chunk(t_nbr *nbr, char *buffer, size_t *total_bytes,
					size_t *buffer_size);

/* movement_support.c */
int				key_release(int keycode, t_game *game);
void			calculate_new_position(t_game *game, int dx, int dy, int *new_x,
					int *new_y);
int				count_collectibles(t_game *game);
int				is_valid_move(t_game *game, int new_x, int new_y);
void			handle_collectible(t_game *game, int new_x, int new_y);
int				handle_exit(t_game *game, int new_x, int new_y);
void			update_and_render(t_game *game, int new_x, int new_y);
long			get_current_time(void);
int				key_press(int keycode, t_game *game);

/* render_support.c */
void			load_textures(t_game *game);
void			render_wall_floor(t_game *game, t_nbr *nbr);
void			render_collectibles(t_game *game, t_nbr *nbr);
void			render_exits(t_game *game, t_nbr *nbr);
void			render_player(t_game *game, t_nbr *nbr);

/* validation_support.c */
int				is_all_walls(t_game *game);
void			flood_fill(t_game *game, int x, int y,
					int *collectibles_reached, int *exit_reached,
					char **visited);
int				check_for_empty_lines(t_game *game);
int				check_map_walls(t_game *game);
int				check_empty_lines_and_walls(t_game *game);
int				validate_element_counts(int p_count, int e_count, int c_count);
int				check_player_surrounded(t_game *game);
int				handle_map_element(t_game *game, int x, int y, int *p_count,
					int *e_count, int *c_count);
int				count_map_elements(t_game *game, int *p_count, int *e_count,
					int *c_count);
void			allocate_visited_rows(t_game *game, char **visited, int y);
void			set_row_to_zero(t_game *game, char *row, int x);
void			count_collectibles_recursive(t_game *game, int y, int x,
					int *total);
void			free_visited_rows(t_game *game, char **visited, int y);
void			perform_flood_fill(t_game *game, char **visited,
					int *collectibles_reached, int *exit_reached);
int				can_reach_collectibles_and_exit(t_game *game);
char			**init_visited_array(t_game *game);
void			count_total_collectibles(t_game *game, int *total_collectibles);
void			cleanup_visited_array(t_game *game, char **visited);
int				validate_reachability(int collectibles_reached,
					int total_collectibles, int exit_reached);

#endif