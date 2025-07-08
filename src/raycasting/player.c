/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:54:45 by ufalzone          #+#    #+#             */
/*   Updated: 2025/07/08 17:00:13 by ufalzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/raycasting.h"

void init_player(float x, float y, t_player *player)
{
    player->x = x;
    player->y = y;

    player->key_down = false;
    player->key_right = false;
    player->key_left = false;
    player->key_up = false;
    
}