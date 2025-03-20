/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 03:46:05 by bchiki            #+#    #+#             */
/*   Updated: 2025/03/20 08:50:49 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

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

void cleanup_and_exit(t_game *game)
{
    destroy_textures(game);
    destroy_window_and_display(game);
    free_map(game);
    exit(0);
}
int close_window(t_game *game)
{
    if (game->won)
        ft_printf("\033[1;35m🎉 Congrats, You Won! 🐺\033[0m\n");
    else
        ft_printf("\033[1;35mWhy did you leave, bro? 🐺\033[0m\n");
    cleanup_and_exit(game);
    return (0);
}
int initialize_map(t_game *game, char *filename)
{
    if (!parse_and_validate_map(game, filename))
        return (0);
    if (!find_exit_position(game))
        return (0);
    return (1);
}
void free_map_on_error(t_game *game)
{
    int i;

    i = 0;
    while (i < game->height)
    {
        free(game->map[i]);
        i++;
    }
    free(game->map);
}
int validate_arguments(int argc, char **argv)
{
    if (argc != 2)
    {
        ft_printf("\033[1;35mError: Usage: ./so_long <map>.ber\033[0m\n");
        return (0);
    }
    if (strlen(argv[1]) < 4 || strcmp(argv[1] + strlen(argv[1]) - 4, ".ber") != 0)
    {
        ft_printf("\033[1;35mError: Map file must have a .ber extension\033[0m\n");
        return (0);
    }
    if (access(argv[1], F_OK) != 0)
    {
        ft_printf("\033[1;35mError: Map file does not exist\033[0m\n");
        return (0);
    }
    return (1);
}
void free_map(t_game *game)
{
    int x;

    x = 0;
    while (x < game->height)
    {
        free(game->map[x]);
        x++;
    }
    free(game->map);
}
void destroy_window_and_display(t_game *game)
{
    if (game->win)
        mlx_destroy_window(game->mlx, game->win);
    if (game->mlx)
        mlx_destroy_display(game->mlx);
    free(game->mlx);
}
int parse_and_validate_map(t_game *game, char *filename)
{
    parse_map(game, filename);
    if (!validate_map(game))
    {
        free_map_on_error(game);
        return (0);
    }
    count_collectibles(game);
    return (1);
}
int find_exit_position(t_game *game)
{
    int x;
    int y;

    game->exit_x = -1;
    game->exit_y = -1;
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
                break;
            }
            x++;
        }
        if (game->exit_x != -1)
            break;
        y++;
    }
    if (game->exit_x == -1 || game->exit_y == -1)
    {
        ft_printf("\033[1;35mError: No exit found in the map\033[0m\n");
        free_map_on_error(game);
        return (0);
    }
    return (1);
}

static int setup_mlx(t_game *game)
{
    game->mlx = mlx_init();
    if (!game->mlx)
    {
        ft_printf("\033[1;35mError: MiniLibX initialization failed\033[0m\n");
        cleanup_and_exit(game);
    }
    game->win = mlx_new_window(game->mlx, game->width * TILE_SIZE, game->height * TILE_SIZE, "So Long");
    if (!game->win)
    {
        ft_printf("Error: Window creation failed\n");
        cleanup_and_exit(game);
    }
    load_textures(game);
    if (!game->tex.wall || !game->tex.floor || !game->tex.player_looking_right || !game->tex.player_looking_left || !game->tex.player_looking_back || !game->tex.player_looking_direct || !game->tex.collectible || !game->tex.exit || !game->tex.exit_open || !game->tex.in_top_of_exit)
    {
        ft_printf("\033[1;35mError: One or more textures failed to load\033[0m\n");
        cleanup_and_exit(game);
    }
    game->current_player_tex = game->tex.player_looking_right;
    game->won = 0;
    game->tried_to_exit = 0;
    return (1);
}

static void start_game(t_game *game)
{
    render_map(game);
    ft_printf("\033[1;35mGame Is Successfully Launched 🐺\033[0m\n");
    mlx_hook(game->win, 17, 0, close_window, game);
    mlx_key_hook(game->win, key_hook, game);
    mlx_loop(game->mlx);
}

int main(int argc, char **argv)
{
    t_game game = {0};

    if (!validate_arguments(argc, argv))
        return (1);
    if (!initialize_map(&game, argv[1]))
        return (1);
    if (!setup_mlx(&game))
        return (1);
    start_game(&game);
    return (0);
}