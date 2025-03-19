/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 03:45:23 by bchiki            #+#    #+#             */
/*   Updated: 2025/03/19 18:03:07 by bchiki           ###   ########.fr       */
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

static void flood_fill(t_game *game, int x, int y, int *collectibles_reached, char **visited)
{
    if (x < 0 || x >= game->width || y < 0 || y >= game->height || visited[y][x] || game->map[y][x] == '1')
        return;
    visited[y][x] = 1;
    if (game->map[y][x] == 'C')
        (*collectibles_reached)++;
    flood_fill(game, x + 1, y, collectibles_reached, visited);
    flood_fill(game, x - 1, y, collectibles_reached, visited);
    flood_fill(game, x, y + 1, collectibles_reached, visited);
    flood_fill(game, x, y - 1, collectibles_reached, visited);
}

static int can_reach_collectibles(t_game *game)
{
    char **visited;
    int collectibles_reached;
    int total_collectibles;
    int x;
    int y;

    collectibles_reached = 0;
    total_collectibles = 0;

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

    flood_fill(game, game->player_x, game->player_y, &collectibles_reached, visited);

    y = 0;
    while (y < game->height)
    {
        free(visited[y]);
        y++;
    }
    free(visited);

    return (collectibles_reached == total_collectibles);
}

int validate_map(t_game *game)
{
    int x;
    int y;
    int p_count;
    int e_count;
    int c_count;

    p_count = 0;
    e_count = 0;
    c_count = 0;

    // Check for empty lines
    y = 0;
    while (y < game->height)
    {
        if (game->map[y][0] == '\0')
        {
            if (y == 0)
                ft_printf("Error: Empty line at the top of the map\n");
            else if (y == game->height - 1)
                ft_printf("Error: Empty line at the end of the map\n");
            else
                ft_printf("Error: Empty line in the middle of the map\n");
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
                ft_printf("Error: Top or bottom wall is not fully '1'\n");
                return (0);
            }
            if ((x == 0 || x == game->width - 1) && game->map[y][x] != '1')
            {
                ft_printf("Error: Left or right wall is not fully '1'\n");
                return (0);
            }
            x++;
        }
        y++;
    }

    // Check for all walls
    if (is_all_walls(game))
    {
        ft_printf("Error: Map contains only walls\n");
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
                ft_printf("Error: Invalid character '%c' in map\n", game->map[y][x]);
                return (0);
            }
            x++;
        }
        y++;
    }

    // Check component counts
    if (p_count != 1)
    {
        ft_printf("Error: Map must have exactly one player (P)\n");
        return (0);
    }
    if (e_count != 1)
    {
        ft_printf("Error: Map must have exactly one exit (E)\n");
        return (0);
    }
    if (c_count < 1)
    {
        ft_printf("Error: Map must have at least one collectible (C)\n");
        return (0);
    }

    // Check if player is surrounded
    if (game->player_x > 0 && game->player_x < game->width - 1 && game->player_y > 0 && game->player_y < game->height - 1)
    {
        if (game->map[game->player_y - 1][game->player_x] == '1' &&
            game->map[game->player_y + 1][game->player_x] == '1' &&
            game->map[game->player_y][game->player_x - 1] == '1' &&
            game->map[game->player_y][game->player_x + 1] == '1')
        {
            ft_printf("Error: Player is completely surrounded by walls\n");
            return (0);
        }
    }

    // Check reachability
    if (!can_reach_collectibles(game))
    {
        ft_printf("Error: Player cannot reach all collectibles\n");
        return (0);
    }

    return (1);
}