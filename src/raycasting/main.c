/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:15:38 by ufalzone          #+#    #+#             */
/*   Updated: 2025/11/09 17:33:14 by ufalzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/raycasting.h"
#include "../../include/parsing.h"

void	put_pixel(int x, int y, int color, t_game *game)
{
	int	index;

	if (x >= WIDHT || y >= HEIGHT || x < 0 || y < 0)
		return ;
	index = y * game->size_line + x * game->bpp / 8;
	game->data[index] = color & 0xFF;
	game->data[index + 1] = (color >> 8) & 0xFF;
	game->data[index + 2] = (color >> 16) & 0xFF;
}

static void	draw_square(int x, int y, int size, int color, t_game *game)
{
	int	i;

	i = 0;
	while (i < size)
	{
		put_pixel(x + i, y, color, game);
		put_pixel(x, y + i, color, game);
		put_pixel(x + size, y + i, color, game);
		put_pixel(x + i, y + size, color, game);
		i++;
	}
}

static void	draw_map(t_game *game, int origin_x, int origin_y)
{
	int		y;
	int		x;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == '1')
				draw_square(origin_x + x * MINIMAP_BLOCKSIZE,
					origin_y + y * MINIMAP_BLOCKSIZE,
					MINIMAP_BLOCKSIZE, 0xFFFFFF, game);
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

static void	draw_minimap(t_game *game, t_player *player)
{
	int	margin;
	int	origin_x;
	int	origin_y;
	int	mini_px;
	int	mini_py;

	margin = 25;
	origin_x = WIDHT - (game->nb_column * MINIMAP_BLOCKSIZE) - margin;
	origin_y = margin;
	fill_rect(game, origin_x, origin_y,
		game->nb_column * MINIMAP_BLOCKSIZE,
		game->nb_lines * MINIMAP_BLOCKSIZE);
	draw_map(game, origin_x, origin_y);
	mini_px = origin_x + (int)((player->x / BLOCKSIZE) * MINIMAP_BLOCKSIZE);
	mini_py = origin_y + (int)((player->y / BLOCKSIZE) * MINIMAP_BLOCKSIZE);
	draw_square(mini_px - 2, mini_py - 2, 4, 0x00FF, game);
}

static int	get_texture_color(t_texture *tex, int x, int y)
{
	char	*pixel;

	if (!tex->addr || tex->width <= 0 || tex->height <= 0)
		return (0);
	if (x < 0)
		x = 0;
	if (x >= tex->width)
		x = tex->width - 1;
	if (y < 0)
		y = 0;
	if (y >= tex->height)
		y = tex->height - 1;
	pixel = tex->addr + y * tex->line_len + x * (tex->bpp / 8);
	return ((unsigned char)pixel[2] << 16
		| (unsigned char)pixel[1] << 8
		| (unsigned char)pixel[0]);
}

static void	draw_ceiling(t_game *game, int column, int end)
{
	int	y;

	if (end < 0)
		end = 0;
	if (end > HEIGHT)
		end = HEIGHT;
	y = 0;
	while (y < end)
	{
		put_pixel(column, y, game->ceiling_color, game);
		y++;
	}
}

static void	draw_floor(t_game *game, int column, int start)
{
	int	y;

	if (start < 0)
		start = 0;
	if (start >= HEIGHT)
		return ;
	y = start;
	while (y < HEIGHT)
	{
		put_pixel(column, y, game->floor_color, game);
		y++;
	}
}

static void	setup_column(t_column *col, t_ray *ray, t_texture *tex)
{
	col->height = HEIGHT / ray->wall_dist;
	if (col->height < 1)
		col->height = 1;
	col->start = (HEIGHT - col->height) / 2;
	if (col->start < 0)
		col->start = 0;
	col->end = (HEIGHT + col->height) / 2 - 1;
	if (col->end >= HEIGHT)
		col->end = HEIGHT - 1;
	col->tex_x = (int)(ray->wall_x * tex->width);
	if ((ray->side == 0 && ray->dir_x > 0)
		|| (ray->side == 1 && ray->dir_y < 0))
		col->tex_x = tex->width - col->tex_x - 1;
	if (col->tex_x < 0)
		col->tex_x = 0;
	if (col->tex_x >= tex->width)
		col->tex_x = tex->width - 1;
	col->step = (double)tex->height / col->height;
	col->tex_pos = (col->start - HEIGHT / 2 + col->height / 2) * col->step;
}

static void	draw_wall(t_game *game, t_texture *tex, t_column *col, int x)
{
	int	y;
	int	tex_y;

	y = col->start;
	while (y <= col->end)
	{
		tex_y = (int)col->tex_pos;
		if (tex_y >= tex->height)
			tex_y = tex->height - 1;
		put_pixel(x, y, get_texture_color(tex, col->tex_x, tex_y), game);
		col->tex_pos += col->step;
		y++;
	}
}

static void	render_column(t_game *game, double angle, int column)
{
	t_ray		ray;
	t_texture	*tex;
	t_column	col;

	init_ray(&ray, &game->player, angle);
	step_ray(&ray, game);
	resolve_ray(&ray);
	ray.wall_dist *= cos(angle - game->player.angle);
	if (ray.wall_dist <= 0.0)
		ray.wall_dist = 0.0001;
	tex = &game->textures[ray.tex_id];
	setup_column(&col, &ray, tex);
	draw_ceiling(game, column, col.start);
	draw_wall(game, tex, &col, column);
	draw_floor(game, column, col.end + 1);
}

static void	render_frame(t_game *game)
{
	double	angle;
	double	step;
	int		column;

	angle = game->player.angle - (FOV / 2.0);
	step = FOV / WIDHT;
	column = 0;
	while (column < WIDHT)
	{
		render_column(game, angle, column);
		angle += step;
		column++;
	}
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

static void	set_map_data(t_game *game)
{
	game->map = game->cub->map;
	set_player_from_map(game);
	game->nb_column = game->cub->map_width;
	game->nb_lines = game->cub->map_height;
	if (game->nb_column <= 0)
		game->nb_column = 1;
	if (game->nb_lines <= 0)
		game->nb_lines = 1;
}

static void	clean_window(t_game *game)
{
	if (game->cub->img)
	{
		mlx_destroy_image(game->cub->mlx, game->cub->img);
		game->cub->img = NULL;
	}
	if (game->cub->win)
	{
		mlx_destroy_window(game->cub->mlx, game->cub->win);
		game->cub->win = NULL;
	}
}

static int	create_window(t_game *game)
{
	clean_window(game);
	game->cub->win = mlx_new_window(game->cub->mlx, WIDHT, HEIGHT, "Cub3D");
	if (!game->cub->win)
		return (1);
	game->cub->img = mlx_new_image(game->cub->mlx, WIDHT, HEIGHT);
	if (!game->cub->img)
		return (clean_window(game), 1);
	game->data = mlx_get_data_addr(game->cub->img, &game->bpp,
			&game->size_line, &game->endian);
	if (!game->data)
		return (clean_window(game), 1);
	mlx_put_image_to_window(game->cub->mlx, game->cub->win,
		game->cub->img, 0, 0);
	return (0);
}

static void	clear_image(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDHT)
			put_pixel(x++, y, 0, game);
		y++;
	}
}

int	init_game(t_game *game)
{
	set_map_data(game);
	if (load_wall_textures(game) != 0)
		return (1);
	if (init_colors(game) != 0)
		return (destroy_textures(game), 1);
	if (create_window(game) != 0)
		return (destroy_textures(game), 1);
	return (0);
}

bool	touch(float px, float py, t_game *game)
{
	int	x;
	int	y;
	int	len;
	char	cell;

	if (px < 0 || py < 0)
		return (true);
	y = py / BLOCKSIZE;
	if (y < 0 || y >= game->cub->map_height)
		return (true);
	x = px / BLOCKSIZE;
	if (!game->map || !game->map[y])
		return (true);
	len = ft_strlen(game->map[y]);
	if (x < 0 || x >= len)
		return (true);
	cell = game->map[y][x];
	if (cell == '1' || cell == ' ')
		return (true);
	return (false);
}

int	draw_loop(t_game *game)
{
	clear_image(game);
	move_player(&game->player, game);
	render_frame(game);
	draw_minimap(game, &game->player);
	mlx_put_image_to_window(game->cub->mlx, game->cub->win,
		game->cub->img, 0, 0);
	return (0);
}

int	close_window(t_game *game)
{
	destroy_textures(game);
	clean_window(game);
	mlx_destroy_display(game->cub->mlx);
	free_cub(game->cub);
	exit(0);
	return (0);
}

static t_cub	*init_parsing(int ac, char **av)
{
	int		fd;
	t_cub	*vars;

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

int	main(int ac, char **av)
{
	t_game	game;
	t_cub	*vars;

	ft_memset(&game, 0, sizeof(t_game));
	vars = init_parsing(ac, av);
	if (!vars)
		return (1);
	game.cub = vars;
	if (init_game(&game) != 0)
	{
		mlx_destroy_display(game.cub->mlx);
		free_cub(game.cub);
		return (1);
	}
	mlx_hook(game.cub->win, 2, 1L << 0, key_press, &game.player);
	mlx_hook(game.cub->win, 3, 1L << 1, key_release, &game.player);
	mlx_hook(game.cub->win, 17, 0, close_window, &game);
	mlx_loop_hook(game.cub->mlx, draw_loop, &game);
	mlx_loop(game.cub->mlx);
	return (0);
}
