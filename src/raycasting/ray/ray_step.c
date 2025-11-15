/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_step.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:51:24 by ufalzone          #+#    #+#             */
/*   Updated: 2025/11/10 18:51:24 by ufalzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

static void	advance_ray(t_ray *ray)
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
}

static bool	hit_wall(t_ray *ray, t_game *game)
{
	char	*row;
	int		row_len;

	if (ray->map_y < 0 || !game->map[ray->map_y])
		return (true);
	row = game->map[ray->map_y];
	row_len = ft_strlen(row);
	if (ray->map_x < 0 || ray->map_x >= row_len)
		return (true);
	if (row[ray->map_x] == '1')
		return (true);
	return (false);
}

void	step_ray(t_ray *ray, t_game *game)
{
	while (1)
	{
		advance_ray(ray);
		if (hit_wall(ray, game))
			break ;
	}
}
