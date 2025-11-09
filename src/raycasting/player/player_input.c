/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:51:03 by ufalzone          #+#    #+#             */
/*   Updated: 2025/11/10 18:51:03 by ufalzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

int    key_press(int keycode, t_player *player)
{
    if (keycode == W)
        player->key_up = true;
    else if (keycode == S)
        player->key_down = true;
    else if (keycode == A)
        player->key_left = true;
    else if (keycode == D)
        player->key_right = true;
    else if (keycode == LEFT)
        player->left_rotate = true;
    else if (keycode == RIGHT)
        player->right_rotate = true;
    return (0);
}

int    key_release(int keycode, t_player *player)
{
    if (keycode == W)
        player->key_up = false;
    else if (keycode == S)
        player->key_down = false;
    else if (keycode == A)
        player->key_left = false;
    else if (keycode == D)
        player->key_right = false;
    else if (keycode == LEFT)
        player->left_rotate = false;
    else if (keycode == RIGHT)
        player->right_rotate = false;
    return (0);
}
