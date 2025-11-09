/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:51:15 by ufalzone          #+#    #+#             */
/*   Updated: 2025/11/10 18:51:15 by ufalzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

static int    fill_rgb_array(char **parts, int rgb[3])
{
    int        i;
    long    value;

    i = 0;
    while (parts[i])
    {
        if (i >= 3)
            return (1);
        value = ft_atol(parts[i]);
        if (value < 0 || value > 255)
            return (1);
        rgb[i] = value;
        i++;
    }
    return (i != 3);
}

static int    rgb_from_line(char *line, int *color)
{
    char    **parts;
    int        rgb[3];

    if (!line || !*line)
        return (1);
    parts = ft_split(line, ',');
    if (!parts)
        return (1);
    if (fill_rgb_array(parts, rgb) != 0)
    {
        ft_free_split(parts);
        return (1);
    }
    *color = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
    ft_free_split(parts);
    return (0);
}

int    init_colors(t_game *game)
{
    if (!game->cub->textures || !game->cub->textures[FLOOR]
        || !game->cub->textures[CEILING])
        return (1);
    if (rgb_from_line(game->cub->textures[FLOOR], &game->floor_color) != 0)
        return (1);
    if (rgb_from_line(game->cub->textures[CEILING],
            &game->ceiling_color) != 0)
        return (1);
    return (0);
}
