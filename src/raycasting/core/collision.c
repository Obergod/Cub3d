/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 19:45:42 by ufalzone          #+#    #+#             */
/*   Updated: 2025/11/10 19:45:42 by ufalzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

static bool    out_of_bounds(float px, float py, t_game *game)
{
    int    x;
    int    y;
    int    len;

    if (px < 0 || py < 0 || !game->map)
        return (true);
    y = (int)(py / BLOCKSIZE);
    if (y < 0 || y >= game->cub->map_height || !game->map[y])
        return (true);
    x = (int)(px / BLOCKSIZE);
    len = ft_strlen(game->map[y]);
    if (x < 0 || x >= len)
        return (true);
    return (false);
}

bool    is_blocked(float px, float py, t_game *game)
{
    int    x;
    int    y;
    char    cell;

    if (out_of_bounds(px, py, game))
        return (true);
    y = (int)(py / BLOCKSIZE);
    x = (int)(px / BLOCKSIZE);
    cell = game->map[y][x];
    if (cell == '1' || cell == ' ')
        return (true);
    return (false);
}
