/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_resolve.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 19:46:20 by ufalzone          #+#    #+#             */
/*   Updated: 2025/11/10 19:46:20 by ufalzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

static void    set_ray_texture(t_ray *ray)
{
    if (ray->side == 0)
    {
        if (ray->dir_x > 0)
            ray->tex_id = EA_TEXT;
        else
            ray->tex_id = WE_TEXT;
    }
    else if (ray->dir_y > 0)
        ray->tex_id = SO_TEXT;
    else
        ray->tex_id = NO_TEXT;
}

void    resolve_ray(t_ray *ray)
{
    if (ray->side == 0)
        ray->wall_dist = (ray->map_x - ray->pos_x + (1 - ray->step_x) / 2.0)
            / ray->dir_x;
    else
        ray->wall_dist = (ray->map_y - ray->pos_y + (1 - ray->step_y) / 2.0)
            / ray->dir_y;
    if (ray->wall_dist <= 0.0)
        ray->wall_dist = 0.0001;
    if (ray->side == 0)
        ray->wall_x = ray->pos_y + ray->wall_dist * ray->dir_y;
    else
        ray->wall_x = ray->pos_x + ray->wall_dist * ray->dir_x;
    ray->wall_x -= floor(ray->wall_x);
    if (ray->wall_x < 0)
        ray->wall_x = 0;
    set_ray_texture(ray);
}
