/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 21:18:36 by ufalzone          #+#    #+#             */
/*   Updated: 2025/11/07 21:18:36 by ufalzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/raycasting.h"

static int	load_texture_path(t_game *game, t_texture *tex, char *line)
{
	if (!line || !*line)
		return (1);
	tex->img = mlx_xpm_file_to_image(game->cub->mlx, line,
			&tex->width, &tex->height);
	if (!tex->img)
		return (1);
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp,
			&tex->line_len, &tex->endian);
	if (!tex->addr)
		return (1);
	return (0);
}

void	destroy_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->textures[i].img)
		{
			mlx_destroy_image(game->cub->mlx, game->textures[i].img);
			game->textures[i].img = NULL;
		}
		i++;
	}
}

int	load_wall_textures(t_game *game)
{
	int	i;

	destroy_textures(game);
	i = 0;
	while (i < 4)
	{
		if (!game->cub->textures || !game->cub->textures[i])
			return (destroy_textures(game), 1);
		if (load_texture_path(game, &game->textures[i],
				game->cub->textures[i]) != 0)
			return (destroy_textures(game), 1);
		i++;
	}
	return (0);
}

static int	fill_rgb_array(char **parts, int rgb[3])
{
	int		i;
	long	value;

	i = 0;
	while (parts[i])
	{
		if (i >= 3)
			return (1);
		value = ft_atol(parts[i]);
		if (value < 0 || value > 255)
			return (1);
		rgb[i] = value;
		i++;
	}
	if (i != 3)
		return (1);
	return (0);
}

static int	rgb_from_line(char *line, int *color)
{
	char	**parts;
	int		rgb[3];

	if (!line || !*line)
		return (1);
	parts = ft_split(line, ',');
	if (!parts)
		return (1);
	if (fill_rgb_array(parts, rgb) != 0)
		return (ft_free_split(parts), 1);
	*color = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	ft_free_split(parts);
	return (0);
}

int	init_colors(t_game *game)
{
	if (!game->cub->textures || !game->cub->textures[FLOOR]
		|| !game->cub->textures[CEILING])
		return (1);
	if (rgb_from_line(game->cub->textures[FLOOR], &game->floor_color) != 0)
		return (1);
	if (rgb_from_line(game->cub->textures[CEILING], &game->ceiling_color) != 0)
		return (1);
	return (0);
}
