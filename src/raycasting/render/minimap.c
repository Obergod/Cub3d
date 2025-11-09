/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:50:36 by ufalzone          #+#    #+#             */
/*   Updated: 2025/11/10 18:50:36 by ufalzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

static void    draw_square(t_game *game, t_point pos, int size, int color)
{
    int    i;

    i = 0;
    while (i <= size)
    {
        put_pixel(pos.x + i, pos.y, color, game);
        put_pixel(pos.x, pos.y + i, color, game);
        put_pixel(pos.x + size, pos.y + i, color, game);
        put_pixel(pos.x + i, pos.y + size, color, game);
        i++;
    }
}

static void    fill_rect(t_game *game, t_rect rect)
{
    int    y;
    int    x;

    y = 0;
    while (y < rect.h)
    {
        x = 0;
        while (x < rect.w)
        {
            put_pixel(rect.x + x, rect.y + y, 0x000000, game);
            x++;
        }
        y++;
    }
}

static void    draw_map(t_game *game, t_point origin)
{
    int        y;
    int        x;
    t_point    cell;

    y = 0;
    while (game->map[y])
    {
        x = 0;
        while (game->map[y][x])
        {
            if (game->map[y][x] == '1')
            {
                cell.x = origin.x + x * MINIMAP_BLOCKSIZE;
                cell.y = origin.y + y * MINIMAP_BLOCKSIZE;
                draw_square(game, cell, MINIMAP_BLOCKSIZE, 0xFFFFFF);
            }
            x++;
        }
        y++;
    }
}

void    draw_minimap(t_game *game, t_player *player)
{
    int        margin;
    t_point    origin;
    t_point    marker;
    t_rect    area;

    margin = 25;
    origin.x = WIDHT - game->nb_column * MINIMAP_BLOCKSIZE - margin;
    origin.y = margin;
    area.x = origin.x;
    area.y = origin.y;
    area.w = game->nb_column * MINIMAP_BLOCKSIZE;
    area.h = game->nb_lines * MINIMAP_BLOCKSIZE;
    fill_rect(game, area);
    draw_map(game, origin);
    marker.x = origin.x
        + (int)((player->x / BLOCKSIZE) * MINIMAP_BLOCKSIZE);
    marker.y = origin.y
        + (int)((player->y / BLOCKSIZE) * MINIMAP_BLOCKSIZE);
    marker.x -= 2;
    marker.y -= 2;
    draw_square(game, marker, 4, 0x00FF);
}
