/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_support_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 00:35:24 by bchiki            #+#    #+#             */
/*   Updated: 2025/03/22 00:41:32 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int close_window(t_game *game)
{
    if (game->won)
        ft_printf("\033[1;38;5;51m🎉 Congrats, You noobie! 🐺\033[0m\n");
    else
        ft_printf("\033[1;38;5;51mWhy did you leave, noobie? 🐺\033[0m\n");
    cleanup_and_exit(game);
    return (0);
}
void cleanup_and_exit(t_game *game)
{
    destroy_textures(game);
    destroy_window_and_display(game);
    free_map(game);
    exit(0);
}
void destroy_window_and_display(t_game *game)
{
    if (game->win)
        mlx_destroy_window(game->mlx, game->win);
    if (game->mlx)
        mlx_destroy_display(game->mlx);
    free(game->mlx);
}
void destroy_textures(t_game *game)
{
    if (game->tex.wall)
        mlx_destroy_image(game->mlx, game->tex.wall);
    if (game->tex.floor)
        mlx_destroy_image(game->mlx, game->tex.floor);
    if (game->tex.player_looking_right)
        mlx_destroy_image(game->mlx, game->tex.player_looking_right);
    if (game->tex.player_looking_left)
        mlx_destroy_image(game->mlx, game->tex.player_looking_left);
    if (game->tex.player_looking_back)
        mlx_destroy_image(game->mlx, game->tex.player_looking_back);
    if (game->tex.player_looking_direct)
        mlx_destroy_image(game->mlx, game->tex.player_looking_direct);
    if (game->tex.collectible)
        mlx_destroy_image(game->mlx, game->tex.collectible);
    if (game->tex.exit)
        mlx_destroy_image(game->mlx, game->tex.exit);
    if (game->tex.exit_open)
        mlx_destroy_image(game->mlx, game->tex.exit_open);
    if (game->tex.in_top_of_exit)
        mlx_destroy_image(game->mlx, game->tex.in_top_of_exit);
}
void search_for_exit(t_game *game)
{
    int x;
    int y;

    y = 0;
    while (y < game->height)
    {
        x = 0;
        while (x < game->width)
        {
            if (game->map[y][x] == 'E')
            {
                game->exit_x = x;
                game->exit_y = y;
                return;
            }
            x++;
        }
        y++;
    }
}