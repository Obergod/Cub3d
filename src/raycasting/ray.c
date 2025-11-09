/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 21:18:46 by ufalzone          #+#    #+#             */
/*   Updated: 2025/11/07 21:18:46 by ufalzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/raycasting.h"

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

void	step_ray(t_ray *ray, t_game *game)
{
	int		row_len;
	char	*row;

	while (1)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_y < 0 || !game->map[ray->map_y])
			break ;
		row = game->map[ray->map_y];
		row_len = ft_strlen(row);
		if (ray->map_x < 0 || ray->map_x >= row_len)
			break ;
		if (row[ray->map_x] == '1')
			break ;
	}
}

static void	set_ray_texture(t_ray *ray)
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

void	resolve_ray(t_ray *ray)
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
