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

void draw_map(t_game *game)
{
    char **map;
    int color;
    int y;
    int x;

    map = game->map;
    color = 0xFFFFFF;
    y = 0;
    while (map[y])
    {
        x = 0;
        while (map[y][x])
        {
            if (map[y][x] == '1')
                draw_circle(x * BLOCKSIZE, y * BLOCKSIZE, BLOCKSIZE, color, game);            
            x++;
        }
        y++;
    }
}

char **get_map(void)
{
    char **map = malloc(sizeof(char *) * 11);
    map[0] = "111111111111111";
    map[1] = "100000000000001";
    map[2] = "100000000000001";
    map[3] = "100000100000001";
    map[4] = "100000000000001";
    map[5] = "100000010000001";
    map[6] = "100001000000001";
    map[7] = "100000000000001";
    map[8] = "100000000000001";
    map[9] = "111111111111111";
    map[10] = NULL;
    return (map);
}

void clear_image(t_game *game)
{
    int y;
    int x;

    y = 0;
    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDHT)
        {
            put_pixel(x, y, 0, game);
            x++;
        }
        y++;
    }
}

void init_game(t_game *game)
{
    init_player(WIDHT / 2, HEIGHT / 2, 0, &game->player);
    game->map = get_map();
    game->mlx = mlx_init();
    game->win = mlx_new_window(game->mlx, WIDHT, HEIGHT, "Cub3D");
    game->img = mlx_new_image(game->mlx, WIDHT, HEIGHT);
    game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, &game->endian);
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

bool touch(float px, float py, t_game *game)
{
    int x = px / BLOCKSIZE;
    int y = py / BLOCKSIZE;
    if (game->map[y][x] == '1')
        return true;
    return false;
}


int draw_loop(t_game *game)
{
    t_player *player;
    float ray_x;
    float ray_y;
    
    player = &game->player;
    clear_image(game);
    move_player(player);
    draw_circle(player->x, player->y, 15, 0x00FF, game);
    draw_map(game);
    ray_x = player->x;
    ray_y = player->y;
    while (!touch(ray_x, ray_y, game))
    {
        put_pixel(ray_x, ray_y, 0xFF0000, game);
        ray_x += cos(player->angle);
        ray_y += sin(player->angle);
    }

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