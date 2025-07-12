/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugo <ugo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:15:38 by ufalzone          #+#    #+#             */
/*   Updated: 2025/07/12 14:20:02 by ugo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/raycasting.h"

void put_pixel(int x, int y, int color, t_game *game)
{
    int index;

    if (x >= WIDHT || y >= HEIGHT || y < 0 || x < 0)
        return ;
    index = y * game->size_line + x * game->bpp / 8;
    game->data[index] = color & 0xFF;
    game->data[index + 1] = (color >> 8) & 0xFF;
    game->data[index + 2] = (color >> 16) & 0xFF;
}

void draw_circle(int x, int y, int size, int color, t_game *game)
{
    int i; 
    
    for (i = 0; i < size ; i++)
        put_pixel(x + i, y, color, game);
    for (i = 0; i < size ; i++)
        put_pixel(x, y + i, color, game);
    for (i = 0; i < size ; i++)
        put_pixel(x + size, y + i, color, game);
    for (i = 0; i < size ; i++)
        put_pixel(x + i, y + size, color, game);
}

void init_game(t_game *game)
{
    init_player(WIDHT / 2, HEIGHT / 2, &game->player);
    game->mlx = mlx_init();
    game->win = mlx_new_window(game->mlx, WIDHT, HEIGHT, "Cub3D");
    game->img = mlx_new_image(game->mlx, WIDHT, HEIGHT);
    game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, &game->endian);
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

int draw_loop(t_game *game)
{
    t_player *player = &game->player;
    move_player(player);
    draw_circle(player->x, player->y, 15, 0x00FF00, game);
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}                               

int main()
{
    t_game game;

    init_game(&game);
    mlx_hook(game.win, 2, 1L<<0, key_press, &game.player);
    mlx_hook(game.win, 3, 1L<<1, key_release, &game.player);
    

    mlx_loop_hook(game.mlx, draw_loop, &game);
    mlx_loop(game.mlx);
}