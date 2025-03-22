/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_support_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 00:41:41 by bchiki            #+#    #+#             */
/*   Updated: 2025/03/22 01:18:15 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void init_game_state(t_game *game)
{
    game->current_player_tex = game->tex.player_looking_right;
    game->won = 0;
    game->tried_to_exit = 0;
    game->last_move_time = 0;
    game->keys.w_pressed = 0;
    game->keys.a_pressed = 0;
    game->keys.s_pressed = 0;
    game->keys.d_pressed = 0;
}

int setup_mlx(t_game *game)
{
    game->mlx = mlx_init();
    if (!game->mlx)
    {
        ft_printf("\033[1;38;5;51mError: MiniLibX initialization failed\033[0m\n");
        cleanup_and_exit(game);
    }
    game->win = mlx_new_window(game->mlx, game->width * TILE_SIZE, game->height * TILE_SIZE, "So Long");
    if (!game->win)
    {
        ft_printf("\033[1;38;5;51mError: Window creation failed\033[0m\n");
        cleanup_and_exit(game);
    }
    load_textures(game);
    if (!game->tex.wall || !game->tex.floor || !game->tex.player_looking_right || !game->tex.player_looking_left || !game->tex.player_looking_back || !game->tex.player_looking_direct || !game->tex.collectible || !game->tex.exit || !game->tex.exit_open || !game->tex.in_top_of_exit)
    {
        ft_printf("\033[1;38;5;51mError: One or more textures failed to load\033[0m\n");
        cleanup_and_exit(game);
    }
    init_game_state(game);
    return (1);
}

void start_game(t_game *game)
{
    render_map(game);
    ft_printf("\033[1;38;5;51mGame Is Successfully Launched 🐺\033[0m\n");
    mlx_hook(game->win, 17, 0, close_window, game);
    mlx_hook(game->win, 2, 1L << 0, key_press, game);
    mlx_hook(game->win, 3, 1L << 1, key_release, game);
    mlx_loop_hook(game->mlx, update_game, game);
    mlx_loop(game->mlx);
}

int find_exit_position(t_game *game)
{
    game->exit_x = -1;
    game->exit_y = -1;
    search_for_exit(game);
    if (game->exit_x == -1 || game->exit_y == -1)
    {
        ft_printf("\033[1;38;5;51mError: No exit found in the map\033[0m\n");
        free_map_on_error(game);
        return (0);
    }
    return (1);
}

int update_game(t_game *game)
{
    long current_time = get_current_time();
    if (current_time - game->last_move_time < 150)
        return (0);
    if (game->keys.w_pressed)
    {
        move_player(game, 0, -1);
        game->last_move_time = current_time;
    }
    else if (game->keys.a_pressed)
    {
        move_player(game, -1, 0);
        game->last_move_time = current_time;
    }
    else if (game->keys.s_pressed)
    {
        move_player(game, 0, 1);
        game->last_move_time = current_time;
    }
    else if (game->keys.d_pressed)
    {
        move_player(game, 1, 0);
        game->last_move_time = current_time;
    }
    return (0);
}
