/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 03:35:11 by bchiki            #+#    #+#             */
/*   Updated: 2025/03/19 18:02:41 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static char *read_file(char *filename)
{
    int fd = open(filename, O_RDONLY);
    char *buffer = malloc(1024);
    char *line = NULL;
    ssize_t bytes;

    if (fd < 0)
    {
        perror("Error opening file");
        return (NULL);
    }
    bytes = read(fd, buffer, 1024);
    if (bytes <= 0)
    {
        free(buffer);
        close(fd);
        return (NULL);
    }
    buffer[bytes] = '\0';
    line = buffer;
    close(fd);
    return (line);
}

void parse_map(t_game *game, char *filename)
{
    char *content = read_file(filename);
    char *temp = content;
    int i;
    int len;

    if (!content)
    {
        ft_printf("Error: Failed to read map\n");
        exit(1);
    }
    game->height = 0;
    while (*temp)
    {
        if (*temp == '\n')
            game->height++;
        temp++;
    }
    if (content[strlen(content) - 1] == '\n')
        game->height--;
    game->height++;
    game->map = malloc(sizeof(char *) * game->height);
    temp = content;
    i = 0;
    while (i < game->height)
    {
        len = 0;
        while (temp[len] && temp[len] != '\n')
            len++;
        game->map[i] = strndup(temp, len);
        temp += len;
        if (*temp == '\n')
            temp++;
        i++;
    }
    game->width = 0;
    while (game->map[0][game->width])
        game->width++;
    free(content);
}