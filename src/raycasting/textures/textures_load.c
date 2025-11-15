/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_load.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 21:18:36 by ufalzone          #+#    #+#             */
/*   Updated: 2025/11/07 21:18:36 by ufalzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

static int	load_texture_path(t_game *game, t_texture *tex, char *line)
{
	if (!line || !*line)
		return (1);
	tex->img = mlx_xpm_file_to_image(game->cub->mlx, line, &tex->width,
			&tex->height);
	if (!tex->img)
		return (1);
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_len,
			&tex->endian);
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
		{
			destroy_textures(game);
			return (1);
		}
		if (load_texture_path(game, &game->textures[i],
				game->cub->textures[i]) != 0)
		{
			destroy_textures(game);
			return (1);
		}
		i++;
	}
	return (0);
}
