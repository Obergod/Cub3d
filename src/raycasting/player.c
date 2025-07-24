/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:54:45 by ufalzone          #+#    #+#             */
/*   Updated: 2025/07/24 17:42:47 by ufalzone         ###   ########.fr       */
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
        player->right_rotate = true;
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
        player->right_rotate = false;
    return (0);
}

void move_player(t_player *player, t_game *game)
{
    float speed;
    float angle_speed;
    float cos_angle;
    float sin_angle;
    
    speed = 0.5;
    angle_speed = 0.01;

    if (player->left_rotate)
        player->angle -= angle_speed;
    if (player->right_rotate)
        player->angle += angle_speed;
    
    if (player->angle > 2 * PI)
        player-> angle = 0;
    if (player->angle < 0)
        player->angle = 2 * PI;
    cos_angle = cos(player->angle);
    sin_angle = sin(player->angle);

    //bouge ou regarde le joueur
    if (player->key_up)
    {
        float new_x = player->x + cos_angle * speed;
        if (!touch((int)new_x, (int)player->y, game))
            player->x = new_x;
        float new_y = player->y + sin_angle * speed;
        if (!touch((int)player->x, (int)new_y, game))
            player->y = new_y; 
    }
    if (player->key_down)
    {
        float new_x = player->x - cos_angle * speed;
        if (!touch((int)new_x, (int)player->y, game))
            player->x = new_x;
        float new_y = player->y - sin_angle * speed;
        if (!touch((int)player->x, (int)new_y, game))
            player->y = new_y; 
    }
    if (player->key_left)
    {
        float new_x = player->x + sin_angle * speed;
        if (!touch((int)new_x, (int)player->y, game))
            player->x = new_x;
        float new_y = player->y - cos_angle * speed;
        if (!touch((int)player->x, (int)new_y, game))
            player->y = new_y; 
    }
    if (player->key_right)
    {
        float new_x = player->x - sin_angle * speed;
        if (!touch((int)new_x, (int)player->y, game))
            player->x = new_x;
        float new_y = player->y + cos_angle * speed;
        if (!touch((int)player->x, (int)new_y, game))
            player->y = new_y; 
    }
}