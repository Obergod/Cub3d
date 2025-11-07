/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafioron <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:10:45 by mafioron          #+#    #+#             */
/*   Updated: 2025/11/07 15:58:13 by mafioron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

int	check_textures(char **cub, t_cub *vars)
{
	int	 i;
	int	nb_texture;

	nb_texture = 0;
	i = -1;
	while (cub[++i])
	{
		if (check_double(cub, i) == 1)
			return (1);
		if (!ft_strncmp(cub[i], "NO ", 3) || !ft_strncmp(cub[i], "SO ", 3) || 
				!ft_strncmp(cub[i], "WE ", 3) || !ft_strncmp(cub[i], "EA ", 3))
		{
			if (test_image(vars, cub[i]) == 1)
				return (1);
			nb_texture++;
		}
		else if (!ft_strncmp(cub[i], "F ", 2) || !ft_strncmp(cub[i], "C ", 2))
		{
			if (check_colors(cub[i]) == 1)
				return (1);
			nb_texture++;
		}
	}
	if (nb_texture != 6)
		return (1);
	return (0);
}

int	check_double(char **cub, int i)
{
	int	j;

	j = i + 1;
	while (j < 6)
	{
		if (!ft_strncmp(cub[i], cub[j], 2))
			return (1);
		j++;
	}
	return (0);
}

int	check_colors(char *texture)
{
	int		i;
	char	**color;
	long	rgb;

	i = only_textures(texture);
	if (i == -1)
		return (1);
	color = ft_split(texture + i, ',');
	if (!color)
		return (1);
	i = -1;
	while (color[++i])
	{
		rgb = ft_atol(color[i]);
		if (rgb < 0 || rgb > 255)
			return (1);
	}
	free(color);
	if (i != 3)
		return (1);
	return (0);
}

int	test_image(t_cub *vars, char *texture)
{
	int	i;

	i = only_textures(texture);
	if (i == -1)
		return (1);
	if (vars->img)
		mlx_destroy_image(vars->mlx, vars->img);
	vars->img = mlx_xpm_file_to_image(vars->mlx, texture + i,
			&vars->height, &vars->width);
	if (vars->img == NULL)
		return (1);
	return (0);
}

int	only_textures(char *texture)
{
	int	i;

	i = 2;
	while (texture[i] == ' ')
		i++;
	if (texture[i] == '\0')
		return (-1);
	return (i);
}
