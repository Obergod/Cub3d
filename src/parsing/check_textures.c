/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafioron <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:10:45 by mafioron          #+#    #+#             */
/*   Updated: 2025/07/08 16:10:51 by mafioron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

//	think about how to do textures, linked lists or strncmp
int	check_textures(char **cub, t_vars *vars)
{
	int	 i;
	int	nb_texture;

	nb_texture = 0;
	i = -1;
	vars->textures = cub;
	while (cub[++i])
	{
		if (ft_strncmp(cub[i], "NO ", 3) == 0)
		{
			if (test_images())
		}
		else if (ft_strncmp(cub[i], "SO ", 3) == 0)
			return (1);
		else if (ft_strncmp(cub[i], "WE ", 3) == 0)
			return (1);
		else if (ft_strncmp(cub[i], "EA ", 3) == 0)
			return (1);
		else if (ft_strncmp(cub[i], "F ", 2) == 0)
			return (1);
		else if (ft_strncmp(cub[i], "C ", 2) == 0)
			return (1);
	}
	if (only_textures(cub, vars) == 1)
		return (1);
	if (test_images(vars) == 1)
		return (1);
// Need to check path and if colors are good
	return (0);
}

int	test_images(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (vars->img)
			mlx_destroy_image(vars->mlx, vars->img);
		vars->img = mlx_xpm_file_to_image(vars->mlx, vars->textures[i],
				&vars->height, &vars->width);
		if (vars->img == NULL)
			return (1);
		i++;
	}
	return (0);
}

int	only_textures(char **cub, t_vars *vars)
{
	int	i;

	i = -1;
	while (++i < 6)
	{
		cub[i] = cub[i] + 2;
		while (*cub[i] == ' ')
			cub[i]++;
		if (*cub[i] == '\0')
			return (1);
	}
	vars->textures = cub;
	return (0);
}
