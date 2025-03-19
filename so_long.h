/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 01:08:25 by bchiki            #+#    #+#             */
/*   Updated: 2025/03/19 04:11:35 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
#define SO_LONG_H

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include "minilibx-linux/mlx.h"
#include "not_your_printf/ft_printf.h"

typedef struct s_textures 
{
	void	*wall;
	void	*floor;
	void	*player;
	void	*collectible;
	void	*exit;
} t_textures;

typedef struct s_game 
{
	void		*mlx;
	void		*win;
	char		**map;
	int			width;
	int			height;
	t_textures	tex;
	int			player_x;
	int			player_y;
	int			moves;
	int			collectibles;
} t_game;

void	render_map(t_game *game);
void	find_player(t_game *game);
int		close_window(t_game *game);
int		validate_map(t_game *game);
void	load_textures(t_game *game);
void	count_collectibles(t_game *game);
int		key_hook(int keycode, t_game *game);
void	parse_map(t_game *game, char *filename);
void	move_player(t_game *game, int dx, int dy);

#endif