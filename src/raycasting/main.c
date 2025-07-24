/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:15:38 by ufalzone          #+#    #+#             */
/*   Updated: 2025/07/24 15:13:28 by ufalzone         ###   ########.fr       */
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

void draw_square(int x, int y, int size, int color, t_game *game)
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
                draw_square(x * BLOCKSIZE, y * BLOCKSIZE, BLOCKSIZE, color, game);            
            x++;
        }
        y++;
    }
}

char **get_map(void)
{
    char **map = malloc(sizeof(char *) * 11);
    map[0] = "111111111111111";
    map[1] = "101000000000001";
    map[2] = "100000000000001";
    map[3] = "100000100000101";
    map[4] = "101000000000001";
    map[5] = "100000010000001";
    map[6] = "100001000001001";
    map[7] = "100000000000101";
    map[8] = "110000000000011";
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
    init_player(WIDHT / 2, HEIGHT / 2, PI / 2, &game->player);
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

float distance (float x, float y)
{
    return sqrt(x * x + y * y);
}

void draw_line(t_player *player, t_game *game, float start_x, int i)
{
    float ray_x;
    float ray_y;
    float cos_angle;
    float sin_angle;
    
    cos_angle = cos(start_x);
    sin_angle = sin(start_x);
    ray_x = player->x;
    ray_y = player->y;
    while (!touch(ray_x, ray_y, game))
    {
        put_pixel(ray_x, ray_y, 0xFF0000, game);
        ray_x += cos_angle;
        ray_y += sin_angle;
    }

    float dist = distance(ray_x - player->y, ray_y - player->y);
    float height = (BLOCKSIZE / dist) * (WIDHT / 2);
    int start_y = (HEIGHT - height) / 2;
    int end = start_y + height;
    while (start_y < end)
    {
        put_pixel(i, start_y, 255, game);
        start_y++;
    }
}


int draw_loop(t_game *game)
{
    t_player *player;
    float ray_x;
    float ray_y;
    
    player = &game->player;
    clear_image(game);
    move_player(player);
    draw_square(player->x, player->y, 15, 0x00FF, game);
    draw_map(game);

    float fraction = PI / 3 / WIDHT; //PI / 3 = FOV (60degres) - FOV / WIDHT = angle couvert par un seul pixel
    // PI / 3 → 60° en radians. (FOV)

    // On divise par WIDTH (disons 640) :
    // fraction=π/3640=60∘640≈0,09375∘≈0,001635 rad
    // fraction=640π/3​=64060∘​≈0,09375∘≈0,001635rad

    // Sens concret :
    // Entre la colonne 0 et la colonne 1, on tourne la tête de 0,09375°.

    // Après 640 incréments, on aura parcouru les 60° complets.

    // printf("fraction : %f\n", fraction);
    float start_x = player->angle - PI / 6;
    //reculer de la moitie du fov, on veut le bord gauche du cone de vision
    int i = 0;
    while (i < WIDHT)
    {
        draw_line(player, game, start_x, i);
        start_x += fraction;
        i++;
    } //la boucle part de la gauche du fov, puis incremente start_x pour qu'il balaye pixel par pixel tout le fov
    //si fov 60, et angle de vue = 0, on part de -30 et on va jusqu'a +30 (= 60)

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