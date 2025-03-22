/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:52:54 by bchiki            #+#    #+#             */
/*   Updated: 2025/03/22 21:09:34 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static t_flood flood_fill(char *map, t_game *game, t_flood state)
{
    int pos = state.y * (state.width + 1) + state.x;

    if (state.x < 0 || state.x >= state.width || state.y < 0 || state.y >= state.height || map[pos] == '1' || map[pos] == 'X')
        return (state);

    if (map[pos] == 'C')
        state.collectibles--;
    if (map[pos] == 'E')
        state.exit = 1;
    map[pos] = 'X';

    t_flood left = flood_fill(map, game, (t_flood){state.x - 1, state.y, state.collectibles, state.exit, state.width, state.height});
    state.collectibles = left.collectibles;
    state.exit = left.exit;

    t_flood right = flood_fill(map, game, (t_flood){state.x + 1, state.y, state.collectibles, state.exit, state.width, state.height});
    state.collectibles = right.collectibles;
    state.exit = right.exit;

    t_flood up = flood_fill(map, game, (t_flood){state.x, state.y - 1, state.collectibles, state.exit, state.width, state.height});
    state.collectibles = up.collectibles;
    state.exit = up.exit;

    t_flood down = flood_fill(map, game, (t_flood){state.x, state.y + 1, state.collectibles, state.exit, state.width, state.height});
    state.collectibles = down.collectibles;
    state.exit = down.exit;

    return (state);
}

int     check_walls(t_game *game)
{
    int i = 0;
    int j;

    while (i < game->width)
    {
        if (game->map[i] != '1' || game->map[(game->height - 1) * (game->width + 1) + i] != '1')
            return (0);
        i++;
    }

    i = 0;
    while (i < game->height)
    {
        j = i * (game->width + 1);
        if (game->map[j] != '1' || game->map[j + game->width - 1] != '1')
            return (0);
        i++;
    }
    return (1);
}

int     check_empty_lines(char *map)
{
    int i = 0;
    while (map[i])
    {
        if (map[i] == '\n' && map[i + 1] == '\n')
            return (0);
        i++;
    }
    return (1);
}

int     check_accessibility(t_game *game)
{
    char *map_copy = ft_strdup(game->map);
    t_flood state = {game->player_x, game->player_y, game->collectibles, 0, game->width, game->height};
    
    if (!map_copy)
    {
        ft_putstr_fd("Error: Memory allocation failed\n", 2);
        return (0);
    }
    state = flood_fill(map_copy, game, state);
    if (state.collectibles > 0 || state.exit == 0)
    {
        ft_putstr_fd("Error: Unreachable collectibles and/or exit\n", 2);
        free(map_copy);
        return (0);
    }
    free(map_copy);
    return (1);
}