/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_support_4.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 02:21:44 by bchiki            #+#    #+#             */
/*   Updated: 2025/03/22 02:43:24 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void allocate_visited_rows(t_game *game, char **visited, int y)
{
    if (y >= game->height)
        return;
    
    visited[y] = malloc(sizeof(char) * game->width);
    if (!visited[y])
    {
        if (y > 0)
            free_visited_rows(game, visited, y - 1); 
        free(visited);
        ft_printf("\033[1;38;5;51mError: Memory allocation failed for visited array\033[0m\n");
        exit(0); 
    }
    set_row_to_zero(game, visited[y], 0);
    allocate_visited_rows(game, visited, y + 1);
}
void set_row_to_zero(t_game *game, char *row, int x)
{
    if (x >= game->width)
        return;
    row[x] = 0;
    set_row_to_zero(game, row, x + 1);
}

void count_collectibles_recursive(t_game *game, int y, int x, int *total)
{
    if (y >= game->height)
        return;
    if (x >= game->width)
    {
        count_collectibles_recursive(game, y + 1, 0, total);
        return;
    }
    if (game->map[y][x] == 'C')
        (*total)++;
    count_collectibles_recursive(game, y, x + 1, total);
}

void free_visited_rows(t_game *game, char **visited, int y)
{
    if (y < 0)
        return;
    free(visited[y]);
    free_visited_rows(game, visited, y - 1);
}

void perform_flood_fill(t_game *game, char **visited, int *collectibles_reached, int *exit_reached)
{
    flood_fill(game, game->player_x, game->player_y, collectibles_reached, exit_reached, visited);
}
