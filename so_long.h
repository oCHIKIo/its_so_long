/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 01:08:25 by bchiki            #+#    #+#             */
/*   Updated: 2025/03/19 03:30:54 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
#define SO_LONG_H


#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include "mlx/mlx.h"
#include "not_your_printf/ft_printf.h"

typedef struct s_game 
{
    void *mlx;
    void *win;
}               t_game;

#endif