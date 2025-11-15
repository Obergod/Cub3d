/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:51:08 by ufalzone          #+#    #+#             */
/*   Updated: 2025/11/10 18:51:08 by ufalzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

#define MOVE_SPEED 0.5f
#define ROT_SPEED 0.01f

static void	move_linear(t_player *player, t_game *game, float dx, float dy)
{
	float	new_x;
	float	new_y;

	new_x = player->x + dx;
	if (!is_blocked(new_x, player->y, game))
		player->x = new_x;
	new_y = player->y + dy;
	if (!is_blocked(player->x, new_y, game))
		player->y = new_y;
}

static void	move_forward_back(t_player *player, t_game *game, float cos_a,
		float sin_a)
{
	float	step_x;
	float	step_y;

	step_x = cos_a * MOVE_SPEED;
	step_y = sin_a * MOVE_SPEED;
	if (player->key_up)
		move_linear(player, game, step_x, step_y);
	if (player->key_down)
		move_linear(player, game, -step_x, -step_y);
}

static void	move_strafe(t_player *player, t_game *game, float cos_a,
		float sin_a)
{
	float	step_x;
	float	step_y;

	step_x = sin_a * MOVE_SPEED;
	step_y = cos_a * MOVE_SPEED;
	if (player->key_left)
		move_linear(player, game, step_x, -step_y);
	if (player->key_right)
		move_linear(player, game, -step_x, step_y);
}

void	move_player(t_player *player, t_game *game)
{
	float	cos_a;
	float	sin_a;

	if (player->left_rotate)
		player->angle -= ROT_SPEED;
	if (player->right_rotate)
		player->angle += ROT_SPEED;
	if (player->angle >= 2 * PI)
		player->angle -= 2 * PI;
	if (player->angle < 0)
		player->angle += 2 * PI;
	cos_a = cos(player->angle);
	sin_a = sin(player->angle);
	move_forward_back(player, game, cos_a, sin_a);
	move_strafe(player, game, cos_a, sin_a);
}
