/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 01:08:25 by bchiki            #+#    #+#             */
/*   Updated: 2025/03/20 08:49:57 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define TILE_SIZE 40
#ifndef SO_LONG_H
# define SO_LONG_H

# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include "minilibx-linux/mlx.h"
# include "not_your_printf/ft_printf.h"

typedef struct t_nbr
{
    int x;
    int y;
}              t_nbr;

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

typedef struct s_game
{
    void        *mlx;
    void        *win;
    char        **map;
    int         width;
    int         height;
    t_textures  tex;
    int         player_x;
    int         player_y;
    int         exit_x; 
    int         exit_y; 
    int         moves;
    int         collectibles;
    void        *current_player_tex;
    int         won;
    int         tried_to_exit;
} t_game;


/* Functions in main.c */
void    free_map(t_game *game);
int     close_window(t_game *game);
void    cleanup_and_exit(t_game *game);
void    free_map_on_error(t_game *game);
void    destroy_window_and_display(t_game *game);
int     validate_arguments(int argc, char **argv);
int find_exit_position(t_game *game);
int     initialize_map(t_game *game, char *filename);
int     parse_and_validate_map(t_game *game, char *filename);

/* Functions in render.c */
void    render_map(t_game *game);
void    load_textures(t_game *game);

/* Functions in map.c */
int     validate_map(t_game *game);
void    parse_map(t_game *game, char *filename);

/* Functions in movement.c */
void    count_collectibles(t_game *game);
int     key_hook(int keycode, t_game *game);
void    move_player(t_game *game, int dx, int dy);

#endif