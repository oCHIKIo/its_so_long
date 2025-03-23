/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:52:24 by bchiki            #+#    #+#             */
/*   Updated: 2025/03/23 05:57:38 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

char    *read_map(char *file)
{
    int fd = open(file, O_RDONLY);
    int size = get_file_size(file);
    char *map = malloc(size + 1);
    int i = 0;
    char c;
    if (!map)
    {
        ft_putstr_fd("\033[1;31mError: Memory allocation failed\033[0m\n", 2);
        exit(1);
    }
    while (read(fd, &c, 1) > 0)
        map[i++] = c;
    map[i] = '\0';
    close(fd);
    return (map);
}

int check_map_validity(t_game *game)
{
    int all_walls = 1;
    if (!check_start_line(game))
        return (0);
    if (!get_map_width(game))
        return (0);
    if (!check_map_lines(game, &all_walls))
        return (0);
    if (!check_end_conditions(game, all_walls))
        return (0);
    return (1);
}

void count_elements(t_game *game)
{
    t_count count;
    init_counts(game, &count);

    while (count.y < game->height)
    {
        count.x = 0;
        while (count.x < game->width)
        {
            if (!check_symbol(game, &count))
                return;
            if (!check_player_exit(game, &count))
                return;
            count.x++;
            count.i++;
        }
        count.i++; // Skip '\n'
        count.y++;
    }
}
