/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 18:09:54 by bchiki            #+#    #+#             */
/*   Updated: 2025/03/22 01:15:11 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../not_your_libft/libft.h"
# include "../not_your_printf/ft_printf.h"
# include "../minilibx-linux/mlx.h"
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>

# define TILE_SIZE 40

typedef struct s_nbr
{
    int     x;
    int     y;
    int     fd;
    int     bytes;
} t_nbr;

typedef struct s_textures
{
    void    *wall;
    void    *floor;
    void    *player_looking_right;
    void    *player_looking_left;
    void    *player_looking_back;
    void    *player_looking_direct;
    void    *collectible;
    void    *exit;
    void    *exit_open;
    void    *in_top_of_exit;
} t_textures;

typedef struct s_keys
{
    int     w_pressed; 
    int     a_pressed; 
    int     s_pressed; 
    int     d_pressed; 
} t_keys;

typedef struct s_game
{
    void        *mlx;
    void        *win;
    char        **map;
    int         width;
    int         height;
    int         player_x;
    int         player_y;
    int         exit_x;
    int         exit_y;
    int         collectibles;
    int         moves;
    int         won;
    int         tried_to_exit;
    void        *current_player_tex;
    t_textures  tex;
    t_keys      keys; // Added to track key states
    long int    last_move_time; // Fixed: Changed 'long' to 'long int' and removed '+'
} t_game;

void    parse_map(t_game *game, char *filename);
void    render_map(t_game *game);
void    load_textures(t_game *game);
int     key_hook(int keycode, t_game *game);
int     count_collectibles(t_game *game);
void    move_player(t_game *game, int dx, int dy);
void    destroy_textures(t_game *game);
void    destroy_window_and_display(t_game *game);
void    free_map(t_game *game);
void    free_map_on_error(t_game *game);
void    cleanup_and_exit(t_game *game);
int key_press(int keycode, t_game *game);
int key_release(int keycode, t_game *game);
int update_game(t_game *game);
int     close_window(t_game *game);
int     validate_map(t_game *game); // Added prototype for validate_map

#endif