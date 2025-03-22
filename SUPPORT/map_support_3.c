/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_support_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 01:09:10 by bchiki            #+#    #+#             */
/*   Updated: 2025/03/22 01:10:17 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void check_trailing_newlines(char *content, size_t len)
{
    size_t i;

    i = len;
    while (i > 0 && content[i - 1] == '\n')
        i--;
    if (i < len)
    {
        ft_printf("\033[1;38;5;51mError: Intruder line\033[0m\n");
        free(content);
        exit(1);
    }
}

void check_consecutive_newlines(char *content, size_t len)
{
    size_t i;

    i = 0;
    while (i < len - 1)
    {
        if (content[i] == '\n' && content[i + 1] == '\n')
        {
            ft_printf("\033[1;38;5;51mError: Intruder line\033[0m\n");
            free(content);
            exit(1);
        }
        i++;
    }
}

void check_trailing_empty_lines(char *content)
{
    size_t len = 0;

    while (content[len] != '\0')
        len++;
    if (len == 0)
        return;
    check_trailing_newlines(content, len);
    check_consecutive_newlines(content, len);
}
