/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:52:54 by bchiki            #+#    #+#             */
/*   Updated: 2025/03/23 00:29:48 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void update_state(t_flood *state, t_flood new_state)
{
    state->collectibles = new_state.collectibles;
    state->exit = new_state.exit;
}

static int is_valid_position(t_flood state, int x, int y, char *map)
{
    if (x < 0 || x >= state.width || y < 0 || y >= state.height)
        return (0);
    
    int pos = y * (state.width + 1) + x;
    if (map[pos] == '1' || map[pos] == 'X')
        return (0);
    
    return (1);
}

static t_flood check_cell(char *map, t_flood state)
{
    int pos = state.y * (state.width + 1) + state.x;
    
    if (map[pos] == 'C')
        state.collectibles--;
    if (map[pos] == 'E')
        state.exit = 1;
    
    map[pos] = 'X';
    return (state);
}

static t_flood flood_fill(char *map, t_game *game, t_flood state)
{
    if (!is_valid_position(state, state.x, state.y, map))
        return (state);
    
    state = check_cell(map, state);
    
    t_flood new_state;
    
    new_state = flood_fill(map, game, (t_flood){state.x - 1, state.y, 
        state.collectibles, state.exit, state.width, state.height});
    update_state(&state, new_state);
    new_state = flood_fill(map, game, (t_flood){state.x + 1, state.y,
        state.collectibles, state.exit, state.width, state.height});
    update_state(&state, new_state);
    new_state = flood_fill(map, game, (t_flood){state.x, state.y - 1,
        state.collectibles, state.exit, state.width, state.height});
    update_state(&state, new_state);
    new_state = flood_fill(map, game, (t_flood){state.x, state.y + 1,
        state.collectibles, state.exit, state.width, state.height});
    update_state(&state, new_state);
    return (state);
}


/*************************************************************** */
/***************************************************************** */
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
