/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:50:41 by ufalzone          #+#    #+#             */
/*   Updated: 2025/11/15 18:37:53 by ufalzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

static void	render_column(t_game *game, double angle, int column)
{
	t_ray		ray;
	t_texture	*tex;
	t_column	col;

	init_ray(&ray, &game->player, angle);
	step_ray(&ray, game);
	resolve_ray(&ray);
	ray.wall_dist *= cos(angle - game->player.angle);
	if (ray.wall_dist <= 0.0)
		ray.wall_dist = 0.0001;
	tex = &game->textures[ray.tex_id];
	prepare_column(&col, &ray, tex);
	draw_ceiling(game, column, col.start);
	draw_wall_segment(game, tex, &col, column);
	draw_floor(game, column, col.end + 1);
}

void	render_frame(t_game *game)
{
	double	angle;
	double	step;
	int		column;

	angle = game->player.angle - ((PI / 3.0) / 2.0);
	step = (PI / 3.0) / WIDHT;
	column = 0;
	while (column < WIDHT)
	{
		render_column(game, angle, column);
		angle += step;
		column++;
	}
}

int	draw_loop(t_game *game)
{
	clear_image(game);
	move_player(&game->player, game);
	render_frame(game);
	draw_minimap(game, &game->player);
	mlx_put_image_to_window(game->cub->mlx, game->cub->win, game->cub->img, 0,
		0);
	return (0);
}
