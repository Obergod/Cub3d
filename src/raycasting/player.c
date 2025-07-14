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

void init_player(float x, float y, float angle, t_player *player)
{
    player->x = x;
    player->y = y;
    player->angle = angle;

    player->key_down = false;
    player->key_right = false;
    player->key_left = false;
    player->key_up = false;   
}

int key_press(int keycode, t_player *player)
{
    if (keycode == W)
        player->key_up = true;
    if (keycode == S)
        player->key_down = true;
    if (keycode == A)
        player->key_left = true;
    if (keycode == D)
        player->key_right = true;
    if (keycode == LEFT)
        player->left_rotate = true;
    if (keycode == RIGHT)
        player->right_rotate = true
    return (0);
}

int key_release(int keycode, t_player *player)
{
    if (keycode == W)
        player->key_up = false;
    if (keycode == S)
        player->key_down = false;
    if (keycode == A)
        player->key_left = false;
    if (keycode == D)
        player->key_right = false;
    if (keycode == LEFT)
        player->left_rotate = false;
    if (keycode == RIGHT)
        player->right_rotate = false
    return (0);
}

void move_player(t_player *player)
{
    float speed;
    float angle_speed;
    float cos_angle;
    float sin_angle;
    
    speed = 0.5;
    angle_speed = 0.1;
    cos_angle = cos(player->angle);
    sin_angle = sin(player->angle);

    if (player->left_rotate)
        player->angle -= angle_speed;
    if (player->right_rotate)
        player->angle += angle_speed;
    
    if (player->angle > 2 * PI)
        player-> angle = 0;
    if (player->angle < 0)
        player->angle = 2 * PI;

    if (player->key_up)
        player->y -= speed;
    if (player->key_down)
        player->y += speed;
    if (player->key_left)
        player->x -= speed;
    if (player->key_right)
        player->x += speed;
}