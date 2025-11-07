/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:15:38 by ufalzone          #+#    #+#             */
/*   Updated: 2025/11/07 19:37:25 by ufalzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/raycasting.h"
#include "../../include/parsing.h"

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

static float	player_angle_from_dir(char dir)
{
	if (dir == 'N')
		return (3 * PI / 2);
	if (dir == 'S')
		return (PI / 2);
	if (dir == 'W')
		return (PI);
	return (0);
}

static void	set_player_from_map(t_game *game)
{
	float	x;
	float	y;
	float	angle;

	x = (game->cub->player_col + 0.5f) * BLOCKSIZE;
	y = (game->cub->player_row + 0.5f) * BLOCKSIZE;
	angle = player_angle_from_dir(game->cub->player_dir);
	init_player(x, y, angle, &game->player);
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
    game->map = game->cub->map;
    set_player_from_map(game);
    game->nb_column = game->cub->map_width;
    game->nb_lines = game->cub->map_height;
    if (game->nb_column <= 0)
        game->nb_column = 1;
    if (game->nb_lines <= 0)
        game->nb_lines = 1;
    game->cub->win = mlx_new_window(game->cub->mlx, WIDHT, HEIGHT, "Cub3D");
    game->cub->img = mlx_new_image(game->cub->mlx, WIDHT, HEIGHT);
    game->data = mlx_get_data_addr(game->cub->img, &game->bpp, &game->size_line, &game->endian);
    mlx_put_image_to_window(game->cub->mlx, game->cub->win, game->cub->img, 0, 0);
}


bool touch(float px, float py, t_game *game)
{
    int x;
    int y;
    int len;
    char cell;

    if (px < 0 || py < 0)
        return true;
    y = py / BLOCKSIZE;
    if (y < 0 || y >= game->cub->map_height)
        return true;
    x = px / BLOCKSIZE;
    if (!game->map || !game->map[y])
        return true;
    len = ft_strlen(game->map[y]);
    if (x < 0 || x >= len)
        return true;
    cell = game->map[y][x];
    if (cell == '1' || cell == ' ')
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
    if (dist < 0.0001f)
        dist = 0.0001f;
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

    // apres 640 increments, on aura parcouru les 60° complets.

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
    mlx_put_image_to_window(game->cub->mlx, game->cub->win, game->cub->img, 0, 0);
}

int close_window(t_game *game)
{
    mlx_destroy_image(game->cub->mlx,game->cub->img);
    mlx_destroy_window(game->cub->mlx,game->cub->win);
    mlx_destroy_display(game->cub->mlx);
    free_cub(game->cub);
    free(game->cub->mlx);
    //tout free
    exit(0);
}

t_cub *init_parsing(int ac, char **av)
{
    int	fd;
    t_cub *vars;

	if (ac != 2)
		return (printf("Error\n"), NULL);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (printf("Error\n"), NULL);
	vars = inits();
	if (!vars)
		return (printf("Error\n"), NULL);
	if (check_errors(fd, vars) == 1)
		return (printf("Error\n"), NULL);
    printf("Tout est bon!");
	return (vars);
}

int print_map(char **av)
{
    int i;
    i = 0;
    int j = 0;
    while (av[i])
    {
        printf("%s\n", av[i]);
        i++;
    }
}

#include <stdio.h>
int main(int ac, char **av)
{
    t_game game;
    t_cub *vars;

    vars = init_parsing(ac, av);
    if (!vars)
        return (1);
    // print_map(vars->map);
    game.cub = vars;
    init_game(&game);
    mlx_hook(game.cub->win, 2, 1L<<0, key_press, &game.player);
    mlx_hook(game.cub->win, 3, 1L<<1, key_release, &game.player);
    mlx_hook(game.cub->win, 17, 0, close_window, &game);
    mlx_loop_hook(game.cub->mlx, draw_loop, &game);
    mlx_loop(game.cub->mlx);
}
