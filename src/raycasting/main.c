/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:15:38 by ufalzone          #+#    #+#             */
/*   Updated: 2025/07/24 17:03:13 by ufalzone         ###   ########.fr       */
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


void draw_map(t_game *game, int origin_x, int origin_y)
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
                draw_square(origin_x + x * MINIMAP_BLOCKSIZE, origin_y + y * MINIMAP_BLOCKSIZE, MINIMAP_BLOCKSIZE, color, game);            
            x++;
        }
        y++;
    }
}
static void	fill_rect(t_game *game, int x0, int y0, int w, int h)
{
	int	x;
	int	y;

	y = 0;
	while (y < h)
	{
		x = 0;
		while (x < w)
		{
			put_pixel(x0 + x, y0 + y, 0x000000, game);
			x++;
		}
		y++;
	}
}

void draw_minimap(t_game *game, t_player *player)
{
    int margin   = 25;
    int origin_x = WIDHT - (game->nb_column * MINIMAP_BLOCKSIZE) - margin;
    int origin_y = margin;
    fill_rect(game, origin_x, origin_y, game->nb_column * MINIMAP_BLOCKSIZE, game->nb_lines * MINIMAP_BLOCKSIZE);
    
    draw_map(game, origin_x, origin_y);

    int mini_px = origin_x + (int)(player->x * MINI_FACTOR) + MINIMAP_BLOCKSIZE / 2;
    int mini_py = origin_y + (int)(player->y * MINI_FACTOR) + MINIMAP_BLOCKSIZE / 2;

    draw_square(mini_px - 2, mini_py - 2, 4, 0x00FF, game);
}


char **get_map(void)
{
    char **map = malloc(sizeof(char *) * 11);
    map[0] = "111111111111111";
    map[1] = "101000000000001";
    map[2] = "100100000000001";
    map[3] = "100010100000001";
    map[4] = "100000000000001";
    map[5] = "101100010000001";
    map[6] = "101101000000001";
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
    init_player(WIDHT / 2, HEIGHT / 2, PI / 2, &game->player);
    game->map = get_map();
    game->nb_column = 15;
    game->nb_lines = 10;
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

float fixed_dist(float x1, float y1, float x2, float y2, t_game *game)
{
    float delta_x = x2 - x1;
    float delta_y = y2 - y1;
    float angle = atan2(delta_y, delta_x) - game->player.angle;
    float fix_dist = distance(delta_x, delta_y) * cos(angle);
    return fix_dist;
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
        // put_pixel(ray_x, ray_y, 0xFF0000, game);
        ray_x += cos_angle;
        ray_y += sin_angle;
    }

    float dist = fixed_dist(player->x, player->y, ray_x, ray_y, game);
    float height = (BLOCKSIZE / dist) * (WIDHT / 2);
    int start_y = (HEIGHT - height) / 2;
    int end = start_y + height;
    //ciel
    int y = 0;
    while (y < start_y)
    {
        put_pixel(i, y, SKY_COLOR, game);
        y++;
    }
    while (start_y < end)
    {
        put_pixel(i, start_y, 255, game);
        start_y++;
    }
    //sol
    y = end + 1;
    while (y < HEIGHT)
    {
        put_pixel(i, y, FLOOR_COLOR, game);
        y++;
    }
}

int draw_loop(t_game *game)
{
    t_player *player;
    float ray_x;
    float ray_y;
    
    player = &game->player;
    clear_image(game);
    move_player(player, game);
    // draw_square(player->x, player->y, 15, 0x00FF, game);
    // draw_map(game);

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
    draw_minimap(game, player);
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