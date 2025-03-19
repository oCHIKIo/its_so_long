/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 01:08:10 by bchiki            #+#    #+#             */
/*   Updated: 2025/03/19 03:28:11 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int close_window(t_game *game) 
{
    mlx_destroy_window(game->mlx, game->win);
    exit(0);
}
int main(int argc, char **argv) 
{
    if (argc != 2) 
    {
        ft_printf("Error: Usage: ./so_long <map>.ber\n");
        return (1);
    }
    ft_printf("Map file: %s\n", argv[1]);
    return (0);
}