/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafioron <mafioron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 19:24:55 by mafioron          #+#    #+#             */
/*   Updated: 2025/11/10 17:37:56 by mafioron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

void	free_cub(t_cub *cub)
{
	if (!cub)
		return ;
	if (cub->map)
		ft_free_split(cub->map);
	if (cub->textures)
		ft_free_split(cub->textures);
	if (cub->mlx && cub->img)
	{
		mlx_destroy_image(cub->mlx, cub->img);
		cub->img = NULL;
	}
	if (cub->mlx)
		free(cub->mlx);
	free(cub);
}

int	is_texture(char *line)
{
	if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3)
		|| !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3))
		return (1);
	return (0);
}
