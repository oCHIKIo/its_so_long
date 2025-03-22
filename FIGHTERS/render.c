/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:54:34 by bchiki            #+#    #+#             */
/*   Updated: 2025/03/22 01:39:51 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void render_map(t_game *game)
{
    t_nbr nbr;

    nbr.y = 0;
    while (nbr.y < game->height)
    {
        nbr.x = 0;
        while (nbr.x < game->width)
        {
            render_wall_floor(game, &nbr);    
            render_collectibles(game, &nbr);  
            render_exits(game, &nbr);     
            render_player(game, &nbr);       
            nbr.x++;
        }
        nbr.y++;
    }
}
