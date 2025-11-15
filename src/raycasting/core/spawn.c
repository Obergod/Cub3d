/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 19:45:32 by ufalzone          #+#    #+#             */
/*   Updated: 2025/11/10 19:45:32 by ufalzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

static float	player_angle_from_dir(char dir)
{
	if (dir == 'N')
		return (3 * PI / 2);
	if (dir == 'S')
		return (PI / 2);
	if (dir == 'W')
		return (PI);
	return (0);
}

static void	set_player_from_map(t_game *game)
{
	float	x;
	float	y;
	float	angle;

	x = (game->cub->player_col + 0.5f) * BLOCKSIZE;
	y = (game->cub->player_row + 0.5f) * BLOCKSIZE;
	angle = player_angle_from_dir(game->cub->player_dir);
	init_player(x, y, angle, &game->player);
}

void	set_map_data(t_game *game)
{
	game->map = game->cub->map;
	set_player_from_map(game);
	game->nb_column = game->cub->map_width;
	game->nb_lines = game->cub->map_height;
	if (game->nb_column <= 0)
		game->nb_column = 1;
	if (game->nb_lines <= 0)
		game->nb_lines = 1;
}
