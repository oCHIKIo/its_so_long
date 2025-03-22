/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 18:10:37 by bchiki            #+#    #+#             */
/*   Updated: 2025/03/22 00:48:40 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

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