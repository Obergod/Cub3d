/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:51:20 by ufalzone          #+#    #+#             */
/*   Updated: 2025/11/10 18:51:20 by ufalzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

static double	get_delta(double value)
{
	if (value == 0)
		return (1e30);
	return (fabs(1.0 / value));
}

static void	set_step_x(t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (ray->pos_x - ray->map_x) * ray->delta_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - ray->pos_x) * ray->delta_x;
	}
}

static void	set_step_y(t_ray *ray)
{
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (ray->pos_y - ray->map_y) * ray->delta_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - ray->pos_y) * ray->delta_y;
	}
}

void	init_ray(t_ray *ray, t_player *player, double angle)
{
	ray->dir_x = cos(angle);
	ray->dir_y = sin(angle);
	ray->pos_x = player->x / BLOCKSIZE;
	ray->pos_y = player->y / BLOCKSIZE;
	ray->map_x = (int)ray->pos_x;
	ray->map_y = (int)ray->pos_y;
	ray->delta_x = get_delta(ray->dir_x);
	ray->delta_y = get_delta(ray->dir_y);
	set_step_x(ray);
	set_step_y(ray);
}
