/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   column.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 19:46:05 by ufalzone          #+#    #+#             */
/*   Updated: 2025/11/10 19:46:05 by ufalzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	prepare_column(t_column *col, t_ray *ray, t_texture *tex)
{
	col->height = HEIGHT / ray->wall_dist;
	if (col->height < 1)
		col->height = 1;
	col->start = (HEIGHT - col->height) / 2;
	if (col->start < 0)
		col->start = 0;
	col->end = (HEIGHT + col->height) / 2 - 1;
	if (col->end >= HEIGHT)
		col->end = HEIGHT - 1;
	col->tex_x = (int)(ray->wall_x * tex->width);
	if ((ray->side == 0 && ray->dir_x > 0) || (ray->side == 1
			&& ray->dir_y < 0))
		col->tex_x = tex->width - col->tex_x - 1;
	if (col->tex_x < 0)
		col->tex_x = 0;
	if (col->tex_x >= tex->width)
		col->tex_x = tex->width - 1;
	col->step = (double)tex->height / col->height;
	col->tex_pos = (col->start - HEIGHT / 2 + col->height / 2) * col->step;
}

void	draw_ceiling(t_game *game, int column, int end)
{
	int	y;

	if (end < 0)
		end = 0;
	if (end > HEIGHT)
		end = HEIGHT;
	y = 0;
	while (y < end)
	{
		put_pixel(column, y, game->ceiling_color, game);
		y++;
	}
}

void	draw_floor(t_game *game, int column, int start)
{
	int	y;

	if (start < 0)
		start = 0;
	if (start >= HEIGHT)
		return ;
	y = start;
	while (y < HEIGHT)
	{
		put_pixel(column, y, game->floor_color, game);
		y++;
	}
}

void	draw_wall_segment(t_game *game, t_texture *tex, t_column *col,
		int column)
{
	int	y;
	int	tex_y;
	int	color;

	y = col->start;
	while (y <= col->end)
	{
		tex_y = (int)col->tex_pos;
		if (tex_y >= tex->height)
			tex_y = tex->height - 1;
		color = get_texture_color(tex, col->tex_x, tex_y);
		put_pixel(column, y, color, game);
		col->tex_pos += col->step;
		y++;
	}
}
