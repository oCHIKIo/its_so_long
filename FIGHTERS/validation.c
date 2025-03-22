/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 18:14:53 by bchiki            #+#    #+#             */
/*   Updated: 2025/03/22 01:49:02 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int validate_map(t_game *game)
{
    int p_count = 0, e_count = 0, c_count = 0;

    if (!check_empty_lines_and_walls(game))
        return (0);
    if (is_all_walls(game))
    {
        ft_printf("\033[1;38;5;51mError: Map contains only walls\033[0m\n");
        return (0);
    }
    if (!count_map_elements(game, &p_count, &e_count, &c_count))
        return (0);
    if (!validate_element_counts(p_count, e_count, c_count))
        return (0);
    if (!check_player_surrounded(game))
        return (0);
    if (!can_reach_collectibles_and_exit(game))
        return (0);
    return (1);
}
