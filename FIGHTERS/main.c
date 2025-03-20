/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 03:46:05 by bchiki            #+#    #+#             */
/*   Updated: 2025/03/20 04:07:12 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void cleanup_and_exit(t_game *game)
{
    int x;

    // Free textures
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
    if (game->win)
        mlx_destroy_window(game->mlx, game->win);
    if (game->mlx)
        mlx_destroy_display(game->mlx);
    free(game->mlx);
    x = 0;
    while (x < game->height)
    {
        free(game->map[x]);
        x++;
    }
    free(game->map);
    exit(0);
}

int close_window(t_game *game)
{
    if (game->won)
        ft_printf("\033[1;35mCongrats, you won noobie! :) 🐺\033[0m\n");
    else
        ft_printf("\033[1;35mWhy did you leave, bro? 🐺\033[0m\n");
    usleep(2000000); 
    cleanup_and_exit(game);
    return (0); // This line is never reached due to exit(0), but included for clarity
}

int main(int argc, char **argv)
{
    t_game game = {0};

    if (argc != 2)
    {
        ft_printf("Error: Usage: ./so_long <map>.ber\n");
        return (1);
    }
    if (strlen(argv[1]) < 4 || strcmp(argv[1] + strlen(argv[1]) - 4, ".ber") != 0)
    {
        ft_printf("Error: Map file must have a .ber extension\n");
        return (1);
    }
    if (access(argv[1], F_OK) != 0)
    {
        ft_printf("Error: Map file does not exist\n");
        return (1);
    }
    parse_map(&game, argv[1]);
    if (!validate_map(&game))
    {
        int i = 0;
        while (i < game.height)
        {
            free(game.map[i]);
            i++;
        }
        free(game.map);
        return (1);
    }
    count_collectibles(&game);
    game.mlx = mlx_init();
    if (!game.mlx)
    {
        ft_printf("Error: MiniLibX initialization failed\n");
        return (1);
    }
    game.win = mlx_new_window(game.mlx, game.width * TILE_SIZE, game.height * TILE_SIZE, "So Long");
    if (!game.win)
    {
        ft_printf("Error: Window creation failed\n");
        return (1);
    }
    load_textures(&game);
    if (!game.tex.wall || !game.tex.floor || !game.tex.player_looking_right || !game.tex.player_looking_left || !game.tex.player_looking_back || !game.tex.player_looking_direct || !game.tex.collectible || !game.tex.exit || !game.tex.exit_open || !game.tex.in_top_of_exit)
    {
        ft_printf("Error: One or more textures failed to load\n");
        mlx_destroy_window(game.mlx, game.win);
        int i = 0;
        while (i < game.height)
        {
            free(game.map[i]);
            i++;
        }
        free(game.map);
        exit(1);
    }
    game.current_player_tex = game.tex.player_looking_right; 
    game.won = 0; // Initialize won flag to 0
    render_map(&game);
    ft_printf("\033[1;33mGame Is Successfully Launched 🐺\033[0m\n");
    mlx_hook(game.win, 17, 0, close_window, &game);
    mlx_key_hook(game.win, key_hook, &game);
    mlx_loop(game.mlx);
    return (0);
}