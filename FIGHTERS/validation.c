/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 03:45:23 by bchiki            #+#    #+#             */
/*   Updated: 2025/03/20 08:19:26 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../so_long.h"

static int is_all_walls(t_game *game)
{
    int x;
    int y;

    y = 0;
    while (y < game->height)
    {
        x = 0;
        while (x < game->width)
        {
            if (game->map[y][x] != '1')
                return (0);
            x++;
        }
        y++;
    }
    return (1);
}

static void flood_fill(t_game *game, int x, int y, int *collectibles_reached, int *exit_reached, char **visited)
{
    if (x < 0 || x >= game->width || y < 0 || y >= game->height || visited[y][x] || game->map[y][x] == '1')
        return;
    visited[y][x] = 1;
    if (game->map[y][x] == 'C')
        (*collectibles_reached)++;
    if (game->map[y][x] == 'E')
        (*exit_reached)++;
    flood_fill(game, x + 1, y, collectibles_reached, exit_reached, visited);
    flood_fill(game, x - 1, y, collectibles_reached, exit_reached, visited);
    flood_fill(game, x, y + 1, collectibles_reached, exit_reached, visited);
    flood_fill(game, x, y - 1, collectibles_reached, exit_reached, visited);
}

static int can_reach_collectibles_and_exit(t_game *game)
{
    char **visited;
    int collectibles_reached = 0;
    int exit_reached = 0;
    int total_collectibles = 0;
    int x, y;

    // Count total collectibles
    y = 0;
    while (y < game->height)
    {
        x = 0;
        while (x < game->width)
        {
            if (game->map[y][x] == 'C')
                total_collectibles++;
            x++;
        }
        y++;
    }

    // Allocate visited array
    visited = malloc(sizeof(char *) * game->height);
    y = 0;
    while (y < game->height)
    {
        visited[y] = malloc(game->width);
        x = 0;
        while (x < game->width)
        {
            visited[y][x] = 0;
            x++;
        }
        y++;
    }

    // Perform flood-fill from player's position
    flood_fill(game, game->player_x, game->player_y, &collectibles_reached, &exit_reached, visited);

    // Free visited array
    y = 0;
    while (y < game->height)
    {
        free(visited[y]);
        y++;
    }
    free(visited);

    // Check if all collectibles are reachable (if any exist)
    if (collectibles_reached != total_collectibles)
    {
        ft_printf("\033[1;35mError: Player cannot reach all collectibles\033[0m\n");
        return (0);
    }

    // Check if the exit is reachable
    if (exit_reached != 1)
    {
        ft_printf("\033[1;35mError: Player cannot reach the exit\033[0m\n");
        return (0);
    }

    return (1);
}

int validate_map(t_game *game)
{
    int x, y;
    int p_count = 0, e_count = 0, c_count = 0;

    // Check for empty lines
    y = 0;
    while (y < game->height)
    {
        if (game->map[y][0] == '\0')
        {
            if (y == 0)
                ft_printf("\033[1;35mError: Empty line at the top of the map\033[0m\n");
            else if (y == game->height - 1)
                ft_printf("\033[1;35mError: Empty line at the end of the map\033[0m\n");
            else
                ft_printf("\033[1;35mError: Empty line in the middle of the map\033[0m\n");
            return (0);
        }
        y++;
    }

    // Check walls
    y = 0;
    while (y < game->height)
    {
        x = 0;
        while (x < game->width)
        {
            if ((y == 0 || y == game->height - 1) && game->map[y][x] != '1')
            {
                ft_printf("\033[1;35mError: Top or bottom wall is not fully '1'\033[0m\n");
                return (0);
            }
            if ((x == 0 || x == game->width - 1) && game->map[y][x] != '1')
            {
                ft_printf("\033[1;35mError: Left or right wall is not fully '1'\033[0m\n");
                return (0);
            }
            x++;
        }
        y++;
    }

    // Check for all walls
    if (is_all_walls(game))
    {
        ft_printf("\033[1;35mError: Map contains only walls\033[0m\n");
        return (0);
    }

    // Count components and find player
    y = 0;
    while (y < game->height)
    {
        x = 0;
        while (x < game->width)
        {
            if (game->map[y][x] == 'P')
            {
                p_count++;
                game->player_x = x;
                game->player_y = y;
            }
            else if (game->map[y][x] == 'E')
                e_count++;
            else if (game->map[y][x] == 'C')
                c_count++;
            else if (game->map[y][x] != '0' && game->map[y][x] != '1')
            {
                ft_printf("\033[1;35mError: Invalid character '%c' in map\033[0m\n", game->map[y][x]);
                return (0);
            }
            x++;
        }
        y++;
    }

    // Check component counts
    if (p_count != 1)
    {
        ft_printf("\033[1;35mError: Map must have exactly one player (P)\033[0m\n");
        return (0);
    }
    if (e_count != 1)
    {
        ft_printf("\033[1;35mError: Map must have exactly one exit (E)\033[0m\n");
        return (0);
    }
    // Removed the requirement for at least one collectible
    // if (c_count < 1)
    // {
    //     ft_printf("Error: Map must have at least one collectible (C)\n");
    //     return (0);
    // }

    // Check if player is surrounded
    if (game->player_x > 0 && game->player_x < game->width - 1 && game->player_y > 0 && game->player_y < game->height - 1)
    {
        if (game->map[game->player_y - 1][game->player_x] == '1' &&
            game->map[game->player_y + 1][game->player_x] == '1' &&
            game->map[game->player_y][game->player_x - 1] == '1' &&
            game->map[game->player_y][game->player_x + 1] == '1')
        {
            ft_printf("\033[1;35mError: Player is completely surrounded by walls noobie\033[0m\n");
            return (0);
        }
    }

    // Check reachability of collectibles and exit
    if (!can_reach_collectibles_and_exit(game))
        return (0);

    return (1);
}