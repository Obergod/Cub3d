/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:50:57 by ufalzone          #+#    #+#             */
/*   Updated: 2025/11/10 18:50:57 by ufalzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void    init_player(float x, float y, float angle, t_player *player)
{
    player->x = x;
    player->y = y;
    player->angle = angle;
    player->key_down = false;
    player->key_right = false;
    player->key_left = false;
    player->key_up = false;
    player->left_rotate = false;
    player->right_rotate = false;
}
