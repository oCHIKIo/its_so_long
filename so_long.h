/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:52:04 by bchiki            #+#    #+#             */
/*   Updated: 2025/03/22 20:39:34 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
#define SO_LONG_H

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "not_your_libft/libft.h"
#include "not_your_printf/ft_printf.h"
#include "/usr/include/minilibx-linux/mlx.h"

#define TILE_SIZE 40

typedef struct s_flood {
    int x;
    int y;
    int collectibles;
    int exit;
    int width;
    int height;
} t_flood;

typedef struct s_game {
    void    *mlx;
    void    *win;
    void    *img[10];
    char    *map;
    int     width;
    int     height;
    int     player_x;
    int     player_y;
    int     collectibles;
    int     moves;
    int     exit_x;
    int     exit_y;
    int     last_dx;
    int     last_dy;
} t_game;

// map.c
char    *read_map(char *file);
int     check_map_validity(t_game *game);
void    count_elements(t_game *game);

// graphics.c
void    init_graphics(t_game *game);
void    load_textures(t_game *game);
void    render_map(t_game *game);

// movement.c
int     key_press(int key, t_game *game);
void    move_player(t_game *game, int dx, int dy);
void    update_player_texture(t_game *game, int dx, int dy);
int     close_window(t_game *game);

// validation.c
int     check_walls(t_game *game);
int     check_empty_lines(char *map);
int     check_accessibility(t_game *game); 

#endif